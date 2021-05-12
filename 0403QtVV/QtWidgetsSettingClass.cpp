#include "QtWidgetsSettingClass.h"

QtWidgetsSettingClass::QtWidgetsSettingClass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.lineEdit->setText(QDir::toNativeSeparators(qApp->applicationDirPath()));

	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(ok()));
}

QtWidgetsSettingClass::~QtWidgetsSettingClass()
{
}
void QtWidgetsSettingClass::ok()
{
	QDir *folder = new QDir;
	QString path = ui.lineEdit->text();
	bool exist = folder->exists(path);
	if (!exist)
	{
		path = ".";
	}
	QString pathwork;
	pathwork = path + "\\His";
	folder->mkdir(pathwork);
	pathwork = path + "\\faceData";
	folder->mkdir(pathwork);
	pathwork = path + "\\screenShot";
	folder->mkdir(pathwork);

	emit this->sendSetting(path.toStdString());
	close();
}
