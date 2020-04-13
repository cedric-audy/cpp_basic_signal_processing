#pragma once
#include <vector>
#include <utility>
#include "PipelineProcedures.h"

class PipelineBlueprint
{
private:
	Procedure mSteps;
public:
	//should that be here ?
	const Procedure getSteps();
	void clearPipelineBP();
	void addStep(StepType s, filter_args a );
	PipelineBlueprint();
};