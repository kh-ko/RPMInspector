#ifndef QMLDEVPANELMODEL_H
#define QMLDEVPANELMODEL_H

#include <QObject>
#include <QtMath>
#include "source/globaldef/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"
#include "source/qmlmodel/qmlmeasuremodel.h"
#include "qml/control/chart/linechart/linechartdata.h"

class QmlDevPanelModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int    mMeasureState              READ getMeasureState            NOTIFY signalEventChangedMeasureState           )
    Q_PROPERTY(int    mAutoStep                  READ getAutoStep                NOTIFY signalEventChangedAutoStep               )
    Q_PROPERTY(bool   mIsConnect                 READ getIsConnect               NOTIFY signalEventChangedIsConnect              )
    Q_PROPERTY(bool   mIsAlarm                   READ getIsAlarm                 NOTIFY signalEventChangedIsAlarm                )
    Q_PROPERTY(bool   mIsChuckConnect            READ getIsChuckConnect          NOTIFY signalEventChangedIsChuckConnect         )
    Q_PROPERTY(bool   mIsValveOpen               READ getIsValveOpen             NOTIFY signalEventChangedIsValveOpen            )
    Q_PROPERTY(qint32 mCurrRPM                   READ getCurrRPM                 NOTIFY signalEventChangedCurrRPM                )
    Q_PROPERTY(qint64 mAutoMeasureMin            READ getAutoMeasureMin          NOTIFY signalEventChangedAutoMeasureMin         )
    Q_PROPERTY(qint64 mAutoMeasureSec            READ getAutoMeasureSec          NOTIFY signalEventChangedAutoMeasureSec         )
    Q_PROPERTY(int    mGraphStartY               READ getGraphStartY             NOTIFY signalEventChangedGraphStartY            )
    Q_PROPERTY(int    mGraphEndY                 READ getGraphEndY               NOTIFY signalEventChangedGraphEndY              )
    Q_PROPERTY(int    mGraphXRange               READ getGraphXRange             NOTIFY signalEventChangedGraphXRange            )

public:
    int    mAutoStep                = QmlEnumDef::AUTOSTEP_NONE;
    bool   mIsConnect               = false;
    bool   mIsAlarm                 = false;
    bool   mIsChuckConnect          = false;
    bool   mIsValveOpen             = false;
    qint32 mCurrRPM                 = 0;
    int    mVoltage                 = 0;
    qint64 mAutoMeasureTime         = 0;

    int * staticGetGraphStartY(){ static int value = 0     ; return &value; }
    int * staticGetGraphEndY  (){ static int value = 25000 ; return &value; }
    int * staticGetGraphXRange(){ static int value = 100000; return &value; }

    int getMeasureState()
    {
        return mpCurrMesaure == &mNonLoadMeasure ? QmlEnumDef::MEASURE_STATE_NONLOAD : mpCurrMesaure == &mLoadMeasure ? QmlEnumDef::MEASURE_STATE_LOAD : QmlEnumDef::MEASURE_STATE_NONE;
    }
    int    getAutoStep            (){ return mAutoStep;}
    bool   getIsConnect           (){ return mIsConnect     ;}
    bool   getIsAlarm             (){ return mIsAlarm       ;}
    bool   getIsChuckConnect      (){ return mIsChuckConnect;}
    bool   getIsValveOpen         (){ return mIsValveOpen   ;}
    qint32 getCurrRPM             (){ return mCurrRPM       ;}
    qint64 getAutoMeasureMin      (){ return (mAutoMeasureTime/1000) / 60;}
    qint64 getAutoMeasureSec      (){ return (mAutoMeasureTime/1000) % 60;}
    int    getGraphStartY         (){ return *staticGetGraphStartY();}
    int    getGraphEndY           (){ return *staticGetGraphEndY  ();}
    int    getGraphXRange         (){ return *staticGetGraphXRange();}

    void setMeasureState(int value)
    {
        if(value == getMeasureState())
            return;

        qDebug() << "[QmlDevPanelModel][setMeasureState]" << value;

        if(value == QmlEnumDef::MEASURE_STATE_NONLOAD)
            mpCurrMesaure = &mNonLoadMeasure;
        else if(value == QmlEnumDef::MEASURE_STATE_LOAD)
            mpCurrMesaure = &mLoadMeasure;
        else
            mpCurrMesaure = nullptr;

        if(mpCurrMesaure != nullptr)
        {
            mpCurrMesaure->resetMeasure();
            mpCurrMesaure->setIsAuto(getAutoStep() != QmlEnumDef::AUTOSTEP_NONE);
        }

        mNonLoadMeasure.setLimitTime(pLSettingSP->mCurrPDSetting.mNonLoadMeasureTime);
        mLoadMeasure.setLimitTime(pLSettingSP->mCurrPDSetting.mLoadMeasureTime);

        if(getAutoStep() == QmlEnumDef::AUTOSTEP_NONE)
        {
            setAutoMeasureTime(0);
        }
        /*
        if(getAutoStep() != QmlEnumDef::AUTOSTEP_NONE)
        {
            //mNonLoadMeasure.setLimitTime(pLSettingSP->mCurrPDSetting.mNonLoadMeasureTime);
            //mLoadMeasure.setLimitTime(pLSettingSP->mCurrPDSetting.mLoadMeasureTime);
        }
        else
        {
            //mNonLoadMeasure.setLimitTime(std::numeric_limits<qint64>::max());
            //mLoadMeasure.setLimitTime(std::numeric_limits<qint64>::max());
            setAutoMeasureTime(0);
        }*/



        emit signalEventChangedMeasureState(getMeasureState());
    }
    void   setAutoStep               (int    value){ if(mAutoStep                == value) return; mAutoStep       = value; emit signalEventChangedAutoStep      (mAutoStep      );}
    void   setIsConnect              (bool   value){ if(mIsConnect               == value) return; mIsConnect      = value; emit signalEventChangedIsConnect     (mIsConnect     );}
    void   setIsAlarm                (bool   value){ if(mIsAlarm                 == value) return; mIsAlarm        = value; emit signalEventChangedIsAlarm       (mIsAlarm       );}
    void   setIsChuckConnect         (bool   value){ if(mIsChuckConnect          == value) return; mIsChuckConnect = value; emit signalEventChangedIsChuckConnect(mIsChuckConnect);}
    void   setIsValveOpen            (bool   value){ if(mIsValveOpen             == value) return; mIsValveOpen    = value; emit signalEventChangedIsValveOpen   (mIsValveOpen   );}
    void   setCurrRPM                (qint32 value){ if(mCurrRPM                 == value) return; mCurrRPM        = value; emit signalEventChangedCurrRPM       (mCurrRPM       );}
    void   setAutoMeasureTime        (qint64 value){ mAutoMeasureTime = value; emit signalEventChangedAutoMeasureMin(getAutoMeasureMin()); emit signalEventChangedAutoMeasureSec(getAutoMeasureSec());}
    void   setGraphStartY            (int    value){ *(staticGetGraphStartY()) = value; emit signalEventChangedGraphStartY(getGraphStartY());}
    void   setGraphEndY              (int    value){ *(staticGetGraphEndY  ()) = value; emit signalEventChangedGraphEndY  (getGraphEndY  ());}
    void   setGraphXRange            (int    value){ *(staticGetGraphXRange()) = value; emit signalEventChangedGraphXRange(getGraphXRange());}

signals:
    void   signalEventChangedMeasureState           (int    value);
    void   signalEventChangedAutoStep               (int   value);
    void   signalEventChangedIsConnect              (bool   value);
    void   signalEventChangedIsAlarm                (bool   value);
    void   signalEventChangedIsChuckConnect         (bool   value);
    void   signalEventChangedIsValveOpen            (bool   value);
    void   signalEventChangedCurrRPM                (qint32 value);
    void   signalEventChangedAutoMeasureMin         (qint64 value);
    void   signalEventChangedAutoMeasureSec         (qint64 value);
    void   signalEventFinishedMeasure               (qint32 loadRPM, qint32 nonLoadRPM, bool isSucc);
    void   signalEventChangedGraphStartY            (int    value);
    void   signalEventChangedGraphEndY              (int    value);
    void   signalEventChangedGraphXRange            (int    value);

public slots:
    Q_INVOKABLE QmlMeasureModel * onCommandGetNonLoadMeasureModel()
    {
        return &mNonLoadMeasure;
    }
    Q_INVOKABLE QmlMeasureModel * onCommandGetLoadMeasureModel()
    {
        return &mLoadMeasure;
    }
    Q_INVOKABLE QString onCommandConnectChuck()
    {
        qDebug() << "[QmlDevPanelModel][onCommandConnectChuck]";

        if(mIsValveOpen)
            return "AIR 공급을 OFF 해주세요.";

        pDspSP->sendChuckConnect();

        return "";
    }
    Q_INVOKABLE QString onCommandDisconnectChuck()
    {
        qDebug() << "[QmlDevPanelModel][onCommandDisconnectChuck]";

        if(mIsValveOpen)
            return "AIR 공급을 OFF 해주세요.";

        pDspSP->sendChuckDisconnect();

        return "";
    }
    Q_INVOKABLE QString onCommandOpenValve()
    {
        qDebug() << "[QmlDevPanelModel][onCommandOpenValve]";

        if(!mIsChuckConnect)
            return "AIR 공급을 전진 해주세요.";

        pDspSP->sendValveOpen();

        return "";
    }
    Q_INVOKABLE QString onCommandCloseValve()
    {
        qDebug() << "[QmlDevPanelModel][onCommandCloseValve]";

        pDspSP->sendValveClose();

        return "";
    }
    Q_INVOKABLE QString onCommandStartNonLoadInsp()
    {
        qDebug() << "[QmlDevPanelModel][onCommandStartNonLoadInsp]";

        pDspSP->sendVoltage(0);
        setMeasureState(QmlEnumDef::MEASURE_STATE_NONLOAD);

        return "";
    }
    Q_INVOKABLE QString onCommandStopNonLoadInsp()
    {
        qDebug() << "[QmlDevPanelModel][onCommandStopNonLoadInsp]";

        setMeasureState(QmlEnumDef::MEASURE_STATE_NONE);

        return "";
    }
    Q_INVOKABLE QString onCommandStartLoadInsp()
    {
        qDebug() << "[QmlDevPanelModel][onCommandStartLoadInsp]";

        if(pLSettingSP->mMeasureConfig.mIsRtAdjVoltage)
        {
            pDspSP->sendVoltage(pRpmSP->convertBaseVoltageToRpmVoltage(mCurrRPM, pLSettingSP->mCurrPDSetting.mVoltage));
        }
        else
        {
            pDspSP->sendVoltage(pRpmSP->convertBaseVoltageToRpmVoltage(pLSettingSP->mCurrPDSetting.mLoadCondition, pLSettingSP->mCurrPDSetting.mVoltage));
        }

        setMeasureState(QmlEnumDef::MEASURE_STATE_LOAD);

        return "";
    }
    Q_INVOKABLE QString onCommandStopLoadInsp()
    {
        qDebug() << "[QmlDevPanelModel][onCommandStopLoadInsp]";

        pDspSP->sendVoltage(0);
        setMeasureState(QmlEnumDef::MEASURE_STATE_NONE);

        return "";
    }
    Q_INVOKABLE QString onCommandStartAutoInsp()
    {
        qDebug() << "[QmlDevPanelModel][onCommandStartAutoInsp]";

        setAutoStep(QmlEnumDef::AUTOSTEP_READY);
        setMeasureState(QmlEnumDef::MEASURE_STATE_NONE);
        mNonLoadMeasure.resetMeasure();
        mLoadMeasure.resetMeasure();
        setAutoMeasureTime(0);

        delayCall(1000,SLOT(autoValveClose()));

        return "";
    }
    Q_INVOKABLE QString onCommandStopInsp()
    {
        qDebug() << "[QmlDevPanelModel][onCommandStopInsp]";

        setAutoStep(QmlEnumDef::AUTOSTEP_NONE);
        setMeasureState(QmlEnumDef::MEASURE_STATE_NONE);
        delayCallCancel();

        pDspSP->sendValveClose();
        pDspSP->sendVoltage(0);

        return "";
    }

    Q_INVOKABLE void onCommandSetCycleCntGraphModel(LineChartData * pLineChartData)
    {
        mpCycleCntChartData = pLineChartData;
    }

    Q_INVOKABLE void onCommandSetRPMGraphModel(LineChartData * pLineChartData)
    {
        mpRPMChartData = pLineChartData;
    }

    Q_INVOKABLE void onCommandSetGraphEndY(int value)
    {
        setGraphEndY(value);
    }

    Q_INVOKABLE void onCommandSetGraphStartY(int value)
    {
        setGraphStartY(value);
    }

    Q_INVOKABLE void onCommandSetGraphXRange(int value)
    {
        setGraphXRange(value);
    }

    void onTimeTick(QDateTime now)
    {
        static qint64 startTime = 0;

        if(mAutoMeasureTime == 0 && mAutoStep != QmlEnumDef::AUTOSTEP_NONE)
        {
            startTime = now.currentMSecsSinceEpoch();
            mAutoMeasureTime = 1;
        }
        else if(mAutoStep != QmlEnumDef::AUTOSTEP_NONE)
        {
            setAutoMeasureTime(now.currentMSecsSinceEpoch() - startTime);
        }

        if(mpCurrMesaure != nullptr)
        {
            mpCurrMesaure->onTimeTick(now.currentMSecsSinceEpoch());
        }

        if(getAutoStep() != QmlEnumDef::AUTOSTEP_NONE && mpCurrMesaure != nullptr && (mpCurrMesaure->getJudg() == QmlEnumDef::JUDG_STATE_FAIL || mpCurrMesaure->getJudg() == QmlEnumDef::JUDG_STATE_SUCC))
        {
            if(mpCurrMesaure->getJudg() == QmlEnumDef::JUDG_STATE_FAIL || getMeasureState() == QmlEnumDef::MEASURE_STATE_NONLOAD)
            {
                qDebug() << "[QmlDevPanelModel][onTimeTick]measure finish :  measure = " << getMeasureState() << ", judg = " << mpCurrMesaure->getJudg();

                emit signalEventFinishedMeasure(mLoadMeasure.mRPM, mNonLoadMeasure.mRPM, mpCurrMesaure->getJudg() == QmlEnumDef::JUDG_STATE_SUCC);

                autoStopMeasure();
            }
            else if(getMeasureState() == QmlEnumDef::MEASURE_STATE_LOAD)
            {
                autoMeasureNonLoad();
            }
        }
        else if(getAutoStep() == QmlEnumDef::AUTOSTEP_NONE && mpCurrMesaure != nullptr)
        {
            if(mpCurrMesaure->mProgressTime == mpCurrMesaure->mLimitTime)
                onCommandStopInsp();
        }
    }

    void onChangedDspIsConnect(bool value)
    {
        setIsConnect(value);

        if(mIsConnect)
        {
            qDebug() << "[QmlDevPanelModel][onChangedDspIsConnect] connect";

            if(getMeasureState() != QmlEnumDef::MEASURE_STATE_LOAD)
                pDspSP->sendVoltage(0);
        }
    }

    void onChangedDspStatus(qint64 msec, DspStatusDto value)
    {
        setIsChuckConnect(value.mDspStatus.mChuckOn);
        setIsValveOpen(value.mDspStatus.mValveOn);
        mVoltage = value.mDspStatus.mVoltage;

        //qDebug() << "[debug] rpm" << value.mDspStatus.mCurrRPM;

        if(mpCurrMesaure != nullptr)
        {
            mpCurrMesaure->addRPM(msec, value.mDspStatus.mCurrRPM);
        }


        mCurrRPMAvg.addValue(msec, value.mDspStatus.mCurrRPM);
        setCurrRPM(mCurrRPMAvg.mAvg);

        if(getMeasureState() == QmlEnumDef::MEASURE_STATE_LOAD)
        {
            if(pLSettingSP->mMeasureConfig.mIsRtAdjVoltage)
            {
                pDspSP->sendVoltage(pRpmSP->convertBaseVoltageToRpmVoltage(mCurrRPM, pLSettingSP->mCurrPDSetting.mVoltage));
            }
            else
            {
                pDspSP->sendVoltage(pRpmSP->convertBaseVoltageToRpmVoltage(pLSettingSP->mCurrPDSetting.mLoadCondition, pLSettingSP->mCurrPDSetting.mVoltage));
            }
        }

        if(mpRPMChartData != nullptr)
            mpRPMChartData->addValue(msec, mCurrRPM);
    }

    void onChangedSelectPDSetting(PDSettingDto dto)
    {
        mNonLoadMeasure.setCondition(dto.mNonLoadConditionFrom, dto.mNonLoadConditionTo, 0);
        mLoadMeasure.setCondition(dto.mLoadCondition, std::numeric_limits<qint32>::max(), dto.mLoadNM);
    }

    void onChangedMeasureCfg(MeasureConfigDto dto)
    {
        mCurrRPMAvg.mXRange = dto.mMeasureAvgRange;
        mLoadMeasure.setMeasureAvgTime(dto.mMeasureAvgRange);
        mNonLoadMeasure.setMeasureAvgTime(dto.mMeasureAvgRange);
    }

    void onChangedMeasureTimeSetting()
    {
        //mCurrRPMAvg.mXRange = ;
        //mNonLoadMeasure.setAvgRange();
        //mLoadMeasure.setAvgRange();
    }

    void autoValveClose()
    {
        qDebug() << "[QmlDevPanelModel][autoValveClose] call";

        if(getAutoStep() == QmlEnumDef::AUTOSTEP_NONE)
            return;

        if(getIsValveOpen())
        {
            pDspSP->sendValveClose();
            delayCall(pLSettingSP->mMeasureConfig.mValveRunDelayTime,SLOT(autoValveClose()));
            return;
        }

        autoChuckConnect();
    }

    void autoChuckConnect()
    {
        qDebug() << "[QmlDevPanelModel][autoChuckConnect] call";

        if(getAutoStep() == QmlEnumDef::AUTOSTEP_NONE)
            return;

        setAutoStep(QmlEnumDef::AUTOSTEP_CHUCK);

        if(!getIsChuckConnect())
        {
            pDspSP->sendChuckConnect();
            delayCall(pLSettingSP->mMeasureConfig.mChuckRunDelayTime,SLOT(autoChuckConnect()));
            return;
        }

        autoSetVoltage();
    }

    void autoSetVoltage()
    {
        qDebug() << "[QmlDevPanelModel][autoSetVoltage] call";

        if(getAutoStep() == QmlEnumDef::AUTOSTEP_NONE)
            return;

        if(mVoltage == 0)
        {
            if(pLSettingSP->mMeasureConfig.mIsRtAdjVoltage)
            {
                pDspSP->sendVoltage(pRpmSP->convertBaseVoltageToRpmVoltage(mCurrRPM, pLSettingSP->mCurrPDSetting.mVoltage));
            }
            else
            {
                pDspSP->sendVoltage(pRpmSP->convertBaseVoltageToRpmVoltage(pLSettingSP->mCurrPDSetting.mLoadCondition, pLSettingSP->mCurrPDSetting.mVoltage));
            }
            delayCall(pLSettingSP->mMeasureConfig.mVoltageSetDelayTime,SLOT(autoSetVoltage()));
            return;
        }

        autoMeasureLoad();
    }

    void autoMeasureLoad()
    {
        qDebug() << "[QmlDevPanelModel][autoMeasureLoad] call";

        if(getAutoStep() == QmlEnumDef::AUTOSTEP_NONE)
            return;

        setAutoStep(QmlEnumDef::AUTOSTEP_AIR);

        if(!getIsValveOpen())
        {
            pDspSP->sendValveOpen();
            delayCall(pLSettingSP->mMeasureConfig.mValveRunDelayTime,SLOT(autoMeasureLoad()));
            return;
        }

        setAutoStep(QmlEnumDef::AUTOSTEP_LOAD);
        setMeasureState(QmlEnumDef::MEASURE_STATE_LOAD);
    }

    void autoMeasureNonLoad()
    {
        qDebug() << "[QmlDevPanelModel][autoMeasureNonLoad] call";

        if(getAutoStep() == QmlEnumDef::AUTOSTEP_NONE)
            return;

        setMeasureState(QmlEnumDef::MEASURE_STATE_NONE);

        if(mVoltage != 0)
        {
            pDspSP->sendVoltage(0);
            delayCall(pLSettingSP->mMeasureConfig.mVoltageSetDelayTime,SLOT(autoMeasureNonLoad()));
            return;
        }

        setAutoStep(QmlEnumDef::AUTOSTEP_NONLOAD);
        setMeasureState(QmlEnumDef::MEASURE_STATE_NONLOAD);
    }

    void autoStopMeasure()
    {
        qDebug() << "[QmlDevPanelModel][autoStopMeasure] call";

        setMeasureState(QmlEnumDef::MEASURE_STATE_NONE);

        if(getAutoStep() == QmlEnumDef::AUTOSTEP_NONE)
            return;

        setAutoStep(QmlEnumDef::AUTOSTEP_AIR);

        if(getIsValveOpen() || mVoltage != 0)
        {
            pDspSP->sendValveClose();
            pDspSP->sendVoltage(0);

            delayCall(pLSettingSP->mMeasureConfig.mValveRunDelayTime,SLOT(autoStopMeasure()));
            return;
        }
        autoChuckDisconnect();
    }

    void autoChuckDisconnect()
    {
        qDebug() << "[QmlDevPanelModel][autoChuckDisconnect] call";

        if(getAutoStep() == QmlEnumDef::AUTOSTEP_NONE)
            return;

        setAutoStep(QmlEnumDef::AUTOSTEP_CHUCK);

        if(getIsChuckConnect())
        {
            pDspSP->sendChuckDisconnect();
            delayCall(pLSettingSP->mMeasureConfig.mChuckRunDelayTime,SLOT(autoChuckDisconnect()));
            return;
        }

        onCommandStopInsp();
    }

public:
    explicit QmlDevPanelModel(QObject *parent = nullptr): QObject(parent)
    {
        pCoreService->start();

        ENABLE_SLOT_LSETTING_CHANGED_SEL_PDSETTING;
        ENABLE_SLOT_DSP_CHANGED_IS_CONNECT;
        ENABLE_SLOT_DSP_CHANGED_STATUS    ;
        ENABLE_SLOT_TIMER_TICK;
        ENABLE_SLOT_LSETTING_CHANGED_MEASURE_CFG;

        pDspSP->connectDSP(pLSettingSP->mCommInfo.mIp, pLSettingSP->mCommInfo.mPort);

        onChangedSelectPDSetting(pLSettingSP->mCurrPDSetting);
        onChangedMeasureCfg(pLSettingSP->mMeasureConfig);
    }
    ~QmlDevPanelModel(){}

private:
    QTimer          * mpTimer = nullptr;
    MathMVAvg         mCurrRPMAvg;
    QmlMeasureModel * mpCurrMesaure = nullptr;
    QmlMeasureModel   mNonLoadMeasure;
    QmlMeasureModel   mLoadMeasure;

    LineChartData * mpCycleCntChartData = nullptr;
    LineChartData * mpRPMChartData = nullptr;

    void delayCall(int delayTime, const char * slotFunc)
    {
        delayCallCancel();

        mpTimer = new QTimer(this);
        mpTimer->setSingleShot(true);
        connect(mpTimer, SIGNAL(timeout()), this, slotFunc);
        mpTimer->start(delayTime);
    }

    void delayCallCancel()
    {
        if(mpTimer != nullptr)
        {
            disconnect(mpTimer, nullptr, nullptr, nullptr);
            mpTimer->stop();
            mpTimer->deleteLater();
            mpTimer = nullptr;
        }
    }

};
#endif // DEVPANELMODEL_H
