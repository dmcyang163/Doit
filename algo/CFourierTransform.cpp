#include "CFourierTransform.h"
#include <iostream>
#include <vector>
#include <omp.h>
#include "CTickCounter.h"

// 构造函数，接收图像路径
CFourierTransform::CFourierTransform(const std::string& imgPath) : m_imgPath(imgPath) {}

// 执行傅里叶变换及相关处理的函数
void CFourierTransform::performTransform() {
	cv::Mat img = readImage();
	if (img.empty())
	{
		throw std::runtime_error("Could not open or find the image");
	}
	TIMEIT;
	cv::Mat floatImg = convertToFloat(img);
	cv::Mat paddedImg = padImage(floatImg);
	cv::Mat complexImg = prepareComplexImage(paddedImg);
	cv::Mat res = performDFT(complexImg);
	cv::Mat magSpec = computeMagnitudeSpectrum(res);
	//displayMagnitudeSpectrum(magSpec);
}

// 读取图像
cv::Mat CFourierTransform::readImage() const {
	cv::Mat img = cv::imread(m_imgPath, cv::IMREAD_GRAYSCALE);
	return img;
}

// 将图像转换为 float 类型
cv::Mat CFourierTransform::convertToFloat(const cv::Mat& img) const {
	cv::Mat floatImg;
	img.convertTo(floatImg, CV_32F);
	return floatImg;
}

// 获取最优的 DFT 尺寸并扩展图像边界
cv::Mat CFourierTransform::padImage(const cv::Mat& floatImg) const {
	cv::Size dftSize;
	dftSize.width = cv::getOptimalDFTSize(floatImg.cols);
	dftSize.height = cv::getOptimalDFTSize(floatImg.rows);
	cv::Mat paddedImg;
	cv::copyMakeBorder(floatImg, paddedImg, 0, dftSize.height - floatImg.rows, 0, dftSize.width - floatImg.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
	return paddedImg;
}

// 准备存储结果的复数图像
cv::Mat CFourierTransform::prepareComplexImage(const cv::Mat& paddedImg) const {
	cv::Mat complexImg;
	cv::merge(std::vector<cv::Mat>{paddedImg, cv::Mat::zeros(paddedImg.size(), CV_32F)}, complexImg);
	return complexImg;
}

// 执行 DFT
cv::Mat CFourierTransform::performDFT(const cv::Mat& complexImg) const {
	TIMEIT;

	cv::Mat res;
	cv::dft(complexImg, res, cv::DFT_COMPLEX_OUTPUT | cv::DFT_SCALE);
	return res;
}
// 假设输入范围在 [0, 100] 之间
const int TABLE_SIZE = 10000;
std::vector<float> sqrtTable(TABLE_SIZE);

void initSqrtTable() {
	for (int i = 0; i < TABLE_SIZE; ++i)
	{
		sqrtTable[i] = std::sqrt(static_cast<float>(i) / 100.0f);
	}
}
// 计算幅度谱
cv::Mat CFourierTransform::computeMagnitudeSpectrum(const cv::Mat& res) const {

	std::vector<cv::Mat> channels;
	cv::split(res, channels);
	cv::Mat magSpec(channels[0].size(), CV_32F);
	TIMEIT;
#if 0


#pragma omp parallel for
	for (int r = 0; r < channels[0].rows; ++r)
	{
		for (int c = 0; c < channels[0].cols; ++c)
		{
			// 获取当前元素的实部和虚部
			float re = channels[0].at<float>(r, c);
			float im = channels[1].at<float>(r, c);

			// 计算幅度谱，存储在 magSpec 中
			magSpec.at<float>(r, c) = std::sqrt(re * re + im * im);
		}
	}
#endif

#if 0

	// 使用 AVX 指令集
#pragma omp parallel for
	for (int r = 0; r < channels[0].rows; ++r)
	{
		for (int c = 0; c < channels[0].cols; c += 8)
		{
			__m256 reVec = _mm256_loadu_ps(&channels[0].at<float>(r, c));
			__m256 imVec = _mm256_loadu_ps(&channels[1].at<float>(r, c));
			__m256 re2 = _mm256_mul_ps(reVec, reVec);
			__m256 im2 = _mm256_mul_ps(imVec, imVec);
			__m256 sum = _mm256_add_ps(re2, im2);
			__m256 magVec = _mm256_sqrt_ps(sum);
			_mm256_storeu_ps(&magSpec.at<float>(r, c), magVec);
		}
	}

#endif

	// 使用 SSE 指令集
#pragma omp parallel for
	for (int r = 0; r < channels[0].rows; ++r)
	{
		for (int c = 0; c < channels[0].cols; c += 4)
		{
			__m128 reVec = _mm_loadu_ps(&channels[0].at<float>(r, c));
			__m128 imVec = _mm_loadu_ps(&channels[1].at<float>(r, c));
			__m128 re2 = _mm_mul_ps(reVec, reVec);
			__m128 im2 = _mm_mul_ps(imVec, imVec);
			__m128 sum = _mm_add_ps(re2, im2);
			__m128 magVec = _mm_sqrt_ps(sum);
			_mm_storeu_ps(&magSpec.at<float>(r, c), magVec);
		}
	}

	// 使用 OpenMP 并行化进行 log 变换和归一化
#pragma omp parallel for
	for (int i = 0; i < magSpec.total(); ++i)
	{
		float value = magSpec.at<float>(i);
		magSpec.at<float>(i) = std::log(value + 1);
	}

	//cv::log(magSpec + 1, magSpec);
	cv::normalize(magSpec, magSpec, 0, 1, cv::NORM_MINMAX);
	return magSpec;
}

// 显示幅度谱
void CFourierTransform::displayMagnitudeSpectrum(const cv::Mat& magSpec) const {
	cv::imshow("Magnitude Spectrum", magSpec);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

#if 0
int main() {



	try
	{
		// 创建 CFourierTransform 类的对象并调用 performTransform 函数
		CFourierTransform fourierTransform("input_image.jpg");
		fourierTransform.performTransform();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return 0;
}
#endif