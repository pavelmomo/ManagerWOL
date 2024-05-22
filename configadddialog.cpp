#include "configadddialog.h"
#include "ui_configadddialog.h"

configadddialog::configadddialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::configadddialog)
{
    ui->setupUi(this);
}

configadddialog::~configadddialog()
{
    delete ui;
}
