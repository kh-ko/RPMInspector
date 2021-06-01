QT += quick widgets serialbus serialport gui-private

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# QXlsx code for Application Qt project
#QXLSX_PARENTPATH=./QXlsx/         # current QXlsx path is . (. means curret directory)
#QXLSX_HEADERPATH=./QXlsx/header/  # current QXlsx header path is ./header/
#QXLSX_SOURCEPATH=./QXlsx/source/  # current QXlsx source path is ./source/
#include(./QXlsx/QXlsx.pri)

SOURCES += \
        QXlsx/source/xlsxabstractooxmlfile.cpp \
        QXlsx/source/xlsxabstractsheet.cpp \
        QXlsx/source/xlsxcell.cpp \
        QXlsx/source/xlsxcellformula.cpp \
        QXlsx/source/xlsxcelllocation.cpp \
        QXlsx/source/xlsxcellrange.cpp \
        QXlsx/source/xlsxcellreference.cpp \
        QXlsx/source/xlsxchart.cpp \
        QXlsx/source/xlsxchartsheet.cpp \
        QXlsx/source/xlsxcolor.cpp \
        QXlsx/source/xlsxconditionalformatting.cpp \
        QXlsx/source/xlsxcontenttypes.cpp \
        QXlsx/source/xlsxdatavalidation.cpp \
        QXlsx/source/xlsxdatetype.cpp \
        QXlsx/source/xlsxdocpropsapp.cpp \
        QXlsx/source/xlsxdocpropscore.cpp \
        QXlsx/source/xlsxdocument.cpp \
        QXlsx/source/xlsxdrawing.cpp \
        QXlsx/source/xlsxdrawinganchor.cpp \
        QXlsx/source/xlsxformat.cpp \
        QXlsx/source/xlsxmediafile.cpp \
        QXlsx/source/xlsxnumformatparser.cpp \
        QXlsx/source/xlsxrelationships.cpp \
        QXlsx/source/xlsxrichstring.cpp \
        QXlsx/source/xlsxsharedstrings.cpp \
        QXlsx/source/xlsxsimpleooxmlfile.cpp \
        QXlsx/source/xlsxstyles.cpp \
        QXlsx/source/xlsxtheme.cpp \
        QXlsx/source/xlsxutility.cpp \
        QXlsx/source/xlsxworkbook.cpp \
        QXlsx/source/xlsxworksheet.cpp \
        QXlsx/source/xlsxzipreader.cpp \
        QXlsx/source/xlsxzipwriter.cpp \
        source/logger/nsdebug.cpp \
        source/main.cpp \
        source/util/etcutil.cpp \
        source/util/mouseeventspy.cpp

RESOURCES += qml/qml.qrc

TRANSLATIONS += Lang_ko_KR.ts
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
target.path = /home/pi/apps/$${TARGET}
INSTALLS += target

HEADERS += \
    QXlsx/header/xlsxabstractooxmlfile.h \
    QXlsx/header/xlsxabstractooxmlfile_p.h \
    QXlsx/header/xlsxabstractsheet.h \
    QXlsx/header/xlsxabstractsheet_p.h \
    QXlsx/header/xlsxcell.h \
    QXlsx/header/xlsxcell_p.h \
    QXlsx/header/xlsxcellformula.h \
    QXlsx/header/xlsxcellformula_p.h \
    QXlsx/header/xlsxcelllocation.h \
    QXlsx/header/xlsxcellrange.h \
    QXlsx/header/xlsxcellreference.h \
    QXlsx/header/xlsxchart.h \
    QXlsx/header/xlsxchart_p.h \
    QXlsx/header/xlsxchartsheet.h \
    QXlsx/header/xlsxchartsheet_p.h \
    QXlsx/header/xlsxcolor_p.h \
    QXlsx/header/xlsxconditionalformatting.h \
    QXlsx/header/xlsxconditionalformatting_p.h \
    QXlsx/header/xlsxcontenttypes_p.h \
    QXlsx/header/xlsxdatavalidation.h \
    QXlsx/header/xlsxdatavalidation_p.h \
    QXlsx/header/xlsxdatetype.h \
    QXlsx/header/xlsxdocpropsapp_p.h \
    QXlsx/header/xlsxdocpropscore_p.h \
    QXlsx/header/xlsxdocument.h \
    QXlsx/header/xlsxdocument_p.h \
    QXlsx/header/xlsxdrawing_p.h \
    QXlsx/header/xlsxdrawinganchor_p.h \
    QXlsx/header/xlsxformat.h \
    QXlsx/header/xlsxformat_p.h \
    QXlsx/header/xlsxglobal.h \
    QXlsx/header/xlsxmediafile_p.h \
    QXlsx/header/xlsxnumformatparser_p.h \
    QXlsx/header/xlsxrelationships_p.h \
    QXlsx/header/xlsxrichstring.h \
    QXlsx/header/xlsxrichstring_p.h \
    QXlsx/header/xlsxsharedstrings_p.h \
    QXlsx/header/xlsxsimpleooxmlfile_p.h \
    QXlsx/header/xlsxstyles_p.h \
    QXlsx/header/xlsxtheme_p.h \
    QXlsx/header/xlsxutility_p.h \
    QXlsx/header/xlsxworkbook.h \
    QXlsx/header/xlsxworkbook_p.h \
    QXlsx/header/xlsxworksheet.h \
    QXlsx/header/xlsxworksheet_p.h \
    QXlsx/header/xlsxzipreader_p.h \
    QXlsx/header/xlsxzipwriter_p.h \
    qml/control/chart/linechart/linechartdata.h \
    qml/control/chart/linechart/loglinechartdata.h \
    qml/control/keypad/keypadcomposit.h \
    qml/control/keypad/keypadmodel.h \
    source/globaldef/qmlenumdef.h \
    source/logger/nsdebug.h \
    source/qmlmodel/dialog/qmlmeasurecfgdlgmodel.h \
    source/qmlmodel/dialog/qmlpdlistdlgmodel.h \
    source/qmlmodel/dialog/qmlpdsettingdlgmodel.h \
    source/qmlmodel/dialog/qmlusbsavedlgmodel.h \
    source/qmlmodel/dialog/qmlwriterinfodlgmodel.h \
    source/qmlmodel/qmldevpanelmodel.h \
    source/qmlmodel/qmlmeasuremodel.h \
    source/qmlmodel/qmlreportmodel.h \
    source/service/coreservice.h \
    source/service/def/builddef.h \
    source/service/def/datetimeform.h \
    source/service/def/filedef.h \
    source/service/dsp/dspasyncworker.h \
    source/service/dsp/dspsprovider.h \
    source/service/dsp/packet/dsppacket.h \
    source/service/dsp/packet/dsppacketstruct.h \
    source/service/dto/comminfodto.h \
    source/service/dto/dspcmddto.h \
    source/service/dto/dspstatusdto.h \
    source/service/dto/enum/enumdef.h \
    source/service/dto/measureconfigdto.h \
    source/service/dto/pdsettingdto.h \
    source/service/dto/reportrowdto.h \
    source/service/dto/reportwriterinfodto.h \
    source/service/dto/rpmtabledto.h \
    source/service/includesvcdto.h \
    source/service/localsetting/localsettingsprovider.h \
    source/service/report/reportsprovider.h \
    source/service/rpm/rpmsprovider.h \
    source/service/timer/timersprovider.h \
    source/service/util/byteswap.h \
    source/service/util/exceptionutil.h \
    source/service/util/filecopylocal.h \
    source/service/util/filefolderreader.h \
    source/service/util/filereaderex.h \
    source/service/util/filewriterex.h \
    source/service/util/interpolationutil.h \
    source/service/util/mathcountmvavg.h \
    source/service/util/mathmvavg.h \
    source/service/util/sproviderconnectutil.h \
    source/util/etcutil.h \
    source/util/mouseeventspy.h

DISTFILES +=
