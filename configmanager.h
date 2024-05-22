#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QList>

class ConfigManager
{
private:
    void createConfigFile();
    void openClearFile();
    void readConfigFromFile();
    int getNewDefaultIndex(int deleteIndex);
    QFile* configFile;
    QJsonDocument jsonDoc;
    QString configFilename = "config.json";

public:
    class Config
    {
    public:
        Config(QString name, QString mac,
                      QString host, int port);
        QString name;
        QString mac;
        QString host;
        int port;
    };

    ConfigManager();
    int defaultConfigIndex;
    void init();
    void clearInit();
    void deleteConfig(int index);
    void addConfig(Config newConfig);
    void updateConfig(Config config, int index);
    void setDefaultConfig(int index);
    QVector<Config> *configurations;
};


class ConfigFileHandleException
{
public:
    ConfigFileHandleException(QString message): message(message){}
    QString message;
};

class InvalidConfigException
{
public:
    InvalidConfigException(QString message): message(message){}
    QString message;
};

#endif // CONFIGMANAGER_H
