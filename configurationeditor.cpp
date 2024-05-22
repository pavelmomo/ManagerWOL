#include "configurationeditor.h"
#include "ui_configurationeditor.h"

ConfigurationEditor::ConfigurationEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationEditor)
{
    ui->setupUi(this);
}

ConfigurationEditor::~ConfigurationEditor()
{
    delete ui;
}
