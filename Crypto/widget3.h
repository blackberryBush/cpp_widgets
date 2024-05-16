#ifndef WIDGET3_H
#define WIDGET3_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget3;
}
QT_END_NAMESPACE

class Widget3 : public QWidget
{
    Q_OBJECT

public:
    Widget3(QWidget *parent = nullptr);
    ~Widget3();

private slots:
    void on_radioButton_encrypt_clicked(bool checked);
    void on_radioButton_decrypt_clicked(bool checked);
    void on_pushButton_clicked();

private:
    Ui::Widget3 *ui;
};
#endif // WIDGET3_H
