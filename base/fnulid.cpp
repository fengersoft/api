#include "fnulid.h"



QString createULID()
{
    // 获取当前时间的时间戳
    std::chrono::time_point now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::microseconds>(now);
    auto epoch = now_ms.time_since_epoch();
    long long timestamp = std::chrono::duration_cast<std::chrono::microseconds>(epoch).count();
    // // 生成随机部分
    return QString::number(timestamp) % "-" % QUuid::createUuid().toString(QUuid::WithoutBraces);
}

QString createULIDV2()
{
    // 获取当前时间的时间戳
    std::chrono::time_point now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::microseconds>(now);
    auto epoch = now_ms.time_since_epoch();
    long long timestamp = std::chrono::duration_cast<std::chrono::microseconds>(epoch).count();
    // // 生成随机部分
    QString uuid(16, '\0');

    static QChar nums[10] {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    srand(time(0));
    for (int i = 0; i < 16; i++)
    {
        int k = rand() % 10;
        uuid[i] = nums[k];
    }
    return QString::number(timestamp) % "-" % uuid;

}
