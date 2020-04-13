#pragma once
#include "ImgProcessingSteps.h"
using filter_args = std::vector<int>;
using Procedure = std::vector<std::pair<StepType, filter_args>>;
using Step = std::pair<StepType, filter_args>;