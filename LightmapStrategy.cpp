#include "LightmapStrategy.h"

LightmapStrategy::LightmapStrategy()
	:ProcessStrategy()
{
}

void LightmapStrategy::process()
{
	mOutput.at(0).setType(channelType::LIGHTMAP);
}
