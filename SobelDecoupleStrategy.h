#pragma once
#include "ProcessStrategy.h"
class SobelDecoupleStrategy :
	public ProcessStrategy
{
public:
	void process();
	SobelDecoupleStrategy();
};

