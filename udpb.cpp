#include "udpb.h"
#include "ui_udpb.h"

UdpB::UdpB(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UdpB)
{
    ui->setupUi(this);
    this->setWindowTitle("服务器端口2:9999");
    udpSocket2 = new QUdpSocket(this);
    //绑定
    udpSocket2->bind(9999);
    connect(udpSocket2,&QUdpSocket::readyRead,this,&UdpB::dealMsg2);
    ui->pushButton_2->setFocus();
    ui->pushButton_2->setDefault(true);
    ui->lineEdit_3->installEventFilter(this);//设置完后自动调用其eventFilter函数
}

void UdpB::dealMsg2()
{
    //读取对方发送的内容
    char buf[1024] = {0};           //内容
    QHostAddress cliAddr;           //对方地址
    quint16 port;                   //对方端口
    qint64 len = udpSocket2->readDatagram(buf,sizeof(buf),&cliAddr,&port);
    QTime cur_time = QTime::currentTime();
    QString time_info = cur_time.toString();
    if(len >0)
    {
        QString str = QString("[%1] %2 [%3]")
                .arg(port)
                .arg(buf)
                .arg(time_info);
        ui->textBrowser->setText(str);
    }
}

bool UdpB::eventFilter(QObject *target, QEvent *event)
{
    if(target == ui->lineEdit_3)
        {
            if(event->type() == QEvent::KeyPress)//回车键
            {
                 QKeyEvent *k = static_cast<QKeyEvent *>(event);

                 if(k->key() == Qt::Key_Return)
                 {
                     on_pushButton_2_clicked();
                     return true;
                 }
            }
        }
        return QWidget::eventFilter(target,event);
}

UdpB::~UdpB()
{
    delete ui;
}


void UdpB::on_pushButton_2_clicked()
{
    //获取对方的ip和端口
    QString ip = ui->lineEdit->text();
    qint16 port = ui->lineEdit_2->text().toInt();
    //获取编辑区内容
    QString str = ui->lineEdit_3->text();
    //给指定的ip发送数据
    udpSocket2->writeDatagram(str.toUtf8(),QHostAddress(ip),port);
    ui->lineEdit_3->clear();
}
