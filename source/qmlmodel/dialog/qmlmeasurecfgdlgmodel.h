#ifndef QMLMEASURECFGDLGMODEL_H
#define QMLMEASURECFGDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/globaldef/qmlenumdef.h"
#include "source/service/coreservice.h"

class QmlMeasureCfgDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint64 mChuckRunDelayTime         READ getChuckRunDelayTime          NOTIFY signalEventChangedChuckRunDelayTime      )
    Q_PROPERTY(qint64 mValveRunDelayTime         READ getValveRunDelayTime          NOTIFY signalEventChangedValveRunDelayTime      )
    Q_PROPERTY(qint64 mVoltageSetDelayTime       READ getVoltageSetDelayTime        NOTIFY signalEventChangedVoltageSetDelayTime    )
    Q_PROPERTY(qint64 mNonLoadMeasureDelayTime   READ getNonLoadMeasureDelayTime    NOTIFY signalEventChangedNonLoadMeasureDelayTime)
    Q_PROPERTY(qint64 mLoadMeasureDelayTime      READ getLoadMeasureDelayTime       NOTIFY signalEventChangedLoadMeasureDelayTime   )
    Q_PROPERTY(qint64 mMeasureAvgRange           READ getMeasureAvgRange            NOTIFY signalEventChangedMeasureAvgRange        )
    Q_PROPERTY(double mKgfcmGain                 READ getKgfcmGain                  NOTIFY signalEventChangedKgfcmGain              )
    Q_PROPERTY(bool   mIsRtAdjVoltage            READ getIsRtAdjVoltage             NOTIFY signalEventChangedIsRtAdjVoltage         )

public:
    qint64 mChuckRunDelayTime      ;
    qint64 mValveRunDelayTime      ;
    qint64 mVoltageSetDelayTime    ;
    qint64 mNonLoadMeasureDelayTime;
    qint64 mLoadMeasureDelayTime   ;
    qint64 mMeasureAvgRange        ;
    double mKgfcmGain              ;
    bool   mIsRtAdjVoltage         ;

    qint64 getChuckRunDelayTime      (){ return mChuckRunDelayTime      ;}
    qint64 getValveRunDelayTime      (){ return mValveRunDelayTime      ;}
    qint64 getVoltageSetDelayTime    (){ return mVoltageSetDelayTime    ;}
    qint64 getNonLoadMeasureDelayTime(){ return mNonLoadMeasureDelayTime;}
    qint64 getLoadMeasureDelayTime   (){ return mLoadMeasureDelayTime   ;}
    qint64 getMeasureAvgRange        (){ return mMeasureAvgRange        ;}
    double getKgfcmGain              (){ return mKgfcmGain              ;}
    bool   getIsRtAdjVoltage         (){ return mIsRtAdjVoltage         ;}

    void   setChuckRunDelayTime      (qint64 value){ if(mChuckRunDelayTime       == value) return; mChuckRunDelayTime       = value; emit signalEventChangedChuckRunDelayTime      (mChuckRunDelayTime      );}
    void   setValveRunDelayTime      (qint64 value){ if(mValveRunDelayTime       == value) return; mValveRunDelayTime       = value; emit signalEventChangedValveRunDelayTime      (mValveRunDelayTime      );}
    void   setVoltageSetDelayTime    (qint64 value){ if(mVoltageSetDelayTime     == value) return; mVoltageSetDelayTime     = value; emit signalEventChangedVoltageSetDelayTime    (mVoltageSetDelayTime    );}
    void   setNonLoadMeasureDelayTime(qint64 value){ if(mNonLoadMeasureDelayTime == value) return; mNonLoadMeasureDelayTime = value; emit signalEventChangedNonLoadMeasureDelayTime(mNonLoadMeasureDelayTime);}
    void   setLoadMeasureDelayTime   (qint64 value){ if(mLoadMeasureDelayTime    == value) return; mLoadMeasureDelayTime    = value; emit signalEventChangedLoadMeasureDelayTime   (mLoadMeasureDelayTime   );}
    void   setMeasureAvgRange        (qint64 value){ if(mMeasureAvgRange         == value) return; mMeasureAvgRange         = value; emit signalEventChangedMeasureAvgRange        (mMeasureAvgRange        );}
    void   setKgfcmGain              (double value){ if(mKgfcmGain               == value) return; mKgfcmGain               = value; emit signalEventChangedKgfcmGain              (mKgfcmGain              );}
    void   setIsRtAdjVoltage         (bool   value){ if(mIsRtAdjVoltage          == value) return; mIsRtAdjVoltage          = value; emit signalEventChangedIsRtAdjVoltage         (mIsRtAdjVoltage         );}
signals:
    void signalEventChangedChuckRunDelayTime      (qint64 value);
    void signalEventChangedValveRunDelayTime      (qint64 value);
    void signalEventChangedVoltageSetDelayTime    (qint64 value);
    void signalEventChangedNonLoadMeasureDelayTime(qint64 value);
    void signalEventChangedLoadMeasureDelayTime   (qint64 value);
    void signalEventChangedMeasureAvgRange        (qint64 value);
    void signalEventChangedKgfcmGain              (double value);
    void signalEventChangedIsRtAdjVoltage         (bool   value);

public slots:
    Q_INVOKABLE void onCommandSetChuckRunDelayTime      (qint64 value){ setChuckRunDelayTime      (value); }
    Q_INVOKABLE void onCommandSetValveRunDelayTime      (qint64 value){ setValveRunDelayTime      (value); }
    Q_INVOKABLE void onCommandSetVoltageSetDelayTime    (qint64 value){ setVoltageSetDelayTime    (value); }
    Q_INVOKABLE void onCommandSetNonLoadMeasureDelayTime(qint64 value){ setNonLoadMeasureDelayTime(value); }
    Q_INVOKABLE void onCommandSetLoadMeasureDelayTime   (qint64 value){ setLoadMeasureDelayTime   (value); }
    Q_INVOKABLE void onCommandSetMeasureAvgRange        (qint64 value){ setMeasureAvgRange        (value); }
    Q_INVOKABLE void onCommandSetKgfcmGain              (double value){ setKgfcmGain              (value); }
    Q_INVOKABLE void onCommandSetIsRtAdjVoltage         (bool   value){ setIsRtAdjVoltage         (value); }

    Q_INVOKABLE void onCommandApply()
    {
        MeasureConfigDto config;

        config.mChuckRunDelayTime       = mChuckRunDelayTime      ;
        config.mValveRunDelayTime       = mValveRunDelayTime      ;
        config.mVoltageSetDelayTime     = mVoltageSetDelayTime    ;
        config.mNonLoadMeasureDelayTime = mNonLoadMeasureDelayTime;
        config.mLoadMeasureDelayTime    = mLoadMeasureDelayTime   ;
        config.mMeasureAvgRange         = mMeasureAvgRange        ;
        config.mKgfcmGain               = mKgfcmGain              ;
        config.mIsRtAdjVoltage          = mIsRtAdjVoltage         ;

        pLSettingSP->setMeasureConfig(config);
    }

public:
    explicit QmlMeasureCfgDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        setChuckRunDelayTime       (pLSettingSP->mMeasureConfig.mChuckRunDelayTime      );
        setValveRunDelayTime       (pLSettingSP->mMeasureConfig.mValveRunDelayTime      );
        setVoltageSetDelayTime     (pLSettingSP->mMeasureConfig.mVoltageSetDelayTime    );
        setNonLoadMeasureDelayTime (pLSettingSP->mMeasureConfig.mNonLoadMeasureDelayTime);
        setLoadMeasureDelayTime    (pLSettingSP->mMeasureConfig.mLoadMeasureDelayTime   );
        setMeasureAvgRange         (pLSettingSP->mMeasureConfig.mMeasureAvgRange        );
        setKgfcmGain               (pLSettingSP->mMeasureConfig.mKgfcmGain              );
        setIsRtAdjVoltage          (pLSettingSP->mMeasureConfig.mIsRtAdjVoltage         );
    }

    ~QmlMeasureCfgDlgModel(){}

};

#endif // QMLMEASURECFGDLGMODEL_H
