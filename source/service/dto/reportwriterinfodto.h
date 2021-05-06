#ifndef REPORTWRITERINFODTO_H
#define REPORTWRITERINFODTO_H
#include <QObject>
class ReportWriterInfoDto
{
public:
    QString mSaveDate = "";
    QString mWriter = "";
    int     mYear   = 0 ;
    int     mMonth  = 0 ;
    int     mDay    = 0 ;

    ReportWriterInfoDto(){}
    ReportWriterInfoDto(const ReportWriterInfoDto& copy) :
        mSaveDate  (copy.mSaveDate),
        mWriter    (copy.mWriter),
        mYear      (copy.mYear  ),
        mMonth     (copy.mMonth ),
        mDay       (copy.mDay   ){}

    ~ReportWriterInfoDto(){}

    ReportWriterInfoDto& operator=(const ReportWriterInfoDto& other)
    {
        mSaveDate   = other.mSaveDate ;
        mWriter     = other.mWriter   ;
        mYear       = other.mYear     ;
        mMonth      = other.mMonth    ;
        mDay        = other.mDay      ;

        return *this;
    }
};
Q_DECLARE_METATYPE(ReportWriterInfoDto);

#endif // REPORTWRITERINFODTO_H
