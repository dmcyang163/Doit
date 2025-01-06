#include "CImgHelper.h"
#include <fstream>



bool CImgHelper::mat2jpgFile(cv::Mat& inputImg, const std::string& ofPath, int quality/* = 90*/) {
    if (inputImg.empty())
    {
        std::cerr << "输入图像为空，无法压缩。" << std::endl;
        return false;
    }

    std::vector<uchar> buffer;
    std::vector<int> params;
    params.push_back(cv::IMWRITE_JPEG_QUALITY);
    params.push_back(quality);

    // 进行图像压缩
    bool success = cv::imencode(".jpg", inputImg, buffer, params);
    if (!success)
    {
        std::cerr << "图像压缩失败。" << std::endl;
        return false;
    }

    std::ofstream outfile(ofPath, std::ios::out | std::ios::binary);
    if (!outfile)
    {
        std::cerr << "无法打开输出文件: " << ofPath << std::endl;
        return false;
    }

    // 将压缩后的数据写入文件
    outfile.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
    outfile.close();
    return true;
}

std::string CImgHelper::mat2jpgStr(cv::Mat& inputImg, int quality/* = 90*/) {
    if (inputImg.empty())
    {
        std::cerr << "输入图像为空，无法压缩。" << std::endl;
        return "";
    }

    std::vector<uchar> buffer;
    std::vector<int> params;
    params.push_back(cv::IMWRITE_JPEG_QUALITY);
    params.push_back(quality);

    // 进行图像压缩
    bool success = cv::imencode(".jpg", inputImg, buffer, params);
    if (!success)
    {
        std::cerr << "图像压缩失败。" << std::endl;
        return "";
    }

    // 将压缩后的数据存储在 std::string 中
    return std::string(buffer.begin(), buffer.end());
}

cv::Mat CImgHelper::jpgStr2mat(const std::string& jpgStr) {
    std::vector<uchar> buffer(jpgStr.begin(), jpgStr.end());
    cv::Mat image = cv::imdecode(buffer, cv::IMREAD_COLOR);
    if (image.empty())
    {
        std::cerr << "图像解码失败。" << std::endl;
        return cv::Mat();
    }
    return image;
}

void CImgHelper::jpgStr2file(const std::string& jpgStr, const std::string& ofPath)
{
	std::ofstream outFile(ofPath, std::ios::binary);
	if (!outFile.is_open())
		std::cerr << "无法打开文件: " << ofPath << std::endl;

	outFile.write(jpgStr.data(), jpgStr.size());
	outFile.close();
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