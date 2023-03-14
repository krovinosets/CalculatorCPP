#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void enableFuncButtons(bool var);
    bool isEnabledFuncButtons();

private slots:
    void on_PB_numspace_clicked();
    void on_PB_funcspace_clicked();
    void on_PB_clicked();
    void on_PB_ac_clicked();
    void on_PB_del_clicked();
    void on_PB_fin_clicked();

    void on_PB_mc_clicked();

    void on_PB_Mplus_clicked();

    void on_PB_Mminus_clicked();

    void on_PB_mr_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
