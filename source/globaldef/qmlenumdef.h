#ifndef ENUMDEFINE_H
#define ENUMDEFINE_H

#include <QObject>
class QmlEnumDef: public QObject{
  Q_OBJECT
  Q_ENUMS(VInputMode)
  Q_ENUMS(MsgBoxType)
  Q_ENUMS(NumberKeypadType)
  Q_ENUMS(MsgBoxResult)
  Q_ENUMS(MeasureState)
  Q_ENUMS(JudgState)
  Q_ENUMS(USBSaveStep)
  Q_ENUMS(AutoStep)

public:
  enum VInputMode{
      INT_MODE                    = 0,
      FLOAT_MODE                  = 1,
      PASSWD_MODE                 = 2,
      STRING_MODE                 = 3,
      IP_MODE                     = 4,
  };

   enum MsgBoxType{
       MSGBOX_TYPE_CONFIRM        = 0,
       MSGBOX_TYPE_YES_OR_NO      = 1,
   };

   enum NumberKeypadType{
       NUMBER_KEYPAD_TYPE_INT     = 0,
       NUMBER_KEYPAD_TYPE_FLOAT   = 1,
   };

   enum MsgBoxResult{
       MSGBOX_RESULT_CONFIRM      = 0,
       MSGBOX_RESULT_YES          = 1,
       MSGBOX_RESULT_NO           = 2
   };

   enum MeasureState{
       MEASURE_STATE_NONE    = 0,
       MEASURE_STATE_NONLOAD = 1,
       MEASURE_STATE_LOAD    = 2,
   };

   enum AutoStep{
       AUTOSTEP_NONE        = 0,
       AUTOSTEP_READY       = 1,
       AUTOSTEP_CHUCK       = 2,
       AUTOSTEP_AIR         = 3,
       AUTOSTEP_LOAD        = 4,
       AUTOSTEP_NONLOAD     = 5
   };

   enum JudgState{
       JUDG_STATE_NONE = 0,
       JUDG_STATE_ING  = 1,
       JUDG_STATE_FAIL = 2,
       JUDG_STATE_SUCC = 3
   };
   enum USBSaveStep{
       USBSAVE_STEP_NONE             = 0,
       USBSAVE_STEP_SCAN             = 1,
       USBSAVE_STEP_COPY             = 2,
       USBSAVE_STEP_COMPLETE         = 3
   };
};

#endif // ENUMDEFINE_H
