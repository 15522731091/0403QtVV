#pragma once

#include <Qdir>
#include <QWidget>
#include <iostream>
#include "ui_QtWidgetsSettingClass.h"
using namespace std;

class QtWidgetsSettingClass : public QWidget
{
	Q_OBJECT

public:
	QtWidgetsSettingClass(QWidget *parent = Q_NULLPTR);
	~QtWidgetsSettingClass();

private:
	Ui::QtWidgetsSettingClass ui;

private slots:
	void ok();

signals:
	void sendSetting(string path);
};
