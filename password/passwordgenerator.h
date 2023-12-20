#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H

#include <QObject>
#include <QRandomGenerator>

class PassWordGenerator : public QObject
{
    Q_OBJECT
public:
    explicit PassWordGenerator(QObject *parent = nullptr);

    bool includeLowerLetter() const;
    void setIncludeLowerLetter(bool newIncludeLowerLetter);

    bool includeUpperLetter() const;
    void setIncludeUpperLetter(bool newIncludeUpperLetter);

    bool includeNumber() const;

    void setIncludeNumber(bool newIncludeNumber);
    QString newPassWord();

    int passWordLength() const;
    void setPassWordLength(int newPassWordLength);

signals:
private:
    bool m_includeLowerLetter;
    bool m_includeUpperLetter;
    bool m_includeNumber;
    bool m_includeSpecialLetter;
    int m_passWordLength;
    QStringList m_uperLetters;
    QStringList m_lowerLetters;
    QStringList m_numbers;
    QStringList m_specialLetters;

};
QString generatorNewPassWord();

#endif // PASSWORDGENERATOR_H
