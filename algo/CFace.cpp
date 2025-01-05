#include "CFace.h"

#include <opencv2/dnn.hpp>

CFace::CFace()
{

}


void CFace::detectFace()
{

	// 打开摄像头
	cv::VideoCapture cap(0);
	if (!cap.isOpened())
	{
		std::cerr << "Error: Cannot open the camera." << std::endl;
		return;
	}


	// 加载 SSD 模型
	cv::dnn::Net net = cv::dnn::readNetFromCaffe("deploy.prototxt", "res10_300x300_ssd_iter_140000.caffemodel");


	// 启用 OpenCL 加速
	net.setPreferableBackend(cv::dnn::DNN_BACKEND_DEFAULT);
	net.setPreferableTarget(cv::dnn::DNN_TARGET_OPENCL);


	cv::Mat frame;
	while (true)
	{
		cap >> frame;
		if (frame.empty())
		{
			std::cerr << "Error: Cannot read frame from the camera." << std::endl;
			break;
		}


		// 将帧转换为网络输入的 blob 格式
		cv::Mat blob = cv::dnn::blobFromImage(frame, 1.0, cv::Size(300, 300), cv::Scalar(104.0, 177.0, 123.0), false, false);


		// 将 blob 作为输入设置到网络中
		net.setInput(blob);


		// 进行前向传播，得到检测结果
		cv::Mat detections = net.forward();


		// 解析检测结果
		for (int i = 0; i < detections.size[2]; ++i)
		{
			float confidence = detections.ptr<float>(0, 0)[i * 7 + 2];


			// 只保留置信度大于 0.5 的人脸检测结果
			if (confidence > 0.5)
			{
				int startX = static_cast<int>(detections.ptr<float>(0, 0)[i * 7 + 3] * frame.cols);
				int startY = static_cast<int>(detections.ptr<float>(0, 0)[i * 7 + 4] * frame.rows);
				int endX = static_cast<int>(detections.ptr<float>(0, 0)[i * 7 + 5] * frame.cols);
				int endY = static_cast<int>(detections.ptr<float>(0, 0)[i * 7 + 6] * frame.rows);


				// 绘制人脸检测框
				cv::rectangle(frame, cv::Point(startX, startY), cv::Point(endX, endY), cv::Scalar(255, 0, 0), 2);
			}
		}


		// 显示结果
		//cv::imshow("Face Detection", frame);

		// 将 cv::Mat 转换为 QImage
		QImage qImage = cvMatToQImage(frame);
		//label.setPixmap(QPixmap::fromImage(qImage));
		//label.show();

		// 按下 'q' 键退出
		if (cv::waitKey(1) == 'q')
		{
			break;
		}
	}


	// 释放摄像头和关闭窗口
	cap.release();
	cv::destroyAllWindows();

}

// 函数：将 cv::Mat 转换为 QImage
QImage CFace::cvMatToQImage(const cv::Mat& inMat) {
	switch (inMat.type())
	{
	case CV_8UC4: {
		QImage image(inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGBA8888);
		return image.copy();
	}
	case CV_8UC3: {
		QImage image(inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	case CV_8UC1: {
		static QVector<QRgb> sColorTable;
		if (sColorTable.isEmpty())
		{
			for (int i = 0; i < 256; ++i)
				sColorTable.push_back(qRgb(i, i, i));
		}
		QImage image(inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8);
		image.setColorTable(sColorTable);
		return image;
	}
	default:
		std::cerr << "不支持的 cv::Mat 类型" << std::endl;
		break;
	}
	return QImage();
}

