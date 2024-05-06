#include "mainwindow.h"
#include <QApplication>

#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //Load the qss file
    QFile qssFile(":/Qss/styles.qss");
    qssFile.open(QFile::ReadOnly); //Open as read-only
    if(qssFile.isOpen())
    {
        QString qss = QLatin1String(qssFile.readAll());
        qApp->setStyleSheet(qss);
        qssFile.close();
    }
    else{qDebug() << "Unable to open file";}


    MainWindow w;
    w.show();
    return a.exec();
}
