#pragma once

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>


class CImgHelper
{
	bool mat2jpgFile(cv::Mat& inputImg, const std::string& ofPath, int quality = 90);
	std::string mat2jpgStr(cv::Mat& inputImg, int quality = 90);
	cv::Mat jpgStr2mat(const std::string& jpgStr);
	void jpgStr2file(const std::string& jpgStr, const std::string& ofPath);
};

