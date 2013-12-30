#if !defined(COORDINATES_H)
#define COORDINATES_H

#include "utilities/containers.h"

namespace Imaging
{
	template <typename T>
	class Point2D : public Array<T, 2>
	{
		static_assert(std::is_arithmetic<T>::value,
		"Only arithmetic data types are supported for this class template.");

	public:
		////////////////////////////////////////////////////////////////////////////////////
		// Default constructors.
		Point2D(void) = default;
		Point2D &operator=(const Point2D<T> &src) = default;
		Point2D(const Point2D<T> &src) = default;	// optional, no need

		////////////////////////////////////////////////////////////////////////////////////
		// Custom constructors.
		template <typename U>
		Point2D(const Point2D<U> &src);

		Point2D(T x, T y);
		Point2D(const Array<T, 2> &srcData);

		T &x = this->data.at(0);
		T &y = this->data.at(1);
	};

	template <typename T>
	class Size2D : public Array<T, 2>
	{
		static_assert(std::is_arithmetic<T>::value,
		"Only arithmetic data types are supported for this class template.");

	public:
		////////////////////////////////////////////////////////////////////////////////////
		// Default constructors.
		Size2D(void) = default;
		Size2D &operator=(const Size2D<T> &src) = default;
		Size2D(const Size2D<T> &src) = default;	// optional, no need

		////////////////////////////////////////////////////////////////////////////////////
		// Custom constructors.
		template <typename U>
		Size2D(const Size2D<U> &src);

		Size2D(T width, T height);
		Size2D(const Array<T, 2> &srcData);

		T &width = this->data.at(0);
		T &height = this->data.at(1);
	};

	/* Rectangle classes.
	RectTypeA: a rectangle with two corners; point1<T>(x, y), point2<T>(x, y)
	RectTypeB: a rectangle with one corner and extension; origin<T>(x, y), size<U>(w, h)
	RectTypeC: a rectangle with a center and extension; center<T>(x, y), extension<U>(w, h)	*/

	template <typename T>
	class RectTypeA
	{
		static_assert(std::is_arithmetic<T>::value,
		"Only arithmetic data types are supported for this class template.");

	public:
		////////////////////////////////////////////////////////////////////////////////////
		// Operators.
		bool operator==(const RectTypeA<T> &rhs) const;
		bool operator!=(const RectTypeA<T> &rhs) const;

		////////////////////////////////////////////////////////////////////////////////////
		// Data.
		Point2D<T> point1, point2;
	};

	template <typename T, typename U>
	class RectTypeB
	{
		static_assert(std::is_arithmetic<T>::value,
		"origin must be integral data type and size must be unsigned integral type.");

	public:
		////////////////////////////////////////////////////////////////////////////////////
		// Operators.
		bool operator==(const RectTypeB<T, U> &rhs) const;
		bool operator!=(const RectTypeB<T, U> &rhs) const;

		////////////////////////////////////////////////////////////////////////////////////
		// Data.
		Point2D<T> origin;
		Size2D<U> size;
	};

	template <typename T, typename U>
	class RectTypeC
	{
		static_assert(std::is_arithmetic<T>::value,
		"Only arithmetic data types are supported for this class template.");

	public:
		////////////////////////////////////////////////////////////////////////////////////
		// Operators.
		bool operator==(const RectTypeC<T, U> &rhs) const;
		bool operator!=(const RectTypeC<T, U> &rhs) const;

		////////////////////////////////////////////////////////////////////////////////////
		// Data.
		Point2D<T> center;
		Size2D<U> extension;
	};
}

#include "coordinates_inl.h"

#endif
