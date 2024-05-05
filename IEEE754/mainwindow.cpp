#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "ieee754.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_CONVERTATION_clicked()
{
    double num;
    string str;

    QString qstr = ui->IN->text();
    if(ui->BIN->isChecked()){
        num = qstr.toDouble();
        str = to_ieee754(num);
        qstr = QString::fromStdString(str);
    }
    else{
        str = qstr.toStdString();
        num = from_ieee754(str);
        qstr = QString::number(num);
    }
    ui->OUT->setText(qstr);
}

