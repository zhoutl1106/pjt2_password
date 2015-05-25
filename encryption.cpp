#include "encryption.h"
#include <QDebug>

/*
 * encry
 * 1. strcat
 * 2. checksum
 * 3. + 7 modulo 10
 * 4. swap
 *
 * return
 *
 * QDate(0,0,0) Code Length err
 * QDate(1,1,1) Checksum err
 * QDate(2,2,2) code mismatch
 * QDate(3,3,3) early date;
 */



int swp[9] = {14,10,12,9,16,17,13,11,15};

Encryption::Encryption(QObject *parent) : QObject(parent)
{

}

Encryption::~Encryption()
{

}

QString Encryption::genPasscode(QString s, QDate dat, QString op)
{
    if(s.length() != 8 || op.length() != 2)
    {
        qDebug()<<s.length()<<op.length();
        return "";
    }
    QString temp = s + dat.toString("yyMMdd")+op;
    char finalString[18];
    short sum = 0;
    for(int i = 0;i<16;i++)
    {
        finalString[i] = temp.toLatin1().at(i) - '0';
        sum += finalString[i];
    }
    finalString[16] = sum/10;
    finalString[17] = sum%10;
    for(int i = 0;i<18;i++)
    {
        finalString[i] = (finalString[i] + 7) % 10;
        finalString[i] += '0';
    }
    for(int i = 0;i<9;i++)
    {
        char temp = finalString[i];
        finalString[i] = finalString[swp[i]];
        finalString[swp[i]] = temp;
    }
    return QString(finalString).mid(0,18);
}

QDate Encryption::checkPasscode(QString s, const QString code, int &op)
{
    if(s.length() != 18)
        return QDate(0,0,0);
    char str[18];
    for(int i = 0;i<18;i++)
        str[i] = s.toLatin1().at(i);
    for(int i = 0;i<9;i++)
    {
        char temp = str[i];
        str[i] = str[swp[i]];
        str[swp[i]] = temp;
    }
    for(int i = 0;i<18;i++)
    {
        str[i] -= '0';
        str[i] = (str[i] + 3) % 10;
    }
    int sum = 0;
    for(int i = 0;i<16;i++)
    {
        sum += str[i];
    }
    int oriSum = str[16]*10 + str[17];
    if(oriSum != sum)
        return QDate(1,1,1);
    op = str[14] * 10 + str[15];
    for(int i = 0;i<8;i++)
        str[i] += '0';
    if(QString(str).mid(0,8).compare(code) != 0)
        return QDate(2,2,2);
    QDate ret = QDate(2000 + str[8]*10+str[9],str[10]*10+str[11],str[12]*10+str[13]);
    if(ret <= QDate::currentDate())
        return QDate(3,3,3);
    return ret;
}
