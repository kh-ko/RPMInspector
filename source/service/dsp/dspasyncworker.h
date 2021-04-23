#ifndef DSPASYNCWORKER_H
#define DSPASYNCWORKER_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QThread>
#include <QDateTime>
#include <QUdpSocket>

#include "source/globaldef/qmlenumdef.h"
#include "source/service/dsp/packet/dsppacketstruct.h"
#include "source/service/dsp/packet/dsppacket.h"
#include "source/service/dto/dspstatusdto.h"
#include "source/service/dto/dspcmddto.h"

class DspASyncWorker : public QObject
{
    Q_OBJECT
public:
    enum eError {
        DSP_ERR_NONE = 0,
        DSP_ERR_OPEN = 1,
        DSP_ERR_RCV_TIMEOUT = 2,
        DSP_ERR_SND_TIMEOUT = 3,
        DSP_ERR_RCV_INVALID_VALUE = 4
    };

    QTimer      * mpTimer          = nullptr;
    QUdpSocket  * mpSock           = nullptr;
    QString       mIp             ;
    QHostAddress  mHostAddr       ;
    quint16       mPort           ;

    bool          mIsConnect       = false;
    qint64        mMonitoringCycle = 100;
    qint64        mSendTimeout     = 100;
    qint64        mRcvTimeout      = 1000;
    quint16       mTransactionID   = 0;

    explicit DspASyncWorker(QObject *parent = nullptr):QObject(parent)
    {

    }
    ~DspASyncWorker()
    {
        if(mpTimer != nullptr)
        {
            mpTimer->stop();
            mpTimer->deleteLater();
            mpTimer = nullptr;
        }
    }

signals:
    void signalEventChangedIsConnect(bool value);
    void signalEventChangedStatus(qint64, DspStatusDto value);

public slots:
    void onCommandConnect(QString ip, quint16 port)
    {
        qDebug() << "[debug]onCommandConnect : ip = " << ip << ", port = " << port;
        connectDsp(ip, port);
    }

    void onCommandSendChuckConnect()
    {
        unsigned short value = 1;
        sendCmd(DSP_COMMANDBLOCK_STARTADDR_CHUCK_ON, (char *)&value, 2);

        qDebug() << "[debug]onCommandSendChuckConnect";
    }

    void onCommandSendChuckDisconnect()
    {
        unsigned short value = 0;
        sendCmd(DSP_COMMANDBLOCK_STARTADDR_CHUCK_ON, (char *)&value, 2);

        qDebug() << "[debug]onCommandSendChuckDisconnect";
    }

    void onCommandSendValveOpen()
    {
        unsigned short value = 1;
        sendCmd(DSP_COMMANDBLOCK_STARTADDR_VALVE_ON, (char *)&value, 2);

        qDebug() << "[debug]onCommandSendValveOpen";
    }

    void onCommandSendValveClose()
    {
        unsigned short value = 0;
        sendCmd(DSP_COMMANDBLOCK_STARTADDR_VALVE_ON, (char *)&value, 2);

        qDebug() << "[debug]onCommandSendValveClose";
    }

    void onCommandSendVoltage(int value)
    {
        sendCmd(DSP_COMMANDBLOCK_STARTADDR_VOLTAGE, (char *)&value, 4);

        qDebug() << "[debug]onCommandSendVoltage :" << value;
    }

    void onCommandSendCmd(DspCmdDto dto)
    {
        sendCmd(DSP_COMMANDBLOCK_STARTADDR_CHUCK_ON, (char *)&(dto.mDspCmd), sizeof(StDspCommand));

        qDebug() << "[debug]onCommandSendCmd";
    }


    void onTimeout()
    {
        if(mpSock == nullptr)
        {
            connectDsp(mIp, mPort);
        }

        sendReadStatus();
    }

private:
    void connectDsp(QString ip, quint16 port)
    {
        disconnectDsp();

        if(mpTimer == nullptr)
        {
            mpTimer = new QTimer;
            mpTimer->setInterval(mMonitoringCycle);
            connect(mpTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

            mpTimer->start();
        }
        mIp = ip;
        mPort = port;
        mHostAddr.setAddress(ip);
        mpSock = new QUdpSocket();
        mpSock->connectToHost(mHostAddr, port);

        qDebug() << "[debug]connectDsp : ip =" << ip << ",port = "<< port;

        if(mpSock->localAddress().toString().contains("0.0.0.0"))
        {
            qDebug() << "[debug]connectDsp : ip is zero";

            disconnectDsp();
            return;
        }
    }

    void disconnectDsp()
    {
        setIsConnect(false);

        if(mpSock != nullptr)
        {
            if(mpSock->isOpen())
                mpSock->close();

            mpSock->deleteLater();

            mpSock = nullptr;
        }
    }

    void sendCmd(unsigned short addr, char * value, int len){

        if(mpSock == nullptr) return;

        mTransactionID++;

        QString dummy = mpSock->readAll().toHex();

        if(dummy.length() > 0)
            qDebug() << "[debug] sendCmd read all : " << dummy;

        DspPacket packet;
        packet.setFuncCode(DSP_FUNCCODE_MULTIBLOCK_WRITE);
        packet.addWriteBlock(DSP_GROUP_ID_COMMAND, addr, len/2, value);
        packet.setTransactionID(mTransactionID);

        QByteArray frameBuffer = packet.createSendBuffer();
        //qDebug() << "[debug]cmd send hex : " << frameBuffer.toHex();

        for(int i = 0; i < 3 ; i ++)
        {
            if (i > 0)
                qDebug() << "[debug]sendCmd retry : " << i;

            qint64 bytesWritten = mpSock->writeDatagram(frameBuffer, mHostAddr, mPort);

            //qDebug() << "[debug][net][sendCmd] "<<frameBuffer.toHex();

            //qDebug() << "[debug]sendCmd : ip =" << mHostAddr.toString() << ",port = "<< mPort;

            if (bytesWritten == -1) {
                    qDebug() << "[debug]sendCmd error : bytesWritten == -1 ";
                    break;
            }
            else if(bytesWritten != frameBuffer.size()) {
                    qDebug() << "[debug]sendCmd error : bytesWritten != frameBuffer.size()";
                    break;
            }

            if(checkAck(mTransactionID))
                return;
        }

        disconnectDsp();
        return;
    }

    bool checkAck(quint16 transcationId)
    {
        QByteArray      responseBuffer;
        QHostAddress    sender;
        quint16         senderPort;
        DspPacket       rcvPacket;

        if(mpSock->waitForReadyRead(mRcvTimeout) == false)
        {
            qDebug() << "[debug] checkAck error : timeout";
            return false;
        }
        else
        {
            responseBuffer.resize(mpSock->pendingDatagramSize());
            mpSock->readDatagram(responseBuffer.data(), responseBuffer.size(), &sender, &senderPort);
        }

        //qDebug() << "[debug][net][checkAck] "<<responseBuffer.toHex();

        if(rcvPacket.setDatagram(responseBuffer) == false)
            return false;

        if(rcvPacket.getFuncCode() != DSP_FUNCCODE_MULTIBLOCK_WRITE)
            return false;

        if(rcvPacket.getTransactionID() != transcationId)
            return false;

        return true;
    }

    void sendReadStatus()
    {
        if(mpSock == nullptr) return;

        mTransactionID++;

        QString dummy = mpSock->readAll().toHex();

        if(dummy.length() > 0)
            qDebug() << "[debug] sendCmd read all : " << dummy;

        DspPacket packet;
        DspPacket rcvPacket;
        DspStatusDto dto;
        StDspStatus * pStatus = nullptr;

        packet.setFuncCode(DSP_FUNCCODE_MULTIBLOCK_READ);
        packet.addReadBlock(DSP_GROUP_ID_STATUS, sizeof(StDspStatus)/2);
        packet.setTransactionID(mTransactionID);

        QByteArray frameBuffer = packet.createSendBuffer();
        //qDebug() << "[debug]sendReadStatus hex : " << frameBuffer.toHex();

        for(int i = 0; i < 3 ; i ++)
        {
            if (i > 0)
                qDebug() << "[debug]sendReadStatus retry : " << i;

            qint64 bytesWritten = mpSock->writeDatagram(frameBuffer, mHostAddr, mPort);
            //qDebug() << "[debug][net][sendReadStatus] "<<frameBuffer.toHex();

            if (bytesWritten == -1) {
                    qDebug() << "[debug]sendReadStatus error : bytesWritten == -1 ";
                    break;
            }
            else if(bytesWritten != frameBuffer.size()) {
                    qDebug() << "[debug]sendReadStatus error : bytesWritten != frameBuffer.size()";
                    break;
            }

            if(checkReadAck(&rcvPacket, DSP_GROUP_ID_STATUS, sizeof(StDspStatus)/2, mTransactionID) == false)
                continue;

            pStatus = (StDspStatus *)rcvPacket.getBlockData(0);

            if(pStatus == nullptr)
                continue;

            setIsConnect(true);
            dto.setValue(pStatus);
            emit signalEventChangedStatus(QDateTime::currentMSecsSinceEpoch(), dto);
            return;
        }

        disconnectDsp();
        return;
    }

    bool checkReadAck(DspPacket *pRcvPacket, quint16 groupId, qint16 wordLen, quint16 transcationId)
    {
        QByteArray      responseBuffer;
        QHostAddress    sender;
        quint16         senderPort;

        qint64 sentMSec = QDateTime::currentMSecsSinceEpoch();

        if(mpSock->waitForReadyRead(mRcvTimeout) == false)
        {
            qDebug() << "[debug] checkReadAck error : timeout, sent = " << sentMSec << ", timeout = " << QDateTime::currentMSecsSinceEpoch();
            return false;
        }
        else
        {
            responseBuffer.resize(mpSock->pendingDatagramSize());
            mpSock->readDatagram(responseBuffer.data(), responseBuffer.size(), &sender, &senderPort);
        }

        if((QDateTime::currentMSecsSinceEpoch() - sentMSec) > 100)
        {
            qDebug() << "[debug] too late response : timeout, sent = " << sentMSec << ", timeout = " << QDateTime::currentMSecsSinceEpoch();
        }
        //qDebug() << "[debug][net][checkReadAck] "<<responseBuffer.toHex();

        if(pRcvPacket->setDatagram(responseBuffer) == false)
            return false;

        if(pRcvPacket->getFuncCode() != DSP_FUNCCODE_MULTIBLOCK_READ)
        {
            qDebug() << "[debug] checkReadAck func error :" << pRcvPacket->getFuncCode();
            return false;
        }

        if(pRcvPacket->getTransactionID() != transcationId)
        {
            qDebug() << "[debug] checkReadAck TransactionID error :" << transcationId << "," << pRcvPacket->getTransactionID();
            return false;
        }

        int blockCnt = pRcvPacket->getBlockCount();

        if(blockCnt != 1)
        {
            qDebug() << "[debug] checkReadAck blockCnt error :" << blockCnt;
            return false;
        }

        StDspBlock * pBlockHeader = pRcvPacket->getBlockHeader(0);

        if(pBlockHeader->mGroupID != groupId)
        {
            qDebug() << "[debug] checkReadAck mGroupID error :" << pBlockHeader->mGroupID;
            return false;
        }

        if(pBlockHeader->mWordLen != wordLen)
        {
            qDebug() << "[debug] checkReadAck mWordLen error :"<< wordLen << "," << pBlockHeader->mWordLen;
            return false;
        }


        if(pBlockHeader->mStartAddr != 0)
        {
            qDebug() << "[debug] checkReadAck mStartAddr error ";
            return false;
        }

        return true;
    }

    void setIsConnect(bool value)
    {
        if(mIsConnect == value) return;

        qDebug() << "[debug] IsConnect : " << value;

        mIsConnect = value;

        emit signalEventChangedIsConnect(mIsConnect);
    }


};

#endif // DSPASYNCWORKER_H
