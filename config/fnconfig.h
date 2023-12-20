#ifndef FNCONFIG_H
#define FNCONFIG_H
#include <QObject>
#include <QSettings>
#include <QApplication>
#include <QDebug>
#include <QString>

template<typename T>
inline void readValueFromConfig(QString key, T& value, T defaultValue)
{
    QSettings ini(QApplication::applicationDirPath() + "/configs/config.ini", QSettings::IniFormat);
    ini.beginGroup("set");

    bool ret;
    ret = ini.value(key, defaultValue).toBool();
    value = ret;
    ini.endGroup();
}
template<>
inline void readValueFromConfig(QString key, QString& value, QString defaultValue)
{
    QSettings ini(QApplication::applicationDirPath() + "/configs/config.ini", QSettings::IniFormat);
    ini.beginGroup("set");

    value = ini.value(key, defaultValue).toString();

    ini.endGroup();
}
template<>
inline void readValueFromConfig(QString key, int& value, int defaultValue)
{
    QSettings ini(QApplication::applicationDirPath() + "/configs/config.ini", QSettings::IniFormat);
    ini.beginGroup("set");

    value = ini.value(key, defaultValue).toInt();

    ini.endGroup();
}


template<typename T>
void writeValuetoConfig(QString key, T value)
{
    QSettings ini(QApplication::applicationDirPath() + "/configs/config.ini", QSettings::IniFormat);
    ini.beginGroup("set");
    ini.setValue(key, value);
    ini.endGroup();
}

#endif // FNCONFIG_H
