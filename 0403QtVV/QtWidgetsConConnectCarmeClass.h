#pragma once

#include <QWidget>
#include "ui_QtWidgetsConConnectCarmeClass.h"
#include <opencv2/opencv.hpp>

class QtWidgetsConConnectCarmeClass : public QWidget
{
	Q_OBJECT

public:
	QtWidgetsConConnectCarmeClass(QWidget *parent = Q_NULLPTR);
	~QtWidgetsConConnectCarmeClass();

private:
	Ui::QtWidgetsConConnectCarmeClass ui;

private: 
	void updata();

private slots:

	void ok();

signals:
	void sendConnect(int number);
};
