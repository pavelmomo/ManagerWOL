#ifndef CONFIGCREATEDIALOG_H
#define CONFIGCREATEDIALOG_H

#include <QDialog>
#include "configmanager.h"

namespace Ui {
class ConfigCreateDialog;
}

enum State { CREATE, UPDATE};

class ConfigCreateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigCreateDialog(ConfigManager *confManager, QWidget *parent = nullptr,
                                const ConfigManager::Config *config = nullptr, int index = 0);
    ~ConfigCreateDialog();

private slots:
    void on_save_clicked();

private:
    State currentState;
    int currentIndex;
    Ui::ConfigCreateDialog *ui;
    ConfigManager *confManager;
    void fillConfigFields(const ConfigManager::Config *config);
};

#endif // CONFIGCREATEDIALOG_H
