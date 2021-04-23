#ifndef MATHCOUNTMVAVG_H
#define MATHCOUNTMVAVG_H

#include<QObject>
#include<QDebug>
#include <QtMath>

class MVCountItem
{
public:
    qint64  mX;
    quint32 mY;

    MVCountItem(){}
    MVCountItem(const MVCountItem& copy) :
        mX(copy.mX),
        mY(copy.mY){}
    ~MVCountItem(){}

    MVCountItem& operator=(const MVCountItem& other)
    {
        mX = other.mX;
        mY = other.mY;

        return *this;
    }

};

Q_DECLARE_METATYPE(MVCountItem);

class MathCountMVAvg{

public:
    qint64  mXRange      = 1000;
    quint32 mAvg         = 0;
    QList<MVCountItem> mXList;

    void clear()
    {
        //mXRange      = 0;
        mAvg         = 0;
        mXList.clear();
    }

    void addValue(qint64 x, quint32 value)
    {
        int listSize  = mXList.size();

        for(int i = 0; i < listSize; i ++)
        {
            if((mXList[0].mX + mXRange) < x)
            {
                mXList.removeAt(0);
            }
            else
            {
                break;
            }
        }

        MVCountItem item;

        item.mX = x;
        item.mY = value;

        mXList.append(item);

        if(mXList.size() < 2)
            return;

        double dMsec =  (mXList[mXList.size() - 1].mX - mXList[0].mX);
        double totalCycle = (mXList[mXList.size() - 1].mY - mXList[0].mY);

        if(totalCycle < 0)
        {
            totalCycle = (mXList[mXList.size() - 1].mY + (0xFFFFFFFF - mXList[0].mY));
        }

        mAvg= qRound((totalCycle / dMsec) * (double)60000);
    }
};

#endif // MATHRPMMVAVG_H
