#include "VVideo.h"

VVideo::VVideo()
{
	vvC.open(videoPath);
	if (!vvC.isOpened())
	{
		isConnectCamera = false;
		throw "VideoCapture Open Faile";
	}
	isConnectCamera = true;
}

VVideo::~VVideo()
{
	vvC.release();
}

void VVideo::update()
{
	static Mat tmpMat;
	
	if (isConnectCamera && isPlay)
	{
		getSystemTime();
		vvC >> tmpMat;
		if (tmpMat.empty()) {
			return;
		}
		resize(tmpMat, tmpMat, Size(1280, 720));

		tmpMat.copyTo(vvMat);
		
		if (isFind)
		{
			if (cs.isInit == false)
			{
				cs.Init(vvMat);
			}
			else
			{
				vvMat = cs.getSpeed(vvMat);
			}
		}

		resize(vvMat, vvMat, Size(640, 360));
		displayHUD();
		Mat2QImage();
	}
}

void VVideo::start()
{
	isPlay = true;
}

void VVideo::pause()
{
	isPlay = false;
}

void VVideo::startFind()
{
	isFind = true;
}

void VVideo::stopFind()
{
	isFind = false;
}

void VVideo::Mat2QImage()
{
	cvtColor(vvMat, vvMat, COLOR_RGB2BGR);
	vvImage = QImage((uchar*)(vvMat.data), vvMat.cols, vvMat.rows, vvMat.cols*(vvMat.channels()), QImage::Format_RGB888);
}

void VVideo::getSystemTime()
{
	time_t nowTime = time(NULL);
	char nowTimeChars[64] = { 0 };
	strftime(nowTimeChars, sizeof(nowTimeChars) - 1, "%Y-%m-%d-%H-%M-%S", localtime(&nowTime));     //年-月-日 时-分-秒
	systemTime = String(nowTimeChars);
}

void VVideo::displayHUD()
{
	putText(vvMat, systemTime, Point(10, 25), 0, 0.5, Scalar(255, 255, 255), 1, LINE_AA);
}
