#include "QDlgDoit.h"
#include <QtWidgets/QApplication>
#include "czip.h"
#include "CZmqHelper.h"
#include "CDealerRouter.h"

#include <iostream>
#include <sstream>

#include "CTickCounter.h"
#include "CFourierTransform.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDlgDoit w;
    w.show();

    // 测试输出
    std::cout << "This is a test message from std::cout" << std::endl;
    std::cerr << "This is an error message from std::cerr" << std::endl;

    {
        
        w.test();
		CFourierTransform fourierTransform("../data/resized.jpg");
		fourierTransform.performTransform();
    }


#if 0


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
    std::this_thread::sleep_for(std::chrono::seconds(5));

#endif
	// 处理事件循环，确保 GUI 更新

    return a.exec();
}
