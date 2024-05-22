#ifndef CONFIGURATIONEDITOR_H
#define CONFIGURATIONEDITOR_H

#include <QDialog>

namespace Ui {
class ConfigurationEditor;
}

class ConfigurationEditor : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigurationEditor(QWidget *parent = nullptr);
    ~ConfigurationEditor();

private:
    Ui::ConfigurationEditor *ui;
};

#endif // CONFIGURATIONEDITOR_H
