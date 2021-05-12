#pragma once

#include <QWidget>
#include "ui_QtWidgetsClassAbout.h"

class QtWidgetsClassAbout : public QWidget
{
	Q_OBJECT

public:
	QtWidgetsClassAbout(QWidget *parent = Q_NULLPTR);
	~QtWidgetsClassAbout();

private:
	Ui::QtWidgetsClassAbout ui;
};
