#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCursor>
#include <QtQuickControls2/QQuickStyle>
#include <QStyleHints>
#include "source/logger/nsdebug.h"
#include "source/globaldef/qmlenumdef.h"
#include "source/service/coreservice.h"
#include "source/util/mouseeventspy.h"
#include "source/qmlmodel/qmldevpanelmodel.h"
#include "source/qmlmodel/qmlmeasuremodel.h"
#include "source/qmlmodel/qmlreportmodel.h"
#include "source/qmlmodel/dialog/qmlpdlistdlgmodel.h"
#include "source/qmlmodel/dialog/qmlpdsettingdlgmodel.h"
#include "source/qmlmodel/dialog/qmlusbsavedlgmodel.h"
#include "source/qmlmodel/dialog/qmlmeasurecfgdlgmodel.h"
#include "qml/control/chart/linechart/linechartdata.h"
#include "qml/control/chart/linechart/loglinechartdata.h"

int main(int argc, char *argv[])
{
    int resultExec = 0;

    //qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));


    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

#if defined(Q_OS_WIN)
    //QGuiApplication::setOverrideCursor(QCursor(Qt::BlankCursor));
#else
    QGuiApplication::setOverrideCursor(Qt::BlankCursor);
#endif

    //QGuiApplication::styleHints()->setMousePressAndHoldInterval(200);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/ui/BaseWindow.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    qmlRegisterUncreatableType<QmlEnumDef>("QmlEnumDef", 1, 0, "QmlEnumDef", "");
    qmlRegisterUncreatableType<EnumDef>("EnumDef", 1, 0, "EnumDef", "");

    qRegisterMetaType<CommInfoDto>();
    qRegisterMetaType<DspStatusDto>();
    qRegisterMetaType<PDSettingDto>();
    qRegisterMetaType<ReportRowDto>();
    qRegisterMetaType<DspCmdDto>();
    qRegisterMetaType<RPMTableDto>();
    qRegisterMetaType<MeasureConfigDto>();

    qmlRegisterType<QmlDevPanelModel>("QmlDevPanelModel", 1, 0, "QmlDevPanelModel");
    qmlRegisterType<QmlMeasureModel>("QmlMeasureModel", 1, 0, "QmlMeasureModel");
    qmlRegisterType<QmlReportModel>("QmlReportModel", 1, 0, "QmlReportModel");
    qmlRegisterType<QmlPDListDlgModel>("QmlPDListDlgModel", 1, 0, "QmlPDListDlgModel");
    qmlRegisterType<QmlPDSettingDlgModel>("QmlPDSettingDlgModel", 1, 0, "QmlPDSettingDlgModel");
    qmlRegisterType<QmlUSBSaveDlgModel>("QmlUSBSaveDlgModel", 1, 0, "QmlUSBSaveDlgModel");
    qmlRegisterType<QmlMeasureCfgDlgModel>("QmlMeasureCfgDlgModel", 1, 0, "QmlMeasureCfgDlgModel");
    qmlRegisterType<LineChartData>("LineChartData", 1, 0, "LineChartData");
    qmlRegisterType<LogLineChartData>("LogLineChartData", 1, 0, "LogLineChartData");

    qmlRegisterSingletonType<MouseEventSpy>("MouseEventSpy", 1, 0, "MouseEventSpy", MouseEventSpy::singletonProvider);
    qmlRegisterSingletonType(QUrl("qrc:/uiengine/FontManager.qml"), "FontManager", 1, 0, "FontManager");

    NSDebug::startService();

    qInstallMessageHandler(NSDebug::debugMessageHandler);

    engine.load(url);
    resultExec = app.exec();

    qInstallMessageHandler(nullptr);
    NSDebug::stopService();

    return resultExec;
}
