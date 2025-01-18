#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QDlgDoit.h"

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <QLabel>
#include <QTimer>

#include "QDlgDebug.h"


class QDlgDoit : public QMainWindow
{
    Q_OBJECT

public:
    QDlgDoit(QWidget *parent = nullptr);
    ~QDlgDoit();


	QDlgDebug* m_dlgDebug;
	void showDebugDlg();

	void test();


private slots:
	void updateFrame();


private:
	cv::VideoCapture cap;
	cv::dnn::Net net;

	QTimer* timer;


public:
    Ui::QDlgDoitClass ui;
};
