#pragma once

#include <QDialog>
#include "ui_QDlgDebug.h"

class QDlgDebug : public QDialog
{
	Q_OBJECT

public:
	QDlgDebug(QWidget *parent = nullptr);
	~QDlgDebug();

private:
	Ui::QDlgDebugClass ui;
};
