#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configeditdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    confManager = new ConfigManager();
    wol = new WakeOnLAN(confManager);
    try
    {
        confManager->init();
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

void MainWindow::updateConfigList()
{

    ui->configList->clear();
    if (confManager->configurations->length() == 0)
    {
        ui->configList->addItem("Отсутствуют конфигурации");
        return;
    }
    for(auto i: *confManager->configurations)
    {
        ui->configList->addItem(QString("[%1] %2").arg(i.mac, i.name));
    }
    ui->configList->setCurrentRow(confManager->defaultConfigIndex);
}

void MainWindow::on_edit_action_triggered()
{
    ConfigEditDialog configEditDialog(confManager, this);
    configEditDialog.exec();
    updateConfigList();
}

void MainWindow::on_wake_clicked()
{
    try
    {
        wol->wake(ui->configList->currentRow());
        QMessageBox::information(this,"Отправлено", "Пакет успешно отправлен");
    }
    catch (const PackageSendException &exc)
    {
        QMessageBox::critical(this,"Ошибка", exc.message);
    }
}

void MainWindow::on_refresh_action_triggered()
{
    try
    {
        confManager->init();
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

void MainWindow::on_about_action_triggered()
{
    QMessageBox::information(this, "О программе",
        "Данное приложение разработано для запуска удаленного ПК\nпри помощи технологии Wake On LAN."
        "\nВерсия: 1.0" );
}

void MainWindow::on_clear_init_action_triggered()
{
    try
    {
        confManager->clearInit();
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


MainWindow::~MainWindow()
{
    delete confManager;
    delete wol;
    delete ui;
}




