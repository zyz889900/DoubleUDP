#include "udpa.h"
#include "ui_udpa.h"

UdpA::UdpA(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UdpA)
{
    ui->setupUi(this);
    this->setWindowTitle("服务器端口:8888");
    udpSocket = new QUdpSocket(this);
    //绑定端口号
    udpSocket->bind(8888);
    //udpSocket->bind(QHostAddress::AnyIPv4,8888);        //必须是主机的ipv4类通信方式,以及本机的ip地址
    //当对方发送数据过来。自动触发readyRead()
    connect(udpSocket,&QUdpSocket::readyRead,this,&UdpA::dealMsg);
    //键盘Enter键设置
    ui->pushButton->setFocus();
    ui->pushButton->setDefault(true);
    ui->lineEdit_3->installEventFilter(this);//设置完后自动调用其eventFilter函数
}

void UdpA::dealMsg()
{
    //读取对方发送的内容
    char buf[1023] = {0};           //内容
    QHostAddress cliAddr;           //对方地址
    quint16 port;                   //对方端口
    qint64 len = udpSocket->readDatagram(buf,sizeof(buf),&cliAddr,&port);
    //添加时间
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

bool UdpA::eventFilter(QObject *target, QEvent *event)
{
    if(target == ui->lineEdit_3) //对象为需要发送的焦点
        {
            if(event->type() == QEvent::KeyPress)//回车键
            {
                 QKeyEvent *k = static_cast<QKeyEvent *>(event);
                 if(k->key() == Qt::Key_Return)
                 {
                     on_pushButton_clicked();
                     return true;
                 }
            }
        }
        return QWidget::eventFilter(target,event);
}

UdpA::~UdpA()
{
    delete ui;
}

void UdpA::on_pushButton_clicked()
{
    //获取对方的ip和端口
    QString ip = ui->lineEdit->text();
    qint16 port = ui->lineEdit_2->text().toInt();
    //获取编辑区内容
    QString str = ui->lineEdit_3->text();
    //给指定的ip发送数据
    udpSocket->writeDatagram(str.toUtf8(),QHostAddress(ip),port);
     ui->lineEdit_3->clear();
}
