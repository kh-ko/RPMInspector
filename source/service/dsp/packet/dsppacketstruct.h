#ifndef DSPPACKETSTRUCT_H
#define DSPPACKETSTRUCT_H
#define DSP_FUNCCODE_MULTIBLOCK_READ  101
#define DSP_FUNCCODE_MULTIBLOCK_WRITE 102
#define DSP_FUNCCODE_MULTIBLOCK_NOTI  103
#define DSP_MODBUS_TCP_UNIT_ID        1
#define DSP_MODBUS_TCP_PROTOCOL_ID    0

#define DSP_GROUP_ID_COMMAND          1
#define DSP_GROUP_ID_SETTING          2
#define DSP_GROUP_ID_STATUS           3

#define DSP_COMMANDBLOCK_STARTADDR_CHUCK_ON            ((quint64)((char *)(&(((StDspCommand *)(0x00))->mChuckOn  ))))/2
#define DSP_COMMANDBLOCK_STARTADDR_VALVE_ON            ((quint64)((char *)(&(((StDspCommand *)(0x00))->mValveOn  ))))/2
#define DSP_COMMANDBLOCK_STARTADDR_VOLTAGE             ((quint64)((char *)(&(((StDspCommand *)(0x00))->mVoltage  ))))/2


#pragma pack(push, 1)
struct StMBAPHeader{
    unsigned short mTransactionID;
    unsigned short mProtocolID   = DSP_MODBUS_TCP_PROTOCOL_ID;
    unsigned short mLength       ;       // byte length

};
struct StDspBlock{
    char           mStartAddr=0;
    char           mGroupID  ;
    unsigned short mWordLen  ;
};
struct StDspPacket{
    StMBAPHeader      mMBAP      ;
    char              mUnitID    = DSP_MODBUS_TCP_UNIT_ID;
    char              mFuncCode  ;
    char              mNumOfBlock;
    unsigned short    mData[0]   ;
};

struct StDspCommand{
    unsigned short mChuckOn      ;
    unsigned short mValveOn      ;
             int   mVoltage      ;
};

struct StDspStatus{
    unsigned short mChuckOn     ;
    unsigned short mValveOn     ;
    int            mVoltage     ;
    int            mCurrRPM     ;
    int            mCycleCnt    ;
    unsigned short mAlarm       ;
};
#pragma pack(pop)
#endif // DSPPACKETSTRUCT_H
