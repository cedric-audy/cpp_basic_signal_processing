#pragma once
#include <qwidget.h>
#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit.h>
#include <QValidator.h>
#include <vector>

#include "magic_enum.hpp" //allows me to go from enum to string easily
#include "PipelineProcedures.h"

class QProcessWidget :
	public QWidget
{
public:
	QProcessWidget();
	QProcessWidget(std::string st);
	QProcessWidget(Step s);
	Step toStep();

	
private:
	Step step;
	QLabel * mTitle;
	std::vector<QLineEdit *> mInputs;

};

