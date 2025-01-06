#pragma once

#include <zmq.hpp>
#include <string>

class CZmqHelper
{
public:
	CZmqHelper();

	void test();

	void sendString(zmq::socket_t& socket, const std::string& str);
	void receiveString(zmq::socket_t& socket, std::string& str);
	void sendFile(zmq::socket_t& socket, const std::string& filePath);
	void receiveFile(zmq::socket_t& socket, const std::string& filePath);

private:
	std::string readFileInChunks(const std::string& filePath, size_t chunkSize);
};

