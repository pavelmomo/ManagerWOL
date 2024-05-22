#ifndef CONFIGEDITDIALOG_H
#define CONFIGEDITDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "configmanager.h"

namespace Ui {
class ConfigEditDialog;
}

class ConfigEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigEditDialog(ConfigManager *confManager, QWidget *parent = nullptr);
    ~ConfigEditDialog();

private slots:
    void on_delete_config_clicked();

    void on_add_config_clicked();

    void on_edit_config_clicked();

    void on_default_config_clicked();

private:
    Ui::ConfigEditDialog *ui;
    ConfigManager *confManager;
    void updateConfigList();
};

#endif // CONFIGEDITDIALOG_H
