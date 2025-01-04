#pragma once

#include <chrono>


class CTickCounter
{
public:
	CTickCounter();
	~CTickCounter();

	std::chrono::high_resolution_clock::time_point begin, end;
};

