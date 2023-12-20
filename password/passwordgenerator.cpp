#include "passwordgenerator.h"

PassWordGenerator::PassWordGenerator(QObject *parent)
    : QObject{parent}
{
    m_includeLowerLetter=true;
    m_includeUpperLetter=true;
    m_includeNumber=true;
    m_passWordLength=16;
    m_includeSpecialLetter=true;


    m_uperLetters<<"A";
    m_uperLetters<<"B";
    m_uperLetters<<"C";
    m_uperLetters<<"D";
    m_uperLetters<<"E";
    m_uperLetters<<"F";
    m_uperLetters<<"G";
    m_uperLetters<<"H";
    m_uperLetters<<"I";
    m_uperLetters<<"J";
    m_uperLetters<<"K";
    m_uperLetters<<"L";
    m_uperLetters<<"M";
    m_uperLetters<<"N";
    m_uperLetters<<"O";
    m_uperLetters<<"P";
    m_uperLetters<<"Q";
    m_uperLetters<<"R";
    m_uperLetters<<"S";
    m_uperLetters<<"T";
    m_uperLetters<<"U";
    m_uperLetters<<"V";
    m_uperLetters<<"W";
    m_uperLetters<<"X";
    m_uperLetters<<"Y";
    m_uperLetters<<"Z";




    m_lowerLetters<<"a";
    m_lowerLetters<<"b";
    m_lowerLetters<<"c";
    m_lowerLetters<<"d";
    m_lowerLetters<<"e";
    m_lowerLetters<<"f";
    m_lowerLetters<<"g";
    m_lowerLetters<<"h";
    m_lowerLetters<<"i";
    m_lowerLetters<<"j";
    m_lowerLetters<<"k";
    m_lowerLetters<<"l";
    m_lowerLetters<<"m";
    m_lowerLetters<<"n";
    m_lowerLetters<<"o";
    m_lowerLetters<<"p";
    m_lowerLetters<<"q";
    m_lowerLetters<<"r";
    m_lowerLetters<<"s";
    m_lowerLetters<<"t";
    m_lowerLetters<<"u";
    m_lowerLetters<<"v";
    m_lowerLetters<<"w";
    m_lowerLetters<<"x";
    m_lowerLetters<<"y";
    m_lowerLetters<<"z";


    m_numbers<<"0";
    m_numbers<<"1";
    m_numbers<<"2";
    m_numbers<<"3";
    m_numbers<<"4";
    m_numbers<<"5";
    m_numbers<<"6";
    m_numbers<<"7";
    m_numbers<<"8";
    m_numbers<<"9";


    m_specialLetters<<"!";
    m_specialLetters<<"@";
    m_specialLetters<<"#";
    m_specialLetters<<"$";
    m_specialLetters<<"&";
    m_specialLetters<<"_";
    m_specialLetters<<"+";
    m_specialLetters<<"=";
    m_specialLetters<<"-";
    m_specialLetters<<"<";
    m_specialLetters<<">";
    m_specialLetters<<"?";
    m_specialLetters<<"/";

}

bool PassWordGenerator::includeLowerLetter() const
{
    return m_includeLowerLetter;
}

void PassWordGenerator::setIncludeLowerLetter(bool newIncludeLowerLetter)
{
    m_includeLowerLetter = newIncludeLowerLetter;
}

bool PassWordGenerator::includeUpperLetter() const
{
    return m_includeUpperLetter;
}

void PassWordGenerator::setIncludeUpperLetter(bool newIncludeUpperLetter)
{
    m_includeUpperLetter = newIncludeUpperLetter;
}

bool PassWordGenerator::includeNumber() const
{
    return m_includeNumber;
}

void PassWordGenerator::setIncludeNumber(bool newIncludeNumber)
{
    m_includeNumber = newIncludeNumber;
}

QString PassWordGenerator::newPassWord()
{
    QString ret;

    while (ret.length()!=m_passWordLength)
    {
        if ((m_includeUpperLetter) && (QRandomGenerator::global()->bounded(0,1000)%2==0))
        {
            int n=QRandomGenerator::global()->bounded(0,26);
            ret+=m_uperLetters[n];
        }else if ((m_includeLowerLetter) && (QRandomGenerator::global()->bounded(0,100)%2==0))
        {
            int n=QRandomGenerator::global()->bounded(0,26);
            ret+=m_lowerLetters[n];
        }
        else if ((m_includeNumber) && (QRandomGenerator::global()->bounded(0,100)%2==0))
                {
                    int n=QRandomGenerator::global()->bounded(0,10);
                    ret+=m_numbers[n];
                }
        else if ((m_includeSpecialLetter) && (QRandomGenerator::global()->bounded(0,100)%2==0))
                {
                    int n=QRandomGenerator::global()->bounded(0,13);
                    ret+=m_specialLetters[n];
                }
    }


    return ret;

}

int PassWordGenerator::passWordLength() const
{
    return m_passWordLength;
}

void PassWordGenerator::setPassWordLength(int newPassWordLength)
{
    m_passWordLength = newPassWordLength;
}

QString generatorNewPassWord()
{
    PassWordGenerator *g=new PassWordGenerator();
    QString ret=g->newPassWord();

    delete g;
    return ret;
}
