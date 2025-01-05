#include "QDlgDoit.h"
#include <QtWidgets/QApplication>
#include "czip.h"
#include "CZmqHelper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDlgDoit w;
    w.show();


    CZip zip;
    zip.test();

    CZmqHelper zmq;
  

    return a.exec();
}
