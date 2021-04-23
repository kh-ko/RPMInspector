#ifndef PDSETTINGDTO_H
#define PDSETTINGDTO_H
#include <QObject>
#include "source/service/dsp/packet/dsppacketstruct.h"
#include "source/service/util/interpolationutil.h"

class PDSettingDto
{
public:
    QString mModel                  ;
    QString mPDNum                  ;
    QString mPDName                 ;
    qint64  mNonLoadMeasureTime     ;
    qint64  mLoadMeasureTime        ;
    int     mNonLoadConditionFrom   ;
    int     mNonLoadConditionTo     ;
    int     mLoadCondition          ;
    int     mRatedRPM               ;
    int     mLoadNM                 ;
    int     mVoltage                ;

    PDSettingDto(){}
    PDSettingDto(const PDSettingDto& copy) :
        mModel                  (copy.mModel                  ),
        mPDNum                  (copy.mPDNum                  ),
        mPDName                 (copy.mPDName                 ),
        mNonLoadMeasureTime     (copy.mNonLoadMeasureTime     ),
        mLoadMeasureTime        (copy.mLoadMeasureTime        ),
        mNonLoadConditionFrom   (copy.mNonLoadConditionFrom   ),
        mNonLoadConditionTo     (copy.mNonLoadConditionTo     ),
        mLoadCondition          (copy.mLoadCondition          ),
        mRatedRPM               (copy.mRatedRPM               ),
        mLoadNM                 (copy.mLoadNM                 ),
        mVoltage                (copy.mVoltage                ){}

    ~PDSettingDto(){}

    PDSettingDto& operator=(const PDSettingDto& other)
    {
        mModel                   = other.mModel                  ;
        mPDNum                   = other.mPDNum                  ;
        mPDName                  = other.mPDName                 ;
        mNonLoadMeasureTime      = other.mNonLoadMeasureTime     ;
        mLoadMeasureTime         = other.mLoadMeasureTime        ;
        mNonLoadConditionFrom    = other.mNonLoadConditionFrom   ;
        mNonLoadConditionTo      = other.mNonLoadConditionTo     ;
        mLoadCondition           = other.mLoadCondition          ;
        mRatedRPM                = other.mRatedRPM               ;
        mLoadNM                  = other.mLoadNM                 ;
        mVoltage                 = other.mVoltage                ;

        return *this;
    }
};
Q_DECLARE_METATYPE(PDSettingDto);
#endif // PDSETTINGDTO_H
