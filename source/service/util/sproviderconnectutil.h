#ifndef SPROVIDERCONNECTUTIL_H
#define SPROVIDERCONNECTUTIL_H

#define ENABLE_SLOT_CORE_START                         connect(CoreService::getInstance()          , SIGNAL(signalEventStarted()                                       ), this, SLOT(onStartedCoreService()                            ))
#define ENABLE_SLOT_CORE_STOP                          connect(CoreService::getInstance()          , SIGNAL(signalEventStopped()                                       ), this, SLOT(onStoppedCoreService()                            ))

#define ENABLE_SLOT_LSETTING_START                     connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventStarted()                                       ), this, SLOT(onStartedLocalSettingSProvider()                  ))
#define ENABLE_SLOT_LSETTING_STOP                      connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventStopped()                                       ), this, SLOT(onStoppedLocalSettingSProvider()                  ))
#define ENABLE_SLOT_LSETTING_CHANGED_COMM_INFO         connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedCommInfo(CommInfoDto)                    ), this, SLOT(onChangedCommInfo(CommInfoDto)                    ))
#define ENABLE_SLOT_LSETTING_CHANGED_MEASURE_CFG       connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedMeasureCfg(MeasureConfigDto)             ), this, SLOT(onChangedMeasureCfg(MeasureConfigDto)             ))
#define ENABLE_SLOT_LSETTING_CHANGED_WRITER_INFO       connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedWriterInfo(ReportWriterInfoDto)          ), this, SLOT(onChangedWriterInfo(ReportWriterInfoDto)          ))
#define ENABLE_SLOT_LSETTING_CHANGED_PDSETTING         connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedPDSetting(QString, QString, PDSettingDto)), this, SLOT(onChangedPDSetting(QString, QString, PDSettingDto)))
#define ENABLE_SLOT_LSETTING_ADDED_PDSETTING           connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventAddedPDSetting(PDSettingDto)                    ), this, SLOT(onAddedPDSetting(PDSettingDto)                    ))
#define ENABLE_SLOT_LSETTING_DELETED_PDSETTING         connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventDeletedPDSetting(QString, QString)              ), this, SLOT(onDeletedPDSetting(QString, QString)              ))
#define ENABLE_SLOT_LSETTING_CHANGED_SEL_PDSETTING     connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedSelectPDSetting(PDSettingDto)            ), this, SLOT(onChangedSelectPDSetting(PDSettingDto)            ))
#define ENABLE_SLOT_LSETTING_CHANGED_LAST_USBSAVE_DATE connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedLastUSBSaveDate(int, int)                ), this, SLOT(onChangedLastUSBSaveDate(int, int)                ))

#define ENABLE_SLOT_DSP_START                      connect(DspSProvider::getInstance()         , SIGNAL(signalEventStarted()                              ), this, SLOT(onStartedDspSProvider()                  ))
#define ENABLE_SLOT_DSP_STOP                       connect(DspSProvider::getInstance()         , SIGNAL(signalEventStopped()                              ), this, SLOT(onStoppedDspSProvider()                  ))
#define ENABLE_SLOT_DSP_CHANGED_IS_CONNECT         connect(DspSProvider::getInstance()         , SIGNAL(signalEventChangedIsConnect(bool)                 ), this, SLOT(onChangedDspIsConnect(bool)              ))
#define ENABLE_SLOT_DSP_CHANGED_STATUS             connect(DspSProvider::getInstance()         , SIGNAL(signalEventChangedStatus (qint64, DspStatusDto )  ), this, SLOT(onChangedDspStatus(qint64, DspStatusDto )))

#define ENABLE_SLOT_TIMER_START                    connect(TimerSProvider::getInstance()       , SIGNAL(signalEventStarted()                              ), this, SLOT(onStartedTimerSProvider()                ))
#define ENABLE_SLOT_TIMER_STOP                     connect(TimerSProvider::getInstance()       , SIGNAL(signalEventStopped()                              ), this, SLOT(onStoppedTimerSProvider()                ))
#define ENABLE_SLOT_TIMER_TICK                     connect(TimerSProvider::getInstance()       , SIGNAL(signalTimeTick(QDateTime)                         ), this, SLOT(onTimeTick(QDateTime)                    ))

#endif // SPROVIDERCONNECTUTIL_H
