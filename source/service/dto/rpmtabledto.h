#ifndef RPMTABLEDTO_H
#define RPMTABLEDTO_H
#include <QObject>
#include <QtMath>

class RPMTableDto
{
public:
    int           mRPM;
    QList<double> mNMList;
    QList<double> mVoltageList;

    RPMTableDto(){}
    RPMTableDto(const RPMTableDto& copy) :
        mRPM        (copy.mRPM        ),
        mNMList     (copy.mNMList     ),
        mVoltageList(copy.mVoltageList){}

    ~RPMTableDto(){}

    RPMTableDto& operator=(const RPMTableDto& other)
    {
        mRPM         = other.mRPM        ;
        mNMList      = other.mNMList     ;
        mVoltageList = other.mVoltageList;

        return *this;
    }

    void append(double nm, double mv)
    {
        mVoltageList.append(mv);
        mNMList.append(nm);
    }
};
Q_DECLARE_METATYPE(RPMTableDto);
#endif // RPMTABLEDTO_H
