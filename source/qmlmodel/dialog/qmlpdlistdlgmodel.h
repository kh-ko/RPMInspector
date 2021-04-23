#ifndef QMLPDLISTDLGMODEL_H
#define QMLPDLISTDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/globaldef/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"

class QmlPDListDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mCurrPDNum READ getCurrPDNum  NOTIFY signalEventChangedCurrPDNum )

public:
    QString mCurrPDNum;

    QString getCurrPDNum(){ return mCurrPDNum;}

    void    setCurrPDNum(QString value){ if(mCurrPDNum == value) return; mCurrPDNum = value; emit signalEventChangedCurrPDNum(mCurrPDNum);}

signals:
    void signalEventChangedCurrPDNum(QString value);

public slots:
    Q_INVOKABLE int onCommandGetPDCnt()
    {
        qDebug() << "[debug]" << pLSettingSP->mPDSettingList.size();
        return pLSettingSP->mPDSettingList.size();
    }

    Q_INVOKABLE QString onCommandGetPDName(int idx)
    {
        return pLSettingSP->mPDSettingList[idx].mPDName;
    }
    Q_INVOKABLE QString onCommandGetPDNum(int idx)
    {
        return pLSettingSP->mPDSettingList[idx].mPDNum;
    }
    Q_INVOKABLE QString onCommandSelectPD(QString pdNum)
    {
        return pLSettingSP->selectPDSetting(pdNum);
    }
    Q_INVOKABLE QString onCommandRemovePD(QString pdNum)
    {
        if(pdNum == pLSettingSP->mCurrPDSetting.mPDNum)
        {
            return QString("현재 선택된 제품은 삭제할 수 없습니다.");
        }
        return pLSettingSP->delPDSetting(pdNum);
    }

    void onChangedSelectPDSetting(PDSettingDto setting)
    {
        setCurrPDNum(setting.mPDNum);
    }

public:
    explicit QmlPDListDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_LSETTING_CHANGED_SEL_PDSETTING;

        onChangedSelectPDSetting(pLSettingSP->mCurrPDSetting);
    }
    ~QmlPDListDlgModel(){}
};
#endif // QMLPDLISTDLGMODEL_H
