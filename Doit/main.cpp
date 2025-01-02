#include "QDlgDoit.h"
#include <QtWidgets/QApplication>


#include "czip.h"
#include<QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDlgDoit w;
    w.show();

	std::vector<unsigned char> originalData = { 'H', 'e', 'l', 'l', 'o', ',', ' ', 'w', 'o', 'r', 'l', 'd', '!' };
	std::vector<unsigned char> compressedData = CZip::compress(originalData);
	std::cout << "Original size: " << originalData.size() << ", Compressed size: " << compressedData.size() << std::endl;

	std::string str(compressedData.begin(), compressedData.end());
	QString qstr = QString::fromStdString(str);

	std::string str2(originalData.begin(), originalData.end());
	QString qstr2 = QString::fromStdString(str2);

	qDebug() << qstr;
	qDebug() << qstr2;



    return a.exec();
}
