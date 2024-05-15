#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>
#include <QFile>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(300, 300);
    setWindowFlags(Qt::FramelessWindowHint);

    QString styleSheet =
        "QMainWindow {"
        "    background-color: #2E2E2E;"  // Темный фон
        "    color: white;"  // Белый цвет текста у всего
        "}"
        "QPushButton {"
        "    background-color: #4A4A4A;"  // Светло-серый фон для кнопок
        "    color: white;"  // Белый текст
        "    border: 2px solid gray;"  // Серый контур
        "    border-radius: 8px;"  // Скругленные углы
        "    font-family: Arial;"  // Шрифт
        "    font-size: 14px;"  // Размер шрифта
        "}"
        "QPushButton:hover {"
        "    background-color: #696969;"  // Цвет фона при наведении курсора
        "    border-color: white;"  // Цвет контура при наведении курсора
        "}"
        "QLabel {"
        "    color: white;"  // Белый цвет текста для QLabel
        "    font-family: San Francisco;"  // Шрифт
        "    font-size: 18px;"  // Размер шрифта
        "}";

    setStyleSheet(styleSheet);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::openCalendarWidget);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::openConvertorWidget);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::openCryptoWidget);
}

void MainWindow::openCryptoWidget() {
    Widget3 *cryptoWidget = new Widget3();

    cryptoWidget->show();
}

void MainWindow::openConvertorWidget() {
    Widget2 *convertorWidget = new Widget2();

    convertorWidget->show();
}

void MainWindow::openCalendarWidget() {
    Widget *calendarWidget = new Widget();

    // Открытие файла стилей
    // QFile file("styles.qss");
    QFile file("../../Calendar/styles.qss");

    if (!file.open(QFile::ReadOnly | QFile::Text)) qDebug() << "Couldn't open stylesheet file";
    else {
        QTextStream in(&file);
        QString styleSheet = in.readAll();
        calendarWidget->setStyleSheet(styleSheet);
    }

    calendarWidget->show();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // Сохранение позиции нажатия мыши
    if (event->button() == Qt::LeftButton) {
        m_dragging = true;
        m_lastMousePos = event->pos();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    // Если активировано перемещение, перемещаем окно
    if (m_dragging) {
        QPoint diff = event->pos() - m_lastMousePos;
        move(pos() + diff);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    // Остановка перемещения при отпускании кнопки мыши
    if (event->button() == Qt::LeftButton) {
        m_dragging = false;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
