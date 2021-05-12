#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtVV.h"
#include <qtimer.h>
#include <qpainter.h>
#include <QProcess>
#include <QDir>

#include "VVideo.h"
#include "QtWidgetsClassAbout.h"
#include "QtWidgetsConConnectCarmeClass.h"
#include "QtWidgetsSettingClass.h"

class QtVV : public QMainWindow
{
    Q_OBJECT

public:
    QtVV(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtVVClass ui;

	VVideo vv;

	int Fps = 41;//ms
	QTimer *LoopTimer;
	
	QtWidgetsClassAbout *widgetAbout = nullptr;
	QtWidgetsConConnectCarmeClass *widgetConnect = nullptr;
	QtWidgetsSettingClass *widgetSetting = nullptr;

private slots:
	void mainloop();
	void reSave();
	void About();
	void Connect();
	void getConnect(int number);
	void Setting();
	void getSetting(string path);


	void upVVideo();
	void vvStart();
	void vvPause();
	void vvStartFind();
	void vvStopFind();
};
