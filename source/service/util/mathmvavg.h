#ifndef MATHMVAVG_H
#define MATHMVAVG_H

#include<QObject>
#include<QDebug>
#include <QtMath>

class MVAvgItem
{
public:
    qint64  mX;
    quint32 mY;

    MVAvgItem(){}
    MVAvgItem(const MVAvgItem& copy) :
        mX(copy.mX),
        mY(copy.mY){}
    ~MVAvgItem(){}

    MVAvgItem& operator=(const MVAvgItem& other)
    {
        mX = other.mX;
        mY = other.mY;

        return *this;
    }

};

Q_DECLARE_METATYPE(MVAvgItem);

class MathMVAvg{

public:
    qint64  mXRange      = 1000;
    quint32 mAvg         = 0;
    QList<MVAvgItem> mXList;
    qint64  mTotalValue  = 0;

    void clear()
    {
        mTotalValue  = 0;
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
                mTotalValue = mTotalValue - mXList[0].mY;
                mXList.removeAt(0);
            }
            else
            {
                break;
            }
        }

        MVAvgItem item;

        item.mX = x;
        item.mY = value;

        mXList.append(item);
        mTotalValue = mTotalValue + value;

        mAvg =  mTotalValue / mXList.size();
    }
};

#endif // MATHMVAVG_H
