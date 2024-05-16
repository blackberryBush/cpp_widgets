#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <Calendar/widget.h>
#include <IEEE/widget2.h>
#include <Crypto/widget3.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool m_dragging = false;
    QPoint m_lastMousePos;

private slots:
    void openCalendarWidget();
    void openConvertorWidget();
    void openCryptoWidget();

private:
    Ui::MainWindow *ui;

    Widget* calendarWidget;
    Widget* convertorWidget;
    Widget* cryptoWidget;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

};
#endif // MAINWINDOW_H
