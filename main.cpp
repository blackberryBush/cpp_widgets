#include "timetable/widget.h"

#include <QApplication>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Загрузка файла стилей из ресурсов
    QFile file(":/styles/styles.qss");
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Couldn't open stylesheet file";
    } else {
        QTextStream in(&file);
        QString styleSheet = in.readAll();
        qApp->setStyleSheet(styleSheet); // Применение стилей ко всему приложению
        // Или применение стилей к отдельному виджету:
        // widget->setStyleSheet(styleSheet);
    }

    Widget w;
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.show();
    return a.exec();
}
