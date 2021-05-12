#pragma once
#include <QtWidgets/QMainWindow>
//#include <qstring.h>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <time.h>
#include <Windows.h>
#include <vector>

#include "CarSpeed.h"
using namespace cv;

class VVideo
{

	Mat vvMat;

	VideoCapture vvC;
	String videoPath = "./TestVideo/3.mp4";

	String systemTime;
	
	CarSpeed cs;

	bool isConnectCamera = false;
	bool isPlay = true;
	bool isFind = false;

public:
	QImage vvImage;

	VVideo();
	~VVideo();
	
	void update();

	void start();
	void pause();

	void startFind();
	void stopFind();

private:
	void Mat2QImage();
	void getSystemTime();
	void displayHUD();
};

