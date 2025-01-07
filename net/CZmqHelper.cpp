#include "CZmqHelper.h"

#include <zmq.h>

#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <deque>
//std::mutex mtx;
std::atomic<bool> error_occurred(false);

#include <filesystem>

namespace fs = std::filesystem;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>         
#include <process.h>
#include <fcntl.h>
#include <assert.h>

CZmqHelper::CZmqHelper()
{
    //test();
}

void CZmqHelper::test()
{
	std::string filePathToSend = "D:/young/qts/Doit/data/resized.jpg"; //  WinSetupMon.log
	std::string filePathToReceive = timeSuffix(filePathToSend); // resized_recv.jpg 


#if 1

	zmq::context_t context(1);
	// 创建 PUSH 套接字
	zmq::socket_t pushSocket(context, ZMQ_PUSH);
	pushSocket.bind("tcp://*:5555");
	// 创建 PULL 套接字
	zmq::socket_t pullSocket(context, ZMQ_PULL);
	pullSocket.connect("tcp://localhost:5555");

	std::vector<std::thread> threads;
	// 启动发送端线程
	threads.emplace_back([&]() { sendFile(pushSocket, filePathToSend); });
	// 启动接收端线程
	threads.emplace_back([&]() { receiveFile(pullSocket, filePathToReceive); });

#endif


	// 等待线程结束
	for (auto& t : threads)
		t.join();

	if (error_occurred)
		std::cerr << "文件传输过程中出现错误，请检查日志。" << std::endl;

}

void CZmqHelper::sendString(zmq::socket_t& socket, const std::string& str) {
	zmq::message_t message(str.data(), str.size());
	try
	{
		socket.send(message, zmq::send_flags::none);
	}
	catch (const zmq::error_t& e)
	{
		//std::lock_guard<std::mutex> lock(mtx);
		std::cerr << "发送字符串时出错: " << e.what() << std::endl;
		error_occurred = true;
		return;
	}
}


void CZmqHelper::receiveString(zmq::socket_t& socket, std::string& str) {
	zmq::message_t message;
	try
	{
		socket.recv(message);
	}
	catch (const zmq::error_t& e)
	{
		std::cerr << "接收字符串时出错: " << e.what() << std::endl;
		error_occurred = true;
		return;
	}
	str = std::string(static_cast<char*>(message.data()), message.size());
}


void CZmqHelper::sendFile(zmq::socket_t& socket, const std::string& filePath) {
	std::string fileContent = readFileInChunks(filePath, 4096);
	sendString(socket, fileContent);

	// 发送结束标志
	zmq::message_t endMessage("==END==", 7);
	try
	{
		socket.send(endMessage, zmq::send_flags::none);
	}
	catch (const zmq::error_t& e)
	{
		std::cerr << "发送结束标志时出错: " << e.what() << std::endl;
		error_occurred = true;
		return;
	}

}


void CZmqHelper::receiveFile(zmq::socket_t& socket, const std::string& filePath) {
	std::ofstream file(filePath, std::ios::binary);
	if (!file.is_open())
	{
		std::cerr << "无法打开接收文件: " << filePath << std::endl;
		error_occurred = true;
		return;
	}
	bool end_received = false;
	while (!end_received)
	{
		std::string msg;
		receiveString(socket, msg);
		if (msg == "==END==")
		{
			end_received = true;
		}
		else
		{
			if (file.write(static_cast<char*>(msg.data()), msg.size()))
			{
				std::cerr << "写入文件时出错" << std::endl;
				error_occurred = true;
				file.close();
				return;
			}
		}
	}
	file.close();
}

// 分块读取文件到 string 的函数
std::string CZmqHelper::readFileInChunks(const std::string& filePath, size_t chunkSize) {
	std::ifstream file(filePath, std::ios::binary);
	if (!file.is_open())
	{
		std::cerr << "无法打开文件: " << filePath << std::endl;
		return "";
	}
	std::stringstream ss;
	std::vector<char> buffer(chunkSize);
	while (file.read(buffer.data(), chunkSize))
	{
		ss.write(buffer.data(), chunkSize);
	}
	// 处理文件最后一部分
	if (file.gcount() > 0)
	{
		ss.write(buffer.data(), file.gcount());
	}
	file.close();
	return ss.str();
}

std::string CZmqHelper::timeSuffix(std::string& filePath)
{
	// 获取当前时间
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	// 将时间转换为字符串格式
	std::stringstream ss;
	ss << std::put_time(std::localtime(&in_time_t), "%Y%m%d_%H%M%S");
	std::string timestamp = ss.str();

	// 分离文件名和扩展名
	fs::path path(filePath);
	std::string stem = path.stem().string();
	std::string extension = path.extension().string();

	// 构建新的文件名
	std::string newFileName = stem + "_" + timestamp + extension;

	// 返回新的文件路径
	return (path.parent_path() / newFileName).string();
}

