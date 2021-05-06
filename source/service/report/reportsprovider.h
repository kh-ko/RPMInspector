#ifndef REPORTSPROVICER_H
#define REPORTSPROVICER_H

#include <QObject>
#include <QDateTime>
#include <QTimer>
#include <QDebug>
#include <QFile>
#include <QDir>

#include "QXlsx/header/xlsxdocument.h"
#include "QXlsx/header/xlsxchartsheet.h"
#include "QXlsx/header/xlsxcellrange.h"
#include "QXlsx/header/xlsxchart.h"
#include "QXlsx/header/xlsxrichstring.h"
#include "QXlsx/header/xlsxworkbook.h"

#include "source/service/localsetting/localsettingsprovider.h"
#include "source/service/def/filedef.h"
#include "source/service/def/datetimeform.h"
#include "source/service/includesvcdto.h"
#include "source/service/util/sproviderconnectutil.h"

using namespace QXlsx;

#define pReportSP ReportSProvider::getInstance()

class ReportSProvider : public QObject
{
    Q_OBJECT

public:
    PDSettingDto mCurrPDSetting;

    static ReportSProvider * getInstance()
    {
        static ReportSProvider *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new ReportSProvider();
        }

        return mpSelf;
    }


    explicit ReportSProvider(QObject * parent = nullptr):QObject(parent)
    {
    }
    ~ReportSProvider()
    {

    }

    void start()
    {
        qDebug() << "[ReportSProvider::start]";

        mIsRunning = true;
        emit signalEventStarted();
    }

    void stop()
    {
        mIsRunning = false;
        emit signalEventStopped();
    }

    QString addReportRow(QDate today, PDSettingDto pdSetting, QString loadRPM, QString nonLoadRPM, QString judg)
    {
        QString fileName = QString("%1-%2.xlsx").arg(today.toString(DATE_MONTH_FMT)).arg(pdSetting.mPDName);

        if(QFile::exists(QString("%1/%2").arg(FileDef::REPORT_DIR()).arg(fileName)) == false)
        {
            qDebug() << "[ReportSProvider::addReportRow] can not found file" << fileName;

            loadReport(today,pdSetting);
        }

        QXlsx::Document report(QString("%1/%2").arg(FileDef::REPORT_DIR()).arg(fileName));

        if(report.load() == false)
        {
            qDebug() << "[ReportSProvider::addReportRow]" << "File load failed";

            return "엑셀파일을 접근할수 없습니다.";
        }

        ReportRowDto writeData;

        writeData.mLoadRPM = loadRPM;
        writeData.mNonRPM  = nonLoadRPM;
        writeData.mJudg    = judg;

        for(int i = 0; i < 500; i++)
        {
            ReportRowDto row;
            row = readRow(&report, i);

            if(row.mJudg == "")
            {
                writeRow(&report, i, writeData);
                saveXlsx(&report);
                break;
            }
        }

        return "";
    }

    QString removeReportRow(QDate today, PDSettingDto pdSetting, QStringList delSeqNumList)
    {
        QList<ReportRowDto> remainRowList;

        QString fileName = QString("%1-%2.xlsx").arg(today.toString(DATE_MONTH_FMT)).arg(pdSetting.mPDName);

        if(QFile::exists(QString("%1/%2").arg(FileDef::REPORT_DIR()).arg(fileName)) == false)
        {
            qDebug() << "[ReportSProvider::removeReportRow] can not found file" << fileName;
            return "엑셀파일이 존재하지 않습니다.";
        }

        QXlsx::Document report(QString("%1/%2").arg(FileDef::REPORT_DIR()).arg(fileName));

        if(report.load() == false)
        {
            qDebug() << "[ReportSProvider::removeReportRow]" << "File load failed";

            return "엑셀파일을 접근할수 없습니다.";
        }

        for(int i = 0; i < 500; i++)
        {
            bool isDelRow = false;
            ReportRowDto row;
            row = readRow(&report, i);

            if(row.mJudg == "")
                continue;

            foreach(QString delSeqNum, delSeqNumList)
            {
                if(row.mSeqNum == delSeqNum)
                {
                    isDelRow = true;
                    break;
                }
            }

            if(!isDelRow)
                remainRowList.append(row);
        }

        for(int i = 0; i < 500; i++)
        {
            ReportRowDto dummyRow;

            if(remainRowList.size() > i)
            {
                writeRow(&report, i, remainRowList[i]);
            }
            else
            {
                writeRow(&report, i, dummyRow);
            }
        }

        saveXlsx(&report);

        return "";
    }

    QString editReportHeader(QDate today, QString pdName, PDSettingDto newSetting) // check
    {
        QString oldFileName = QString("%1-%2.xlsx").arg(today.toString(DATE_MONTH_FMT)).arg(pdName);
        QString newFileName = QString("%1-%2.xlsx").arg(today.toString(DATE_MONTH_FMT)).arg(newSetting.mPDName);

        if(pdName != newSetting.mPDName)
        {
            if(QFile::exists(QString("%1/%2").arg(FileDef::REPORT_DIR()).arg(oldFileName)) == false)
            {
                qDebug() << "[ReportSProvider::editReportHeader] can not found old file" << today.toString(DATE_MONTH_FMT) << "-"<< pdName;
            }

            if(QFile::exists(QString("%1/%2").arg(FileDef::REPORT_DIR()).arg(newFileName)) == true)
            {
                qDebug() << "[ReportSProvider::editReportHeader] already exist new file" << today.toString(DATE_MONTH_FMT) << "-"<< newSetting.mPDName;
                return "제품의 엑셀파일이 이미 존재합니다.";
            }

            QFile::rename(QString("%1/%2").arg(FileDef::REPORT_DIR()).arg(oldFileName), QString("%1/%2").arg(FileDef::REPORT_DIR()).arg(newFileName));
        }

        QXlsx::Document report(QString("%1/%2").arg(FileDef::REPORT_DIR()).arg(newFileName));

        if(report.load() == false)
        {
            qDebug() << "[ReportSProvider::editReportHeader]" << "File load failed";

            return "엑셀파일을 접근할수 없습니다.";
        }

        writeHeader(&report, newSetting);

        return "";
    }

    ReportWriterInfoDto readWriterInfo(QDate today) // check
    {
        ReportWriterInfoDto writerInfo;
        QString fileName;
        qDebug() << "[ReportSProvider::readWriterInfo]";

        QDir dir(FileDef::REPORT_DIR());
        QStringList fileList = dir.entryList(QStringList() << QString("%1-*.xlsx").arg(today.toString(DATE_MONTH_FMT)),QDir::Files,QDir::SortFlag::Name);

        if(fileList.size() < 1)
            return writerInfo;

        fileName = fileList[0];

        qDebug() << "[ReportSProvider::readWriterInfo]fileName = " << fileName;

        QXlsx::Document report(QString("%1/%2").arg(FileDef::REPORT_DIR()).arg(fileName));

        if(report.load() == false)
        {
            qDebug() << "[ReportSProvider::load]" << "File load failed";

            return writerInfo;
        }

        QStringList dateList = report.read(5, 14).toString().split(" ");
        writerInfo.mWriter = report.read(6, 3).toString();

        foreach(QString date, dateList)
        {
            if(date.endsWith("년"))
            {
                writerInfo.mYear = date.left(date.length() - 1).toInt();
            }
            if(date.endsWith("월"))
            {
                writerInfo.mMonth = date.left(date.length() - 1).toInt();
            }
            if(date.endsWith("일"))
            {
                writerInfo.mDay = date.left(date.length() - 1).toInt();
            }
        }

        return writerInfo;
    }

    void setWriterInfo(QDate today, ReportWriterInfoDto writerInfo) // check
    {
        qDebug() << "[ReportSProvider::setWriterInfo]";

        QDir dir(FileDef::REPORT_DIR());
        QStringList fileList = dir.entryList(QStringList() << QString("%1-*.xlsx").arg(today.toString(DATE_MONTH_FMT)),QDir::Files,QDir::SortFlag::Name);

        foreach(QString fileName, fileList)
        {
            QXlsx::Document report(QString("%1/%2").arg(FileDef::REPORT_DIR()).arg(fileName));

            if(report.load() == false)
            {
                qDebug() << "[ReportSProvider::setWriterInfo]" << "File load failed";
                continue;
            }

            writeWriterInfo(&report, writerInfo);
        }
    }

    void removeReport(QString pdName)  // check
    {
        QDir dir(FileDef::REPORT_DIR());
        QStringList fileList = dir.entryList(QStringList() << QString("*-%1.xlsx").arg(pdName),QDir::Files,QDir::SortFlag::Name);

        foreach(QString file, fileList)
        {
            QFile::remove(QString("%1/%2").arg(FileDef::REPORT_DIR()).arg(file));
        }
    }

    QList<ReportRowDto> loadReport(QDate today, PDSettingDto pdSetting)
    {
        qDebug() << "[ReportSProvider::loadReport]";

        bool isNewFile = false;
        QList<ReportRowDto> list;
        QString fileName = QString("%1-%2.xlsx").arg(today.toString(DATE_MONTH_FMT)).arg(pdSetting.mPDName);

        if(QFile::exists(QString("%1/%2").arg(FileDef::REPORT_DIR()).arg(fileName)) == false)
        {
            QXlsx::Document newXlsx(QString("%1/%2").arg(FileDef::REPORT_SAMPLE_DIR()).arg(FileDef::REPORT_SAMPLE_FILENAME()));
            newXlsx.load();
            newXlsx.saveAs(QString("%1/%2").arg(FileDef::REPORT_DIR()).arg(fileName));

            isNewFile = true;
        }

        QXlsx::Document report(QString("%1/%2").arg(FileDef::REPORT_DIR()).arg(fileName));

        if(report.load() == false)
        {
            qDebug() << "[ReportSProvider::load]" << "File load failed";

            return list;
        }

        if(isNewFile)
        {
            ReportWriterInfoDto writerInfo;

            writeNumbering(&report, today.toString(DATE_MONTH_FMT));

            //qDebug() << "today = " << today.toString(DATE_MONTH_FMT) << ", saveDate = " << pLSettingSP->mWriterInfo.mSaveDate;

            if(today.toString(DATE_MONTH_FMT) == pLSettingSP->mWriterInfo.mSaveDate)
                writeWriterInfo(&report, pLSettingSP->mWriterInfo);
        }


        writeHeader(&report, pdSetting);

        for(int i = 0; i < 500; i++)
        {
            ReportRowDto row;
            row = readRow(&report, i);

            if(row.mJudg == "")
            {
                break;
            }

            list.append(row);
        }

        return list;
    }


private:
    bool              mIsRunning  = false;

    void writeNumbering(QXlsx::Document *xlsxFile, QString strDate)
    {
        for(int idx = 0; idx < 500; idx ++)
        {
            int pageIdx = idx / 50;
            int lineIdx = (idx % 25) + 9;
            int rowIdx  = 40 * pageIdx + lineIdx;
            int colIdx  = ((idx / 25) % 2) == 0 ? 1 : 9;

            xlsxFile->write(rowIdx,colIdx + 0, idx+1);
            xlsxFile->write(rowIdx,colIdx + 1, QString("%1%2").arg(strDate).arg(QString::number(idx+1).rightJustified(3,'0')));
        }

        xlsxFile->save();
    }

    void writeHeader(QXlsx::Document *xlsxFile, PDSettingDto setting)
    {
        for(int i = 0; i < 10; i ++)
        {
            int rowIdx = (40 * i) + 5;
            xlsxFile->write(rowIdx, 1,setting.mModel);
            xlsxFile->write(rowIdx, 5, setting.mPDNum);
            xlsxFile->write(rowIdx, 8, setting.mPDName);
            xlsxFile->write(rowIdx + 3, 4, QString("%L1\n이상").arg(setting.mLoadCondition));
            xlsxFile->write(rowIdx + 3, 5, QString("%L1~\n%L2\n이하").arg(setting.mNonLoadConditionFrom).arg(setting.mNonLoadConditionTo));
            xlsxFile->write(rowIdx + 3, 12, QString("%L1\n이상").arg(setting.mLoadCondition));
            xlsxFile->write(rowIdx + 3, 13, QString("%L1~\n%L2\n이하").arg(setting.mNonLoadConditionFrom).arg(setting.mNonLoadConditionTo));
        }

        xlsxFile->save();
    }

    void writeWriterInfo(QXlsx::Document *xlsxFile, ReportWriterInfoDto info)
    {
        for(int i = 0; i < 10; i ++)
        {
            int rowIdx = (40 * i) + 5;
            xlsxFile->write(rowIdx, 14,QString("%1년 %2월 %3일").arg(info.mYear).arg(info.mMonth).arg(info.mDay));
            xlsxFile->write(rowIdx+1, 3, info.mWriter);
        }

        xlsxFile->save();
    }

    ReportRowDto readRow(QXlsx::Document *xlsxFile, int idx)
    {
        int pageIdx = idx / 50;
        int lineIdx = (idx % 25) + 9;
        int rowIdx  = 40 * pageIdx + lineIdx;
        int colIdx  = ((idx / 25) % 2) == 0 ? 1 : 9;

        ReportRowDto row;

        row.mSeqNum   = xlsxFile->read(rowIdx,colIdx + 0).toString();
        row.mPDSeqNum = xlsxFile->read(rowIdx,colIdx + 1).toString();
        row.mLoadRPM  = xlsxFile->read(rowIdx,colIdx + 3).toString();
        row.mNonRPM   = xlsxFile->read(rowIdx,colIdx + 4).toString();
        row.mJudg     = xlsxFile->read(rowIdx,colIdx + 7).toString();

        qDebug() << "[debug]row.mSeqNum   = " << row.mSeqNum  ;
        qDebug() << "[debug]row.mPDSeqNum = " << row.mPDSeqNum;
        qDebug() << "[debug]row.mLoadRPM  = " << row.mLoadRPM ;
        qDebug() << "[debug]row.mNonRPM   = " << row.mNonRPM  ;
        qDebug() << "[debug]row.mJudg     = " << row.mJudg    ;
        return row;
    }

    void writeRow(QXlsx::Document *xlsxFile, int idx, ReportRowDto rowData)
    {
        int pageIdx = idx / 50;
        int lineIdx = (idx % 25) + 9;
        int rowIdx  = 40 * pageIdx + lineIdx;
        int colIdx  = ((idx / 25) % 2) == 0 ? 1 : 9;

        xlsxFile->write(rowIdx,colIdx + 3, rowData.mLoadRPM);
        xlsxFile->write(rowIdx,colIdx + 4, rowData.mNonRPM );
        xlsxFile->write(rowIdx,colIdx + 7, rowData.mJudg   );

        //xlsxFile->save();
    }

    void saveXlsx(QXlsx::Document *xlsxFile)
    {
        xlsxFile->save();
    }

signals:
    void signalEventStarted        ();
    void signalEventStopped        ();

};
#endif // REPORTSPROVICER_H
