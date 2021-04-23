#ifndef DSPSPROVIDER_H
#define DSPSPROVIDER_H
#include <QObject>
#include <QDateTime>
#include <QTimer>
#include "source/service/def/filedef.h"
#include "source/service/util/exceptionutil.h"
#include "source/service/util/filefolderreader.h"
#include "source/service/util/filereaderex.h"
#include "source/service/util/filewriterex.h"
#include "source/service/dsp/dspasyncworker.h"
#include "source/service/dto/enum/enumdef.h"

#define pDspSP DspSProvider::getInstance()

class DspSProvider : public QObject
{
    Q_OBJECT

public :

    static DspSProvider * getInstance()
    {
        static DspSProvider *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new DspSProvider();
        }

        return mpSelf;
    }

    explicit DspSProvider(QObject *parent = nullptr):QObject(parent)
    {

    }
    ~DspSProvider()
    {
        stop();
    }

    void start()
    {
        qDebug() << "[DspSProvider::start]";

        mIsRunning = true;

        mpASyncWorkerThread = new QThread;
        mpASyncWorker       = new DspASyncWorker;
        mpASyncWorker->moveToThread(mpASyncWorkerThread);
        mpASyncWorkerThread->start();

        connect(mpASyncWorkerThread, &QThread::finished, mpASyncWorker, &QObject::deleteLater);
        connect(this         , SIGNAL(signalCommandConnect(QString, quint16)        ), mpASyncWorker, SLOT(onCommandConnect(QString, quint16)   ));
        connect(this         , SIGNAL(signalCommandSendVoltage(int)                 ), mpASyncWorker, SLOT(onCommandSendVoltage(int)            ));
        connect(this         , SIGNAL(signalCommandSendChuckConnect()               ), mpASyncWorker, SLOT(onCommandSendChuckConnect()          ));
        connect(this         , SIGNAL(signalCommandSendChuckDisconnect()            ), mpASyncWorker, SLOT(onCommandSendChuckDisconnect()       ));
        connect(this         , SIGNAL(signalCommandSendValveOpen()                  ), mpASyncWorker, SLOT(onCommandSendValveOpen()             ));
        connect(this         , SIGNAL(signalCommandSendValveClose()                 ), mpASyncWorker, SLOT(onCommandSendValveClose()            ));
        connect(this         , SIGNAL(signalCommandSendCmd(DspCmdDto)               ), mpASyncWorker, SLOT(onCommandSendCmd(DspCmdDto)          ));
        connect(mpASyncWorker, SIGNAL(signalEventChangedIsConnect(bool)             ), this         , SLOT(onChangedIsConnect(bool)             ));
        connect(mpASyncWorker, SIGNAL(signalEventChangedStatus(qint64, DspStatusDto)), this         , SLOT(onChangedStatus(qint64, DspStatusDto)));

        qDebug() << "[DspSProvider::started]";

        emit signalEventStarted();
    }

    void stop()
    {
        mIsRunning = false;

        if(mpASyncWorker != nullptr)
        {
            disconnect(this         , SIGNAL(signalCommandConnect(QString, quint16)        ), mpASyncWorker, SLOT(onCommandConnect(QString, quint16)   ));
            disconnect(this         , SIGNAL(signalCommandSendVoltage(int)                 ), mpASyncWorker, SLOT(onCommandSendVoltage(int)            ));
            disconnect(this         , SIGNAL(signalCommandSendChuckConnect()               ), mpASyncWorker, SLOT(onCommandSendChuckConnect()          ));
            disconnect(this         , SIGNAL(signalCommandSendChuckDisconnect()            ), mpASyncWorker, SLOT(onCommandSendChuckDisconnect()       ));
            disconnect(this         , SIGNAL(signalCommandSendValveOpen()                  ), mpASyncWorker, SLOT(onCommandSendValveOpen()             ));
            disconnect(this         , SIGNAL(signalCommandSendValveClose()                 ), mpASyncWorker, SLOT(onCommandSendValveClose()            ));
            disconnect(this         , SIGNAL(signalCommandSendCmd(DspCmdDto)               ), mpASyncWorker, SLOT(onCommandSendCmd(DspCmdDto)          ));
            disconnect(mpASyncWorker, SIGNAL(signalEventChangedIsConnect(bool)             ), this         , SLOT(onChangedIsConnect(bool)             ));
            disconnect(mpASyncWorker, SIGNAL(signalEventChangedStatus(qint64, DspStatusDto)), this         , SLOT(onChangedStatus(qint64, DspStatusDto)));

            mpASyncWorker= nullptr;
         }

        if(mpASyncWorkerThread != nullptr)
        {
            if(mpASyncWorkerThread->isRunning())
            {
                mpASyncWorkerThread->quit();
                mpASyncWorkerThread->wait();
            }

            mpASyncWorkerThread->deleteLater();

            mpASyncWorkerThread = nullptr;
        }

        emit signalEventStopped();
    }

    bool isConnect()
    {
        if(mIsRunning == false)
            return false;

        return mpASyncWorker->mIsConnect;
    }

    void connectDSP(QString ip, quint16 port)
    {
        emit signalCommandConnect(ip, port);
    }

    void sendChuckConnect()
    {
        emit signalCommandSendChuckConnect();
    }

    void sendChuckDisconnect()
    {
        emit signalCommandSendChuckDisconnect();
    }

    void sendValveOpen()
    {
        emit signalCommandSendValveOpen();
    }

    void sendValveClose()
    {
        emit signalCommandSendValveClose();
    }

    void sendVoltage(int value)
    {
        if(value > 50000)
        {
            qDebug() << "[DspSProvider][sendVoltage]too big voltage : " << value;
            value = 25000;
        }
        emit signalCommandSendVoltage(value);
    }

    void sendCmd(DspCmdDto value)
    {
        emit signalCommandSendCmd(value);
    }

signals:
    void signalEventStarted                         ();
    void signalEventStopped                         ();
    void signalEventChangedIsConnect                (bool          value);
    void signalEventChangedStatus                   (qint64 msec, DspStatusDto  value);

    void signalCommandConnect(QString ip, quint16 port);
    void signalCommandSendChuckConnect();
    void signalCommandSendChuckDisconnect();
    void signalCommandSendValveOpen();
    void signalCommandSendValveClose();
    void signalCommandSendVoltage(int);
    void signalCommandSendCmd(DspCmdDto);

public slots:
    void onChangedIsConnect(bool value)
    {
        emit signalEventChangedIsConnect(value);
    }

    void onChangedStatus(qint64 msec, DspStatusDto value)
    {
        CHECK_FALSE_RETURN(mIsRunning)

        emit signalEventChangedStatus(msec, value);
    }

private :

    bool                 mIsRunning = false;
    QThread            * mpASyncWorkerThread = nullptr;
    DspASyncWorker     * mpASyncWorker       = nullptr;
};
#endif // DSPSPROVIDER_H
