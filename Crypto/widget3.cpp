#include "widget3.h"
#include "./ui_widget3.h"

using namespace std;

Widget3::Widget3(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget3)
{
    ui->setupUi(this);
    if(ui->radioButton_encrypt->isChecked()){
        ui->pushButton->setText("Зашифровать");
    }
}

Widget3::~Widget3()
{
    delete ui;
}

void Widget3::on_radioButton_encrypt_clicked(bool checked)
{
    if(checked){
        ui->pushButton->setText("Зашифровать");
    }
}


void Widget3::on_radioButton_decrypt_clicked(bool checked)
{
    if(checked){
        ui->pushButton->setText("Расшифровать");
    }
}

// Функция для шифрования
string Encrypt(const string &text, const string &key) {
    string result;
    int keyIndex = 0;

    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            c = (c - base + (toupper(key[keyIndex]) - 'A')) % 26 + base;
            keyIndex = (keyIndex + 1) % key.length();
        }
        result += c;
    }

    return result;
}

// Функция для расшифрования
string Decrypt(const string &text, const string &key) {
    string result;
    int keyIndex = 0;

    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            c = (c - base - (toupper(key[keyIndex]) - 'A') + 26) % 26 + base;
            keyIndex = (keyIndex + 1) % key.length();
        }
        result += c;
    }
    return result;
}

void Widget3::on_pushButton_clicked()
{
    ui->plainTextEdit_out->clear();


    string text = ui->plainTextEdit_in->toPlainText().toStdString();
    string key = ui->lineEdit_key->text().toStdString();

    if(ui->radioButton_encrypt->isChecked()){
        text = Encrypt(text, key);
    }else{
        text = Decrypt(text, key);
    }

    QString qstring = QString::fromStdString(text);
    ui->plainTextEdit_out ->insertPlainText(qstring);
}
