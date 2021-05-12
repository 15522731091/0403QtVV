#include "CarSpeed.h"

void CarSpeed::Init(Mat Img)
{
	if (!isInit)
	{
		//cs1.Init(Img);
		cs2.Init(Img);
		isInit = true;
	}
}

Mat CarSpeed::getSpeed(Mat Img)
{
	//return cs1.getSpeed(Img);
	return cs2.getSpeed(Img);
}



void csTest1::Init(Mat Img)
{
	if (!isInit)
	{
		Img.copyTo(img_temp);
		cvtColor(img_temp, gray, COLOR_BGR2GRAY);
		gray.convertTo(temp, CV_8U);
		bilateralFilter(temp, prevImg, 5, 20, 20);

		// start the clock
		time(&start);
		isInit = true;
	}
}

Mat csTest1::getSpeed(Mat Img)
{
	count = 0;

	Img.copyTo(frame);
	cvtColor(frame, gray, COLOR_BGR2GRAY);
	gray.convertTo(temp, CV_8U);
	bilateralFilter(temp, img, 5, 20, 20);
	//bg.operator()(img, fore);
	bg->apply(img, fore);
	erode(fore, fore, Mat());
	dilate(fore, fore, Mat());
	//findContours(fore, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	findContours(fore, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	vector<vector<Point> > contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());
	vector<Point2f> center(contours.size());
	vector<float> radius(contours.size());

	tempContoursCenters.clear();
	time(&end);
	// calculate current FPS
	++counter;
	sec = difftime(end, start);
	fps = counter / sec;
	for (size_t i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), contours_poly[i], 10, true);
		boundRect[i] = boundingRect(Mat(contours_poly[i]));
		vehicle_ROI = img(boundRect[i]);
		area = contourArea(contours[i], false);
		ar = vehicle_ROI.cols / vehicle_ROI.rows;
		if (area > 450.0 && ar > 0.8)
		{
			minEnclosingCircle((Mat)contours_poly[i], center[i], radius[i]);
			rectangle(frame, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 1, 8, 0);
			tempContoursCenters.push_back(center[i]);
			get_speed(frame, contours[i], center[i], radius[i], prevContoursCenters, fps);
			count = count + 1;
		}
	}
	stringstream ss;
	ss << count;
	string s = ss.str();
	int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
	double fontScale = 1;
	int thickness = 3;
	cv::Point textOrg(10, 110);
	cv::putText(frame, s, textOrg, fontFace, fontScale, Scalar(255, 255, 255), thickness, 5);
	int win_size = 10;
	int maxCorners = 200;
	double qualityLevel = 0.5;
	double minDistance = 1;
	int blockSize = 3;
	double k = 0.04;
	vector<Point2f> img_corners;
	img_corners.reserve(maxCorners);
	vector<Point2f> prevImg_corners;
	prevImg_corners.reserve(maxCorners);
	goodFeaturesToTrack(img, img_corners, maxCorners, qualityLevel, minDistance, Mat(), blockSize, true);
	cornerSubPix(img, img_corners, Size(win_size, win_size), Size(-1, -1),
		//TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03));
		TermCriteria(1 | 2, 20, 0.03));
	vector<uchar> features_found;
	features_found.reserve(maxCorners);
	vector<float> feature_errors;
	feature_errors.reserve(maxCorners);
	calcOpticalFlowPyrLK(img, prevImg, img_corners, prevImg_corners, features_found, feature_errors,
		Size(win_size, win_size), 3,
		TermCriteria(1 | 2, 20, 0.3), 0, k);
	//        for( int i=0; i < features_found.size(); i++ ){
	//            Point2f p0( ceil( img_corners[i].x ), ceil( img_corners[i].y ) );
	//            Point2f p1( ceil( prevImg_corners[i].x ), ceil( prevImg_corners[i].y ) );
	//            line( frame, p0, p1, CV_RGB(255,0,0), 5 );
	//        }
	prevImg = img;
	prevContoursCenters.clear();
	prevContoursCenters = tempContoursCenters;
	//imshow("Frame", frame);
	return frame;
}

double csTest1::get_speed(cv::Mat& frame, vector<Point>& contour, Point2f center, float radius, vector<Point2f> prevContourCenters, double fps)
{
	int meters = 30;
	int maxSpeed = 100;
	if (center.x > 5 && center.x < 200) {
		for (size_t i = 0; i < prevContourCenters.size(); i++)
		{
			if (prevContourCenters[i].x < center.x) {
				double diff = double(center.x) - double(prevContourCenters[i].x);
				cv::Point x, y;
				int fontFace = 3;
				double fontScale = 0.5;
				int thickness = 1.8;
				Point textOrg(center.x - 20, center.y - radius - 5);
				String str2 = " km/h";
				double speed = diff * fps / 300 * meters * 3.6;
				if (speed > 100) speed = 101;
				std::stringstream strSpeed;
				strSpeed << speed;
				if (speed > maxSpeed) {
					putText(frame, strSpeed.str() + str2, textOrg, fontFace, fontScale, Scalar(0, 255, 0), thickness, 5);
					imwrite("./Test.jpg", frame);
				}
				else {
					putText(frame, strSpeed.str() + str2, textOrg, fontFace, fontScale, Scalar(0, 255, 0), thickness, 5);
				}
				return speed;
			}
		}
	}
}

void csTest2::Init(Mat Img)
{
	cvtColor(Img, BeforeFrame, COLOR_RGB2GRAY);
	detector = cv::xfeatures2d::SURF::create(400);
}

Mat csTest2::getSpeed(Mat Img)
{
	s1SetFrame(Img);
	s2SetROI();
	s3GaussianBlur();
	s4Gary();
	s5Difference();
	s6Threshold();
	s7Dilate();
	s8Erode();
	s9DrawCar();

	return FrameBackup;
}

void csTest2::s1SetFrame(Mat InputMat)
{
	InputMat.copyTo(Frame);
	InputMat.copyTo(FrameBackup);
}

void csTest2::s2SetROI()
{
	Rect ROI = Rect(0, 0, Frame.cols, Frame.rows);
	Frame = Frame(ROI);
}

void csTest2::s3GaussianBlur()
{
	GaussianBlur(Frame, Frame, Size(3, 3), 2, 2);
}

void csTest2::s4Gary()
{
	cvtColor(Frame, Frame, COLOR_RGB2GRAY);
}

void csTest2::s5Difference()
{
	Mat tmp;
	absdiff(BeforeFrame, Frame, tmp);
	BeforeFrame = Frame;
	Frame = tmp;
}

void csTest2::s6Threshold()
{
	threshold(Frame, Frame, 30, 255, THRESH_BINARY);
}

void csTest2::s7Dilate()
{
	Mat element = getStructuringElement(MORPH_RECT, Size(50, 50));
	dilate(Frame, Frame, element);
}

void csTest2::s8Erode()
{
	Mat element = getStructuringElement(MORPH_ERODE, Size(45, 45));
	erode(Frame, Frame, element);
}

void csTest2::s9DrawCar()
{
	static double scalce = 0.3;
	std::vector<KeyPoint> KpCar, KpSour;
	Mat DpCar, DpSour,Car,Sour;
	// 加载主画面
	FrameBackup.copyTo(Sour);
	detector->detectAndCompute(Sour, noArray(), KpSour, DpSour);
	//matchTemplate

	vector<vector<Point> > contours;
	findContours(Frame, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	vector<Rect> boundRect(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		boundRect[i] = boundingRect(contours[i]);

		//if (boundRect[i].width < 15 || boundRect[i].height < 15)
		//{
		//	continue;
		//}
		//获取当前画面某一车辆画面
		Car = FrameBackup(boundRect[i]);
		//resize(Car, Car, Size(0, 0), 2, 2);
		detector->detectAndCompute(Car, noArray(), KpCar, DpCar);
		if (KpCar.size()==0)
		{
			continue;
		}
		Ptr<DescriptorMatcher> matcherTmp = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);

		std::vector< std::vector<DMatch> > KNN_mTmp;
		std::vector<DMatch> good_matchesTmp;

		matcherTmp->knnMatch(DpCar, DpSour, KNN_mTmp, 2);

		double sumx = 0;
		double sumy = 0;

		string CarClass = "undifine";

		for (size_t i = 0; i < KNN_mTmp.size(); i++)
		{
			if (KNN_mTmp[i][0].distance < 0.66 * KNN_mTmp[i][1].distance)
			{
				good_matchesTmp.push_back(KNN_mTmp[i][0]);
				sumx += Car.cols / 2 - KpCar[KNN_mTmp[i][0].queryIdx].pt.x + KpSour[KNN_mTmp[i][0].trainIdx].pt.x;
				sumy += Car.rows / 2 - KpCar[KNN_mTmp[i][0].queryIdx].pt.y + KpSour[KNN_mTmp[i][0].trainIdx].pt.y;
			}
		}
		sumx = sumx / KNN_mTmp.size();
		sumy = sumy / KNN_mTmp.size();

		Mat img_matches, imgmap, imgminmap;
		double dis = sqrt(sumx* sumx + sumy * sumy);

		drawMatches(Car, KpCar, Sour, KpSour, good_matchesTmp, img_matches, Scalar::all(-1), Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
		
		int CarSpeed = 0;
		CarSpeed = dis * scalce - (boundRect[i].y - 50.0) / 5.0;
		// 根据面积判断车型
		if (Car.cols * Car.rows>4500)
		{
			CarClass = "Large Car";
		}
		else
		{
			CarClass = "Compact Car";
		}
		// 在图上写上车型
		putText(FrameBackup, CarClass, Point(boundRect[i].x, boundRect[i].y+20), 1, 1, Scalar(0, 255, 0), 2);
		// 在图上写车速
		putText(FrameBackup, to_string((int)CarSpeed), Point(boundRect[i].x, boundRect[i].y), 1, 1, Scalar(0, 255, 0), 1);
		// 将车车框出来
		rectangle(FrameBackup, Rect(boundRect[i].x , boundRect[i].y, boundRect[i].width, boundRect[i].height), Scalar(0, 255, 0), 1);
	}
}
