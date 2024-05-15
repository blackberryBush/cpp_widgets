#include "widget2.h"
#include "./ui_widget2.h"
#include "ieee754.h"

Widget2::Widget2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget2)
{
    ui->setupUi(this);
}

Widget2::~Widget2()
{
    delete ui;
}

void Widget2::on_CONVERTATION_clicked()
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

