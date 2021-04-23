#ifndef LINECHARTDATA_H
#define LINECHARTDATA_H

#include <QObject>

class LineChartData : public QObject
{
    Q_OBJECT
public :
    Q_PROPERTY(int     mLastIdx     READ getLastIdx    NOTIFY signalEventChangedLastIdx   )

    QList<int> mXValueList;
    QList<int> mYValueList;

    int     mLastIdx    = -1;

    int     getLastIdx   (){ return mLastIdx   ;}
    void    setLastIdx   (int     value){ if(value == mLastIdx   ) return; mLastIdx    = value; emit signalEventChangedLastIdx   (mLastIdx   );}

public:
    explicit LineChartData(QObject *parent = nullptr): QObject(parent)
    {

    }
    ~LineChartData(){}

    void addValue(int xValue, int yValue)
    {
        mXValueList.append(xValue);
        mYValueList.append(yValue);

        setLastIdx(mXValueList.size() - 1);
    }

    void addValue(QList<int> xValueList, QList<int> yValueList)
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

    Q_INVOKABLE int onCommandGetYValue(int idx)
    {
        if(idx > mYValueList.size() - 1)
            return 0;

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

#endif // LINECHARTDATA_H
