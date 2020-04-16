#include "ImgDemo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ImgDemo w;
	w.show();
	return a.exec();
}
