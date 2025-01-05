#include "CZmqHelper.h"


#include <iostream>
#include <zmq.hpp>
#include <string>
#include <thread>


CZmqHelper::CZmqHelper()
{
    test();
}

void CZmqHelper::test()
{
	// 启动服务器线程
	std::thread server_thread(&CZmqHelper::server, this);

	// 启动客户端线程
	std::thread client_thread(&CZmqHelper::client, this);

	// 等待线程完成
	server_thread.join();
	client_thread.join();
}

void CZmqHelper::server() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_ROUTER);
    socket.bind("tcp://*:5555");

    std::cout << "服务器启动，等待客户端连接..." << std::endl;

    while (true)
    {
        zmq::message_t identity;
        zmq::message_t request;

        // 接收客户端的身份和请求
        if (socket.recv(&identity) && socket.recv(&request))
        {
            std::string identity_str(static_cast<char*>(identity.data()), identity.size());
            std::string request_str(static_cast<char*>(request.data()), request.size());

            std::cout << "从客户端 " << identity_str << " 接收到请求: " << request_str << std::endl;

            // 发送回复
            std::string reply = "Hello, " + request_str;
            zmq::message_t reply_msg(reply.size());
            memcpy(reply_msg.data(), reply.data(), reply.size());

            socket.send(identity, ZMQ_SNDMORE);
            socket.send(reply_msg);
        }
    }
}

// 客户端函数
void CZmqHelper::client() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_DEALER);
    socket.connect("tcp://localhost:5555");

    std::string client_identity = "Client_1";
    socket.setsockopt(ZMQ_IDENTITY, client_identity.data(), client_identity.size());

    std::string request = "World";
    zmq::message_t request_msg(request.size());
    memcpy(request_msg.data(), request.data(), request.size());

    socket.send(request_msg);
    std::cout << "客户端发送请求: " << request << std::endl;

    zmq::message_t reply;
    socket.recv(&reply);
    std::string reply_str(static_cast<char*>(reply.data()), reply.size());
    std::cout << "客户端收到回复: " << reply_str << std::endl;
}

