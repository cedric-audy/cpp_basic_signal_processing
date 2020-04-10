#include "ImgDemo.h"

#include <QCameraInfo>

#include <qdockwidget.h>
#include <QVBoxLayout>
#include "QSimpleImageGrabber.h"
#include "pixelIterators.h"

ImgDemo::ImgDemo(QWidget *parent)
	: QMainWindow(parent),
		mLightmapPipeline{},
		mMainPipeline{},
		mConnectButton{ new QPushButton("Connect") },
		mDisconnectButton{ new QPushButton("Disconnect") },
		mCaptureOneButton{ new QPushButton("Capture one image") },
		mCaptureContinuouslyButton{ new QPushButton("Start capture continuously") },
		mSaveButton{ new QPushButton("Save current image")},
		mInputImage{ new QSimpleImageViewer },
		mLightMap{ new QSimpleImageViewer },
		mProcessedImage{ new QSimpleImageViewer },
		mBuildLightmap{new QPushButton("Build light map")},
		mMainProcess{new QPushButton("Run main process")},
		mCapturingContinuously{ false },
		mLightmapReady{false},
		mCreatingMap{false}
{
	ui.setupUi(this);

	//central window with images
	QVBoxLayout * layout{ new QVBoxLayout };
	QHBoxLayout * hLayout3{ new QHBoxLayout };

	//floating menu bar
	QHBoxLayout * hLayout1{ new QHBoxLayout };
	QHBoxLayout * hLayout2{ new QHBoxLayout };
	QDockWidget * floatingBar{ new QDockWidget() };
	hLayout1->addWidget(mConnectButton);
	hLayout1->addWidget(mDisconnectButton);
	hLayout1->addWidget(mCaptureOneButton);
	hLayout1->addWidget(mCaptureContinuouslyButton);
	hLayout1->addWidget(mSaveButton);
	hLayout2->addWidget(mMainProcess);
	hLayout2->addWidget(mBuildLightmap);


	QWidget * menuWidget{ new QWidget };
	QVBoxLayout * layout2{ new QVBoxLayout };

	layout2->addLayout(hLayout1);
	layout2->addLayout(hLayout2);
	menuWidget->setLayout(layout2);
	floatingBar->setWidget(menuWidget);
	
	addDockWidget(Qt::DockWidgetArea::TopDockWidgetArea, floatingBar);
	hLayout3->addWidget(mInputImage);
	hLayout3->addWidget(mLightMap);
	hLayout3->addWidget(mProcessedImage);
	layout->addLayout(hLayout3);
	QWidget * centralWidget{ new QWidget };
	centralWidget->setLayout(layout);

	setCentralWidget(centralWidget);

	connect(mConnectButton, &QPushButton::clicked, this, &ImgDemo::connectCamera);
	connect(mDisconnectButton, &QPushButton::clicked, this, &ImgDemo::disconnectCamera);
	connect(mCaptureOneButton, &QPushButton::clicked, this, &ImgDemo::captureOne);

	//save
	connect(mSaveButton, &QPushButton::clicked, this, &ImgDemo::saveCurrImg);
	
	//build lightmap or no
	connect(mBuildLightmap, &QPushButton::clicked, this, &ImgDemo::lightmapReady);
	connect(mMainProcess, &QPushButton::clicked, this, &ImgDemo::activateMainProcess);




	connect(mCaptureContinuouslyButton, &QPushButton::clicked, this, &ImgDemo::captureContinuously);
	
	connect(&mSimpleImageGrabber, &QSimpleImageGrabber::imageCaptured, mInputImage, &QSimpleImageViewer::setImage);
	connect(&mSimpleImageGrabber, &QSimpleImageGrabber::imageCaptured, this, &ImgDemo::processDispatch);
	//connect(&mSimpleImageGrabber, &QSimpleImageGrabber::imageCaptured, this, &ImgDemo::processCapturedImage);
	connect(&mSimpleImageGrabber, &QSimpleImageGrabber::readyForCaptureChanged, this, &ImgDemo::processReadyToCapture);

	updateGui();
}

void ImgDemo::activateMainProcess() {

	mMainPipeline.addStep(NULL);
	mMainPipeline.execute();
}

void ImgDemo::buildLightmap()
{
	mLightmapPipeline.defaultLightmapProcess();
	mLightmapPipeline.execute();
}

void ImgDemo::lightmapReady()
{
	mLightmapPipeline.clearInput();
	mLightmapReady = false;
	mCreatingMap = true;
}

void ImgDemo::connectCamera()
{
	mSimpleImageGrabber.connect();
	updateGui();
}

void ImgDemo::saveCurrImg() //successful test version
{
	const QPixmap * px = mProcessedImage->pixmap();
	QImage img = px->toImage();
	bool success = img.save("C:/Users/ced/Desktop/schooldump/testdemo.bmp");
	updateGui();
}

void ImgDemo::disconnectCamera()
{
	mSimpleImageGrabber.disconnect();
	updateGui();
}

void ImgDemo::captureOne()
{
	mSimpleImageGrabber.capture();
	updateGui();
}

void ImgDemo::captureContinuously()
{
	mCapturingContinuously = !mCapturingContinuously;
	mSimpleImageGrabber.capture();
	updateGui();
}

void ImgDemo::processReadyToCapture(bool ready)
{
	if (ready && mCapturingContinuously) {
		mSimpleImageGrabber.capture();
	}
}

void ImgDemo::updateGui()
{
	mConnectButton->setEnabled(!mSimpleImageGrabber.isConnected());
	mDisconnectButton->setEnabled(mSimpleImageGrabber.isConnected());
	mCaptureOneButton->setEnabled(mSimpleImageGrabber.isConnected() && !mCapturingContinuously);
	mCaptureContinuouslyButton->setEnabled(mSimpleImageGrabber.isConnected());
	mCaptureContinuouslyButton->setText(mCapturingContinuously ? "Stop capture continuously" : "Start capture continuously");
}

void zipData(int * in_beg, int * in_end, unsigned char * out) {
	//dont know if good practice
		while (in_beg < in_end) {

			unsigned char average{ *out };
			*in_beg = (average << 16) |
				(average << 8) |
				(average << 0) |
				0xff'00'00'00;

			++out;
			++in_beg;
		}

}

//void zipDataColor(int * in_beg, int * in_end, unsigned char * out) {
//
//	while (in_beg < in_end) {
//		int c{ *in_beg };
//		unsigned char r{ static_cast<unsigned char>((c & 0x00'FF'00'00) >> 16) };
//		unsigned char g{ static_cast<unsigned char>((c & 0x00'00'FF'00) >> 8) };
//		unsigned char b{ static_cast<unsigned char>((c & 0x00'00'00'FF) >> 0) };
//
//		unsigned char average{ *out };
//		r /= average;
//		g /= average;
//		b /= average;
//
//		*in_beg = (r << 16) |
//			(g << 8) |
//			(b << 0) |
//			0xff'00'00'00;
//
//		++out;
//		++in_beg;
//	}
//
//}

void ImgDemo::processDispatch(QImage const & image)
{
	if (mCreatingMap) {
		QImage im(image);
		mLightmapPipeline.pushImg(im);
		//hardcoded number of ref imgs
		if (mLightmapPipeline.inputSize() == 32) {
			ImgDemo::buildLightmap();

			unsigned char * out = mLightmapPipeline.getOutputPtr();
			int * curpix{ reinterpret_cast<int*>(im.bits()) };
			int * endpix{ curpix + im.width() * im.height() };
			zipData(curpix, endpix, out);


			mLightMap->setImage(im);
			mLightmapPipeline.clearInput();
			mCreatingMap = false;
			mLightmapReady = true;
			Grayscale1DImage lightmap = im;
			lightmap.setType(GrayscaleType::LIGHTMAP);
			mMainPipeline.setCurrentImage(lightmap, 1);
		}	
	}
	else if (mLightmapReady) {
		QImage im(image);
		mMainPipeline.setCurrentImage(im, 0);
		ImgDemo::activateMainProcess();

		unsigned char * out = mMainPipeline.getOutputPtr();
		int * curpix{ reinterpret_cast<int*>(im.bits()) };
		int * endpix{ curpix + im.width() * im.height() };
		zipData(curpix, endpix, out);

		mProcessedImage->setImage(im);

	}


}
//
//void ImgDemo::boxFilter(std::vector<unsigned char> &v, size_t width, size_t height, int kernelSize, bool vertical)
//{
//	std::vector<unsigned char> copy(v);
//	std::vector<unsigned char>::iterator it = copy.begin();
//
//	int offset = vertical ? width : 1;
//
//	size_t sum{ 0 };
//	float avr{0};
//
//	//var used to store the last (closest) valid neighbour, value is used when iterator is out of bounds (kernel wise) on x-y plane
//	size_t lastVal{ 0 };
//	
//	int xCount{ 0 };
//	//possible optimization: keep current neighbours in memory so we dont have to look them up every time (queue?)
//	for (size_t i = 0; i < v.size(); i++)
//	{
//		lastVal = *it;
//		for (int k = 0 - kernelSize/2; k < (kernelSize/2)+1; k++)
//		{
//			if (i + k*offset > 0 
//				&& i + k*offset < width*height
//				&&  k + xCount > 0
//				&& k + xCount < width) {
//					lastVal = *(it + k*offset);
//					sum += lastVal;
//			}
//			else {
//				sum += lastVal;
//			}
//		}
//		avr = sum / kernelSize;
//		sum = 0;
//		v[i] = avr;
//		++it;
//		xCount = (xCount%width) + 1;
//	}
//
//}
//
//void ImgDemo::maxFilter(std::vector<unsigned char> &v, size_t width, size_t height, int kernelSize, bool vertical)
//{
//	std::vector<unsigned char> copy(v);
//	std::vector<unsigned char>::iterator it = copy.begin();
//
//	int offset = vertical ? width : 1;
//
//	//var used to store the last (closest) valid neighbour, value is used when iterator is out of bounds (kernel wise) on x-y plane
//	size_t maxVal{ 0 };
//
//	//possible optimization: keep current neighbours in memory so we dont have to look them up every time (queue?)
//	for (size_t i = 0; i < v.size(); i++)
//	{
//		maxVal = *it;
//		for (int k = 0 - kernelSize / 2; k < (kernelSize / 2) + 1; k++)
//		{
//			if (i + k * offset > 0 && i + k * offset < width*height) {
//				maxVal = *(it + k * offset) > maxVal? *(it + k * offset):maxVal;
//			}
//		}
//		v[i] = maxVal;
//		++it;
//	}
//}
//
//void ImgDemo::uniformize(std::vector<unsigned char>& original, std::vector<unsigned char> const & map)
//{
//	int min = 0;
//	int max = 255;
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
//		original[i] = ((divided[i] - min) / (max - min))*255;
//	}
//}
//
//




	//
	////CONCEPT : DO A UC ARR OF GRAYSCALE VALUES; easier to manipulate and access (i guess?)
	//curPix = reinterpret_cast<int*>(im.bits());
	//endPix = curPix + im.width() * im.height();
	//std::vector<unsigned char> grayPixArr{};
	//while (curPix < endPix) {
	//	grayPixArr.push_back(*curPix);
	//	++curPix;
	//}


	//std::vector<unsigned char> original(grayPixArr);
	//boxFilter(grayPixArr, im.width(), im.height(), 11, false);
	//boxFilter(grayPixArr, im.width(), im.height(), 11, true);
	//boxFilter(grayPixArr, im.width(), im.height(), 11, false);
	//boxFilter(grayPixArr, im.width(), im.height(), 11, true);
	//boxFilter(grayPixArr, im.width(), im.height(), 11, false);
	//boxFilter(grayPixArr, im.width(), im.height(), 11, true);

	//maxFilter(grayPixArr, im.width(), im.height(), 11, false);
	//maxFilter(grayPixArr, im.width(), im.height(), 11, true);

	//boxFilter(grayPixArr, im.width(), im.height(), 99, false);
	//boxFilter(grayPixArr, im.width(), im.height(), 99, true);
	//boxFilter(grayPixArr, im.width(), im.height(), 99, false);
	//boxFilter(grayPixArr, im.width(), im.height(), 99, true);
	//boxFilter(grayPixArr, im.width(), im.height(), 99, false);
	//boxFilter(grayPixArr, im.width(), im.height(), 99, true);

	//uniformize(original, grayPixArr);

	//QImage im2(image);
	//int * refPix = reinterpret_cast<int*>(im2.bits());
	//endPix = refPix + im2.width() * im2.height();
	//
	//for (auto v: original) {
	//	*refPix = (v << 16) |
	//		(v << 8) |
	//		(v << 0) |
	//		0xFF'00'00'00;
	//	++refPix;
	//}

    //!emit imageProcessed(im);
