#if !defined(CONTAINERS_H)
#define CONTAINERS_H

/*
Defines custom container classes.
Defines global functions using standard or custom container classes.
*/

#include <array>
#include <vector>

#include "algorithms.h"

namespace Imaging
{
	/*
	This class template expands the functionality of std::array<T, N> by overloading member
	operators so they can be used outside of the namespace.

	It does NOT have any user defined ctor or protected/private members, so it can use
	aggregate initialization.
	NOTE: Since std::array<T, N> cannot be used with a move ctor,
	there is not much benefit to implement them for its derived classes.
	*/
	template <typename T, std::size_t N>
	class Array
	{
		static_assert(std::is_arithmetic<T>::value,
			"Only arithmetic data types are supported for this class template.");

	public:
		////////////////////////////////////////////////////////////////////////////////////
		// Overloaded operators.

		/* Data type of operator arguments.
		The right-hand side argument can be a different data type, but the result is the
		same type. In other words, C is always the same data type as A, while B or b could be
		a different data type from A. */

		// C = A + B
		template <typename U>
		Array<T, N> operator+(const Array<U, N> &rhs) const;

		// C = A - B
		template <typename U>
		Array<T, N> operator-(const Array<U, N> &rhs) const;

		// C = A * B
		template <typename U>
		Array<T, N> operator*(const Array<U, N> &rhs) const;

		// C = A + b
		template <typename U>
		std::enable_if_t<std::is_arithmetic<U>::value, Array<T, N>> operator+(U rhs) const;

		// C = A - b
		template <typename U>
		std::enable_if_t<std::is_arithmetic<U>::value, Array<T, N>> operator-(U rhs) const;

		// C = A * b
		template <typename U>
		std::enable_if_t<std::is_arithmetic<U>::value, Array<T, N>> operator*(U rhs) const;

		// A += B
		template <typename U>
		void operator+=(const Array<U, N> &rhs);

		// A -= B
		template <typename U>
		void operator-=(const Array<U, N> &rhs);

		// A *= B
		template <typename U>
		void operator*=(const Array<U, N> &rhs);

		// A += b
		template <typename U>
		std::enable_if_t<std::is_arithmetic<U>::value, void> operator+=(U rhs);

		// A -= b
		template <typename U>
		std::enable_if_t<std::is_arithmetic<U>::value, void> operator-=(U rhs);

		// A *= b
		template <typename U>
		std::enable_if_t<std::is_arithmetic<U>::value, void> operator*=(U rhs);

		Array<T, N> &operator++(void);	// ++A
		Array<T, N> operator++(int);	// A++ (not efficient)
		Array<T, N> &operator--(void);	// --A
		Array<T, N> operator--(int);	// A-- (not efficient)

		bool operator==(const Array<T, N> &rhs) const;
		bool operator!=(const Array<T, N> &rhs) const;

		//template <typename U>
		//operator Array<U, N>();			// cast

		////////////////////////////////////////////////////////////////////////////////////
		// Members.
		std::array<T, N> data;
	};


	////////////////////////////////////////////////////////////////////////////////////////
	// Global functions for Array<T, N>.

	template <typename T, typename U, ::size_t N>
	std::enable_if_t<std::is_floating_point<U>::value, Array<T, N>>	RoundAs(
		const Array<U, N> &src);

	// Global functions for Array<T, N>.
	////////////////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////////////////
	// Global functions for std::vector<T>.

	/* Copies data from a raw pointer for given number of bytes to an std::vector<T>.
	Destination is resized per the size of source data.
	NOTE: Since there is no way to check the dimension of source data, users must ensure
	length is a valid value. */
	//template <typename T>
	//void Copy(const T *src, std::size_t length, std::vector<T> &dst);

	// Gets a std::vector<T> with a range value for given length.
	// It is similar to range function in Python.
	template <typename T>
	std::vector<T> GetRangeVector(std::size_t length);

	// Global functions for std::vector<T>.
	////////////////////////////////////////////////////////////////////////////////////////

}

#include "containers_inl.h"

#endif
