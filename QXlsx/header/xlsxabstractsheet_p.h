// xlsxabstractsheet_p/h

#ifndef XLSXABSTRACTSHEET_P_H
#define XLSXABSTRACTSHEET_P_H

#include <QtGlobal>
#include <QString>
#include <QSharedPointer>

#include "QXlsx/header/xlsxglobal.h"

#include "QXlsx/header/xlsxabstractsheet.h"
#include "QXlsx/header/xlsxabstractooxmlfile_p.h"
#include "QXlsx/header/xlsxdrawing_p.h"

QT_BEGIN_NAMESPACE_XLSX

class AbstractSheetPrivate : public AbstractOOXmlFilePrivate
{
    Q_DECLARE_PUBLIC(AbstractSheet)
public:
    AbstractSheetPrivate(AbstractSheet *p, AbstractSheet::CreateFlag flag);
    ~AbstractSheetPrivate();

    Workbook *workbook;
    QSharedPointer<Drawing> drawing;

    QString name;
    int id;
    AbstractSheet::SheetState sheetState;
    AbstractSheet::SheetType type;
};

QT_END_NAMESPACE_XLSX

#endif // XLSXABSTRACTSHEET_P_H
