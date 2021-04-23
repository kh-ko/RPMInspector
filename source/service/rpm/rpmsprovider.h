#ifndef RPMSPROVIDER_H
#define RPMSPROVIDER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDir>

#include "QXlsx/header/xlsxdocument.h"
#include "QXlsx/header/xlsxchartsheet.h"
#include "QXlsx/header/xlsxcellrange.h"
#include "QXlsx/header/xlsxchart.h"
#include "QXlsx/header/xlsxrichstring.h"
#include "QXlsx/header/xlsxworkbook.h"

#include "source/service/def/filedef.h"
#include "source/service/includesvcdto.h"

using namespace QXlsx;

#define pRpmSP RPMSProvider::getInstance()

class RPMSProvider : public QObject
{
    Q_OBJECT

public:
    QList<RPMTableDto> mRPMTable;

    static RPMSProvider * getInstance()
    {
        static RPMSProvider *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new RPMSProvider();
        }

        return mpSelf;
    }


    explicit RPMSProvider(QObject * parent = nullptr):QObject(parent)
    {
    }
    ~RPMSProvider()
    {

    }

    void start()
    {
        qDebug() << "[RPMSProvider::start]";

        loadRPMTable();

        mIsRunning = true;
        emit signalEventStarted();
    }

    void stop()
    {
        mIsRunning = false;
        emit signalEventStopped();
    }

    void loadRPMTable()
    {
        qDebug() << "[RPMSProvider::loadRPMTable]";

        mRPMTable.clear();

        QXlsx::Document report(QString("%1/%2").arg(FileDef::RPM_DIR()).arg(FileDef::RPM_FILENAME()));

        if(report.load() == false)
        {
            qDebug() << "[RPMSProvider::loadRPMTable]" << FileDef::RPM_FILENAME() << "load failed";
            return;
        }

        RPMTableDto table;

        table.mRPM = 10000;

        for(int volIdx = 3; volIdx < 1000000; volIdx++)
        {
            QString strMv = report.read(volIdx,1).toString();
            QString strNM = report.read(volIdx,2).toString();
            double mv = strMv.toDouble();
            double nm = strNM.toDouble();

            if(strMv== "" || strNM == "" || mv == 0 || nm == 0)
            {
                qDebug() << "[debug]invalid value mv[" << strMv << "]nm[" << strMv << "]";
                break;
            }

            table.append(nm, mv);
        }

        mRPMTable.append(table);
    }

    int convertBaseVoltage(int nm, double nmGain){
        int retVoltage;
        nm = qCeil((double)nm * nmGain);

        if(mRPMTable.size() < 1)
        {
            qDebug() << "[debug] empty rpm table !";
            return 0;
        }
        QList<double>rpmList;
        QList<double>volList;

        retVoltage = InterpolationUtil::monotonicCubicHermiteSpline(nm, mRPMTable[0].mNMList, mRPMTable[0].mVoltageList);

        return retVoltage;
    }

    int convertBaseVoltageToRpmVoltage(int rpm, int voltage)
    {
        int retVoltage;

        double voltageBase = 10.55721 + (2.79265 * 0.0001) * 10000; // 0.3nm
        double voltageTarget = 10.55721 + (2.79265 * 0.0001) * (double)rpm; // 0.3nm

        retVoltage = qCeil((double)voltage * (voltageTarget/ voltageBase));

        return retVoltage;
    }

    int convertVoltage(int rpm, int nm, double nmGain)
    {
        int retVoltage;
        nm = qCeil((double)nm * nmGain);

        if(mRPMTable.size() < 1)
        {
            qDebug() << "[debug] empty rpm table !";
            return 0;
        }
        QList<double>rpmList;
        QList<double>volList;

        int selectVoltage = InterpolationUtil::monotonicCubicHermiteSpline(nm, mRPMTable[0].mNMList, mRPMTable[0].mVoltageList);

        double voltageBase = 10.55721 + (2.79265 * 0.0001) * 10000; // 0.3nm
        double voltageTarget = 10.55721 + (2.79265 * 0.0001) * (double)rpm; // 0.3nm

        retVoltage = qCeil((double)selectVoltage * (voltageTarget/ voltageBase));

        return retVoltage;
    }
    /*
    void loadRPMTable()
    {
        qDebug() << "[RPMSProvider::loadRPMTable]";

        mRPMTable.clear();

        QXlsx::Document report(QString("%1/%2").arg(FileDef::RPM_DIR()).arg(FileDef::RPM_FILENAME()));

        if(report.load() == false)
        {
            qDebug() << "[RPMSProvider::loadRPMTable]" << FileDef::RPM_FILENAME() << "load failed";
            return;
        }

        for(int rpmIdx = 1; rpmIdx < 1000000; rpmIdx += 3)
        {
            RPMTableDto table;

            QString rpmString = report.read(1, rpmIdx + 1).toString();
            int     ratedRPM  = rpmString.toInt();

            if(rpmString == "" || ratedRPM == 0)
                break;

            table.mRPM = ratedRPM;

            for(int volIdx = 3; volIdx < 1000000; volIdx++)
            {
                QString strMv = report.read(volIdx,rpmIdx).toString();
                QString strNM = report.read(volIdx,rpmIdx+1).toString();
                double mv = strMv.toDouble();
                double nm = strNM.toDouble();

                if(strMv== "" || strNM == "" || mv == 0 || nm == 0)
                {
                    qDebug() << "[debug]invalid value mv[" << strMv << "]nm[" << strMv << "]";
                    break;
                }

                table.append(nm, mv);
            }

            mRPMTable.append(table);
        }
    }

    int convertVoltage(int rpm, int nm)
    {
        int retVoltage;

        QList<double>rpmList;
        QList<double>volList;

        foreach(RPMTableDto rpmTable, mRPMTable)
        {
            rpmList.append(rpmTable.mRPM);
            volList.append(InterpolationUtil::monotonicCubicHermiteSpline(nm, rpmTable.mNMList, rpmTable.mVoltageList));
        }

        retVoltage = InterpolationUtil::monotonicCubicHermiteSpline(rpm, rpmList, volList);

        return retVoltage;
    }*/

private:
    bool mIsRunning  = false;

signals:
    void signalEventStarted        ();
    void signalEventStopped        ();

};
#endif // RPMSPROVIDER_H
