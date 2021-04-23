#ifndef COMMINFODTO_H
#define COMMINFODTO_H

#include <QObject>
class CommInfoDto
{
public:
    QString mIp      ;
    int     mPort    ;

    CommInfoDto(){}
    CommInfoDto(const CommInfoDto& copy) :
        mIp    (copy.mIp    ),
        mPort  (copy.mPort  ){}
    ~CommInfoDto(){}

    CommInfoDto& operator=(const CommInfoDto& other)
    {
        mIp     = other.mIp    ;
        mPort   = other.mPort  ;

        return *this;
    }

};
Q_DECLARE_METATYPE(CommInfoDto);

#endif // COMMINFODTO_H
