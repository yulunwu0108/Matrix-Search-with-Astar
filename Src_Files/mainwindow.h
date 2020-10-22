#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include "func.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void show_block();

private slots:

    void on_SetdimBtn_clicked();

    void on_GenBtn_clicked();

    void on_InitBtn_clicked();

    void on_SetTargtBtn_clicked();

    void on_SrchBtn_clicked();

    void on_ShowBtn_clicked();

    void show_start_state();
    void show_route(int n);

private:
    Ui::MainWindow *ui;
    QPushButton* NumBtn[maxBLK];
    QLineEdit* InitEdit[maxBLK];
    QLineEdit* TargtEdit[maxBLK];
};

#endif // MAINWINDOW_H
