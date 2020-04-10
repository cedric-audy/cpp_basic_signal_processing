#pragma once
#include "ProcessStrategy.h"
class LightmapStrategy :
	public ProcessStrategy
{
	//process that takes an img (first of input vector) and changes its type to lightmap
	//almost an empty shell

public:
	LightmapStrategy();
	void process();
};

