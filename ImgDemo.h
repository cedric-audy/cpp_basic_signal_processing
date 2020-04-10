#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ImgDemo.h"


#include <QPushButton>
#include <QTimer>
#include "QSimpleImageGrabber.h"
#include "QSimpleImageViewer.h"


//CED'S
#include "Grayscale1DImage.h"
#include "IPPipeline.h"


class ImgDemo : public QMainWindow
{
	Q_OBJECT

public:
	ImgDemo(QWidget *parent = Q_NULLPTR);

	IPPipeline mLightmapPipeline;
	IPPipeline mMainPipeline;

private:
	Ui::ImgDemoClass ui;

	QPushButton * mConnectButton, *mDisconnectButton, *mCaptureOneButton, *mCaptureContinuouslyButton, *mSaveButton, *mBuildLightmap, *mMainProcess;
	QSimpleImageGrabber mSimpleImageGrabber;
	QSimpleImageViewer * mInputImage;
	QSimpleImageViewer * mLightMap;
	QSimpleImageViewer * mProcessedImage;

	QTimer mTimer;
	bool mCapturingContinuously;

	bool mCreatingMap;
	bool mLightmapReady;

private slots:
	void connectCamera();
	void disconnectCamera();
	void saveCurrImg();
	void captureOne();
	void captureContinuously();
	void processReadyToCapture(bool ready);
	void buildLightmap();
	void lightmapReady();
	void activateMainProcess();


	//for testing
    virtual void processDispatch(QImage const & image);
	//void boxFilter(std::vector<unsigned char> &v, size_t width, size_t height, int size, bool vertical);
	//void maxFilter(std::vector<unsigned char> &v, size_t width, size_t height, int size, bool vertical);
	//void uniformize(std::vector<unsigned char> &original, std::vector<unsigned char> const &map);
	////


	void updateGui();

//!signals:
    //!void imageProcessed(QImage const & image);
};



/*

#include <cstdint>
#include <vector>

class Image
{
public:
	using pixel_t = uint8_t;

	Image() = default;
	Image(size_t width, size_t height, size_t band = 1) { resize(width, height, band); }
	Image(Image const &) = default;
	Image(Image &&) = default;
	Image& operator=(Image const &) = default;
	Image& operator=(Image &&) = default;
	~Image() = default;

	void clear() {
		mWidth = mHeight = mBand = mDepth = mBandSize = 0;
		mBuffer.clear();
	}

	void resize(size_t width, size_t height, size_t band = 1) {
		if (width == 0 || height == 0 || band == 0) {
			clear();
			return;
		}

		mWidth = width;
		mHeight = height;
		mBand = band;
		mDepth = sizeof(pixel_t) * 8;
		mBandSize = mWidth * mHeight;
		mBuffer.resize(mBandSize * mBand);
	}
	void resize(Image const & im) { resize(im.width(), im.height(), im.band()); }

	bool isValid() const {
		return mBuffer.size() != 0;
	}

	size_t width() const { return mWidth; }
	size_t height() const { return mHeight; }
	size_t band() const { return mBand; }
	size_t depth() const { return mDepth; }
	size_t bandSize() const { return mBandSize; }
	size_t size() const { return mBuffer.size(); }

	pixel_t pixel(int x, int y) const { return mBuffer[offset(x, y)]; }
	pixel_t pixel(int x, int y, int band) const { return mBuffer[offset(x, y, band)]; }
	pixel_t pixelAt(int x, int y) const { return mBuffer.at(offset(x, y)); }
	pixel_t pixelAt(int x, int y, int band) const { return mBuffer.at(offset(x, y, band)); }

	void set(int x, int y, pixel_t value) { mBuffer[offset(x, y)] = value; }
	void set(int x, int y, int band, pixel_t value) { mBuffer[offset(x, y, band)] = value; }
	void setAt(int x, int y, pixel_t value) { mBuffer.at((x, y)) = value; }
	void setAt(int x, int y, int band, pixel_t value) { mBuffer.at(offset(x, y, band)) = value; }

	pixel_t const * buffer() const { return mBuffer.data(); }
	pixel_t * buffer() { return mBuffer.data(); }

private:
	size_t mWidth{}, mHeight{}, mBand{}, mDepth{};
	size_t mBandSize{};
	std::vector<pixel_t> mBuffer;

	size_t offset(int x, int y) const { return y * mWidth + x; }
	size_t offset(int x, int y, int band) const { return band * mBandSize + y * mWidth + x; }
};



class ImageGrabber
{
public:
	virtual bool isReady() = 0;
	virtual void initialize() = 0;
	virtual void grabOne(Image & image) = 0;
};

class Camera : public ImageGrabber
{
public:
	Camera() = default;
	Camera(Camera const &) = delete;
	Camera(Camera &&) = delete;
	Camera& operator=(Camera const &) = delete;
	Camera& operator=(Camera &&) = delete;
	~Camera() = default;

	bool connect(int id = 0);

	bool isReady() override;
	void initialize() override;
	void grabOne(Image & image) override;
};

class ImageFileReader : public ImageGrabber
{
public:
	ImageFileReader() = default;
	ImageFileReader(ImageFileReader const &) = default;
	ImageFileReader(ImageFileReader &&) = default;
	ImageFileReader& operator=(ImageFileReader const &) = default;
	ImageFileReader& operator=(ImageFileReader &&) = default;
	~ImageFileReader() = default;

	// enum class LoadingMode { LoadOnRequest, PreLoad };

	bool loadImage(std::string const & filename);
	bool loadFolder(std::string const & folder);

	size_t size() const { return mImages.size(); }
	Image const & operator[](int index) const { return mImages[index]; }
	Image const & at(int index) const { return mImages.at(index); }

	bool isReady() override { return mImages.size() > 0; }
	void initialize() override {}
	void grabOne(Image & image) override;

private:
	int mCurrentImage{ -1 };
	std::vector<Image> mImages;
};



class ImageGenerator
{
public:
	virtual void generate(Image & out) = 0;
};

class ImageUnaryProcessor
{
public:
	virtual void process(Image const & in, Image & out) = 0;
};

class ImageInverter : public ImageUnaryProcessor
{
public:
	void process(Image const & in, Image & out) {
		if (out.size() != in.size()) {
			out.resize(in);
		}
		Image::pixel_t const * curIn{ in.buffer() };
		Image::pixel_t const * endIn{ in.buffer() + in.size() };
		Image::pixel_t * curOut{ out.buffer() };
		while (curIn < curOut) {
			*curOut++ = 255 - *curIn++;
		}
	}
};

class ImageBinaryProcessor
{
public:
	virtual void process(Image const & in1, Image const & in2, Image & out) = 0;
};
*/