#include "QDlgDoit.h"
#include "CTickCounter.h"
#include "CEigens.h"
#include <thread>

QDlgDoit::QDlgDoit(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	
	showDebugDlg();


	// 加载预训练的 SSD 人脸检测模型
	std::string path = "D:/young/Doit/algo/model/ssd/";
	std::string prototxtPath = path + "deploy.prototxt";
	std::string modelPath = path + "res10_300x300_ssd_iter_140000.caffemodel";
	net = cv::dnn::readNetFromCaffe(prototxtPath, modelPath);

	// 启用 OpenCL 加速
	//net.setPreferableBackend(cv::dnn::DNN_BACKEND_DEFAULT);
	//net.setPreferableTarget(cv::dnn::DNN_TARGET_OPENCL);


	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &QDlgDoit::updateFrame);
	//timer->start(40);


	// 打开摄像头
	cap.open(0);
	if (!cap.isOpened())
	{
		qDebug() << "Error: Cannot open the camera.";
	}

}

QDlgDoit::~QDlgDoit()
{
	cap.release();
}

void QDlgDoit::showDebugDlg()
{
	m_dlgDebug = new QDlgDebug(this);
	m_dlgDebug->show();
}


void QDlgDoit::test()
{
	CEigens eg;
	std::thread t([&eg]() {
		eg.calculate();
		});
	
	t.detach();
}

void QDlgDoit::updateFrame()
{
	CTickCounter tc;

	cv::Mat frame;
	cap >> frame;


	if (frame.empty())
	{
		qDebug() << "Error: Cannot read frame from the camera.";
		return;
	}


	// 将输入帧转换为网络所需的 blob 格式
	cv::Mat blob = cv::dnn::blobFromImage(frame, 1.0, cv::Size(300, 300), cv::Scalar(104.0, 177.0, 123.0), true, false);


	// 将 blob 作为网络输入
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
			cv::rectangle(frame, cv::Point(startX, startY), cv::Point(endX, endY), cv::Scalar(0, 0, 255), 2);
		}
	}

	// 将 cv::Mat 转换为 QImage
	QImage qImage = QImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888).rgbSwapped();


	// 创建 QPixmap 并设置到 QLabel
	QPixmap pixmap = QPixmap::fromImage(qImage);
	ui.lblImg->setPixmap(pixmap);
}
