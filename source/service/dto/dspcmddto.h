#ifndef DSPCMDDTO_H
#define DSPCMDDTO_H

#include <QObject>
#include "source/service/dsp/packet/dsppacketstruct.h"
class DspCmdDto
{
public:
    StDspCommand mDspCmd;

    DspCmdDto(){}
    DspCmdDto(const DspCmdDto& copy){
        memcpy(&mDspCmd, &copy.mDspCmd, sizeof(StDspCommand));
    }

    ~DspCmdDto(){}

    DspCmdDto& operator=(const DspCmdDto& other)
    {
        memcpy(&mDspCmd, &other.mDspCmd, sizeof(StDspStatus));

        return *this;
    }
    void setValue(StDspStatus * pStatus)
    {
        memcpy(&mDspCmd, pStatus, sizeof(StDspStatus));
    }

};
Q_DECLARE_METATYPE(DspCmdDto);
#endif // DSPCMDDTO_H
