#ifndef CORESERVICE_H
#define CORESERVICE_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QDateTime>


#include "source/service/localsetting/localsettingsprovider.h"
#include "source/service/report/reportsprovider.h"
#include "source/service/dsp/dspsprovider.h"
#include "source/service/timer/timersprovider.h"
#include "source/service/rpm/rpmsprovider.h"
#include "source/service/util/sproviderconnectutil.h"

#define pCoreService CoreService::getInstance()

class CoreService : public QObject
{
    Q_OBJECT
public:
    static CoreService * getInstance()
    {
        static CoreService *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new CoreService();
        }

        return mpSelf;
    }

public:
    bool                        mIsRunning = false;

    void start()
    {
        QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));

        pRpmSP->start();
        pLSettingSP->start();
        pReportSP->start();
        pDspSP->start();
        pTimerSP->start();

        mIsRunning = true;

        emit signalEventStarted();
    }
    void stop()
    {
        mIsRunning = false;

        pRpmSP->stop();
        pTimerSP->stop();
        pDspSP->stop();
        pReportSP->stop();
        pLSettingSP->stop();

        emit signalEventStopped();
    }

signals:
    void signalEventStarted();
    void signalEventStopped();

public:
    explicit CoreService(QObject *parent = nullptr):QObject(parent)
    {
    }
    ~CoreService()
    {
        stop();
    }

};

#endif // CORESERVICE_H
