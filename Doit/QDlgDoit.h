#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QDlgDoit.h"

class QDlgDoit : public QMainWindow
{
    Q_OBJECT

public:
    QDlgDoit(QWidget *parent = nullptr);
    ~QDlgDoit();

private:
    Ui::QDlgDoitClass ui;
};
