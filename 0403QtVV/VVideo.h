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
	int vvCid = 0;
	String videoPath = "./TestVideo/3.mp4";
	VideoWriter loopSave;

	String systemTime;
	String loopSavePath = "Save\\";
	String loopSaveName="";
	//bool isExistLoopSavePath = false;
	
	CarSpeed cs;

	bool isConnectCamera = false;
	bool isPlay = true;
	bool isSave = false;
	bool isFind = false;

public:
	string Index = ".";

	VVideo();
	~VVideo();

	void openCamrea();

	QImage vvImage;

	void update();

	void start();
	void pause();

	void startSave();
	void stopSave();

	void startFind();
	void stopFind();

	void screenShot();

	void reConnect(int number);
	void reSetting(string path);
private:
	void Mat2QImage();
	void getSystemTime();
	void displayHUD();
};

