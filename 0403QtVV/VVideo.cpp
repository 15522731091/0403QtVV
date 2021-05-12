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

void VVideo::openCamrea()
{
	vvC.open(vvCid);
	if (!vvC.isOpened())
	{
		isConnectCamera = false;
		throw "VideoCapture Open Faile";
	}
	isConnectCamera = true;
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
		resize(tmpMat, tmpMat, Size(640, 360));
		tmpMat.copyTo(vvMat);
		displayHUD();

		if (isSave)
		{
			if (loopSave.isOpened() == false)
			{
				loopSave.open(loopSaveName, VideoWriter::fourcc('X', '2', '6', '4'), 24, Size(tmpMat.cols, tmpMat.rows));
			}
			else
			{
				loopSave.write(vvMat);
			}
		}

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

void VVideo::startSave()
{
	isSave = true;
	if (loopSaveName == "")
	{
		getSystemTime();
		loopSaveName = Index + "/His/"+systemTime + ".mp4";
	}
}

void VVideo::stopSave()
{
	isSave = false;
	loopSave.release();
	loopSaveName = "";
}

void VVideo::startFind()
{
	isFind = true;
}

void VVideo::stopFind()
{
	isFind = false;
}

void VVideo::screenShot()
{
	if (!vvMat.empty())
	{
		string nowPngName = Index +"/screenShot/" + systemTime + ".png";
		imwrite(nowPngName, vvMat);
	}
}

void VVideo::reConnect(int number)
{

	if (isPlay)
	{
		isPlay = false;
	}
	vvC.release();
	vvCid = number;
	vvC.open(vvCid);
	if (!vvC.isOpened())
	{
		isConnectCamera = false;
		throw "VideoCapture ReOpen Faile";
	}
	isConnectCamera = true;

}

void VVideo::reSetting(string path)
{
	Index = path;
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
	putText(vvMat, systemTime, Point(10, 25), 0, 0.5, Scalar(0, 0, 0), 1, LINE_AA);
	if (isSave)
	{
		circle(vvMat, Point(230, 20), 5, Scalar(0, 0, 255), -1, LINE_AA);
	}
}
