#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
#include <QApplication>
#include <QLabel>
#include <QPixmap>

class CFace
{
public:
	CFace();

	void detectFace();

	QImage cvMatToQImage(const cv::Mat& inMat);
};

