#pragma once

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>


class CImgHelper
{
	bool mat2jpgFile(cv::Mat& inputImage, const std::string& outputFilePath, int quality = 90);
	std::string mat2jpgString(cv::Mat& inputImage, int quality = 90);
	cv::Mat jpgString2mat(const std::string& jpegString);
	std::vector<uchar> mat2jpg(const cv::Mat& image, int quality = 90);
	cv::Mat jpg2mat(const std::vector<uchar>& buffer);
	void jpg2file(std::vector<uchar>& buffer, const std::string& outputFilePath);
};

