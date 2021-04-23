// xlsxcelllocation.cpp

#include <QtGlobal>
#include <QObject>
#include <QString>
#include <QVector>
#include <QList>

#include "QXlsx/header/xlsxglobal.h"
#include "QXlsx/header/xlsxcell.h"
#include "QXlsx/header/xlsxcelllocation.h"

QT_BEGIN_NAMESPACE_XLSX

CellLocation::CellLocation()
{
    col = -1;
    row = -1;

    cell.clear();
}

QT_END_NAMESPACE_XLSX
