#include "QtWidgetsConConnectCarmeClass.h"

QtWidgetsConConnectCarmeClass::QtWidgetsConConnectCarmeClass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	updata();

	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(ok()));
}

QtWidgetsConConnectCarmeClass::~QtWidgetsConConnectCarmeClass()
{

}

void QtWidgetsConConnectCarmeClass::updata()
{
	bool isCheckOver = false;
	int count = 0;
	int maxID = -1;
	ui.comboBox->clear();
	while (!isCheckOver)
	{
		cv::VideoCapture VC(count);
		if (!VC.isOpened())
		{
			break;
		}
		VC.release();
		ui.comboBox->addItem(QString::asprintf("CAM: %d", count));
		maxID = count;
		count++;
	}
}

void QtWidgetsConConnectCarmeClass::ok()
{
	if (ui.comboBox->currentIndex() >= 0)
	{
		emit this->sendConnect(ui.comboBox->currentIndex());
	}
	close();
}

