#ifndef WIDGET2_H
#define WIDGET2_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget2;
}
QT_END_NAMESPACE

class Widget2 : public QWidget
{
    Q_OBJECT

public:
    Widget2(QWidget *parent = nullptr);
    ~Widget2();

private slots:
    void on_CONVERTATION_clicked();

private:
    Ui::Widget2 *ui;
};
#endif // WIDGET2_H
