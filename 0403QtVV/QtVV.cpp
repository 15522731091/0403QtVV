#include "QtVV.h"

QtVV::QtVV(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	LoopTimer = new QTimer(this);
	LoopTimer->start(Fps);//1000/30=33.3,1000/24=42
	connect(LoopTimer, SIGNAL(timeout()), this, SLOT(mainloop()));


	connect(ui.action_About, SIGNAL(triggered()), this, SLOT(About()));
	connect(ui.action_Setting, SIGNAL(triggered()), this, SLOT(Setting()));
	connect(ui.action_ConCam, SIGNAL(triggered()), this, SLOT(Connect()));

	connect(ui.pushButton_Start, SIGNAL(clicked()), this, SLOT(vvStart()));
	connect(ui.pushButton_Pause, SIGNAL(clicked()), this, SLOT(vvPause()));
	connect(ui.pushButton_StartFind, SIGNAL(clicked()), this, SLOT(vvStartFind()));
	connect(ui.pushButton_StopFind, SIGNAL(clicked()), this, SLOT(vvStopFind()));


	vv.Index = QDir::toNativeSeparators(qApp->applicationDirPath()).toStdString();
	QDir *folder = new QDir;
	QString path = QString::fromStdString(vv.Index);
	QString pathwork;
	pathwork = path + "\\His";
	folder->mkdir(pathwork);
}

void QtVV::mainloop()
{
	static bool isUpdataEnd = true;
	//更新是否已结束
	if (isUpdataEnd)
	{
		isUpdataEnd = false;
		emit this->upVVideo();
		isUpdataEnd = true;
		//启动下一帧
		LoopTimer->start(Fps);
	}
	else
	{
		//启动下一帧
		LoopTimer->start(Fps);
	}
}

void QtVV::reSave()
{
	vv.stopSave();
	vv.startSave();
}

void QtVV::About()
{
	if (widgetAbout == nullptr)
	{
		widgetAbout = new QtWidgetsClassAbout();
		widgetAbout->show();
	}
	else
	{
		widgetAbout->show();
	}
}

void QtVV::Connect()
{
	if (widgetConnect == nullptr)
	{
		widgetConnect = new QtWidgetsConConnectCarmeClass();
		connect(widgetConnect, SIGNAL(sendConnect(int)), this, SLOT(getConnect(int)));
		widgetConnect->show();
	}
	else
	{
		widgetConnect->show();
	}
}

void QtVV::getConnect(int number)
{
	vv.reConnect(number);
}

void QtVV::Setting()
{
	if (widgetSetting == nullptr)
	{
		widgetSetting = new QtWidgetsSettingClass();
		connect(widgetSetting, SIGNAL(sendSetting(string)), this, SLOT(getSetting(string)));
		widgetSetting->show();
	}
	else
	{
		widgetSetting->show();
	}
}

void QtVV::getSetting(string path)
{
	vv.reSetting(path);
}

void QtVV::upVVideo()
{
	vv.update();
	//update();
	ui.vvImg->setPixmap(QPixmap::fromImage(vv.vvImage));
}

void QtVV::vvStart()
{
	vv.start();
}

void QtVV::vvPause()
{
	vv.pause();
}

void QtVV::vvStartFind()
{
	vv.startFind();
}

void QtVV::vvStopFind()
{
	vv.stopFind();
}