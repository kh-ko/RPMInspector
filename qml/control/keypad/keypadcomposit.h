#ifndef KEYPADCOMPOSIT_H
#define KEYPADCOMPOSIT_H

#include <QObject>

class KeypadComposit : public QObject
{
    Q_OBJECT

public:

    explicit KeypadComposit(QObject *parent = nullptr): QObject(parent)
    {
        mIndexConsonant.append("ㄱ");  mIndexConsonant.append("ㄲ");mIndexConsonant.append("ㄴ");mIndexConsonant.append("ㄷ");mIndexConsonant.append("ㄸ");
        mIndexConsonant.append("ㄹ");  mIndexConsonant.append("ㅁ");mIndexConsonant.append("ㅂ");mIndexConsonant.append("ㅃ");mIndexConsonant.append("ㅅ");
        mIndexConsonant.append("ㅆ");  mIndexConsonant.append("ㅇ");mIndexConsonant.append("ㅈ");mIndexConsonant.append("ㅉ");mIndexConsonant.append("ㅊ");
        mIndexConsonant.append("ㅋ");  mIndexConsonant.append("ㅌ");mIndexConsonant.append("ㅍ");mIndexConsonant.append("ㅎ");
        mIndexConsonant.append("ㄱㅅ"); mIndexConsonant.append("ㄴㅈ");mIndexConsonant.append("ㄴㅎ");mIndexConsonant.append("ㄹㄱ"); mIndexConsonant.append("ㄹㅁ");
        mIndexConsonant.append("ㄹㅂ"); mIndexConsonant.append("ㄹㅅ");mIndexConsonant.append("ㄹㅌ");mIndexConsonant.append("ㄹㅍ"); mIndexConsonant.append("ㄹㅎ");
        mIndexConsonant.append("ㅂㅅ");


        mIndexCho.append("ㄱ");mIndexCho.append("ㄲ");mIndexCho.append("ㄴ");mIndexCho.append("ㄷ");mIndexCho.append("ㄸ");
        mIndexCho.append("ㄹ");mIndexCho.append("ㅁ");mIndexCho.append("ㅂ");mIndexCho.append("ㅃ");mIndexCho.append("ㅅ");
        mIndexCho.append("ㅆ");mIndexCho.append("ㅇ");mIndexCho.append("ㅈ");mIndexCho.append("ㅉ");mIndexCho.append("ㅊ");
        mIndexCho.append("ㅋ");mIndexCho.append("ㅌ");mIndexCho.append("ㅍ");mIndexCho.append("ㅎ");

        mIndexJung.append("ㅏ"  );mIndexJung.append("ㅐ" );mIndexJung.append("ㅑ");mIndexJung.append("ㅒ");mIndexJung.append("ㅓ");
        mIndexJung.append("ㅔ"  );mIndexJung.append("ㅕ" );mIndexJung.append("ㅖ");mIndexJung.append("ㅗ");mIndexJung.append("ㅗㅏ");
        mIndexJung.append("ㅗㅐ");mIndexJung.append("ㅗㅣ");mIndexJung.append("ㅛ");mIndexJung.append("ㅜ");mIndexJung.append("ㅜㅓ");
        mIndexJung.append("ㅜㅔ");mIndexJung.append("ㅜㅣ");mIndexJung.append("ㅠ");mIndexJung.append("ㅡ");mIndexJung.append("ㅡㅣ");
        mIndexJung.append("ㅣ");

        mIndexJong.append(""); mIndexJong.append("ㄱ");mIndexJong.append("ㄲ");mIndexJong.append("ㄱㅅ");mIndexJong.append("ㄴ");
        mIndexJong.append("ㄴㅈ");mIndexJong.append("ㄴㅎ");mIndexJong.append("ㄷ");mIndexJong.append("ㄹ");mIndexJong.append("ㄹㄱ");
        mIndexJong.append("ㄹㅁ");mIndexJong.append("ㄹㅂ");mIndexJong.append("ㄹㅅ");mIndexJong.append("ㄹㅌ");mIndexJong.append("ㄹㅍ");
        mIndexJong.append("ㄹㅎ");mIndexJong.append("ㅁ");mIndexJong.append("ㅂ");mIndexJong.append("ㅂㅅ");mIndexJong.append("ㅅ");
        mIndexJong.append("ㅆ");mIndexJong.append("ㅇ");mIndexJong.append("ㅈ");mIndexJong.append("ㅊ");mIndexJong.append("ㅋ");
        mIndexJong.append("ㅌ");mIndexJong.append("ㅍ");mIndexJong.append("ㅎ");
    }
    ~KeypadComposit(){}

    bool isProc()
    {
        return mInputList.size() > 0 ? true : false;
    }

    bool checkHangle(QString key)
    {
        foreach(QString value, mIndexConsonant)
        {
            if(value == key)
                return true;
        }

        foreach(QString value, mIndexJung)
        {
            if(value == key)
                return true;
        }

        return false;
    }

    QString insert(QString key)
    {
        QString lastKey;

        if(mInputList.size() == 0)
        {
            mInputList.append(key);
            return "";
        }

        lastKey = getLastKey();

        if(isConsonantHangle(lastKey) && isConsonantHangle(key)) // 자음 + 자음
        {
            if(mInputList.size() > 1 && isConsonantHangle(mInputList.at(mInputList.size() - 2))) // 자음 + 자음 + 자음
            {
                QString completed;
                completed = buildComposit();
                mInputList.clear();
                mInputList.append(key);
                return completed;
            }
            else if(isConsonantHangle(lastKey + key) == false)
            {
                QString completed;
                completed = buildComposit();
                mInputList.clear();
                mInputList.append(key);
                return completed;
            }
        }
        else if(isConsonantHangle(lastKey) && isVowelHangle(key))  // 자음 + 모음
        {
            QString completed;
            mInputList.removeLast();
            completed = buildComposit();
            mInputList.clear();
            mInputList.append(lastKey);
            mInputList.append(key);
            return completed;
        }
        else if(isVowelHangle(lastKey) && isConsonantHangle(key))  // 모음 + 자음
        {
            if(isVowelHangle(mInputList.first())) // 모음 + 모음 + 자음
            {
                QString completed;
                completed = buildComposit();
                mInputList.clear();
                mInputList.append(key);
                return completed;
            }
        }
        else if(isVowelHangle(lastKey) && isVowelHangle(key))  // 모음 + 모음
        {
            if(mInputList.size() > 1 && isVowelHangle(mInputList.at(mInputList.size() - 2))) // 모음 + 모음 + 모음
            {
                QString completed;
                completed = buildComposit();
                mInputList.clear();
                mInputList.append(key);
                return completed;
            }
            else if(isVowelHangle(lastKey + key) == false)
            {
                QString completed;
                completed = buildComposit();
                mInputList.clear();
                mInputList.append(key);
                return completed;
            }
        }

        mInputList.append(key);

        return "";
    }

    void del()
    {
        if(mInputList.size() > 0)
        {
            mInputList.removeLast();
        }
    }

    QString release()
    {
        QString composit = buildComposit();

        mInputList.clear();

        return composit;
    }

    QString buildComposit()
    {
        QString inputCho  = "";
        QString inputJung = "";
        QString inputJong = "";

        foreach(QString temp, mInputList)
        {
            if(isConsonantHangle(inputCho + temp) && inputJung == "")
            {
                inputCho = inputCho + temp;
            }
            if(isVowelHangle(inputJung + temp) && inputJong == "")
            {
                inputJung = inputJung + temp;
            }
            if(isConsonantHangle(inputJong + temp) && inputJung != "")
            {
                inputJong = inputJong + temp;
            }
        }

        if(inputCho != "" && inputJung != "")
        {
            int iIdx = 0;
            int mIdx = 0;
            int tIdx = 0;

            for(iIdx = 0; iIdx < mIndexCho.size(); iIdx ++)
            {
                if(inputCho == mIndexCho.at(iIdx))
                    break;
            }

            for(mIdx = 0; mIdx < mIndexJung.size(); mIdx ++)
            {
                if(inputJung == mIndexJung.at(mIdx))
                    break;
            }

            for(tIdx = 0; tIdx < mIndexJong.size(); tIdx ++)
            {
                if(inputJong == mIndexJong.at(tIdx))
                    break;
            }

            QChar composit = 0xAC00 + ((iIdx * 21) + mIdx) *28 + tIdx;

            return QString(composit);
        }
        else
        {
            if     (inputCho  == "ㄱㅅ") return "ㄳ";
            else if(inputCho  == "ㄴㅈ") return "ㄵ";
            else if(inputCho  == "ㄴㅎ") return "ㄵ";
            else if(inputCho  == "ㄹㄱ") return "ㄺ";
            else if(inputCho  == "ㄹㅁ") return "ㄻ";
            else if(inputCho  == "ㄹㅂ") return "ㄼ";
            else if(inputCho  == "ㄹㅅ") return "ㄽ";
            else if(inputCho  == "ㄹㅌ") return "ㄾ";
            else if(inputCho  == "ㄹㅍ") return "ㄿ";
            else if(inputCho  == "ㄹㅎ") return "ㅀ";
            else if(inputCho  == "ㅂㅅ") return "ㅄ";
            else if(inputCho  != ""    ) return inputCho;
            else if(inputJung == "ㅗㅏ") return "ㅘ";
            else if(inputJung == "ㅗㅐ") return "ㅙ";
            else if(inputJung == "ㅗㅣ") return "ㅚ";
            else if(inputJung == "ㅜㅓ") return "ㅝ";
            else if(inputJung == "ㅜㅔ") return "ㅞ";
            else if(inputJung == "ㅜㅣ") return "ㅟ";
            else if(inputJung == "ㅡㅣ") return "ㅢ";
            else if(inputJung != ""    ) return inputJung;
            else
            {
                return "";
            }
        }
    }


private:
    //초성 19자
    QList<QString> mIndexCho;
    QList<QString> mIndexJung;
    QList<QString> mIndexJong;
    QList<QString> mIndexConsonant;
    QList<QString> mIndexVowel;

    QList<QString> mInputList;

    QString getLastKey()
    {
        if(mInputList.size() > 0)
            return mInputList.at(mInputList.size() - 1);

        return "";
    }

    bool isConsonantHangle(QString key)
    {
        foreach(QString value, mIndexConsonant)
        {
            if(value == key)
                return true;
        }
        return false;
    }

    bool isVowelHangle(QString key)
    {
        foreach(QString value, mIndexJung)
        {
            if(value == key)
                return true;
        }
        return false;
    }

    bool isCho(QString key)
    {
        foreach(QString value, mIndexCho)
        {
            if(value == key)
                return true;
        }
        return false;
    }

    bool isJong(QString key)
    {
        foreach(QString value, mIndexJong)
        {
            if(value == key)
                return true;
        }
        return false;
    }

};
#endif // KEYPADCOMPOSIT_H
