#pragma once
#include <vector>

template <class pixel_type> class OneDimg
{
public:
	void process();
	void addInput(OneDimg in);
	void setInput(std::vector<OneDimg>*)
	void clearInput();

protected:
	std::vector<pixel_type>* mInput;
	std::vector<pixel_type> mOutput;
};

template<class pixel_type>
inline void OneDimg<pixel_type>::process()
{
	mOutput = *(mInput);
}

template<class pixel_type>
inline void OneDimg<pixel_type>::addInput(OneDimg in)
{
	mInput->push_back(in);
}

template<class pixel_type>
inline void OneDimg<pixel_type>::clearInput()
{
	mOutput.clear();
	mInput->clear();
}
