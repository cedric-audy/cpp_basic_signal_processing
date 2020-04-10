#include "UniformizeStrategy.h"

bool UniformizeStrategy::isValid()
{
	bool hasBasic = false, hasMap = false;
	for (auto& i: *mInput) {

		if (i.type() == GrayscaleType::BASIC) { hasBasic = true; }
		else if (i.type() == GrayscaleType::LIGHTMAP) {hasMap = true;}

	}
	return hasBasic && hasMap;
}

void UniformizeStrategy::process()
{
	Grayscale1DImage * map;
	Grayscale1DImage * image;

	for (auto& i : *mInput) {
		if (i.type() == GrayscaleType::BASIC) {
			image = &i;
		}
		else if (i.type() == GrayscaleType::LIGHTMAP) {
			map = &i;
		}

	}

	unsigned char * in = image->getStart();
	unsigned char * in_end = image->getStart() + (image->height()*image->width());
	unsigned char * in_map = map->getStart();


	std::vector<double> divided{};

	while (in != in_end) {
	

		if (*in_map != 0) {
			double d = (double) ((double)*(in) * 1/(double)*(in_map));
			divided.push_back(d);
			
			//mMax = d > mMax ? d : mMax;
			//mMin = d < mMin ? d : mMin;

			if (d > mMax) { mMax = d; }
			if (d < mMin) { mMin = d; }
		} 

		else {
			divided.push_back(0);
			mMin = 0;
		}

		++in;
		++in_map;
	}

	unsigned char * out = mOutput[0].getStart();
	unsigned char * out_end = mOutput[0].getStart() + (mOutput[0].height()*mOutput[0].width());
	int i = 0;

	for (auto& d : divided) {
		*out = ((d - mMin) / (mMax - mMin)) * 255;
		++out;
	}
	//}
	//while (out != out_end) {
	//	*out = ((divided[i] - mMin) / (mMax - mMin)) * 255;
	//	++i;
	//	++out;
	//}


	//
//
//void ImgDemo::uniformize(std::vector<unsigned char>& original, std::vector<unsigned char> const & map)
//{
//	int min = 0;
//	int max = 0;
//
//	std::vector<float> divided{};
//
//	for (size_t i = 0; i < original.size(); i++)
//	{
//		if (map[i] != 0) {
//			double d = (double)original[i] / map[i];
//			divided.push_back(d);
//			if (d > max) { max = d; }
//			if (d < min) { min = d; }
//		}
//		else {
//			divided.push_back(0);
//		}
//	}
//
//	for (size_t i = 0; i < original.size(); i++)
//	{
//		//replace 255 with const var
//		original[i] = ((divided[i] - min) / (max - min)) * 255;
//	}
//}

}

int UniformizeStrategy::max()
{
	return mMax;
}

int UniformizeStrategy::min()
{
	return mMin;
}

UniformizeStrategy::UniformizeStrategy()
	:ProcessStrategy(), mMax{ 0 }, mMin{999}
{
}
