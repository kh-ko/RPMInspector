#ifndef QMLPDSETTINGDLGMODEL_H
#define QMLPDSETTINGDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/globaldef/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"
#include "qml/control/chart/linechart/linechartdata.h"

class QmlPDSettingDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mOldPDNum             READ getOldPDNum              NOTIFY signalEventChangedOldPDNum            )
    Q_PROPERTY(QString mModel                READ getModel                 NOTIFY signalEventChangedModel               )
    Q_PROPERTY(QString mPDNum                READ getPDNum                 NOTIFY signalEventChangedPDNum               )
    Q_PROPERTY(QString mPDName               READ getPDName                NOTIFY signalEventChangedPDName              )
    Q_PROPERTY(qint64  mNonLoadMeasureTime   READ getNonLoadMeasureTime    NOTIFY signalEventChangedNonLoadMeasureTime  )
    Q_PROPERTY(qint64  mLoadMeasureTime      READ getLoadMeasureTime       NOTIFY signalEventChangedLoadMeasureTime     )
    Q_PROPERTY(int     mLoadNM               READ getLoadNM                NOTIFY signalEventChangedLoadNM              )
    Q_PROPERTY(int     mNonLoadConditionFrom READ getNonLoadConditionFrom  NOTIFY signalEventChangedNonLoadConditionFrom)
    Q_PROPERTY(int     mNonLoadConditionTo   READ getNonLoadConditionTo    NOTIFY signalEventChangedNonLoadConditionTo  )
    Q_PROPERTY(int     mLoadCondition        READ getLoadCondition         NOTIFY signalEventChangedLoadCondition       )
    Q_PROPERTY(int     mRatedRPM             READ getRatedRPM              NOTIFY signalEventChangedRatedRPM            )

    Q_PROPERTY(int     mNMMax                READ getNMMax                 NOTIFY signalEventChangedNMMax               )
    Q_PROPERTY(int     mVolMax               READ getVolMax                NOTIFY signalEventChangedVolMax              )

public:
    QString mOldPDNum            ;
    QString mModel               ;
    QString mPDNum               ;
    QString mPDName              ;
    qint64  mNonLoadMeasureTime  ;
    qint64  mLoadMeasureTime     ;
    int     mLoadNM              ;
    int     mNonLoadConditionFrom;
    int     mNonLoadConditionTo  ;
    int     mLoadCondition       ;
    int     mRatedRPM            ;

    int     mNMMax               ;
    int     mVolMax              ;

    QString getOldPDNum            (){ return mOldPDNum            ;}
    QString getModel               (){ return mModel               ;}
    QString getPDNum               (){ return mPDNum               ;}
    QString getPDName              (){ return mPDName              ;}
    qint64  getNonLoadMeasureTime  (){ return mNonLoadMeasureTime  ;}
    qint64  getLoadMeasureTime     (){ return mLoadMeasureTime     ;}
    int     getLoadNM              (){ return mLoadNM              ;}
    int     getNonLoadConditionFrom(){ return mNonLoadConditionFrom;}
    int     getNonLoadConditionTo  (){ return mNonLoadConditionTo  ;}
    int     getLoadCondition       (){ return mLoadCondition       ;}
    int     getRatedRPM            (){ return mRatedRPM            ;}
    int     getNMMax               (){ return mNMMax               ;}
    int     getVolMax              (){ return mVolMax              ;}

    void    setOldPDNum            (QString value){ if(mOldPDNum             == value) return; mOldPDNum             = value; emit signalEventChangedOldPDNum            (mOldPDNum            );}
    void    setModel               (QString value){ if(mModel                == value) return; mModel                = value; emit signalEventChangedModel               (mModel               );}
    void    setPDNum               (QString value){ if(mPDNum                == value) return; mPDNum                = value; emit signalEventChangedPDNum               (mPDNum               );}
    void    setPDName              (QString value){ if(mPDName               == value) return; mPDName               = value; emit signalEventChangedPDName              (mPDName              );}
    void    setNonLoadMeasureTime  (qint64  value){ if(mNonLoadMeasureTime   == value) return; mNonLoadMeasureTime   = value; emit signalEventChangedNonLoadMeasureTime  (mNonLoadMeasureTime  );}
    void    setLoadMeasureTime     (qint64  value){ if(mLoadMeasureTime      == value) return; mLoadMeasureTime      = value; emit signalEventChangedLoadMeasureTime     (mLoadMeasureTime     );}
    void    setLoadNM              (int     value){ if(mLoadNM               == value) return; mLoadNM               = value; emit signalEventChangedLoadNM              (mLoadNM              );}
    void    setNonLoadConditionFrom(int     value){ if(mNonLoadConditionFrom == value) return; mNonLoadConditionFrom = value; emit signalEventChangedNonLoadConditionFrom(mNonLoadConditionFrom);}
    void    setNonLoadConditionTo  (int     value){ if(mNonLoadConditionTo   == value) return; mNonLoadConditionTo   = value; emit signalEventChangedNonLoadConditionTo  (mNonLoadConditionTo  );}
    void    setLoadCondition       (int     value){ if(mLoadCondition        == value) return; mLoadCondition        = value; emit signalEventChangedLoadCondition       (mLoadCondition       );}
    void    setRatedRPM            (int     value){ if(mRatedRPM             == value) return; mRatedRPM             = value; emit signalEventChangedRatedRPM            (mRatedRPM            );}
    void    setNMMax               (int     value){ if(mNMMax                == value) return; mNMMax                = value; emit signalEventChangedNMMax               (mNMMax               );}
    void    setVolMax              (int     value){ if(mVolMax               == value) return; mVolMax               = value; emit signalEventChangedVolMax              (mVolMax              );}

signals:
    void signalEventChangedOldPDNum            (QString value);
    void signalEventChangedModel               (QString value);
    void signalEventChangedPDNum               (QString value);
    void signalEventChangedPDName              (QString value);
    void signalEventChangedNonLoadMeasureTime  (qint64  value);
    void signalEventChangedLoadMeasureTime     (qint64  value);
    void signalEventChangedLoadNM              (int     value);
    void signalEventChangedNonLoadConditionFrom(int     value);
    void signalEventChangedNonLoadConditionTo  (int     value);
    void signalEventChangedLoadCondition       (int     value);
    void signalEventChangedRatedRPM            (int     value);
    void signalEventChangedNMMax               (int     value);
    void signalEventChangedVolMax              (int     value);

public slots:
    Q_INVOKABLE void onCommandSetOldPDNum            (QString value){setOldPDNum            (value);}
    Q_INVOKABLE void onCommandSetModel               (QString value){setModel               (value);}
    Q_INVOKABLE void onCommandSetPDNum               (QString value){setPDNum               (value);}
    Q_INVOKABLE void onCommandSetPDName              (QString value){setPDName              (value);}
    Q_INVOKABLE void onCommandSetNonLoadMeasureTime  (qint64  value){setNonLoadMeasureTime  (value);}
    Q_INVOKABLE void onCommandSetLoadMeasureTime     (qint64  value){setLoadMeasureTime     (value);}
    Q_INVOKABLE void onCommandSetLoadNM              (int     value){setLoadNM              (value);}
    Q_INVOKABLE void onCommandSetNonLoadConditionFrom(int     value){setNonLoadConditionFrom(value);}
    Q_INVOKABLE void onCommandSetNonLoadConditionTo  (int     value){setNonLoadConditionTo  (value);}
    Q_INVOKABLE void onCommandSetLoadCondition       (int     value){setLoadCondition       (value);}
    Q_INVOKABLE void onCommandSetRatedRPM            (int     value){setRatedRPM            (value);}

    Q_INVOKABLE QString onCommandApply()
    {
        PDSettingDto setting;

        setting.mModel                = mModel               ;
        setting.mPDNum                = mPDNum               ;
        setting.mPDName               = mPDName              ;
        setting.mNonLoadMeasureTime   = mNonLoadMeasureTime  ;
        setting.mLoadMeasureTime      = mLoadMeasureTime     ;
        setting.mLoadNM               = mLoadNM              ;
        setting.mNonLoadConditionFrom = mNonLoadConditionFrom;
        setting.mNonLoadConditionTo   = mNonLoadConditionTo  ;
        setting.mLoadCondition        = mLoadCondition       ;
        setting.mRatedRPM             = mRatedRPM            ;

        if(mOldPDNum == "")
        {
            QString ret = pLSettingSP->addPDSetting(setting);
            if(ret != "")
                return ret;

             return pLSettingSP->selectPDSetting(mPDNum);
        }
        else
        {
            return pLSettingSP->editPDSetting(mOldPDNum, setting);
        }
    }

    Q_INVOKABLE void onCommandLoadPDSetting(QString pdNum)
    {
        mOldPDNum = pdNum;

        if(mOldPDNum != "")
        {
            foreach(PDSettingDto setting ,pLSettingSP->mPDSettingList)
            {
                if(mOldPDNum == setting.mPDNum)
                {
                    setModel               (setting.mModel               );
                    setPDNum               (setting.mPDNum               );
                    setPDName              (setting.mPDName              );
                    setNonLoadMeasureTime  (setting.mNonLoadMeasureTime  );
                    setLoadMeasureTime     (setting.mLoadMeasureTime     );
                    setLoadNM              (setting.mLoadNM              );
                    setNonLoadConditionFrom(setting.mNonLoadConditionFrom);
                    setNonLoadConditionTo  (setting.mNonLoadConditionTo  );
                    setLoadCondition       (setting.mLoadCondition       );
                    setRatedRPM            (setting.mRatedRPM            );

                    break;
                }
            }
        }
        else
        {
            setModel               (pLSettingSP->mDefaultPDModel             );
            setPDNum               ("0000000"                                );
            setPDName              ("-"                                      );
            setNonLoadMeasureTime  (pLSettingSP->mDefaultNonLoadMeasureTime  );
            setLoadMeasureTime     (pLSettingSP->mDefaultLoadMeasureTime     );
            setLoadNM              (pLSettingSP->mDefaultLoadNM              );
            setNonLoadConditionFrom(pLSettingSP->mDefaultNonLoadConditionFrom);
            setNonLoadConditionTo  (pLSettingSP->mDefaultNonLoadConditionTo  );
            setLoadCondition       (pLSettingSP->mDefaultLoadCondition       );
            setRatedRPM            (pLSettingSP->mDefaultRatedRPM            );
        }
    }

    Q_INVOKABLE void onCommandSetNMGraphModel(LineChartData * pNMChartModel)
    {
       int startNM = pRpmSP->mRPMTable[0].mNMList[0];
       int maxNM = pRpmSP->mRPMTable[0].mNMList[pRpmSP->mRPMTable[0].mNMList.size() - 1];
       int lastVol = 0;

       for(int i = 0; startNM + (i * 100) <= maxNM; i ++ )
       {
            lastVol = pRpmSP->convertVoltage( mLoadCondition, startNM + (i * 100), pLSettingSP->mMeasureConfig.mKgfcmGain);
            pNMChartModel->addValue(lastVol, startNM + (i * 100));

            qDebug() << "[debug]gain = " << pLSettingSP->mMeasureConfig.mKgfcmGain <<", kgfcm = " << startNM + (i * 100) <<", voltage = " << lastVol;
       }

       setNMMax(maxNM);
       setVolMax(lastVol);
    }

public:
    explicit QmlPDSettingDlgModel(QObject *parent = nullptr): QObject(parent)
    {
    }
    ~QmlPDSettingDlgModel(){}

};

#endif // QMLPDSETTINGDLGMODEL_H
