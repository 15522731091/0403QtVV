#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtVV.h"
#include <qtimer.h>
#include <qpainter.h>
#include <QProcess>
#include <QDir>

#include "VVideo.h"

class QtVV : public QMainWindow
{
    Q_OBJECT

public:
    QtVV(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtVVClass ui;

	VVideo vv;

	int Fps = 16;//ms
	QTimer *LoopTimer;


private slots:
	void mainloop();


	void upVVideo();
	void vvStart();
	void vvPause();
	void vvStartFind();
	void vvStopFind();
};
