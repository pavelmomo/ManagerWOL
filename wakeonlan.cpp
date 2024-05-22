#include "wakeonlan.h"
#include <QMessageBox>
#include <QHostAddress>
#include <QUdpSocket>
#include <QNetworkDatagram>

WakeOnLAN::WakeOnLAN(ConfigManager *confManager)
{
    this->confManager = confManager;
    this->currentSocket = new QUdpSocket();
}

void WakeOnLAN::wake(int confgIndex)
{
    ConfigManager::Config currentConfig = confManager->configurations->at(confgIndex);
    currentConfig.mac = currentConfig.mac.replace(":", " ");
    QByteArray magicPacket;
    QByteArray macAddress = QByteArray::fromHex(currentConfig.mac.toUtf8().data());
    for(int i = 0; i < 6; ++i)
    {
        magicPacket.append(0xff);
    }
    for(int i = 0; i < 16; ++i)
    {
        magicPacket.append(macAddress);
    }
    currentSocket->connectToHost(currentConfig.host, currentConfig.port);
    if (currentSocket->write(magicPacket) == -1)
    {
        currentSocket->disconnectFromHost();
        throw PackageSendException("Произошла ошибка при отправке пакета");
    }
    currentSocket->disconnectFromHost();
}

WakeOnLAN::~WakeOnLAN()
{
    delete currentSocket;
}
