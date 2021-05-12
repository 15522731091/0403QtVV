#pragma once
#include <iostream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/xfeatures2d/cuda.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <cmath>
#include <vector>
#include <typeinfo>

using namespace std;
using namespace cv;

class csTest1
{
	double area, ar;
	Mat frame, fore, img, prevImg, temp, gray, vehicle_ROI, img_temp;
	Ptr<BackgroundSubtractorMOG2> bg = createBackgroundSubtractorMOG2(500, 25, false);
	int count;


	vector<vector<Point> > contours;
	vector<Point2f> prevContoursCenters;
	vector<Point2f> tempContoursCenters;
	vector<Rect> cars;


	// start and end times
	time_t start, end;
	// fps calculated using number of frames / seconds
	double fps;
	// frame counter
	int counter = 0;
	// floating point seconds elapsed since start
	double sec;

public:
	bool isInit = false;

	void Init(Mat Img);
	Mat getSpeed(Mat Img);

private:
	double get_speed(cv::Mat& frame, vector<Point>& contour, Point2f center, float radius, vector<Point2f> prevContourCenters, double fps);
};


class csTest2
{
	Mat Frame;
	Mat FrameBackup;
	Mat BeforeFrame;

	Ptr<cv::xfeatures2d::SURF> detector;

public:
	bool isInit = false;

	void Init(Mat Img);
	Mat getSpeed(Mat Img);
private:
	void s1SetFrame(Mat InputMat);
	void s2SetROI();
	void s3GaussianBlur();
	void s4Gary();
	void s5Difference();
	void s6Threshold();
	void s7Dilate();
	void s8Erode();
	void s9DrawCar();
};



class CarSpeed
{
	csTest1 cs1;
	csTest2 cs2;

public:
	bool isInit = false;

	void Init(Mat Img);
	Mat getSpeed(Mat Img);
};
