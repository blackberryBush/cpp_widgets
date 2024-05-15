#ifndef WIDGET_H
#define WIDGET_H

#include <QMap>
#include <QWidget>

QT_BEGIN_NAMESPACE

class QPushButton;
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void saveButtonDataToJson(const QString &filename);
    void buttonTextChanged(QPushButton *button, const QString &text);
    void loadButtonDataFromJson(const QString &filename);
private slots:

    void onButtonClicked();


private:
    Ui::Widget *ui;
    QMap<QPushButton*, QString> buttonTextMap;
};
#endif // WIDGET_H
