#ifndef LOGLINECHARTDATA_H
#define LOGLINECHARTDATA_H

#include <QObject>
#include <QDebug>

class LogLineChartData : public QObject
{
    Q_OBJECT
public :
    Q_PROPERTY(int     mLastIdx     READ getLastIdx    NOTIFY signalEventChangedLastIdx   )

    QList<int>    mXValueList;
    QList<double> mYValueList;

    int     mLastIdx    = -1;

    int     getLastIdx   (){ return mLastIdx   ;}
    void    setLastIdx   (int     value){ if(value == mLastIdx   ) return; mLastIdx    = value; emit signalEventChangedLastIdx   (mLastIdx   );}

public:
    explicit LogLineChartData(QObject *parent = nullptr): QObject(parent)
    {

    }
    ~LogLineChartData(){}

    void addValue(int xValue, double yValue)
    {
        qDebug() << "[debug] [addValue]yValue = " << yValue;

        mXValueList.append(xValue);
        mYValueList.append(yValue);

        setLastIdx(mXValueList.size() - 1);
    }

    void addValue(QList<int> xValueList, QList<double> yValueList)
    {
        mXValueList.append(xValueList);
        mYValueList.append(yValueList);

        setLastIdx(mXValueList.size() - 1);
    }

signals:
    void signalEventChangedLastIdx   (int     value);

public slots:
    Q_INVOKABLE int onCommandGetXValue(int idx)
    {
        if(idx > mXValueList.size() - 1)
            return 0;

        return mXValueList[idx];
    }

    Q_INVOKABLE double onCommandGetYValue(int idx)
    {
        if(idx > mYValueList.size() - 1)
            return 0;

        qDebug() << "[debug] [onCommandGetYValue]yValue = " << mYValueList[idx];

        return mYValueList[idx];
    }

    Q_INVOKABLE int onCommandGetNearMinIdx(int xValue)
    {
        for(int i = mXValueList.size() - 1; i > -1; i--)
        {
            if(xValue > mXValueList[i])
                return i;
        }

        return 0;
    }

};

#endif // LOGLINECHARTDATA_H
