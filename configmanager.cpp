#include "configmanager.h"
#include <QMessageBox>

ConfigManager::ConfigManager()
{
    configurations = new QVector<Config>();
    configFile = new QFile();
    configFile->setFileName(configFilename);
}

ConfigManager::Config::Config(QString name, QString mac,
                                                   QString host, int port)
{
    this->name = name;
    this->host = host;
    this->port = port;
    this->mac = mac;
}

void ConfigManager::readConfigFromFile()
{
    configurations->clear();
    QJsonParseError error;
    if(!configFile->open(QIODevice::ReadOnly | QFile::Text))
    {
        createConfigFile();
        if (!configFile->open(QIODevice::ReadOnly | QFile::Text))
        {
            throw ConfigFileHandleException("Ошибка при обращении к файлу конфигурации");
        }
    }
    jsonDoc = QJsonDocument::fromJson(QByteArray(configFile->readAll()),&error);
    configFile->close();
    if (error.error != QJsonParseError::NoError)
    {
        throw InvalidConfigException("Файл конфигурации невалиден");
    }

    defaultConfigIndex = jsonDoc.object().value("default_configuration").toInt();
    QJsonArray fileConfigArr = jsonDoc.object().value("configurations").toArray();
    for (int i = 0; i < fileConfigArr.count(); ++i)
    {
        Config buffer = Config(fileConfigArr.at(i).toObject().value("name").toString(),
                               fileConfigArr.at(i).toObject().value("mac").toString(),
                               fileConfigArr.at(i).toObject().value("host").toString(),
                               fileConfigArr.at(i).toObject().value("port").toInt());
        configurations->append(buffer);
    }
}

void ConfigManager::openClearFile()
{
    if(!configFile->open(QIODevice::ReadWrite | QFile::Text | QFile::Truncate))
    {
        throw ConfigFileHandleException("Ошибка при обращении к файлу конфигурации");
    }
}

void ConfigManager::createConfigFile()
{
    jsonDoc = QJsonDocument();
    QVariantMap mainBuffer;
    mainBuffer.insert("configurations", QJsonArray());
    mainBuffer.insert("default_configuration", QJsonValue::fromVariant(0));
    QJsonObject mainJson = QJsonObject::fromVariantMap(mainBuffer);
    jsonDoc.setObject(mainJson);
    openClearFile();
    configFile->write(jsonDoc.toJson());
    configFile->close();
}

int ConfigManager::getNewDefaultIndex(int deleteIndex)
{
    if (deleteIndex > defaultConfigIndex)
    {
        return defaultConfigIndex;
    }
    else if (deleteIndex == defaultConfigIndex)
    {
        return 0;
    }
    else if (deleteIndex < defaultConfigIndex)
    {
        return defaultConfigIndex - 1;
    }
}

void ConfigManager::deleteConfig(int index)
{
    QJsonArray confArr = jsonDoc.object().value("configurations").toArray();
    confArr.removeAt(index);
    QVariantMap mainBuffer;
    mainBuffer.insert("default_configuration", QJsonValue::fromVariant(getNewDefaultIndex(index)));
    mainBuffer.insert("configurations", confArr);
    QJsonObject mainJson = QJsonObject::fromVariantMap(mainBuffer);
    jsonDoc.setObject(mainJson);
    openClearFile();
    configFile->write(jsonDoc.toJson());
    configFile->close();
    readConfigFromFile();
}
void ConfigManager::addConfig(ConfigManager::Config newConfig)
{
    QJsonArray confArr = jsonDoc.object().value("configurations").toArray();
    QVariantMap newConfigBuffer;
    newConfigBuffer.insert("name",QJsonValue::fromVariant(newConfig.name));
    newConfigBuffer.insert("mac",QJsonValue::fromVariant(newConfig.mac));
    newConfigBuffer.insert("host",QJsonValue::fromVariant(newConfig.host));
    newConfigBuffer.insert("port",QJsonValue::fromVariant(newConfig.port));
    QJsonObject newConfigJson = QJsonObject::fromVariantMap(newConfigBuffer);
    confArr.append(newConfigJson);
    QVariantMap mainBuffer;
    mainBuffer.insert("default_configuration", QJsonValue::fromVariant(defaultConfigIndex));
    mainBuffer.insert("configurations", confArr);
    QJsonObject mainJson = QJsonObject::fromVariantMap(mainBuffer);
    jsonDoc.setObject(mainJson);
    openClearFile();
    configFile->write(jsonDoc.toJson());
    configFile->close();
    readConfigFromFile();
}

void ConfigManager::updateConfig(Config config, int index)
{
    QJsonArray confArr = jsonDoc.object().value("configurations").toArray();
    confArr.removeAt(index);
    QVariantMap configBuffer;
    configBuffer.insert("name",QJsonValue::fromVariant(config.name));
    configBuffer.insert("mac",QJsonValue::fromVariant(config.mac));
    configBuffer.insert("host",QJsonValue::fromVariant(config.host));
    configBuffer.insert("port",QJsonValue::fromVariant(config.port));
    QJsonObject configJson = QJsonObject::fromVariantMap(configBuffer);
    confArr.insert(index, configJson);
    QVariantMap mainBuffer;
    mainBuffer.insert("default_configuration", QJsonValue::fromVariant(defaultConfigIndex));
    mainBuffer.insert("configurations", confArr);
    QJsonObject mainJson = QJsonObject::fromVariantMap(mainBuffer);
    jsonDoc.setObject(mainJson);
    openClearFile();
    configFile->write(jsonDoc.toJson());
    configFile->close();
    readConfigFromFile();

}

void ConfigManager::setDefaultConfig(int index)
{
    QJsonArray confArr = jsonDoc.object().value("configurations").toArray();
    QVariantMap mainBuffer;
    mainBuffer.insert("default_configuration", QJsonValue::fromVariant(index));
    mainBuffer.insert("configurations", confArr);
    QJsonObject mainJson = QJsonObject::fromVariantMap(mainBuffer);
    jsonDoc.setObject(mainJson);
    openClearFile();
    configFile->write(jsonDoc.toJson());
    defaultConfigIndex = index;
    configFile->close();
    readConfigFromFile();
}

void ConfigManager::init()
{
    readConfigFromFile();
}

void ConfigManager::clearInit()
{
    createConfigFile();
    init();
}
