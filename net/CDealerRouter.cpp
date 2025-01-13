#include "CDealerRouter.h"
#include <iostream>
#include <vector>
#include <chrono>


// 发送字符串的函数
void CDealerRouter::sendStr(const std::string& str, zmq::socket_t& socket) {
    std::lock_guard<std::mutex> lock(mtx);


    zmq::message_t message(str.size());
    memcpy(message.data(), str.data(), str.size());


    try
    {
        // 使用新的 send 函数签名，添加 send_flags 参数
        socket.send(message, zmq::send_flags::none);
    }
    catch (const zmq::error_t& e)
    {
        std::cerr << "Error sending string: " << e.what() << std::endl;
    }
}


// 接收并处理消息的函数
void CDealerRouter::recvStr(zmq::socket_t& socket) {
    while (!stop_signal)
    {
        zmq::message_t message;
        bool received = false;


        try
        {
            if (socket.recv(&message) == 0)
            {
                std::string str(static_cast<char*>(message.data()), message.size());


                std::cout << "Received string: " << str << std::endl;


                // 处理接收到的字符串，这里可以添加自定义的处理逻辑
                std::cout << "Received: " << str << std::endl;


                // 回复一个确认消息
                sendStr("Message received successfully", socket);


                received = true;
            }
        }
        catch (const zmq::error_t& e)
        {
            std::cerr << "Error receiving string: " << e.what() << std::endl;
        }


        if (!received)
        {
            auto start_time = std::chrono::steady_clock::now();
            auto end_time = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
            if (duration > 5000)
            { // 超时时间设置为 5 秒
                std::cerr << "Timeout waiting for string." << std::endl;
                break;
            }


            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}


// CDealerRouter 构造函数
CDealerRouter::CDealerRouter(const std::string& router_addr, const std::string& dealer_addr) : stop_signal(false) {
    try
    {
        context = zmq::context_t(1);
        router_socket = zmq::socket_t(context, ZMQ_ROUTER);
        dealer_socket = zmq::socket_t(context, ZMQ_DEALER);


        router_socket.bind(router_addr);
        dealer_socket.connect(dealer_addr);


        // 启动接收消息的线程
        std::thread router_thread(&CDealerRouter::recvStr, this, std::ref(router_socket));
        router_thread.detach();


        std::thread dealer_thread(&CDealerRouter::recvStr, this, std::ref(dealer_socket));
        dealer_thread.detach();
    }
    catch (const zmq::error_t& e)
    {
        std::cerr << "Error creating sockets: " << e.what() << std::endl;
    }
}


// 析构函数，用于设置停止信号
CDealerRouter::~CDealerRouter() {
    stop_signal = true;
}

#if 0

int main() {
    CDealerRouter cr1("tcp://*:5555", "tcp://localhost:5556");
    CDealerRouter cr2("tcp://*:5556", "tcp://localhost:5555");


    // cr1 向 cr2 发送字符串
    cr1.sendStr("Hello from cr1", cr1.dealer_socket);


    // cr2 向 cr1 发送字符串
    cr2.sendStr("Hello from cr2", cr2.dealer_socket);


    // 等待一段时间，确保消息传输完成
    std::this_thread::sleep_for(std::chrono::seconds(10));


    return 0;
}


#endif