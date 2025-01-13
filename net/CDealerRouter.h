#ifndef CDEALERROUTER_H
#define CDEALERROUTER_H


#include <zmq.hpp>
#include <string>
#include <thread>
#include <mutex>
#include <atomic>


class CDealerRouter {
private:
	zmq::context_t context;

	std::mutex mtx;
	std::atomic<bool> stop_signal;


	// 接收并处理消息的函数
	void recvStr(zmq::socket_t& socket);

public:
	zmq::socket_t router_socket;
	zmq::socket_t dealer_socket;

public:
	CDealerRouter(const std::string& router_addr, const std::string& dealer_addr);


	// 发送字符串的公共函数
	void sendStr(const std::string& str, zmq::socket_t& socket);


	// 析构函数，用于设置停止信号
	~CDealerRouter();
};


#endif // CDEALERROUTER_H