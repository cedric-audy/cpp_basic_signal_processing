#pragma once
#include <algorithm>
#include <vector>

#include "Custom1DChannel.h"

class Custom1DImg
{
public:
	enum colorSpace
	{
		RGB,
		HSV
	};

	Custom1DImg() = default;
	Custom1DImg(QImage & im, colorSpace = colorSpace::HSV);

	Custom1DChannel * getChannel(channelType ctype);
	void Custom1DImg::makeChannelFrom(channelType from, channelType to);

	void setWidth(size_t w) { mWidth = w; }
	size_t width() { return mWidth; }

	void setHeight(size_t h) { mHeight = h; }
	size_t height() { return mHeight; }

	colorSpace getColorSpace() { return mColorSpace; };
	void setColorSpace(colorSpace  cs) { mColorSpace = cs; };

private:
	colorSpace mColorSpace;

	int mWidth;
	int mHeight;
	//color space
	std::vector<Custom1DChannel> channels;

	void defaultChannels();

};

