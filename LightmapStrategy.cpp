#include "LightmapStrategy.h"

LightmapStrategy::LightmapStrategy()
	:ProcessStrategy()
{
}

void LightmapStrategy::process()
{
	for (auto& i : mOutput) {
		i.makeChannelFrom(channelType::GRAY, channelType::LIGHTMAP);
	}
}
