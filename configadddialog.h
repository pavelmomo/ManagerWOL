#ifndef CONFIGADDDIALOG_H
#define CONFIGADDDIALOG_H

#include <QDialog>

namespace Ui {
class configadddialog;
}

class configadddialog : public QDialog
{
    Q_OBJECT

public:
    explicit configadddialog(QWidget *parent = nullptr);
    ~configadddialog();

private:
    Ui::configadddialog *ui;
};

#endif // CONFIGADDDIALOG_H
