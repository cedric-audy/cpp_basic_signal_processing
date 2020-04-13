#include "PipelineBlueprint.h"

const Procedure PipelineBlueprint::getSteps()
{
	return mSteps;
}

void PipelineBlueprint::clearPipelineBP()
{
	mSteps.clear();
	mSteps.resize(0);
}

void PipelineBlueprint::addStep(StepType s, filter_args a)
{
	std::pair<StepType, filter_args> addition{ s,a };
	mSteps.push_back(addition);
}

PipelineBlueprint::PipelineBlueprint()
	:mSteps{0}
{
	mSteps.resize(0);
}

