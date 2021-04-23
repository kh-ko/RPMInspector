#ifndef QMLMEASUREMODEL_H
#define QMLMEASUREMODEL_H

#include <QObject>
#include <QtMath>
#include "source/globaldef/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"
#include "source/service/util/mathcountmvavg.h"
#include "source/service/util/mathmvavg.h"

class QmlMeasureModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qint32  mRPM              READ getRPM              NOTIFY signalEventChangedRPM          )
    Q_PROPERTY(int     mJudg             READ getJudg             NOTIFY signalEventChangedJudg         )
    Q_PROPERTY(qint64  mProgressTime     READ getProgressTime     NOTIFY signalEventChangedProgressTime )
    Q_PROPERTY(qint64  mProgressMin      READ getProgressMin      NOTIFY signalEventChangedProgressMin  )
    Q_PROPERTY(qint64  mProgressSec      READ getProgressSec      NOTIFY signalEventChangedProgressSec  )
    Q_PROPERTY(qint32  mConditionFrom    READ getConditionFrom    NOTIFY signalEventChangedConditionFrom)
    Q_PROPERTY(qint32  mConditionTo      READ getConditionTo      NOTIFY signalEventChangedConditionTo  )
    Q_PROPERTY(qint64  mLimitTime        READ getLimitTime        NOTIFY signalEventChangedLimitTime    )
    Q_PROPERTY(qint32  mNM               READ getNM               NOTIFY signalEventChangedNM           )

public:
    qint32  mRPM           = 0;
    int     mJudg          = QmlEnumDef::JUDG_STATE_NONE;
    qint64  mProgressTime  = 0;
    qint32  mConditionFrom = 0;
    qint32  mConditionTo   = std::numeric_limits<qint32>::max();;
    qint64  mLimitTime     = std::numeric_limits<qint64>::max();
    qint32  mNM            = 0;

    qint32  getRPM          (){ return mRPM          ; }
    int     getJudg         (){ return mJudg         ; }
    qint64  getProgressTime (){ return mProgressTime ; }
    qint64  getProgressMin  (){ return (mProgressTime / 1000)/60;};
    qint64  getProgressSec  (){ return (mProgressTime / 1000)%60;};
    qint32  getConditionFrom(){ return mConditionFrom; }
    qint32  getConditionTo  (){ return mConditionTo  ; }
    qint64  getLimitTime    (){ return mLimitTime    ; }
    qint32  getNM           (){ return mNM           ; }

    void    setRPM          (qint32 value){if(mRPM           == value) return; mRPM           = value; emit signalEventChangedRPM          (mRPM          );}
    void    setJudg         (int    value){if(mJudg          == value) return; mJudg          = value; emit signalEventChangedJudg         (mJudg         );}
    void    setProgressTime (qint64 value){if(mProgressTime  == value) return; mProgressTime  = value; emit signalEventChangedProgressTime (mProgressTime ); emit signalEventChangedProgressMin(getProgressMin()); emit signalEventChangedProgressSec(getProgressSec());}
    void    setConditionFrom(qint32 value){if(mConditionFrom == value) return; mConditionFrom = value; emit signalEventChangedConditionFrom(mConditionFrom);}
    void    setConditionTo  (qint32 value){if(mConditionTo   == value) return; mConditionTo   = value; emit signalEventChangedConditionTo  (mConditionTo  );}
    void    setLimitTime    (qint64 value){if(mLimitTime     == value) return; mLimitTime     = value; emit signalEventChangedLimitTime    (mLimitTime    );}
    void    setNM           (qint32 value){if(mNM            == value) return; mNM            = value; emit signalEventChangedNM           (mNM           );}

signals:
    void    signalEventChangedRPM          (qint32 value);
    void    signalEventChangedJudg         (int    value);
    void    signalEventChangedProgressTime (qint64 value);
    void    signalEventChangedProgressMin  (qint64 value);
    void    signalEventChangedProgressSec  (qint64 value);
    void    signalEventChangedConditionFrom(qint32 value);
    void    signalEventChangedConditionTo  (qint32 value);
    void    signalEventChangedLimitTime    (qint64 value);
    void    signalEventChangedNM           (qint32 value);


public:
    void resetMeasure()
    {
        setJudg(QmlEnumDef::JUDG_STATE_NONE);
        mRPMAvg.clear();
        setRPM(mRPMAvg.mAvg);
        setProgressTime(0);
    }

    void setIsAuto(bool value)
    {
        mIsAuto = value;
    }

    void setCondition(qint64 from, qint64 to, qint32 nm)
    {
        setConditionFrom(from);
        setConditionTo(to);
        setNM(nm);
    }

    void setMeasureAvgTime(qint64 msec)
    {
        mRPMAvg.mXRange = msec;
    }

    void addRPM(qint64 msec, quint32 rpm)
    {
        if(mLimitTime > mProgressTime)
        {
            mRPMAvg.addValue(msec, rpm);
            setRPM(mRPMAvg.mAvg);
        }
    }

    void onTimeTick(qint64 nowMSec)
    {
        static qint64 startTime = 0;

        if(mProgressTime == 0)
        {
            startTime = nowMSec;
            mProgressTime = 1;
        }
        else if((nowMSec - startTime) >= mLimitTime)
        {
            setProgressTime(mLimitTime);

            if(mIsAuto == false)
            {
                return;
            }

            if(mRPM >= mConditionFrom && mRPM <= mConditionTo)
            {
                setJudg(QmlEnumDef::JUDG_STATE_SUCC);
            }
            else
            {
                setJudg(QmlEnumDef::JUDG_STATE_FAIL);
            }
        }
        else
        {
            setProgressTime(nowMSec - startTime);
        }
    }

    explicit QmlMeasureModel(QObject *parent = nullptr): QObject(parent)
    {

    }
    ~QmlMeasureModel(){}

private:
    MathMVAvg         mRPMAvg;
    bool              mIsAuto = false;
};
#endif // QMLMEASUREMODEL_H
