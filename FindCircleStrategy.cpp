#include "FindCircleStrategy.h"

void FindCircleStrategy::setRadius(size_t r)
{
	mCircleRadius = r;
}

void FindCircleStrategy::process()
{
	int width = mInput->at(0).width();
	int height = mInput->at(0).height();

	//inspiration
	//https://www.thecrazyprogrammer.com/2016/12/bresenhams-midpoint-circle-algorithm-c-c.html

	int x0{ 0 };
	int y0{ 0 };
	int rad = mCircleRadius;

	int x = rad;
	int y = 0;
	int err = 0;

	std::vector<int> circleDots{};

	while (x >= y) {
		circleDots.push_back(width * (x0 + x) + (y0 + y));
		circleDots.push_back(width * (x0 + y) + (y0 + x));
		circleDots.push_back(width * (x0 - y) + (y0 + x));
		circleDots.push_back(width * (x0 - x) + (y0 + y));
		circleDots.push_back(width * (x0 - x) + (y0 - y));
		circleDots.push_back(width * (x0 - y) + (y0 - x));
		circleDots.push_back(width * (x0 + y) + (y0 - x));
		circleDots.push_back(width * (x0 + x) + (y0 - y));

		if (err <= 0) {
		
			y += 1;
			err += 2 * y + 1;
		}

		if (err > 0) {
		
			x -= 1;
			err -= 2 * x + 1;
		}
	}

	unsigned char * in = mInput->at(0).getStart();
	unsigned char * out = mOutput.at(0).getStart();
	unsigned char * out_end = mOutput.at(0).getStart() + (width*height);

	while (out < out_end) {
		*out = 0;
		for (auto& p : circleDots) {
			if (p > 0 && p < width*height) {
				in += p;
				*out += *in/112;
				in -= p;
			}
			p += 1;
		}
	
		++out;
	}
}


FindCircleStrategy::FindCircleStrategy()
	:ProcessStrategy(), mCircleRadius{22}
{
}
