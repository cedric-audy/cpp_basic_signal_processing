#include "Grayscale1DImage.h"


Grayscale1DImage::Grayscale1DImage(QImage & im):
	mImg{}, mWidth{ im.width() }, mHeight{ im.height() }, mType{GrayscaleType::BASIC}
{
	//problem: cant use const ref bc reinterpret_cast wont work, yet there is no need to modify parameter img
	//probablement pas optimal ... const iterator ?
	int * curPix{ reinterpret_cast<int*>(im.bits()) };
	int * endPix{ curPix + im.width() * im.height() };

	while (curPix < endPix) {

		int c{ *curPix };

		unsigned char r{ static_cast<unsigned char>((c & 0x00'FF'00'00) >> 16) };
		unsigned char g{ static_cast<unsigned char>((c & 0x00'00'FF'00) >> 8) };
		unsigned char b{ static_cast<unsigned char>((c & 0x00'00'00'FF) >> 0) };

		int average{ static_cast<int>((float)r * 0.25f + (float)g * 0.67f + (float)b * 0.08f) };

		//note: push back is slow, change to pre initialized vector and use ptrs
		mImg.push_back(average);
		++curPix;
	}
}
