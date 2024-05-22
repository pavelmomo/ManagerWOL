#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "configmanager.h"
#include "wakeonlan.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_edit_action_triggered();

    void on_wake_clicked();

    void on_refresh_action_triggered();

    void on_about_action_triggered();

    void on_clear_init_action_triggered();

private:
    Ui::MainWindow *ui;
    ConfigManager *confManager;
    WakeOnLAN *wol;
    void updateConfigList();
};
#endif // MAINWINDOW_H
