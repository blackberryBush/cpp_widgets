#include "widget.h"
#include "./ui_widget.h"

#include <QMessageBox>
#include <QDebug>
#include <QInputDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    for (int i = 0; i < ui->upper_week_layout->count(); ++i) {
        QLayoutItem *item = ui->upper_week_layout->itemAt(i);
        if (item && item->widget() && item->widget()->inherits("QPushButton")) {
            QPushButton *button = qobject_cast<QPushButton*>(item->widget());
            if (button) {
                connect(button, &QPushButton::clicked, this, &Widget::onButtonClicked);
            }
        }
    }

    for (int i = 0; i < ui->lower_week_layout->count(); ++i) {
        QLayoutItem *item = ui->lower_week_layout->itemAt(i);
        if (item && item->widget() && item->widget()->inherits("QPushButton")) {
            QPushButton *button = qobject_cast<QPushButton*>(item->widget());
            if (button) {
                connect(button, &QPushButton::clicked, this, &Widget::onButtonClicked);
            }
        }
    }

    for (int i = 0; i < ui->hours->count(); ++i) {
        QLayoutItem *item = ui->hours->itemAt(i);
        if (item && item->widget() && item->widget()->inherits("QPushButton")) {
            QPushButton *button = qobject_cast<QPushButton*>(item->widget());
            if (button) {
                connect(button, &QPushButton::clicked, this, &Widget::onButtonClicked);
            }
        }
    }

    connect(ui->corner_button, &QPushButton::clicked, this, &Widget::onButtonClicked);

    // Загрузка данных о кнопках из файла при запуске приложения
    loadButtonDataFromJson("button_data.json");
}

Widget::~Widget()
{
    // Сохранение данных о кнопках в файл при закрытии приложения
    saveButtonDataToJson("button_data.json");
    delete ui;
}

void Widget::onButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender()); // Получаем указатель на кнопку, вызвавшую сигнал
    if (button) {
        bool ok;
        QString text = QInputDialog::getText(this, tr("Введите текст"), tr("Текст для кнопки:"), QLineEdit::Normal, "", &ok);
        if (ok && !text.isEmpty()) {
            button->setText(text); // Устанавливаем текст кнопки
            buttonTextChanged(button, text); // Вызываем функцию для обновления контейнера
        }
    }
}

void Widget::buttonTextChanged(QPushButton *button, const QString &text)
{
    if (button) {
        buttonTextMap[button] = text; // Обновляем контейнер
    }
}

void Widget::saveButtonDataToJson(const QString &filename)
{
    QJsonObject json;

    // Заполнение JSON объекта данными о кнопках
    for (auto it = buttonTextMap.constBegin(); it != buttonTextMap.constEnd(); ++it) {
        QPushButton *button = it.key();
        QString text = it.value();
        json[button->objectName()] = text;
    }

    // Сохранение JSON объекта в файл
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(json);
        file.write(doc.toJson());
        file.close();
    }
}

void Widget::loadButtonDataFromJson(const QString &filename)
{
    // Чтение JSON объекта из файла
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        QJsonDocument doc(QJsonDocument::fromJson(data));
        QJsonObject json = doc.object();
        file.close();

        // Восстановление данных о кнопках из JSON объекта
        for (auto it = json.constBegin(); it != json.constEnd(); ++it) {
            QString buttonName = it.key();
            QString text = it.value().toString();
            QPushButton *button = findChild<QPushButton*>(buttonName);
            if (button) {
                button->setText(text);
                buttonTextMap[button] = text;
            }
        }
    }
}
