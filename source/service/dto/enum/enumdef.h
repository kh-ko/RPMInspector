#ifndef ENUMDEF_H
#define ENUMDEF_H
#include <QObject>

class EnumDef: public QObject{
    Q_OBJECT
    Q_ENUMS(ePDError)

public:

    enum ePDError{
        PDERR_NONE          = 0,
        PDERR_FILE_WRITE    = 1,
        PDERR_NOT_EXIST     = 2,
        PDERR_SAME_PD_NUM   = 3,
        PDERR_SELECTED      = 9,
    };
};
#endif // ENUMDEF_H
