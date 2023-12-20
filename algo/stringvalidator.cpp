#include "stringvalidator.h"



bool isEnglish(QString str)
{
   const QByteArray ba = str.toLatin1();
    const char *ch = ba.data();
    while (*ch) {
        if((*ch >= 'A' && *ch <= 'Z')||(*ch >= 'a' && *ch <= 'z')){

        }else {
            return false;
        }

        ch++;
    }

    return true;

}

//判断是否为纯数字
bool isNumber(QString str)
{
  const   QByteArray ba = str.toLatin1();
    const char *ch = ba.data();
    while (*ch) {
        if(*ch >= '0' && *ch <= '9'){

        }else {
            return false;
        }

        ch++;
    }

    return true;
}
//判断是否为纯中文
bool isChinese(QString str)
{
    int count = str.count();

    for(int i = 0; i < count; i++){
        QChar ch = str.at(i);
        ushort us = ch.unicode();
        if(us >= 0x4E00 && us <= 0x9FA5){

        }else {
            return false;
        }

    }

    return true;
}
