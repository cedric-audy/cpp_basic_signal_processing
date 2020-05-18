#pragma once
#include <qgroupbox.h>
#include <qcombobox.h>
#include <QVBoxLayout>
#include <qlineedit.h>
#include"PipelineBlueprint.h"
#include <qpushbutton.h>
#include <vector>
#include "magic_enum.hpp"

class QBlueprintBuilder :
	public QGroupBox
{

public:
	QBlueprintBuilder();


	//void showBlueprint();
	//void setBlueprint(PipelineBlueprint * bp);
	//void applyChanges();

private:
	void applyBlueprint();
	QPushButton *mApply;
	QComboBox *mBlueprintOptions;
	QLineEdit *mInput;

	PipelineBlueprint mBlueprint;
};

//class QBlueprintBuilder :
//	public QGroupBox
//{
//
//public:
//	QBlueprintBuilder();
//
//	void showBlueprint();
//	void setBlueprint(PipelineBlueprint * bp);
//	void applyChanges();
//
//private:
//
//
//	QHBoxLayout *mButtons;
//	QPushButton *mApply;
//
//
//	PipelineBlueprint* mBlueprint;
//	std::vector<QProcessWidget*> mSteps;
//
//	void setButtons();
//
//
//};