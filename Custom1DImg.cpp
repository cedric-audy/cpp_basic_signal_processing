#include "Custom1DImg.h"


Custom1DImg::Custom1DImg(QImage & im, colorSpace cSpace)
	:mWidth{ im.width() }, mHeight{ im.height() }, channels{}, mColorSpace{cSpace}
{
	Custom1DImg::defaultChannels();

	int * curPix{ reinterpret_cast<int*>(im.bits()) };
	int * endPix{ curPix + mWidth * mHeight };

	unsigned char * channel1{ Custom1DImg::getChannel(CHANNEL1)->getStart() };
	unsigned char * channel2{ Custom1DImg::getChannel(CHANNEL2)->getStart() };
	unsigned char * channel3{ Custom1DImg::getChannel(CHANNEL3)->getStart() };
	unsigned char * channelGray{ Custom1DImg::getChannel(GRAY)->getStart() };

	while (curPix < endPix) {

		int curVal{ *curPix };

		unsigned char c1{ static_cast<unsigned char>((curVal & 0x00'FF'00'00) >> 16) };
		unsigned char c2{ static_cast<unsigned char>((curVal & 0x00'00'FF'00) >> 8) };
		unsigned char c3{ static_cast<unsigned char>((curVal & 0x00'00'00'FF) >> 0) };

		*channel1 = c1;
		*channel2 = c2;
		*channel3 = c3;
		*channelGray = mColorSpace == HSV ? c3 : static_cast<unsigned char>((float)c1 * 0.25f + (float)c2 * 0.67f + (float)c3 * 0.08f);
	
		++channel1;
		++channel2;
		++channel3;
		++channelGray;
		++curPix;
	}
}

void Custom1DImg::defaultChannels()
{
	Custom1DChannel c{ &mWidth,&mHeight,channelType::CHANNEL1 };
	channels.push_back(c);
	c.setType(channelType::CHANNEL2);
	channels.push_back(c);
	c.setType(channelType::CHANNEL3);
	channels.push_back(c);
	c.setType(channelType::GRAY);
	channels.push_back(c);

}
Custom1DChannel * Custom1DImg::getChannel(channelType ctype)
{
	//return &(*(std::find(channels.begin(), channels.end(), [&ctype](const channelType c) {return c == ctype; })));

	return nullptr;
}

void Custom1DImg::makeChannelFrom(channelType from, channelType to){

	//auto fromType{std::find(channels.begin(), channels.end(), [&from](const channelType c) {return c == from; }) };
	//Custom1DChannel newChannel = *fromType;
	//newChannel.setType(to);
	//channels.push_back(newChannel);
}

