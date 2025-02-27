﻿#include "CTickCounter.h"
#include <QDebug>
#include <QString>
#include <iostream>



CTickCounter::CTickCounter()
{
	begin = std::chrono::high_resolution_clock::now();
}

CTickCounter::CTickCounter(std::string str)
{
	this->str = str;
	begin = std::chrono::high_resolution_clock::now();

}

CTickCounter::~CTickCounter()
{
	end = std::chrono::high_resolution_clock::now();
	// 计算时间差并转换为ms
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

	
	//qDebug() << QString::number(duration.count());
	std::cout << str << "执行时间: " << duration.count() << " ms" << std::endl;
}
