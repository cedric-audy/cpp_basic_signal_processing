#include "QBlueprintBuilder.h"


QBlueprintBuilder::QBlueprintBuilder()
	:QGroupBox("Blueprint Text Input"),
	mApply{new QPushButton("Apply changes")},
	mInput{ new QLineEdit() },
	mBlueprint{},
	mBlueprintOptions{new QComboBox()}
{
	QHBoxLayout * hl{ new QHBoxLayout() };
	hl->addWidget(mApply);
	hl->addWidget(mBlueprintOptions);

	QVBoxLayout * vl{ new QVBoxLayout() };
	vl->addLayout(hl);
	vl->addWidget(mInput);

	setLayout(vl);
	mBlueprintOptions->addItem("test");
	mBlueprintOptions->addItem("DEFAULT_LIGHTMAP:11:11:99");
	connect(mBlueprintOptions, &QComboBox::currentTextChanged, mInput, &QLineEdit::setText);
	connect(mApply, &QPushButton::clicked, this, &QBlueprintBuilder::applyBlueprint);
}

void QBlueprintBuilder::applyBlueprint()
{
	QStringList newBlueprint{ mInput->text().split(' ') };

	for (auto& s : newBlueprint) {
	
		QStringList args{ s.split(':') };
		auto st = magic_enum::enum_cast<StepType>(args[0].toStdString());
		args.removeAt(0);
		filter_args int_args{};
		for (auto& i : args) {
			int_args.push_back(i.toInt());
		}
		if (st.has_value()) {
			mBlueprint.addStep(st.value(), int_args);
		}
	}
	this->setVisible(false);

}




//some old stuff

//QBlueprintBuilder::QBlueprintBuilder()
//	:QGroupBox("Blueprint Builder"),
//	mApply{ new QPushButton("Apply changes")},
//	mButtons{ new QHBoxLayout() },
//	mSteps{}
//
//{
//	QBlueprintBuilder::setButtons();
//}
//
//
//void QBlueprintBuilder::setButtons()
//{
//	mButtons->addWidget(mApply);
//
//	connect(mApply, &QPushButton::clicked, this, &QBlueprintBuilder::applyChanges);
//}
//
//
//void QBlueprintBuilder::showBlueprint()
//{
//	
//	//qDeleteAll(this->children());
//	//QBlueprintBuilder::setButtons();
//	QVBoxLayout * layout = new QVBoxLayout();
//
//	layout->addLayout(mButtons);
//	for (auto& i : mBlueprint->getSteps()) {
//	
//		QProcessWidget *w{ new QProcessWidget(i) };
//		layout->addWidget(w);
//		mSteps.push_back(w);
//	}
//
//	layout->addStretch(1);
//	this->setLayout(layout);
//}
//
//void QBlueprintBuilder::applyChanges()
//{
//	mBlueprint->clearPipelineBP();
//
//	for (auto& s : mSteps) {
//	
//		mBlueprint->addStep(s->toStep().first, s->toStep().second);
//	}
//
//	QBlueprintBuilder::showBlueprint();
//
//}
//
//void QBlueprintBuilder::setBlueprint(PipelineBlueprint * bp)
//{
//	mBlueprint = bp;
//}

