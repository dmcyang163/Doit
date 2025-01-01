#include "QDlgDoit.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDlgDoit w;
    w.show();
    return a.exec();
}
