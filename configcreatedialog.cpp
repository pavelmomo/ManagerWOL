#include <QMessageBox>
#include "configcreatedialog.h"
#include "ui_configcreatedialog.h"

ConfigCreateDialog::ConfigCreateDialog(ConfigManager *confManager, QWidget *parent,
                                       const ConfigManager::Config *config, int index) :
    QDialog(parent),
    ui(new Ui::ConfigCreateDialog)
{
    ui->setupUi(this);
    this->confManager = confManager;

    if (config != nullptr)
    {
        currentState = UPDATE;
        currentIndex = index;
        ui->mainLabel->setText("Редактирование конфигурации");
        fillConfigFields(config);
    }
    else
    {
        currentState = CREATE;
    }

}

void ConfigCreateDialog::fillConfigFields(const ConfigManager::Config *config)
{
    ui->name->setText(config->name);
    ui->mac->setText(config->mac);
    ui->host->setText(config->host);
    ui->port->setText(QString::number(config->port));
}

void ConfigCreateDialog::on_save_clicked()
{
    if(ui->name->text().isEmpty() || ui->mac->text().length() != 17)
    {
        QMessageBox::information(this, "Ошибка ввода",
                                 "Заполните все обязательные поля");
        return;
    }
    if(ui->host->text().isEmpty())
    {
        ui->host->setText("255.255.255.255");
    }
    if(ui->port->text().isEmpty())
    {
        ui->port->setText("9");
    }

    bool intConversionStatus;
    ConfigManager::Config newConfig(ui->name->text(),
                                    ui->mac->text(),
                                    ui->host->text(),
                                    ui->port->text().toInt(&intConversionStatus));
    if (!intConversionStatus)
    {
        QMessageBox::information(this, "Ошибка ввода", "Были введены некорректные данные о порте");
        return;
    }

    try
    {
        if (currentState == CREATE)
        {
            confManager->addConfig(newConfig);
        }
        else
        {
            confManager->updateConfig(newConfig, currentIndex);
        }
    }
    catch(const InvalidConfigException &exc)
    {
        QMessageBox::critical(this, "Ошибка", exc.message );
    }
    catch(const ConfigFileHandleException &exc)
    {
        QMessageBox::critical(this, "Ошибка", exc.message );
    }
    close();
}

ConfigCreateDialog::~ConfigCreateDialog()
{
    delete ui;
}
