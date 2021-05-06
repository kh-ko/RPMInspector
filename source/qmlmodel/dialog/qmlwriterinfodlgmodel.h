#ifndef QMLWRITERINFODLGMODEL_H
#define QMLWRITERINFODLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/globaldef/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"
#include "qml/control/chart/linechart/linechartdata.h"

class QmlWriterInfoDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mWriter             READ getWriter      NOTIFY signalEventChangedWriter    )
    Q_PROPERTY(int     mWriteYear          READ getWriteYear   NOTIFY signalEventChangedWriteYear )
    Q_PROPERTY(int     mWriteMonth         READ getWriteMonth  NOTIFY signalEventChangedWriteMonth)
    Q_PROPERTY(int     mWriteDay           READ getWriteDay    NOTIFY signalEventChangedWriteDay  )

public:
    QString mWriter    ;
    int     mWriteYear ;
    int     mWriteMonth;
    int     mWriteDay  ;

    QString getWriter    (){ return mWriter    ;}
    int     getWriteYear (){ return mWriteYear ;}
    int     getWriteMonth(){ return mWriteMonth;}
    int     getWriteDay  (){ return mWriteDay  ;}

    void    setWriter    (QString value){ if(mWriter     == value) return; mWriter     = value; emit signalEventChangedWriter    (mWriter    );}
    void    setWriteYear (int     value){ if(mWriteYear  == value) return; mWriteYear  = value; emit signalEventChangedWriteYear (mWriteYear );}
    void    setWriteMonth(int     value){ if(mWriteMonth == value) return; mWriteMonth = value; emit signalEventChangedWriteMonth(mWriteMonth);}
    void    setWriteDay  (int     value){ if(mWriteDay   == value) return; mWriteDay   = value; emit signalEventChangedWriteDay  (mWriteDay  );}

signals:
    void signalEventChangedWriter    (QString value);
    void signalEventChangedWriteYear (int     value);
    void signalEventChangedWriteMonth(int     value);
    void signalEventChangedWriteDay  (int     value);

public slots:
    Q_INVOKABLE void onCommandSetWriter    (QString value){setWriter    (value);}
    Q_INVOKABLE void onCommandSetWriteYear (int     value){setWriteYear (value);}
    Q_INVOKABLE void onCommandSetWriteMonth(int     value){setWriteMonth(value);}
    Q_INVOKABLE void onCommandSetWriteDay  (int     value){setWriteDay  (value);}
    Q_INVOKABLE QString onCommandApply()
    {
        QDate today = QDate::currentDate();
        ReportWriterInfoDto wInfo;

        wInfo.mSaveDate = today.toString(DATE_MONTH_FMT);
        wInfo.mWriter = getWriter();
        wInfo.mYear   = getWriteYear();
        wInfo.mMonth  = getWriteMonth();
        wInfo.mDay    = getWriteDay();

        pLSettingSP->setWriterInfo(wInfo);
        pReportSP->setWriterInfo(today, wInfo);
        return "";
    }

public:
    explicit QmlWriterInfoDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        QDate today = QDate::currentDate();
        ReportWriterInfoDto wInfo;

        wInfo = pReportSP->readWriterInfo(today);

        setWriter(wInfo.mWriter);
        setWriteYear(wInfo.mYear);
        setWriteMonth(wInfo.mMonth);
        setWriteDay(wInfo.mDay);
    }
    ~QmlWriterInfoDlgModel(){}

};

#endif // QMLWRITERINFODLGMODEL_H
