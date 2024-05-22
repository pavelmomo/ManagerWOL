#ifndef WAKEONLAN_H
#define WAKEONLAN_H

#include <QUdpSocket>
#include "configmanager.h"


class WakeOnLAN
{
private:
    ConfigManager *confManager;
    QUdpSocket *currentSocket;
public:
    WakeOnLAN(ConfigManager *confManager);
    ~WakeOnLAN();
    void wake(int configIndex);
};


class PackageSendException
{
public:
    PackageSendException(QString message): message(message){}
    QString message;
};

#endif // WAKEONLAN_H
