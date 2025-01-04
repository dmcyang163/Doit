#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QDlgDoit.h"

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <QLabel>
#include <QTimer>

class QDlgDoit : public QMainWindow
{
    Q_OBJECT

public:
    QDlgDoit(QWidget *parent = nullptr);
    ~QDlgDoit();


private slots:
	void updateFrame();


private:
	cv::VideoCapture cap;
	cv::dnn::Net net;

	QTimer* timer;


private:
    Ui::QDlgDoitClass ui;
};
