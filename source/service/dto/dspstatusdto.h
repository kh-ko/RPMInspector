#ifndef DSPSTATUSDTO_H
#define DSPSTATUSDTO_H

#include <QObject>
#include "source/service/dsp/packet/dsppacketstruct.h"
class DspStatusDto
{
public:
    StDspStatus mDspStatus;

    DspStatusDto(){}
    DspStatusDto(const DspStatusDto& copy){
        memcpy(&mDspStatus, &copy.mDspStatus, sizeof(StDspStatus));
    }

    ~DspStatusDto(){}

    DspStatusDto& operator=(const DspStatusDto& other)
    {
        memcpy(&mDspStatus, &other.mDspStatus, sizeof(StDspStatus));

        return *this;
    }
    void setValue(StDspStatus * pStatus)
    {
        memcpy(&mDspStatus, pStatus, sizeof(StDspStatus));
    }

};
Q_DECLARE_METATYPE(DspStatusDto);
#endif // DSPSTATUSDTO_H
