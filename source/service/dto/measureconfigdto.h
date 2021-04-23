#ifndef MEASURECONFIGDTO_H
#define MEASURECONFIGDTO_H
#include <QObject>

class MeasureConfigDto
{
public:
    qint64 mChuckRunDelayTime       = 0;
    qint64 mValveRunDelayTime       = 0;
    qint64 mVoltageSetDelayTime     = 0;
    qint64 mNonLoadMeasureDelayTime = 0;
    qint64 mLoadMeasureDelayTime    = 0;
    qint64 mMeasureAvgRange         = 0;
    double mKgfcmGain               = 1;
    bool   mIsRtAdjVoltage          = false;

    MeasureConfigDto(){}
    MeasureConfigDto(const MeasureConfigDto& copy) :
        mChuckRunDelayTime      (copy.mChuckRunDelayTime      ),
        mValveRunDelayTime      (copy.mValveRunDelayTime      ),
        mVoltageSetDelayTime    (copy.mVoltageSetDelayTime    ),
        mNonLoadMeasureDelayTime(copy.mNonLoadMeasureDelayTime),
        mLoadMeasureDelayTime   (copy.mLoadMeasureDelayTime   ),
        mMeasureAvgRange        (copy.mMeasureAvgRange        ),
        mKgfcmGain              (copy.mKgfcmGain              ),
        mIsRtAdjVoltage         (copy.mIsRtAdjVoltage         ){}

    ~MeasureConfigDto(){}

    MeasureConfigDto& operator=(const MeasureConfigDto& other)
    {
        mChuckRunDelayTime       = other.mChuckRunDelayTime      ;
        mValveRunDelayTime       = other.mValveRunDelayTime      ;
        mVoltageSetDelayTime     = other.mVoltageSetDelayTime    ;
        mNonLoadMeasureDelayTime = other.mNonLoadMeasureDelayTime;
        mLoadMeasureDelayTime    = other.mLoadMeasureDelayTime   ;
        mMeasureAvgRange         = other.mMeasureAvgRange        ;
        mKgfcmGain               = other.mKgfcmGain              ;
        mIsRtAdjVoltage          = other.mIsRtAdjVoltage         ;

        return *this;
    }
};
Q_DECLARE_METATYPE(MeasureConfigDto);
#endif // MEASURECONFIGDTO_H
