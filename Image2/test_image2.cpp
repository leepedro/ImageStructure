#include "image2.h"

void TestImage(void)
{
	ImageFrameT<unsigned char> img1;
	img1.Reset(5, 4, 3);
	img1.Reset();
	//img1.data[0] = 0;		// doesn't know memory is allocated or not due to lack of range checking
	unsigned char d1 = img1.dataC[0];
	//std::free(img1.data);	// Bad
	//img1.dataC[0] = 0;	// Good
}
int main(void)
{
	TestImage();
	//TestImageProcessing();
}