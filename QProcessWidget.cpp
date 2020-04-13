#include <string>
#include <qstring.h>
#include "QProcessWidget.h"

QProcessWidget::QProcessWidget()
	:QWidget(), mInputs{}
{
}

QProcessWidget::QProcessWidget(std::string st)
{
	auto s = magic_enum::enum_cast<StepType>(st);

	QProcessWidget::QProcessWidget(Step{ s.value(),{0,0,0,0,0} });
}

QProcessWidget::QProcessWidget(Step s)
	: QWidget(), mInputs{}, step{ s }
{
	QHBoxLayout * layout = new QHBoxLayout();
	auto t = (magic_enum::enum_name(s.first));
	//QString t2 = (s.first == StepType::DEFAULT_LIGHTMAP) ? "Default lightmap" : "Something else";
	std::string title{ t };
	mTitle = new QLabel(QString::fromStdString(title));
	layout->addWidget(mTitle);

	for (auto& i : s.second) {
		QLineEdit * input = new QLineEdit();
		input->setValidator(new QIntValidator());
		input->setText(QString::number(i));
		mInputs.push_back(input);
		layout->addWidget(input);
	}

	this->setLayout(layout);

}

Step QProcessWidget::toStep()
{
	filter_args a{};
	for (auto& i : mInputs) {
		a.push_back(i->text().toInt());
	}

	step.second = a;

	return step;
}


