#if !defined(CONTAINERS_INL_H)
#define CONTAINERS_INL_H

namespace Imaging
{
	////////////////////////////////////////////////////////////////////////////////////////
	// Array<T, N>

	// C = A + B
	template <typename T, ::size_t N> template <typename U>
	Array<T, N> Array<T, N>::operator+(const Array<U, N> &rhs) const
	{
		Array<T, N> result;
		AddRange(this->data.cbegin(), this->data.cend(), rhs.data.cbegin(),
			result.data.begin());
		return result;
	}

	// C = A - B
	template <typename T, ::size_t N> template <typename U>
	Array<T, N> Array<T, N>::operator-(const Array<U, N> &rhs) const
	{
		Array<T, N> result;
		SubtractRange(this->data.cbegin(), this->data.cend(), rhs.data.cbegin(),
			result.data.begin());
		return result;
	}

	// C = A * B
	template <typename T, ::size_t N> template <typename U>
	Array<T, N> Array<T, N>::operator*(const Array<U, N> &rhs) const
	{
		Array<T, N> result;
		MultiplyRange(this->data.cbegin(), this->data.cend(), rhs.data.cbegin(),
			result.data.begin());
		return result;
	}

	/* Type checking operand arguments.
	For operands that taking a scalar value, we must check if the operand argument is simple
	arithmetic type, otherwise Array<U, N> is taken as U. */

	// C = A + b
	template <typename T, ::size_t N> template <typename U>
	std::enable_if_t<std::is_arithmetic<U>::value, Array<T, N>> Array<T, N>::operator+(
		U rhs) const
	{
		Array<T, N> result;
		auto it = this->data.cbegin(), itEnd = this->data.cend();
		for (auto itDst = result.data.begin(); it != itEnd; ++it, ++itDst)
			Add(*it, rhs, *itDst);
		return result;
	}

	// C = A - b
	template <typename T, ::size_t N> template <typename U>
	std::enable_if_t<std::is_arithmetic<U>::value, Array<T, N>> Array<T, N>::operator-(
		U rhs) const
	{
		Array<T, N> result;
		auto it = this->data.cbegin(), itEnd = this->data.cend();
		for (auto itDst = result.data.begin(); it != itEnd; ++it, ++itDst)
			Subtract(*it, rhs, *itDst);
		return result;
	}

	// C = A * b
	template <typename T, ::size_t N> template <typename U>
	std::enable_if_t<std::is_arithmetic<U>::value, Array<T, N>> Array<T, N>::operator*(
		U rhs) const
	{
		Array<T, N> result;
		auto it = this->data.cbegin(), itEnd = this->data.cend();
		for (auto itDst = result.data.begin(); it != itEnd; ++it, ++itDst)
			Multiply(*it, rhs, *itDst);
		return result;
	}

	// A += B
	template <typename T, ::size_t N> template <typename U>
	void Array<T, N>::operator+=(const Array<U, N> &rhs)
	{
		AddRange(rhs.data.cbegin(), rhs.data.cend(), this->data.begin());
	}

	// A -= B
	template <typename T, ::size_t N> template <typename U>
	void Array<T, N>::operator-=(const Array<U, N> &rhs)
	{
		SubtractRange(rhs.data.cbegin(), rhs.data.cend(), this->data.begin());
	}

	// A *= B
	template <typename T, ::size_t N> template <typename U>
	void Array<T, N>::operator*=(const Array<U, N> &rhs)
	{
		MultiplyRange(rhs.data.cbegin(), rhs.data.cend(), this->data.begin());
	}

	/* Type checking operand arguments.
	For operands that taking a scalar value, we must check if the operand argument is simple
	arithmetic type, otherwise Array<U, N> is taken as U. */

	// A += b
	template <typename T, ::size_t N> template <typename U>
	std::enable_if_t<std::is_arithmetic<U>::value, void> Array<T, N>::operator+=(U rhs)
	{		
		for (auto it = this->data.begin(), itEnd = this->data.end(); it != itEnd; ++it)
			Add(*it, rhs, *it);
	}

	// A -= b
	template <typename T, ::size_t N> template <typename U>
	std::enable_if_t<std::is_arithmetic<U>::value, void> Array<T, N>::operator-=(U rhs)
	{
		for (auto it = this->data.begin(), itEnd = this->data.end(); it != itEnd; ++it)
			Subtract(*it, rhs, *it);
	}

	// A *= b
	template <typename T, ::size_t N> template <typename U>
	std::enable_if_t<std::is_arithmetic<U>::value, void> Array<T, N>::operator*=(U rhs)
	{
		for (auto it = this->data.begin(), itEnd = this->data.end(); it != itEnd; ++it)
			Multiply(*it, rhs, *it);
	}

	// ++A
	template <typename T, ::size_t N>
	Array<T, N> &Array<T, N>::operator++(void)
	{
		IncrementRange(this->data.begin(), this->data.end());
		return *this;
	}

	// A++ (not efficient)
	template <typename T, ::size_t N>
	Array<T, N> Array<T, N>::operator++(int)
	{
		Array<T, N> temp = *this;
		++*this;
		return temp;
	}

	// --A
	template <typename T, ::size_t N>
	Array<T, N> &Array<T, N>::operator--(void)
	{
		DecrementRange(this->data.begin(), this->data.end());
		return *this;
	}

	// A-- (not efficient)
	template <typename T, ::size_t N>
	Array<T, N> Array<T, N>::operator--(int)
	{
		Array<T, N> temp = *this;
		--*this;
		return temp;
	}

	template <typename T, ::size_t N>
	bool Array<T, N>::operator==(const Array<T, N> &rhs) const
	{
		return this->data == rhs.data;
	}

	template <typename T, ::size_t N>
	bool Array<T, N>::operator!=(const Array<T, N> &rhs) const
	{
		return this->data != rhs.data;
	}

	// cast
	//template <typename T, ::size_t N> template <typename U>
	//Array<T, N>::operator Array<U, N>()
	//{
	//	Array<U, N> dst;
	//	auto it = this->data.cbegin(), itEnd = this->data.cend();
	//	for (auto itDst = dst.data.begin(); it != itEnd; ++it, ++itDst)
	//		*itDst = Cast<U>(*it);
	//	return dst;
	//}

	// Array<T, N>
	////////////////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////////////////
	// Global functions for Array<T, N>.

	template <typename T, typename U, ::size_t N>
	std::enable_if_t<std::is_floating_point<U>::value, Array<T, N>> RoundAs(
		const Array<U, N> &src)
	{
		Array<T, N> dst;
		auto itDst = dst.data.begin(), itDstEnd = dst.data.end();
		for (auto itSrc = src.data.cbegin(); itDst != itDstEnd; ++itDst, ++itSrc)
			*itDst = Cast<T>(std::round(*itSrc));
		return dst;
	}

	// Global functions for Array<T, N>.
	////////////////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////////////////
	// Global functions for std::vector<T>.

	//template <typename T>
	//void Copy(const T *src, std::size_t length, std::vector<T> &dst)
	//{
	//	// Re-allocate destination if necessary.
	//	if (dst.size() != length)
	//		dst.resize(length);
	//	std::copy_n(src, length, dst.begin());
	//}

	template <typename T>
	std::vector<T> GetRangeVector(std::size_t length)
	{
		std::vector<T> v(length);
		FillRange(v.begin(), v.end());
		return v;
	}

	// Global functions for std::vector<T>.
	////////////////////////////////////////////////////////////////////////////////////////

}

#endif
