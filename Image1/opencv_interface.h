#if !defined(OPENCV_INTERFACE_H)
#define OPENCV_INTERFACE_H

#include "image.h"

#include "opencv2/opencv.hpp"

namespace Imaging
{
	int GetOpenCvType(DataType ty, std::size_t d)
	{
		switch (ty)
		{
		case DataType::CHAR:
			return CV_MAKETYPE(CV_8S, Cast<int>(d));
		case DataType::SCHAR:
			return CV_MAKETYPE(CV_8S, Cast<int>(d));
		case DataType::UCHAR:
			return CV_MAKETYPE(CV_8U, Cast<int>(d));
		case DataType::SHORT:
			return CV_MAKETYPE(CV_16S, Cast<int>(d));
		case DataType::USHORT:
			return CV_MAKETYPE(CV_16U, Cast<int>(d));
		case DataType::INT:
			return CV_MAKETYPE(CV_32S, Cast<int>(d));
		case DataType::FLOAT:
			return CV_MAKETYPE(CV_32F, Cast<int>(d));
		case DataType::DOUBLE:
			return CV_MAKETYPE(CV_64F, Cast<int>(d));
		default:
			throw std::runtime_error("Unsupported data type.");
		}
	}

	DataType GetDataType(int cvType)
	{
		switch (cvType)
		{
		case CV_8S:
			return DataType::SCHAR;
		case CV_8U:
			return DataType::UCHAR;
		case CV_16S:
			return DataType::SHORT;
		case CV_16U:
			return DataType::USHORT;
		case CV_32S:
			return DataType::INT;
		case CV_32F:
			return DataType::FLOAT;
		case CV_64F:
			return DataType::DOUBLE;
		default:
			throw std::logic_error("Unrecognized OpenCV data type.");
		}
	}
}

#endif
