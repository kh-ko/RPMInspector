#ifndef FILEDEF_H
#define FILEDEF_H

#include <QObject>
#include <QDateTime>
#include <QApplication>
#include "source/service/def/datetimeform.h"

class FileDef: public QObject
{
    Q_OBJECT
public:
    explicit FileDef(QObject *parent = nullptr) : QObject(parent){}
    ~FileDef(){}

    static QString RPM_DIR()
    {
        static QString dir = QString("%1/rpm").arg(QApplication::applicationDirPath());
        return dir;
    }

    static QString RPM_FILENAME()
    {
        static QString file = "rpm.xlsx";
        return file;
    }

    static QString REPORT_DIR()
    {
        static QString dir = QString("%1/report").arg(QApplication::applicationDirPath());
        return dir;
    }

    static QString REPORT_SAMPLE_DIR()
    {
        static QString dir = QString("%1/report_sample").arg(QApplication::applicationDirPath());
        return dir;
    }

    static QString REPORT_SAMPLE_FILENAME()
    {
        static QString file = "sample.xlsx";
        return file;
    }

    /*
    static QString GRAPH_RECORD_DIR()
    {
        static QString dir = QString("%1/graph").arg(QApplication::applicationDirPath());
        return dir;
    }

    static QString GRAPH_RECORD_FILENAME()
    {
        static QString dir = QString("%1.txt").arg(QDateTime::currentDateTime().toString(DATE_TIME_FILE_NAME_FMT));
        return dir;
    }

    static QString DEFAULT_SETTING_DIR()
    {
        static QString dir = QString("%1/defaultvalue").arg(QApplication::applicationDirPath());
        return dir;
    }

    static QString DEFAULT_SETTING_FILENAME()
    {
        static QString file = "defaultvalue.txt";
        return file;
    }
*/
};

#endif // FILEDEF_H
