#pragma once

#include <chrono>

#define TIMEIT CTickCounter tc(__FUNCTION__);
class CTickCounter
{
public:
	CTickCounter();
	CTickCounter(std::string str);

	~CTickCounter();

	std::chrono::high_resolution_clock::time_point begin, end;
	std::string str;
};

