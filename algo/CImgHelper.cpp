#include "CImgHelper.h"
#include <fstream>



bool CImgHelper::mat2jpgFile(cv::Mat& inputImage, const std::string& outputFilePath, int quality/* = 90*/) {
    if (inputImage.empty())
    {
        std::cerr << "输入图像为空，无法压缩。" << std::endl;
        return false;
    }

    std::vector<uchar> buffer;
    std::vector<int> params;
    params.push_back(cv::IMWRITE_JPEG_QUALITY);
    params.push_back(quality);

    // 进行图像压缩
    bool success = cv::imencode(".jpg", inputImage, buffer, params);
    if (!success)
    {
        std::cerr << "图像压缩失败。" << std::endl;
        return false;
    }

    std::ofstream outfile(outputFilePath, std::ios::out | std::ios::binary);
    if (!outfile)
    {
        std::cerr << "无法打开输出文件: " << outputFilePath << std::endl;
        return false;
    }

    // 将压缩后的数据写入文件
    outfile.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
    outfile.close();
    return true;
}

std::string CImgHelper::mat2jpgString(cv::Mat& inputImage, int quality/* = 90*/) {
    if (inputImage.empty())
    {
        std::cerr << "输入图像为空，无法压缩。" << std::endl;
        return "";
    }

    std::vector<uchar> buffer;
    std::vector<int> params;
    params.push_back(cv::IMWRITE_JPEG_QUALITY);
    params.push_back(quality);

    // 进行图像压缩
    bool success = cv::imencode(".jpg", inputImage, buffer, params);
    if (!success)
    {
        std::cerr << "图像压缩失败。" << std::endl;
        return "";
    }

    // 将压缩后的数据存储在 std::string 中
    return std::string(buffer.begin(), buffer.end());
}

cv::Mat CImgHelper::jpgString2mat(const std::string& jpegString) {
    std::vector<uchar> buffer(jpegString.begin(), jpegString.end());
    cv::Mat image = cv::imdecode(buffer, cv::IMREAD_COLOR);
    if (image.empty())
    {
        std::cerr << "图像解码失败。" << std::endl;
        return cv::Mat();
    }
    return image;
}

// 将 cv::Mat 转换为 JPEG 格式并存储在内存中的函数
std::vector<uchar> CImgHelper::mat2jpg(const cv::Mat& image, int quality/* = 90*/) {
	std::vector<uchar> buffer;
	std::vector<int> params;
	params.push_back(cv::IMWRITE_JPEG_QUALITY);
	params.push_back(quality); // JPEG 质量，范围 0-100
	cv::imencode(".jpg", image, buffer, params);
	return buffer;
}

// 从内存中的 JPEG 数据恢复 cv::Mat 的函数
cv::Mat CImgHelper::jpg2mat(const std::vector<uchar>& buffer) {
	cv::Mat image = cv::imdecode(buffer, cv::IMREAD_COLOR);
	return image;
}

void CImgHelper::jpg2file(std::vector<uchar>& buffer, const std::string& outputFilePath)
{
	std::ofstream outfile(outputFilePath, std::ios::binary);
	outfile.write(reinterpret_cast<char*>(buffer.data()), buffer.size());
	outfile.close();
}

#if 0

int main() {
    cv::Mat image = cv::imread("input_image.jpg");
    if (image.empty())
    {
        std::cerr << "无法读取输入图像。" << std::endl;
        return -1;
    }

    std::string jpegData = compressMatToJpegString(image);
    if (!jpegData.empty())
    {
        std::cout << "图像已成功压缩，压缩后数据长度: " << jpegData.size() << std::endl;
        // 在这里可以对压缩后的数据进行进一步处理，如发送到网络或存储在其他地方
    }
    else
    {
        std::cerr << "图像压缩失败。" << std::endl;
    }

    return 0;
}

#endif