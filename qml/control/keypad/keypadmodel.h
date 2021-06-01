#ifndef KEYPADMODEL_H
#define KEYPADMODEL_H

#include <QObject>
#include "qml/control/keypad/keypadcomposit.h"

class KeypadModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int     mSelectStart READ getSelectStart )
    Q_PROPERTY(int     mSelectEnd   READ getSelectEnd   )
    Q_PROPERTY(QString mDpText      READ getDpText      )

public:
    int     getSelectStart(){ return mSelectStart;}
    int     getSelectEnd  (){ return mSelectEnd  ;}
    QString getDpText     (){ return mDpText     ;}

    explicit KeypadModel(QObject *parent = nullptr): QObject(parent)
    {

    }
    ~KeypadModel(){}

signals:
    void signalEventChangedComposit(QString value);
    void signalEventCompletedInput(QString value);

public slots:
    Q_INVOKABLE void onCommandSetText(QString text)
    {
        mComposit.release();

        mText = text;
        mDpText = text;

        setSelection(0, text.size());
    }

    Q_INVOKABLE void onCommandDelKey(int selStart, int selEnd)
    {
        if(isChangeSelection(selStart, selEnd))
        {
            if(mComposit.isProc())
            {
                inputKey(mComposit.release());
            }

            setSelection(selStart, selEnd);
            deleteKey();
        }
        else
        {
            if(mComposit.isProc())
            {
                mComposit.del();

                if(mComposit.isProc() == false)
                {
                    setSelection(selStart, selStart);
                }
            }
            else
            {
                setSelection(selStart, selEnd);
                deleteKey();
            }
        }

        buildDpText();
    }

    Q_INVOKABLE void onCommandInputKey(int selStart, int selEnd, QString key)
    {
        if(isChangeSelection(selStart, selEnd))
        {
            if(mComposit.isProc())
            {
                inputKey(mComposit.release());
            }

            setSelection(selStart, selEnd);

            if(selStart != selEnd)
                deleteKey();
        }
        else
        {
            setSelection(selStart, selEnd);

            if(mComposit.isProc() == false)
            {
                if(selStart != selEnd)
                    deleteKey();
            }
        }

        if(mComposit.checkHangle(key))
        {
            QString releaseComposit = mComposit.insert(key);

            if(releaseComposit.size() > 0)
                inputKey(releaseComposit);

            if(mComposit.isProc())
            {
                setSelection(mSelectStart, mSelectStart+1);
            }
        }
        else
        {
            if(mComposit.isProc())
            {
                inputKey(mComposit.release());
            }
            inputKey(key);
        }

        buildDpText();
    }
private:
    KeypadComposit mComposit;
    QString        mText   = "";
    QString        mDpText = "";
    int            mSelectStart = 0;
    int            mSelectEnd   = 0;

    bool isChangeSelection(int selStart, int selEnd)
    {
        return (mSelectStart != selStart || mSelectEnd != selEnd) ? true : false;
    }

    void setSelection(int selStart, int selEnd)
    {
        mSelectStart = selStart;
        mSelectEnd = selEnd;
    }


    void inputKey(QString key)
    {
        mText = mText.left(mSelectStart) + key + mText.mid(mSelectStart);

        setSelection(mSelectStart + 1, mSelectStart + 1);
    }

    void deleteKey()
    {
        if(mSelectStart < mSelectEnd)
        {
            mText = mText.left(mSelectStart) + mText.mid(mSelectEnd);
            setSelection(mSelectStart, mSelectStart);
        }
        else if(mSelectStart > 0)
        {
            mText = mText.left(mSelectStart - 1) + mText.mid(mSelectStart);
            setSelection(mSelectStart - 1, mSelectStart - 1);
        }
    }

    void buildDpText()
    {
        if(mComposit.isProc())
            mDpText = mText.left(mSelectStart) + mComposit.buildComposit() + mText.mid(mSelectStart);
        else
            mDpText = mText;
    }
};
#endif // KEYPADMODEL_H
