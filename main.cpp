#include "udpa.h"
#include "udpb.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UdpA w;
    UdpB k;
    w.show();
    k.show();
    return a.exec();
}
