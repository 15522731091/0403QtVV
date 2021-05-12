#include "QtVV.h"

QtVV::QtVV(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	LoopTimer = new QTimer(this);
	LoopTimer->start(Fps);//1000/30=33.3,1000/24=42
	connect(LoopTimer, SIGNAL(timeout()), this, SLOT(mainloop()));

	connect(ui.pushButton_Start, SIGNAL(clicked()), this, SLOT(vvStart()));
	connect(ui.pushButton_Pause, SIGNAL(clicked()), this, SLOT(vvPause()));
	connect(ui.pushButton_StartFind, SIGNAL(clicked()), this, SLOT(vvStartFind()));
	connect(ui.pushButton_StopFind, SIGNAL(clicked()), this, SLOT(vvStopFind()));
}

void QtVV::mainloop()
{
	static bool isUpdataEnd = true;
	//�����Ƿ��ѽ���
	if (isUpdataEnd)
	{
		isUpdataEnd = false;
		emit this->upVVideo();
		isUpdataEnd = true;
		//������һ֡
		LoopTimer->start(Fps);
	}
	else
	{
		//������һ֡
		LoopTimer->start(Fps);
	}
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