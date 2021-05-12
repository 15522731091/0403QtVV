#pragma once
#include<iostream>
#include<opencv2/opencv.hpp>
#include <opencv2/face/facerec.hpp>

using namespace std;
using namespace cv;

class FindFace
{
	CascadeClassifier faceCascade;
	vector<Mat> FaceList;
	string Index = ".";
public:
	~FindFace();
	bool isInit = false;
	
	void init();
	vector<Rect> findFace(Mat Img);
	bool findFace(Mat Img, vector<Rect> &faceRects);
	vector<int> getFaceId(vector<Mat> FaceImg);
	int getFaceId(Mat FaceImg);

	double calFaceDis(Mat InFaceMat, Mat OutFaceMat);
	void reSetting(string path);
private:
	void loadFaces();
	void saveFaces();
	void saveFace(Mat Face,int id);
};

