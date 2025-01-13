#include "QDlgDoit.h"
#include <QtWidgets/QApplication>
#include "czip.h"
#include "CZmqHelper.h"
#include "CDealerRouter.h"

#include <iostream>
#include <sstream>

#include <QtWidgets/QTextEdit>
#include <QTimer>

class ConsoleOutput : public std::stringbuf {
public:
	ConsoleOutput(QTextEdit* textEdit) : m_textEdit(textEdit) {}


	int sync() override {
		m_textEdit->append(QString::fromStdString(str()));
		str("");
		return 0;
	}


private:
	QTextEdit* m_textEdit;
};




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDlgDoit w;
    w.show();

	ConsoleOutput consoleOutput(w.ui.txtDebug);
	std::cout.rdbuf(&consoleOutput);
	std::cout << "This is a test output in custom text edit." << std::endl;
    std::cerr.rdbuf(&consoleOutput);

    CZip zip;
    zip.test();

    CZmqHelper zmq;
    zmq.test();
  

    CDealerRouter cr1("tcp://*:5555", "tcp://localhost:5556");
    CDealerRouter cr2("tcp://*:5556", "tcp://localhost:5555");


    // cr1 向 cr2 发送字符串
    cr1.sendStr("Hello from cr1", cr1.dealer_socket);


    // cr2 向 cr1 发送字符串
    cr2.sendStr("Hello from cr2", cr2.dealer_socket);


    // 等待一段时间，确保消息传输完成
    std::this_thread::sleep_for(std::chrono::seconds(10));

    return a.exec();
}
