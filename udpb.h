#ifndef UDPB_H
#define UDPB_H

#include <QWidget>
#include <QUdpSocket>
#include <QHostAddress>
#include <QDebug>
#include <QTime>
#include <QKeyEvent>

namespace Ui {
class UdpB;
}

class UdpB : public QWidget
{
    Q_OBJECT

public:
    explicit UdpB(QWidget *parent = 0);
    ~UdpB();
    void dealMsg2();
protected:
    bool eventFilter(QObject *target, QEvent *event);//事件过滤器
private slots:
    void on_pushButton_2_clicked();
private:
    Ui::UdpB *ui;
    QUdpSocket *udpSocket2;
};

#endif // UDPB_H
