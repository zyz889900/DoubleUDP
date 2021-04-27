#ifndef UDPA_H
#define UDPA_H

#include <QWidget>
#include <QUdpSocket>
#include <QHostAddress>
#include <QDebug>
#include <QTime>
#include <QKeyEvent>

namespace Ui {
class UdpA;
}

class UdpA : public QWidget
{
    Q_OBJECT

public:
    explicit UdpA(QWidget *parent = 0);
    ~UdpA();
    void dealMsg();         //槽函数，处理对方发过来的数据
protected:
    bool eventFilter(QObject *target, QEvent *event);//事件过滤器
private slots:
    void on_pushButton_clicked();
private:
    Ui::UdpA *ui;
    QUdpSocket *udpSocket;
};

#endif // UDPA_H
