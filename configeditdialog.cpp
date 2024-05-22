#include "configeditdialog.h"
#include "ui_configeditdialog.h"
#include "configcreatedialog.h"

ConfigEditDialog::ConfigEditDialog(ConfigManager *confManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigEditDialog)
{
    ui->setupUi(this);
    this->confManager = confManager;
    updateConfigList();
}

void ConfigEditDialog::updateConfigList()
{

    ui->configList->clear();
    if (confManager->configurations->length() == 0)
    {
        ui->configList->addItem("Отсутствуют конфигурации");
        ui->delete_config->setEnabled(false);
        ui->edit_config->setEnabled(false);
        ui->default_config->setEnabled(false);
        return;
    }
    ui->delete_config->setEnabled(true);
    ui->edit_config->setEnabled(true);
    ui->default_config->setEnabled(true);
    int index = 0;
    for(auto i: *confManager->configurations)
    {

        if (index == confManager->defaultConfigIndex)
        {
            ui->configList->addItem(QString("[+]  [MAC]: %1  [HOST]: %2  [NAME]: %3")
                                    .arg(i.mac, i.host, i.name));
        }
        else
        {
            ui->configList->addItem(QString("[_]  [MAC]: %1  [HOST]: %2  [NAME]: %3")
                                    .arg(i.mac, i.host, i.name));
        }
        ++index;
    }
    ui->configList->setCurrentRow(confManager->defaultConfigIndex);
}

ConfigEditDialog::~ConfigEditDialog()
{
    delete ui;
}

void ConfigEditDialog::on_delete_config_clicked()
{
    try
    {
        confManager->deleteConfig(ui->configList->currentRow());
    }
    catch(const InvalidConfigException &exc)
    {
        QMessageBox::critical(this, "Ошибка", exc.message );
    }
    catch(const ConfigFileHandleException &exc)
    {
        QMessageBox::critical(this, "Ошибка", exc.message );
    }
    updateConfigList();
}


void ConfigEditDialog::on_add_config_clicked()
{
    ConfigCreateDialog dialog(confManager,this);
    dialog.exec();
    updateConfigList();
}


void ConfigEditDialog::on_edit_config_clicked()
{
    ConfigCreateDialog dialog(confManager, this,
                              &confManager->configurations->at(ui->configList->currentRow()),
                              ui->configList->currentRow());
    dialog.exec();
    updateConfigList();
}


void ConfigEditDialog::on_default_config_clicked()
{
    try
    {
        confManager->setDefaultConfig(ui->configList->currentRow());
    }
    catch(const InvalidConfigException &exc)
    {
        QMessageBox::critical(this, "Ошибка", exc.message );
    }
    catch(const ConfigFileHandleException &exc)
    {
        QMessageBox::critical(this, "Ошибка", exc.message );
    }
    updateConfigList();
}

