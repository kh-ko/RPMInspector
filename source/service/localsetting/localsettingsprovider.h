#ifndef LOCALSETTINGSPROVIDER_H
#define LOCALSETTINGSPROVIDER_H

#include <QObject>
#include <QDateTime>
#include <QSettings>
#include <QTimer>
#include <QDebug>

#include "source/service/def/datetimeform.h"
#include "source/service/util/exceptionutil.h"
#include "source/service/includesvcdto.h"
#include "source/service/rpm/rpmsprovider.h"

#define pLSettingSP LocalSettingSProvider::getInstance()

class LocalSettingSProvider : public QObject
{
    Q_OBJECT

private:
    const QString mDefaultLastUSBSaveYearKey            = "default/LastUSBSaveYear"              ;
    const QString mDefaultLastUSBSaveMonthKey           = "default/LastUSBSaveMonth"             ;
    const QString mDefaultIpKey                         = "default/Ip"                           ;
    const QString mDefaultPortKey                       = "default/Port"                         ;
    const QString mDefaultPDModelKey                    = "default/PDModel"                      ;
    const QString mDefaultPDNumKey                      = "default/PDNum"                        ;
    const QString mDefaultPDNameKey                     = "default/PDName"                       ;
    const QString mDefaultNonLoadMeasureTimeKey         = "default/NonLoadMeasureTime"           ;
    const QString mDefaultLoadMeasureTimeKey            = "default/LoadMeasureTime"              ;
    const QString mDefaultNonLoadConditionFromKey       = "default/NonLoadConditionFrom"         ;
    const QString mDefaultNonLoadConditionToKey         = "default/NonLoadConditionTo"           ;
    const QString mDefaultLoadConditionKey              = "default/LoadCondition"                ;
    const QString mDefaultLoadNMKey                     = "default/LoadNM"                       ;
    const QString mDefaultRatedRPMKey                   = "default/RatedRPM"                     ;
    const QString mDefaultChuckRunDelayTimeKey          = "default/ChuckRunDelayTime"            ;
    const QString mDefaultValveRunDelayTimeKey          = "default/ValveRunDelayTime"            ;
    const QString mDefaultVoltageSetDelayTimeKey        = "default/VoltageSetDelayTime"          ;
    const QString mDefaultNonLoadMeasureDelayTimeKey    = "default/NonLoadMeasureDelayTime"      ;
    const QString mDefaultLoadMeasureDelayTimeKey       = "default/LoadMeasureDelayTime"         ;
    const QString mDefaultMeasureAvgRangeKey            = "default/MeasureAvgRange"              ;
    const QString mDefaultKgfcmGainKey                  = "default/KgfcmGain"                    ;
    const QString mDefaultIsRtAdjVoltageKey             = "default/IsRtAdjVoltage"               ;

    const QString mLastUSBSaveYearKey                   = "lastUSBSaveDate/Year"                 ;
    const QString mLastUSBSaveMonthKey                  = "lastUSBSaveDate/Month"                ;

    const QString mCommInfoIpKey                        = "commInfo/Ip"                          ;
    const QString mCommInfoPortKey                      = "commInfo/Port"                        ;

    const QString mSettingSelectPDNumKey                = "setting/SelectPDNum"                  ;
    const QString mSettingPDModelKey                    = "setting_%1/PDModel"                   ;
    const QString mSettingPDNameKey                     = "setting_%1/PDName"                    ;
    const QString mSettingNonLoadMeasureTimeKey         = "setting_%1/NonLoadMeasureTime"        ;
    const QString mSettingLoadMeasureTimeKey            = "setting_%1/LoadMeasureTime"           ;
    const QString mSettingNonLoadConditionFromKey       = "setting_%1/NonLoadConditionFrom"      ;
    const QString mSettingNonLoadConditionToKey         = "setting_%1/NonLoadConditionTo"        ;
    const QString mSettingLoadConditionKey              = "setting_%1/LoadCondition"             ;
    const QString mSettingLoadNMKey                     = "setting_%1/LoadNM"                    ;
    const QString mSettingRatedRPMKey                   = "setting_%1/RatedRPM"                  ;

    const QString mMeasureCfgChuckRunDelayTimeKey       = "measureConfig/ChuckRunDelayTime"      ;
    const QString mMeasureCfgValveRunDelayTimeKey       = "measureConfig/ValveRunDelayTime"      ;
    const QString mMeasureCfgVoltageSetDelayTimeKey     = "measureConfig/VoltageSetDelayTime"    ;
    const QString mMeasureCfgNonLoadMeasureDelayTimeKey = "measureConfig/NonLoadMeasureDelayTime";
    const QString mMeasureCfgLoadMeasureDelayTimeKey    = "measureConfig/LoadMeasureDelayTime"   ;
    const QString mMeasureCfgMeasureAvgRangeKey         = "measureConfig/MeasureAvgRange"        ;
    const QString mMeasureCfgKgfcmGainKey               = "measureConfig/KgfcmGain"              ;
    const QString mMeasureCfgIsRtAdjVoltageKey          = "measureConfig/IsRtAdjVoltage"         ;

    const QString mWriterInfoSaveDateKey                = "writerInfo/SaveDate"                  ;
    const QString mWriterInfoWriterKey                  = "writerInfo/Writer"                    ;
    const QString mWriterInfoYearKey                    = "writerInfo/Year"                      ;
    const QString mWriterInfoMonthKey                   = "writerInfo/Month"                     ;
    const QString mWriterInfoDayKey                     = "writerInfo/Day"                       ;

public:
    static LocalSettingSProvider * getInstance()
    {
        static LocalSettingSProvider *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new LocalSettingSProvider();
        }

        return mpSelf;
    }

    int     mDefaultLastUSBSaveYear         = 2021;
    int     mDefaultLastUSBSaveMonth        = 1;
    QString mDefaultIp                      = "192.168.0.160";
    quint16 mDefaultPort                    = 10020;
    QString mDefaultPDModel                 = "AIR ANGLE GRINDER";
    QString mDefaultPDNum                   = "8014900";
    QString mDefaultPDName                  = "DAG-2WS";
    qint64  mDefaultNonLoadMeasureTime      = 10000;
    qint64  mDefaultLoadMeasureTime         = 10000;
    int     mDefaultNonLoadConditionFrom    = 15000;
    int     mDefaultNonLoadConditionTo      = 22000;
    int     mDefaultLoadCondition           = 7500;
    int     mDefaultLoadNM                  = 0;
    int     mDefaultRatedRPM                = 20000;
    qint64  mDefaultChuckRunDelayTime       = 1000;
    qint64  mDefaultValveRunDelayTime       = 2000;
    qint64  mDefaultVoltageSetDelayTime     = 3000;
    qint64  mDefaultNonLoadMeasureDelayTime = 4000;
    qint64  mDefaultLoadMeasureDelayTime    = 5000;
    qint64  mDefaultMeasureAvgRange         = 1000;
    double  mDefaultKgfcmGain               = 1;
    bool    mDefaultIsRtAdjVoltage          = false;

    int                 mLastUSBSaveYear        ;
    int                 mLastUSBSaveMonth       ;
    CommInfoDto         mCommInfo               ;
    MeasureConfigDto    mMeasureConfig          ;
    PDSettingDto        mCurrPDSetting          ;
    QList<PDSettingDto> mPDSettingList          ;
    ReportWriterInfoDto mWriterInfo             ;

    explicit LocalSettingSProvider(QObject * parent = nullptr):QObject(parent)
    {
        mpSetting = new QSettings("novasen", "RPM_SETTING", this);
    }
    ~LocalSettingSProvider()
    {
    }

    void start()
    {
        qDebug() << "[LocalSettingSProvider::start]";
        load();

        emit signalEventStarted();
    }

    void stop()
    {

        mIsRunning = false;
        emit signalEventStopped();
    }

    void setLastUSBSaveDate(int year, int month)
    {
        internalSetLastUSBSaveDate(year, month);

        emit signalEventChangedLastUSBSaveDate(year, month);
    }

    void setCommInfo(CommInfoDto info)
    {
        internalSetCommInfo(info);

        emit signalEventChangedCommInfo(info);
    }

    void setMeasureConfig(MeasureConfigDto config)
    {
        internalSetMeasureConfig(config);

        emit signalEventChangedMeasureCfg(config);
    }

    void setWriterInfo(ReportWriterInfoDto info)
    {
        internalSetWriterInfo(info);

        emit signalEventChangedWriterInfo(info);
    }

    QString editPDSetting(QString oldPdNum, PDSettingDto setting)
    {
        QString oldPdName = "";
        setting.mVoltage = pRpmSP->convertBaseVoltage(setting.mLoadNM, mMeasureConfig.mKgfcmGain);

        qDebug() << "[debug][editPDSetting] pdNum = " << setting.mPDNum << ", RatedRPM = " << setting.mRatedRPM << ", LoadKgfcm = " << setting.mLoadNM << ", gain = " << mMeasureConfig.mKgfcmGain << ", voltage = " << setting.mVoltage;

        foreach(PDSettingDto tempSetting, mPDSettingList)
        {
            if(tempSetting.mPDNum == oldPdNum)
            {
                oldPdName = tempSetting.mPDName;
            }
        }

        QString ret = internalEditPDSetting(oldPdNum, setting);

        if(ret == "")
        {
            emit signalEventChangedPDSetting(oldPdNum, oldPdName, setting);

            if(mCurrPDSetting.mPDNum == oldPdNum)
            {
                ret = selectPDSetting(setting.mPDNum);
                return ret;
            }
        }

        return ret;
    }

    QString addPDSetting(PDSettingDto setting)
    {
        setting.mVoltage = pRpmSP->convertBaseVoltage(setting.mLoadNM, mMeasureConfig.mKgfcmGain);

        qDebug() << "[debug][editPDSetting] pdNum = " << setting.mPDNum << ", RatedRPM = " << setting.mRatedRPM << ", LoadKgfcm = " << setting.mLoadNM << ", gain = " << mMeasureConfig.mKgfcmGain << ", voltage = " << setting.mVoltage;

        QString ret = internalAddPDSetting(setting);

        if(ret == "")
            emit signalEventAddedPDSetting(setting);

        return ret;
    }

    QString delPDSetting(QString pdNum)
    {
        QString pdName = "";

        foreach(PDSettingDto tempSetting, mPDSettingList)
        {
            if(tempSetting.mPDNum == pdNum)
            {
                pdName = tempSetting.mPDName;
            }
        }

        QString ret = internalDeletePDSetting(pdNum);

        if(ret == "")
            emit signalEventDeletedPDSetting(pdNum, pdName);

        return ret;
    }

    QString selectPDSetting(QString pdNum)
    {
        QString ret = internalSelectPDSetting(pdNum);

        if(ret == "")
            emit signalEventChangedSelectPDSetting(mCurrPDSetting);

        return ret;
    }

private:
    QSettings    * mpSetting   = nullptr;
    bool           mIsRunning  = false;

    void load()
    {
        qDebug() << "[LocalSettingSProvider::load]";

        mDefaultLastUSBSaveYear                 = mpSetting->value(mDefaultLastUSBSaveYearKey           , mDefaultLastUSBSaveYear        ).toInt();
        mDefaultLastUSBSaveMonth                = mpSetting->value(mDefaultLastUSBSaveMonthKey          , mDefaultLastUSBSaveMonth       ).toInt();
        mDefaultIp                              = mpSetting->value(mDefaultIpKey                        , mDefaultIp                     ).toString();
        mDefaultPort                            = mpSetting->value(mDefaultPortKey                      , mDefaultPort                   ).toUInt();
        mDefaultPDModel                         = mpSetting->value(mDefaultPDModelKey                   , mDefaultPDModel                ).toString();
        mDefaultPDNum                           = mpSetting->value(mDefaultPDNumKey                     , mDefaultPDNum                  ).toString();
        mDefaultPDName                          = mpSetting->value(mDefaultPDNameKey                    , mDefaultPDName                 ).toString();
        mDefaultNonLoadMeasureTime              = mpSetting->value(mDefaultNonLoadMeasureTimeKey        , mDefaultNonLoadMeasureTime     ).toLongLong();
        mDefaultLoadMeasureTime                 = mpSetting->value(mDefaultLoadMeasureTimeKey           , mDefaultLoadMeasureTime        ).toLongLong();
        mDefaultNonLoadConditionFrom            = mpSetting->value(mDefaultNonLoadConditionFromKey      , mDefaultNonLoadConditionFrom   ).toInt();
        mDefaultNonLoadConditionTo              = mpSetting->value(mDefaultNonLoadConditionToKey        , mDefaultNonLoadConditionTo     ).toInt();
        mDefaultLoadCondition                   = mpSetting->value(mDefaultLoadConditionKey             , mDefaultLoadCondition          ).toInt();
        mDefaultLoadNM                          = mpSetting->value(mDefaultLoadNMKey                    , mDefaultLoadNM                 ).toInt();
        mDefaultRatedRPM                        = mpSetting->value(mDefaultRatedRPMKey                  , mDefaultRatedRPM               ).toUInt();
        mDefaultChuckRunDelayTime               = mpSetting->value(mDefaultChuckRunDelayTimeKey         , mDefaultChuckRunDelayTime      ).toLongLong();
        mDefaultValveRunDelayTime               = mpSetting->value(mDefaultValveRunDelayTimeKey         , mDefaultValveRunDelayTime      ).toLongLong();
        mDefaultVoltageSetDelayTime             = mpSetting->value(mDefaultVoltageSetDelayTimeKey       , mDefaultVoltageSetDelayTime    ).toLongLong();
        mDefaultNonLoadMeasureDelayTime         = mpSetting->value(mDefaultNonLoadMeasureDelayTimeKey   , mDefaultNonLoadMeasureDelayTime).toLongLong();
        mDefaultLoadMeasureDelayTime            = mpSetting->value(mDefaultLoadMeasureDelayTimeKey      , mDefaultLoadMeasureDelayTime   ).toLongLong();
        mDefaultMeasureAvgRange                 = mpSetting->value(mDefaultMeasureAvgRangeKey           , mDefaultMeasureAvgRange        ).toLongLong();
        mDefaultKgfcmGain                       = mpSetting->value(mDefaultKgfcmGainKey                 , mDefaultKgfcmGain              ).toDouble();
        mDefaultIsRtAdjVoltage                  = mpSetting->value(mDefaultIsRtAdjVoltageKey            , mDefaultIsRtAdjVoltage         ).toBool();

        mLastUSBSaveYear                        = mpSetting->value(mLastUSBSaveYearKey                  , mDefaultLastUSBSaveYear        ).toInt();
        mLastUSBSaveMonth                       = mpSetting->value(mLastUSBSaveMonthKey                 , mDefaultLastUSBSaveMonth       ).toInt();

        mCommInfo.mIp                           = mpSetting->value(mCommInfoIpKey                       , mDefaultIp                     ).toString();
        mCommInfo.mPort                         = mpSetting->value(mCommInfoPortKey                     , mDefaultPort                   ).toInt()   ;

        mMeasureConfig.mChuckRunDelayTime       = mpSetting->value(mMeasureCfgChuckRunDelayTimeKey      , mDefaultChuckRunDelayTime      ).toLongLong();
        mMeasureConfig.mValveRunDelayTime       = mpSetting->value(mMeasureCfgValveRunDelayTimeKey      , mDefaultValveRunDelayTime      ).toLongLong();
        mMeasureConfig.mVoltageSetDelayTime     = mpSetting->value(mMeasureCfgVoltageSetDelayTimeKey    , mDefaultVoltageSetDelayTime    ).toLongLong();
        mMeasureConfig.mNonLoadMeasureDelayTime = mpSetting->value(mMeasureCfgNonLoadMeasureDelayTimeKey, mDefaultNonLoadMeasureDelayTime).toLongLong();
        mMeasureConfig.mLoadMeasureDelayTime    = mpSetting->value(mMeasureCfgLoadMeasureDelayTimeKey   , mDefaultLoadMeasureDelayTime   ).toLongLong();
        mMeasureConfig.mMeasureAvgRange         = mpSetting->value(mMeasureCfgMeasureAvgRangeKey        , mDefaultMeasureAvgRange        ).toLongLong();
        mMeasureConfig.mKgfcmGain               = mpSetting->value(mMeasureCfgKgfcmGainKey              , mDefaultKgfcmGain              ).toDouble();
        mMeasureConfig.mIsRtAdjVoltage          = mpSetting->value(mMeasureCfgIsRtAdjVoltageKey         , mDefaultIsRtAdjVoltage         ).toBool();

        mWriterInfo.mSaveDate                   = mpSetting->value(mWriterInfoSaveDateKey               , ""                             ).toString();
        mWriterInfo.mWriter                     = mpSetting->value(mWriterInfoWriterKey                 , ""                             ).toString();
        mWriterInfo.mYear                       = mpSetting->value(mWriterInfoYearKey                   , 0                              ).toInt();
        mWriterInfo.mMonth                      = mpSetting->value(mWriterInfoMonthKey                  , 0                              ).toInt();
        mWriterInfo.mDay                        = mpSetting->value(mWriterInfoDayKey                    , 0                              ).toInt();

        QStringList keyList = mpSetting->allKeys();
        foreach(QString key, keyList)
        {
            if(key.startsWith("setting_") && key.endsWith("PDName"))
            {
                PDSettingDto pdSetting;
                pdSetting.mPDNum = key.split("/")[0].split("_")[1];

                mPDSettingList.append(pdSetting);
            }
        }

        if(mPDSettingList.size() < 1)
        {
            PDSettingDto pdSetting;
            pdSetting.mModel                               = mDefaultPDModel                ;
            pdSetting.mPDNum                               = mDefaultPDNum                  ;
            pdSetting.mPDName                              = mDefaultPDName                 ;
            pdSetting.mNonLoadMeasureTime                  = mDefaultNonLoadMeasureTime     ;
            pdSetting.mLoadMeasureTime                     = mDefaultLoadMeasureTime        ;
            pdSetting.mNonLoadConditionFrom                = mDefaultNonLoadConditionFrom   ;
            pdSetting.mNonLoadConditionTo                  = mDefaultNonLoadConditionTo     ;
            pdSetting.mLoadCondition                       = mDefaultLoadCondition          ;
            pdSetting.mRatedRPM                            = mDefaultRatedRPM               ;
            pdSetting.mLoadNM                              = mDefaultLoadNM                 ;
            pdSetting.mVoltage                             = pRpmSP->convertBaseVoltage(pdSetting.mLoadNM, mMeasureConfig.mKgfcmGain);

            qDebug() << "[debug][load] pdNum = " << pdSetting.mPDNum << ", RatedRPM = " << pdSetting.mRatedRPM << ", LoadKgfcm = " << pdSetting.mLoadNM << ", gain = " << mMeasureConfig.mKgfcmGain << ", voltage = " << pdSetting.mVoltage;

            internalAddPDSetting(pdSetting);
            internalSelectPDSetting(pdSetting.mPDNum);
        }
        else
        {
            for(int i = 0; i < mPDSettingList.size(); i ++)
            {
                PDSettingDto pdSetting = mPDSettingList[i];

                pdSetting.mModel                   = mpSetting->value(mSettingPDModelKey.arg(pdSetting.mPDNum)                , mDefaultPDModel                ).toString();
                pdSetting.mPDName                  = mpSetting->value(mSettingPDNameKey.arg(pdSetting.mPDNum)                 , mDefaultPDName                 ).toString();
                pdSetting.mNonLoadMeasureTime      = mpSetting->value(mSettingNonLoadMeasureTimeKey.arg(pdSetting.mPDNum)     , mDefaultNonLoadMeasureTime     ).toLongLong();
                pdSetting.mLoadMeasureTime         = mpSetting->value(mSettingLoadMeasureTimeKey.arg(pdSetting.mPDNum)        , mDefaultLoadMeasureTime        ).toLongLong();
                pdSetting.mNonLoadConditionFrom    = mpSetting->value(mSettingNonLoadConditionFromKey.arg(pdSetting.mPDNum)   , mDefaultNonLoadConditionFrom   ).toInt();
                pdSetting.mNonLoadConditionTo      = mpSetting->value(mSettingNonLoadConditionToKey.arg(pdSetting.mPDNum)     , mDefaultNonLoadConditionTo     ).toInt();
                pdSetting.mLoadCondition           = mpSetting->value(mSettingLoadConditionKey.arg(pdSetting.mPDNum)          , mDefaultLoadCondition          ).toInt();
                pdSetting.mRatedRPM                = mpSetting->value(mSettingRatedRPMKey.arg(pdSetting.mPDNum)               , mDefaultRatedRPM               ).toInt();
                pdSetting.mLoadNM                  = mpSetting->value(mSettingLoadNMKey.arg(pdSetting.mPDNum)                 , mDefaultLoadNM                 ).toInt();
                pdSetting.mVoltage                 = pRpmSP->convertBaseVoltage(pdSetting.mLoadNM, mMeasureConfig.mKgfcmGain);

                qDebug() << "[debug][load] pdNum = " << pdSetting.mPDNum << ", RatedRPM = " << pdSetting.mRatedRPM << ", LoadKgfcm = " << pdSetting.mLoadNM << ", gain = " << mMeasureConfig.mKgfcmGain << ", voltage = " << pdSetting.mVoltage;

                internalEditPDSetting(pdSetting.mPDNum, pdSetting);
            }
        }

        QString selectPDNum = mpSetting->value(mSettingSelectPDNumKey  , mPDSettingList[0].mPDNum).toString();
        internalSelectPDSetting(selectPDNum);

        internalSetCommInfo(mCommInfo);

        internalSetMeasureConfig(mMeasureConfig);
        internalSetLastUSBSaveDate(mLastUSBSaveYear, mLastUSBSaveMonth);
        internalSetWriterInfo(mWriterInfo);
    }

    void internalSetMeasureConfig(MeasureConfigDto config)
    {
        mMeasureConfig = config;

        mpSetting->setValue(mMeasureCfgChuckRunDelayTimeKey           , mMeasureConfig.mChuckRunDelayTime      );
        mpSetting->setValue(mMeasureCfgValveRunDelayTimeKey           , mMeasureConfig.mValveRunDelayTime      );
        mpSetting->setValue(mMeasureCfgVoltageSetDelayTimeKey         , mMeasureConfig.mVoltageSetDelayTime    );
        mpSetting->setValue(mMeasureCfgNonLoadMeasureDelayTimeKey     , mMeasureConfig.mNonLoadMeasureDelayTime);
        mpSetting->setValue(mMeasureCfgLoadMeasureDelayTimeKey        , mMeasureConfig.mLoadMeasureDelayTime   );
        mpSetting->setValue(mMeasureCfgMeasureAvgRangeKey             , mMeasureConfig.mMeasureAvgRange        );
        mpSetting->setValue(mMeasureCfgKgfcmGainKey                   , mMeasureConfig.mKgfcmGain              );
        mpSetting->setValue(mMeasureCfgIsRtAdjVoltageKey              , mMeasureConfig.mIsRtAdjVoltage         );

        for(int i = 0; i < mPDSettingList.size(); i ++)
        {
            PDSettingDto pdSetting = mPDSettingList[i];

            pdSetting.mVoltage = pRpmSP->convertBaseVoltage(pdSetting.mLoadNM, mMeasureConfig.mKgfcmGain);

            qDebug() << "[debug][internalSetMeasureConfig] pdNum = " << pdSetting.mPDNum << ", RatedRPM = " << pdSetting.mRatedRPM << ", LoadKgfcm = " << pdSetting.mLoadNM << ", gain = " << mMeasureConfig.mKgfcmGain << ", voltage = " << pdSetting.mVoltage;

            internalEditPDSetting(pdSetting.mPDNum, pdSetting);

            if(mCurrPDSetting.mPDNum == pdSetting.mPDNum)
            {
                mCurrPDSetting = pdSetting;
            }
        }
    }

    void internalSetLastUSBSaveDate(int year, int month)
    {
        mLastUSBSaveYear  = year;
        mLastUSBSaveMonth = month;

        mpSetting->setValue(mLastUSBSaveYearKey , mLastUSBSaveYear );
        mpSetting->setValue(mLastUSBSaveMonthKey, mLastUSBSaveMonth);
    }

    void internalSetCommInfo(CommInfoDto dto)
    {
        mCommInfo = dto;

        mpSetting->setValue(mCommInfoIpKey, dto.mIp  );
        mpSetting->setValue(mCommInfoPortKey , dto.mPort   );
    }

    void internalSetWriterInfo(ReportWriterInfoDto info)
    {
        mWriterInfo = info;

        mpSetting->setValue(mWriterInfoSaveDateKey  , info.mSaveDate);
        mpSetting->setValue(mWriterInfoWriterKey    , info.mWriter  );
        mpSetting->setValue(mWriterInfoYearKey      , info.mYear    );
        mpSetting->setValue(mWriterInfoMonthKey     , info.mMonth   );
        mpSetting->setValue(mWriterInfoDayKey       , info.mDay     );
    }

    QString internalEditPDSetting(QString oldPdNum, PDSettingDto newSetting)
    {
        if(newSetting.mPDNum.length() < 1)
            return "제품번호를 입력해 주세요";

        for(int i = 0; i < mPDSettingList.size(); i ++)
        {
            PDSettingDto pdSetting = mPDSettingList[i];

            if(pdSetting.mPDNum == newSetting.mPDNum && oldPdNum != newSetting.mPDNum)
            {
                return "같은 제품번호가 이미 존재합니다.";
            }
        }

        for(int i = 0; i < mPDSettingList.size(); i ++)
        {
            PDSettingDto pdSetting = mPDSettingList[i];

            if(pdSetting.mPDNum == oldPdNum)
            {
                mPDSettingList.replace(i, newSetting);

                removeSettingByNum(oldPdNum);

                mpSetting->setValue(mSettingPDModelKey.arg(newSetting.mPDNum)                , newSetting.mModel                  );
                mpSetting->setValue(mSettingPDNameKey.arg(newSetting.mPDNum)                 , newSetting.mPDName                 );
                mpSetting->setValue(mSettingNonLoadMeasureTimeKey.arg(newSetting.mPDNum)     , newSetting.mNonLoadMeasureTime     );
                mpSetting->setValue(mSettingLoadMeasureTimeKey.arg(newSetting.mPDNum)        , newSetting.mLoadMeasureTime        );
                mpSetting->setValue(mSettingNonLoadConditionFromKey.arg(newSetting.mPDNum)   , newSetting.mNonLoadConditionFrom   );
                mpSetting->setValue(mSettingNonLoadConditionToKey.arg(newSetting.mPDNum)     , newSetting.mNonLoadConditionTo     );
                mpSetting->setValue(mSettingLoadConditionKey.arg(newSetting.mPDNum)          , newSetting.mLoadCondition          );
                mpSetting->setValue(mSettingRatedRPMKey.arg(newSetting.mPDNum)               , newSetting.mRatedRPM               );
                mpSetting->setValue(mSettingLoadNMKey.arg(newSetting.mPDNum)                 , newSetting.mLoadNM                 );

                return  "";
            }
        }

        return "존재하지 않는 제품입니다.";
    }

    QString internalSelectPDSetting(QString pdNum)
    {
        for(int i = 0; i < mPDSettingList.size(); i ++)
        {
            PDSettingDto pdSetting = mPDSettingList[i];

            if(pdSetting.mPDNum == pdNum)
            {
                mCurrPDSetting = pdSetting;
                mpSetting->setValue(mSettingSelectPDNumKey, pdNum);
                return  "";
            }
        }
        return "존재하지 않는 제품입니다.";
    }

    QString internalAddPDSetting(PDSettingDto newSetting)
    {
        if(newSetting.mPDNum.length() < 1)
            return "제품번호를 입력해 주세요";

        for(int i = 0; i < mPDSettingList.size(); i ++)
        {
            PDSettingDto pdSetting = mPDSettingList[i];

            if(pdSetting.mPDNum == newSetting.mPDNum)
            {
                return  "같은 제품번호가 이미 존재합니다.";
            }
        }

        mPDSettingList.append(newSetting);

        mpSetting->setValue(mSettingPDModelKey.arg(newSetting.mPDNum)                , newSetting.mModel                  );
        mpSetting->setValue(mSettingPDNameKey.arg(newSetting.mPDNum)                 , newSetting.mPDName                 );
        mpSetting->setValue(mSettingNonLoadMeasureTimeKey.arg(newSetting.mPDNum)     , newSetting.mNonLoadMeasureTime     );
        mpSetting->setValue(mSettingLoadMeasureTimeKey.arg(newSetting.mPDNum)        , newSetting.mLoadMeasureTime        );
        mpSetting->setValue(mSettingNonLoadConditionFromKey.arg(newSetting.mPDNum)   , newSetting.mNonLoadConditionFrom   );
        mpSetting->setValue(mSettingNonLoadConditionToKey.arg(newSetting.mPDNum)     , newSetting.mNonLoadConditionTo     );
        mpSetting->setValue(mSettingLoadConditionKey.arg(newSetting.mPDNum)          , newSetting.mLoadCondition          );
        mpSetting->setValue(mSettingLoadNMKey.arg(newSetting.mPDNum)                 , newSetting.mLoadNM                 );
        mpSetting->setValue(mSettingRatedRPMKey.arg(newSetting.mPDNum)               , newSetting.mRatedRPM               );

        return "";
    }

    QString internalDeletePDSetting(QString pdNum)
    {
        for(int i = 0; i < mPDSettingList.size(); i ++)
        {
            PDSettingDto pdSetting = mPDSettingList[i];

            if(pdSetting.mPDNum == pdNum)
            {
                mPDSettingList.removeAt(i);

                removeSettingByNum(pdNum);
                return  "";
            }
        }

        return "존재하지 않는 제품입니다.";
    }


signals:
    void signalEventStarted        ();
    void signalEventStopped        ();

    void signalEventChangedLastUSBSaveDate(int year, int month);
    void signalEventChangedCommInfo(CommInfoDto dto);
    void signalEventChangedMeasureCfg(MeasureConfigDto dto);
    void signalEventChangedWriterInfo(ReportWriterInfoDto dto);
    void signalEventChangedPDSetting(QString oldPdNum, QString oldPdName, PDSettingDto dto);
    void signalEventAddedPDSetting(PDSettingDto dto);
    void signalEventDeletedPDSetting(QString pdNum, QString oldPdName);
    void signalEventChangedSelectPDSetting(PDSettingDto dto);

private:
    void removeSettingByNum(QString settingNum)
    {
        QStringList keyList = mpSetting->allKeys();
        foreach(QString key, keyList)
        {
            if(key.startsWith(QString("setting_%1").arg(settingNum)))
            {
                mpSetting->remove(key);
            }
        }
    }
};
#endif // LOCALSETTINGSPROVIDER_H
