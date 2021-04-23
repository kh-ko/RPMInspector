#ifndef QMLREPORTMODEL_H
#define QMLREPORTMODEL_H

#include <QObject>
#include <QtMath>
#include "source/globaldef/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"
#include "source/service/util/mathmvavg.h"

class QmlReportModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString  mModel              READ getModel         NOTIFY signalEventChangedModel  )
    Q_PROPERTY(QString  mPDNum              READ getPDNum         NOTIFY signalEventChangedPDNum  )
    Q_PROPERTY(QString  mPDName             READ getPDName        NOTIFY signalEventChangedPDName )

public:
    QString getModel (){ return pLSettingSP->mCurrPDSetting.mModel ;}
    QString getPDNum (){ return pLSettingSP->mCurrPDSetting.mPDNum ;}
    QString getPDName(){ return pLSettingSP->mCurrPDSetting.mPDName;}

signals:
    void   signalEventChangedModel (QString   value);
    void   signalEventChangedPDNum (QString   value);
    void   signalEventChangedPDName(QString   value);
    void   signalEventRefreshList  (               );
    void   signalEventRefreshItem  (               );

public slots:
    Q_INVOKABLE int onCommandGetListSize()
    {
        return mReportRowList.size();
    }

    Q_INVOKABLE QString onCommandGetSeq(int i)
    {
        if(mReportRowList.size()-1 < i)
            return "";

        return mReportRowList[i].mSeqNum;
    }

    Q_INVOKABLE QString onCommandGetPDSeq(int i)
    {
        if(mReportRowList.size()-1 < i)
            return "";

        return mReportRowList[i].mPDSeqNum;
    }

    Q_INVOKABLE QString onCommandGetNonLoadRPM(int i)
    {
        if(mReportRowList.size()-1 < i)
            return "";

        return mReportRowList[i].mNonRPM;
    }

    Q_INVOKABLE QString onCommandGetLoadRPM(int i)
    {
        if(mReportRowList.size()-1 < i)
            return "";

        return mReportRowList[i].mLoadRPM;
    }

    Q_INVOKABLE QString onCommandGetJudg(int i)
    {
        if(mReportRowList.size()-1 < i)
            return "";

        return mReportRowList[i].mJudg;
    }

    Q_INVOKABLE bool onCommandIsCheck(int i)
    {
        if(mReportRowList.size()-1 < i)
            return false;

        return mReportRowList[i].mCheck;
    }

    Q_INVOKABLE void onCommandToggleCheck(int i)
    {
        if(mReportRowList.size()-1 < i)
            return;

        mReportRowList[i].mCheck = !mReportRowList[i].mCheck;
    }

    Q_INVOKABLE void onCommandRemoveCheckList()
    {
        QStringList delList;
        foreach(ReportRowDto row, mReportRowList)
        {
            if(row.mCheck)
            {
                delList.append(row.mSeqNum);
            }
        }

        pReportSP->removeReportRow(mLastDateTime.date(), pLSettingSP->mCurrPDSetting, delList);

        reloadList(mLastDateTime);
    }

    Q_INVOKABLE void onCommandAllSelect()
    {
        for(int i = 0; i < mReportRowList.size(); i ++)
        {
            mReportRowList[i].mCheck =true;
        }

        emit signalEventRefreshItem();
    }

    Q_INVOKABLE void onCommandClearCheckList()
    {
        for(int i = 0; i < mReportRowList.size(); i ++)
        {
            mReportRowList[i].mCheck =false;
        }

        emit signalEventRefreshItem();
    }

    Q_INVOKABLE void onCommandAddReport(QString loadRPM, QString nonLoadRPM, bool isSucc)
    {
        qDebug()  << "[debug]loadRPM = " << loadRPM << ", nonLoadRPM = " << nonLoadRPM;
        pReportSP->addReportRow(mLastDateTime.date(), pLSettingSP->mCurrPDSetting, loadRPM, nonLoadRPM, QString("O"));

        reloadList(mLastDateTime);
    }

    void onChangedPDSetting(QString oldPDNum, PDSettingDto newSetting){
        pReportSP->editReportHeader(mLastDateTime.date(), oldPDNum,  newSetting);
    }

    void onChangedSelectPDSetting(PDSettingDto dto)
    {
        emit signalEventChangedModel (pLSettingSP->mCurrPDSetting.mModel );
        emit signalEventChangedPDNum (pLSettingSP->mCurrPDSetting.mPDNum );
        emit signalEventChangedPDName(pLSettingSP->mCurrPDSetting.mPDName);

        qDebug() << "[debug]onChangedSelectPDSetting";
        reloadList(mLastDateTime);

        pRpmSP->loadRPMTable();
    }

    void onDeletedPDSetting(QString pdNum){
        pReportSP->removeReport(pdNum);
    }

    void onTimeTick(QDateTime now)
    {
        if(mLastDateTime.date().year() != now.date().year() || mLastDateTime.date().month() != now.date().month())
        {
            reloadList(now);
        }
        mLastDateTime = now;
    }

    void onStartedCoreService()
    {
        mLastDateTime = QDateTime::currentDateTime();
        onChangedSelectPDSetting(pLSettingSP->mCurrPDSetting);
    }

public:
    explicit QmlReportModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_CORE_START;
        ENABLE_SLOT_LSETTING_CHANGED_SEL_PDSETTING;
        ENABLE_SLOT_LSETTING_CHANGED_PDSETTING;
        ENABLE_SLOT_LSETTING_DELETED_PDSETTING;

        ENABLE_SLOT_TIMER_TICK;
    }

    ~QmlReportModel(){}

private:
    QList<ReportRowDto> mReportRowList;
    QDateTime mLastDateTime;

    void reloadList(QDateTime today)
    {
        mReportRowList.clear();

        mReportRowList = pReportSP->loadReport(today.date(), pLSettingSP->mCurrPDSetting);

        emit signalEventRefreshList();
    }
};
#endif // QMLREPORTMODEL_H
