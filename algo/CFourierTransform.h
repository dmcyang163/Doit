#ifndef C_FOURIER_TRANSFORM_H
#define C_FOURIER_TRANSFORM_H

#include <opencv2/opencv.hpp>
#include <string>

class CFourierTransform {
public:
	// 构造函数，接收图像路径
	CFourierTransform(const std::string& imgPath);

	// 执行傅里叶变换及相关处理的函数
	void performTransform();

private:
	std::string m_imgPath;  // 存储图像路径

	// 读取图像
	cv::Mat readImage() const;

	// 将图像转换为 float 类型
	cv::Mat convertToFloat(const cv::Mat& img) const;

	// 获取最优的 DFT 尺寸并扩展图像边界
	cv::Mat padImage(const cv::Mat& floatImg) const;

	// 准备存储结果的复数图像
	cv::Mat prepareComplexImage(const cv::Mat& paddedImg) const;

	// 执行 DFT
	cv::Mat performDFT(const cv::Mat& complexImg) const;

	// 计算幅度谱
	cv::Mat computeMagnitudeSpectrum(const cv::Mat& res) const;

	// 显示幅度谱
	void displayMagnitudeSpectrum(const cv::Mat& magSpec) const;
};

#endif