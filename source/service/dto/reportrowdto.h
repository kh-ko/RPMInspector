#ifndef REPORTROWDTO_H
#define REPORTROWDTO_H
#include <QObject>
class ReportRowDto
{
public:
    bool    mCheck   = false;
    QString mSeqNum  ;
    QString mPDSeqNum;
    QString mLoadRPM ;
    QString mNonRPM  ;
    QString mJudg    ;

    ReportRowDto(){}
    ReportRowDto(const ReportRowDto& copy) :
        mCheck   (copy.mCheck   ),
        mSeqNum  (copy.mSeqNum  ),
        mPDSeqNum(copy.mPDSeqNum),
        mLoadRPM (copy.mLoadRPM ),
        mNonRPM  (copy.mNonRPM  ),
        mJudg    (copy.mJudg    ){}

    ~ReportRowDto(){}

    ReportRowDto& operator=(const ReportRowDto& other)
    {
        mCheck    = other.mCheck   ;
        mSeqNum   = other.mSeqNum  ;
        mPDSeqNum = other.mPDSeqNum;
        mLoadRPM  = other.mLoadRPM ;
        mNonRPM   = other.mNonRPM  ;
        mJudg     = other.mJudg    ;

        return *this;
    }
};
Q_DECLARE_METATYPE(ReportRowDto);
#endif // REPORTROWDTO_H
