#ifndef QMLUSBSAVEDLGMODEL_H
#define QMLUSBSAVEDLGMODEL_H

#include <QObject>
#include <QtMath>
#include <QProcess>
#include "source/globaldef/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/util/filecopylocal.h"
#include "source/service/coreservice.h"

class QmlUSBSaveDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int mSaveStep     READ getSaveStep     NOTIFY signalEventChangedSaveStep   )
    Q_PROPERTY(int mFromYear     READ getFromYear     NOTIFY signalEventChangedFromYear   )
    Q_PROPERTY(int mFromMonth    READ getFromMonth    NOTIFY signalEventChangedFromMonth  )
    Q_PROPERTY(int mTotalCnt     READ getTotalCnt     NOTIFY signalEventChangedTotalCnt   )
    Q_PROPERTY(int mProgressCnt  READ getProgressCnt  NOTIFY signalEventChangedProgressCnt)


public:
    int mSaveStep   ;
    int mFromYear   ;
    int mFromMonth  ;
    int mTotalCnt   =1;
    int mProgressCnt=0;

    int getSaveStep   (){ return mSaveStep   ;}
    int getFromYear   (){ return mFromYear   ;}
    int getFromMonth  (){ return mFromMonth  ;}
    int getTotalCnt   (){ return mTotalCnt   ;}
    int getProgressCnt(){ return mProgressCnt;}

    void setSaveStep   (int value){
        if(mSaveStep == value)
            return;

        if(value == QmlEnumDef::USBSAVE_STEP_SCAN)
            mScanningTime = QDateTime::currentMSecsSinceEpoch();

        mSaveStep = value;

        emit signalEventChangedSaveStep(mSaveStep);
    }
    void setFromYear   (int value){ if(mFromYear    == value) return; mFromYear    = value; emit signalEventChangedFromYear   (mFromYear   );}
    void setFromMonth  (int value){ if(mFromMonth   == value) return; mFromMonth   = value; emit signalEventChangedFromMonth  (mFromMonth  );}
    void setTotalCnt   (int value){ if(mTotalCnt    == value) return; mTotalCnt    = value; emit signalEventChangedTotalCnt   (mTotalCnt   );}
    void setProgressCnt(int value){ if(mProgressCnt == value) return; mProgressCnt = value; emit signalEventChangedProgressCnt(mProgressCnt);}

signals:
    void signalEventChangedSaveStep   (int     value);
    void signalEventChangedFromYear   (int     value);
    void signalEventChangedFromMonth  (int     value);
    void signalEventChangedTotalCnt   (int     value);
    void signalEventChangedProgressCnt(int     value);
    void signalEventUSBNotSearch      (             );
    void signalEventFileNotSearch     (             );
    void signalEventCopyFail          (QString value);

    void signalCommandCopy(QString, QString, QString);

public slots:
    Q_INVOKABLE void onCommandSetFromYear (int value){setFromYear (value);}
    Q_INVOKABLE void onCommandSetFromMonth(int value){setFromMonth(value);}
    Q_INVOKABLE void onCommandSave()
    {
        if(QFile::exists("/dev/sda1") == false)
        {
            emit signalEventUSBNotSearch();
            return;
        }
        setSaveStep((int)QmlEnumDef::USBSAVE_STEP_SCAN);
    }

    void onTimeTick(QDateTime now)
    {
        if(mSaveStep == QmlEnumDef::USBSAVE_STEP_SCAN){

            if(QDateTime::currentMSecsSinceEpoch() - mScanningTime > 60000)
            {
                setSaveStep((int)QmlEnumDef::USBSAVE_STEP_NONE);
                emit signalEventUSBNotSearch();

                return;
            }

            if(isDetectUSB())
            {
                copyToUSB();
            }
        }
    }

    void onCopiedFile(int progressCnt, int totalCnt)
    {
        if(totalCnt == progressCnt)
        {
            if(totalCnt == 0)
            {
                setSaveStep((int)QmlEnumDef::USBSAVE_STEP_NONE);
                emit signalEventFileNotSearch();
            }
            else
            {
                setSaveStep((int)QmlEnumDef::USBSAVE_STEP_COMPLETE);
                pLSettingSP->setLastUSBSaveDate(QDateTime::currentDateTime().date().year(), QDateTime::currentDateTime().date().month());

                unmountUSB();
            }
            stopCopyThread();
            return;
        }

        setTotalCnt(totalCnt);
        setProgressCnt(progressCnt);
    }

    void onCompletedCopy(bool isSucc)
    {
        if(isSucc == false)
        {
            emit signalEventCopyFail("USB로 복사중 오류가 발생하였습니다.");
            setSaveStep((int)QmlEnumDef::USBSAVE_STEP_NONE);
            stopCopyThread();
        }
    }

public:
    explicit QmlUSBSaveDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_TIMER_TICK;

        setSaveStep((int)QmlEnumDef::USBSAVE_STEP_NONE);
        setFromYear(pLSettingSP->mLastUSBSaveYear);
        setFromMonth(pLSettingSP->mLastUSBSaveMonth);
        setTotalCnt(1);
        setProgressCnt(0);
    }
    ~QmlUSBSaveDlgModel()
    {
        stopCopyThread();
    }

private:
    qint64        mScanningTime;
    QThread       *mpCopyThread = nullptr;
    FileCopyLocal *mpCopyWorker = nullptr;

    bool isDetectUSB()
    {
        QProcess process;
        process.start("df -h");
        process.waitForFinished(100);

        QString output = process.readAllStandardOutput();

        return output.contains("/dev/sda1");
    }

    void unmountUSB()
    {
        QString cmd;

       cmd.sprintf("sudo umount /home/pi/usb");

       system(cmd.toStdString().c_str());
    }

    void copyToUSB()
    {
        setSaveStep((int)QmlEnumDef::USBSAVE_STEP_COPY);

        QDate fromDate;
        fromDate.setDate(mFromYear, mFromMonth,1);

        mpCopyThread  = new QThread;
        mpCopyWorker = new FileCopyLocal;
        mpCopyWorker->moveToThread(mpCopyThread);
        mpCopyThread->start();

        connect(mpCopyThread, &QThread::finished, mpCopyWorker, &QObject::deleteLater);
        connect(this        , SIGNAL(signalCommandCopy(QString, QString, QString)), mpCopyWorker, SLOT(onCommandCopyFolder(QString, QString, QString)));
        connect(mpCopyWorker, SIGNAL(signalEventProgress(int, int)               ), this        , SLOT(onCopiedFile(int, int)                        ));
        connect(mpCopyWorker, SIGNAL(signalEventComplete(bool)                   ), this        , SLOT(onCompletedCopy(bool )                        ));

        emit signalCommandCopy("/home/pi/usb/rpm_inspector", FileDef::REPORT_DIR(), fromDate.toString(DATE_MONTH_FMT));
    }

    void stopCopyThread()
    {
        if(mpCopyWorker != nullptr)
        {
            disconnect(this        , SIGNAL(signalCommandCopy(QString, QString, QString)), mpCopyWorker, SLOT(onCommandCopyFolder(QString, QString, QString)));
            disconnect(mpCopyWorker, SIGNAL(signalEventProgress(int, int)               ), this        , SLOT(onCopiedFile(int, int)                        ));
            disconnect(mpCopyWorker, SIGNAL(signalEventComplete(bool)                   ), this        , SLOT(onCompletedCopy(bool )                        ));

            mpCopyWorker->cancel();
            mpCopyWorker= nullptr;
         }

        if(mpCopyThread != nullptr)
        {
            if(mpCopyThread->isRunning())
            {
                mpCopyThread->quit();
                mpCopyThread->wait();
            }

            mpCopyThread->deleteLater();

            mpCopyThread = nullptr;
        }
    }
};

#endif // QMLUSBSAVEDLGMODEL_H
