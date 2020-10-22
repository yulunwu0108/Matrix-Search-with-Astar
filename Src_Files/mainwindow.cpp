#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFont>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //init_all();
    ui->setupUi(this);
    setWindowTitle("Matrix Search");
    for(int i = 0; i < maxBLK; i++){
        NumBtn[i] = new QPushButton(Num2str(i), this);
        InitEdit[i] = new QLineEdit(this);
        TargtEdit[i] = new QLineEdit(this);
        //设置颜色
        //NumBtn[i]->setStyleSheet("background-color: rgb(200,200,200)");
        //NumBtn[i]->setStyleSheet("border: none");
        NumBtn[i]->setVisible(0);
        InitEdit[i]->setVisible(0);
        TargtEdit[i]->setVisible(0);
    }
    show_block();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//
void MainWindow::show_block(){
    for(int i = 0; i < maxBLK; i++){
        NumBtn[i]->setVisible(0);
        InitEdit[i]->setVisible(0);
        TargtEdit[i]->setVisible(0);
    }

    QFont ft;
    ft.setFamily("华文彩云");
    ft.setPointSize(25);

    for(int i = 0; i < M*N && i < maxBLK; i++){
        //NumBtn[i] = new QPushButton(Num2str(start_state[i / N][i % N]), this);
        NumBtn[i]->setVisible(1);
        NumBtn[i]->setText(Num2str(start_state[i / N][i % N]));
        NumBtn[i]->move(100 + (600 / N)*(i % N), 130 + (600 / M)*(i / N));
        NumBtn[i]->resize(600 / N, 600 / M);
        NumBtn[i]->setFont(ft);

        InitEdit[i]->setVisible(1);
        InitEdit[i]->move(850 + (300 / N)*(i % N), 130 + (150 / M)*(i / N));
        InitEdit[i]->resize(200 / N, 100 / M);
        //NumBtn[i]->setFont(ft);

        TargtEdit[i]->setVisible(1);
        TargtEdit[i]->move(850 + (300 / N)*(i % N), 330 + (150 / M)*(i / N));
        TargtEdit[i]->resize(200 / N, 100 / M);
    }
    //ui->SizeBtn->setText("ok");
    //qDebug() << start_state[1][0];
}

void MainWindow::on_SetdimBtn_clicked()
{
    int m = ui->RowEdit->text().toInt();
    int n = ui->ColEdit->text().toInt();
    if(m * n > maxBLK){
        QMessageBox::information(this, "Message", "Input out of range! Please re-input!");
    }
    else{
        M = m;
        N = n;
        change_dims(m, n);
        show_block();
    }
}

void MainWindow::show_start_state(){
    for(int i = 0; i < M*N && i < maxBLK; i++){
        NumBtn[i]->setText(Num2str(start_state[i / N][i % N]));
    }
}
void MainWindow::on_GenBtn_clicked()
{
    autoGenerate(start_state);
    show_start_state();
}

void MainWindow::on_InitBtn_clicked()
{
    //Init_StartState(start_state, ui->InitText->toPlainText());
    for(int i = 0; i < M*N; i++){
        start_state[i / N][i % N] = InitEdit[i]->text().toInt();
    }
    show_start_state();
}

void MainWindow::on_SetTargtBtn_clicked()
{
    for(int i = 0; i < M*N; i++){
        target_state[i / N][i % N] = TargtEdit[i]->text().toInt();
    }
    //show_start_state();
    //if(Init_StartState(target_state, ui->TargtText->toPlainText())){
    QMessageBox::information(this, "Message", "Successfully set!");
    //}
    init_all();
}

void MainWindow::on_SrchBtn_clicked()
{
    if((!Search_Route()) && (!no_space) ){
        QMessageBox::information(this, "Message", "Cannot find a route!");
    }
    else if (no_space) {
        QMessageBox::information(this, "Message", "No space!");
        no_space = false;
    }
    else {
        QMessageBox::information(this, "Message", "Found!");
        ui->StepTB->setText(QString::number(step_num));
        ui->TimeTB->setText(QString::number(srch_time) + " s");
    }
}

void MainWindow::show_route(int n){
    for(int i = 0; i < M*N; i++){
        NumBtn[i]->setText(Num2str(all_state[i / N][i % N][n]));
    }
}

void MainWindow::on_ShowBtn_clicked()
{
    show_route(0);
    for(int i = index - 1; i >= 0; i--){

        sleep((4 - (ui->SpeedBox->text().toInt())) * 100);
        show_route(sh_route[i]);
    }
}
