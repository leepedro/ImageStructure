#include "image.h"
#include "opencv_interface.h"

void TestImage(void)
{
	using namespace Imaging;

	ImageFrame::ROI roi1;
	ImageFrame::ROI roi2 = { { 0, 0 }, { 64, 32 } };
	ImageFrame::ROI roi3{ { 0, 0 }, { 64, 32 } };

	ImageFrame img1;
	img1.Reset<unsigned char>({ 16, 8 }, 3);
	img1.Reset<unsigned char>({ 48, 8 }, 1);
	img1.Reset<unsigned char>({ 48, 8 });
	img1.Reset<int>({ 4, 8 }, 3);
	img1.Reset<int>({ 12, 8 }, 1);
	img1.Reset<int>({ 12, 8 });
	img1.Reset(DataType::UCHAR, { 16, 8 }, 3);
	img1.Reset(DataType::UCHAR, { 48, 8 }, 1);
	img1.Reset(DataType::UCHAR, { 48, 8 });
	img1.Reset(DataType::INT, { 4, 8 }, 3);
	img1.Reset(DataType::INT, { 12, 8 }, 1);
	img1.Reset(DataType::INT, { 12, 8 });
}

void TestImageProcessing(void)
{
	using namespace Imaging;

	// Load an image from a file.
	cv::Mat cvSrc1 = cv::imread(std::string("Lenna.png"), CV_LOAD_IMAGE_COLOR);	
	cv::namedWindow(std::string("Source 1"), CV_WINDOW_AUTOSIZE);
	cv::imshow(std::string("Source 1"), cvSrc1);
	cv::waitKey(0);

	// Copy image data from cv::Mat object to ImageFrame.
	ImageFrame img1;
	Size2D<std::size_t> szSrc1 = { Cast<std::size_t>(cvSrc1.cols), Cast<std::size_t>(cvSrc1.rows) };
	img1.CopyFrom(GetDataType(cvSrc1.depth()), reinterpret_cast<const char *>(cvSrc1.ptr()), szSrc1, cvSrc1.channels(), cvSrc1.cols * cvSrc1.channels() * cvSrc1.elemSize1());

	// Copy image data from ImageFrame to cv::Mat object.
	auto it = img1.Begin();
	cv::Mat cvDst1(Cast<int>(img1.size.height), Cast<int>(img1.size.width), GetOpenCvType(img1.dataType, img1.depth), &(*it));
	cv::namedWindow(std::string("Copied 1"), CV_WINDOW_AUTOSIZE);
	cv::imshow(std::string("Copied 1"), cvDst1);
	cv::waitKey(0);
}

int main(void)
{
	TestImage();
	TestImageProcessing();
}