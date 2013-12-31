#if !defined(SAFE_OPERATIONS_H)
#define SAFE_OPERATIONS_H

/*
Defines common operations for overflow checking.
If overflow happens, throws an std::overflow_error.
Uses the built-in safeint.h for Visual C++.
Uses the downloadable SafeInt.hpp from http://safeint.codeplex.com/ for other compilers.
*/

#include <stdexcept>
#include <sstream>
#include <type_traits>
#include <typeinfo>

#if defined(_MSC_VER)
// Use the built-in safeint.h for Visual C++.
#include <safeint.h>
using namespace msl::utilities;
#else
// Use the downloadable SafeInt.hpp from http://safeint.codeplex.com/ for other compilers.
#include "SafeInt.hpp"
#endif

#if defined(__GNUG__)
// std::enable_if_t<bool, T> is not defined for g++ as it is a C++14 feature.
namespace std
{
	template <bool B, typename T = void>
	using enable_if_t = typename enable_if<B, T>::type;
}
#endif

namespace Imaging
{
	/* The convention for return values.
	Most of return values of the functions defined in this file are given as a reference
	argument instead of returning as a value in order to control the data type of return
	value through the template parameter. */

	template <typename T, typename U>
	void Add(T t, U u, T &result)
	{
		static_assert(std::is_arithmetic<T>::value && std::is_arithmetic<U>::value,
			"Only arithmetic data types are supported for this function template.");
		Add_imp(t, u, result, std::is_integral<T>(), std::is_integral<U>());
	}

	// integral = integral + integral; checking overflow.
	template <typename T, typename U>
	void Add_imp(T t, U u, T &result, std::true_type, std::true_type)
	{
		if (!SafeAdd(t, u, result))
		{
			std::ostringstream errMsg;
			errMsg << "The result of add operation exceeds the limit of " <<
				typeid(result).name() << " data type.";
			throw std::overflow_error(errMsg.str());
		}
	}

	// integral = integral + floating; unsupported and disabled.
	template <typename T, typename U>
	void Add_imp(T t, U u, T &result, std::true_type, std::false_type)
	{
		static_assert(!std::is_integral<T>::value || std::is_integral<U>::value,
			"Unsupported scenario.");
	}

	// floating = floating + integral.
	template <typename T, typename U>
	void Add_imp(T t, U u, T &result, std::false_type, std::true_type)
	{
		result = t + u;
	}

	// floating = floating + floating.
	template <typename T, typename U>
	void Add_imp(T t, U u, T &result, std::false_type, std::false_type)
	{
		result = t + u;
	}

	template <typename T, typename U>
	void Subtract(T t, U u, T &result)
	{
		static_assert(std::is_arithmetic<T>::value && std::is_arithmetic<U>::value,
			"Only arithmetic data types are supported for this function template.");
		Subtract_imp(t, u, result, std::is_integral<T>(), std::is_integral<U>());
	}

	// integral = integral - integral; checking overflow.
	template <typename T, typename U>
	void Subtract_imp(T t, U u, T &result, std::true_type, std::true_type)
	{
		if (!SafeSubtract(t, u, result))
		{
			std::ostringstream errMsg;
			errMsg << "The result of add operation exceeds the limit of " <<
				typeid(result).name() << " data type.";
			throw std::overflow_error(errMsg.str());
		}
	}

	// integral = integral - floating; unsupported and disabled.
	template <typename T, typename U>
	void Subtract_imp(T t, U u, T &result, std::true_type, std::false_type)
	{
		static_assert(!std::is_integral<T>::value || std::is_integral<U>::value,
			"Unsupported scenario.");
	}

	// floating = floating - integral.
	template <typename T, typename U>
	void Subtract_imp(T t, U u, T &result, std::false_type, std::true_type)
	{
		result = t - u;
	}

	// floating = floating - floating.
	template <typename T, typename U>
	void Subtract_imp(T t, U u, T &result, std::false_type, std::false_type)
	{
		result = t - u;
	}

	template <typename T, typename U>
	void Multiply(T t, U u, T &result)
	{
		static_assert(std::is_arithmetic<T>::value && std::is_arithmetic<U>::value,
			"Only arithmetic data types are supported for this function template.");
		Multiply_imp(t, u, result, std::is_integral<T>(), std::is_integral<U>());
	}

	// integral = integral * integral; checking overflow.
	template <typename T, typename U>
	void Multiply_imp(T t, U u, T &result, std::true_type, std::true_type)
	{
		if (!SafeMultiply(t, u, result))
		{
			std::ostringstream errMsg;
			errMsg << "The result of add operation exceeds the limit of " <<
				typeid(result).name() << " data type.";
			throw std::overflow_error(errMsg.str());
		}
	}

	// integral = integral - floating; unsupported and disabled.
	template <typename T, typename U>
	void Multiply_imp(T t, U u, T &result, std::true_type, std::false_type)
	{
		static_assert(!std::is_integral<T>::value || std::is_integral<U>::value,
			"Unsupported scenario.");
	}

	// floating = floating - integral.
	template <typename T, typename U>
	void Multiply_imp(T t, U u, T &result, std::false_type, std::true_type)
	{
		result = t * u;
	}

	// floating = floating - floating.
	template <typename T, typename U>
	void Multiply_imp(T t, U u, T &result, std::false_type, std::false_type)
	{
		result = t * u;
	}

	template <typename T>
	void Increment(T &value)
	{
		static_assert(std::is_arithmetic<T>::value,
			"Only arithmetic data types are supported for this function template.");
		Increment_imp(value, std::is_integral<T>());
	}

	// integral; checking overflow.
	template <typename T>
	void Increment_imp(T &value, std::true_type)
	{
		Add(value, 1, value);
	}

	// floating.
	template <typename T>
	void Increment_imp(T &value, std::false_type)
	{
		++value;
	}

	template <typename T>
	void Decrement(T &value)
	{
		static_assert(std::is_arithmetic<T>::value,
			"Only arithmetic data types are supported for this function template.");
		Decrement_imp(value, std::is_integral<T>());
	}

	// integral; checking overflow.
	template <typename T>
	void Decrement_imp(T &value, std::true_type)
	{
		Subtract(value, 1, value);
	}

	// floating.
	template <typename T>
	void Decrement_imp(T &value, std::false_type)
	{
		--value;
	}

	template <typename T, typename U>
	T Cast(U src)
	{
		static_assert(std::is_arithmetic<T>::value && std::is_arithmetic<U>::value,
			"Only arithmetic data types are supported for this function template.");
		T dst;
		Cast_imp(src, dst, std::is_integral<U>(), std::is_integral<T>());
		return dst;
	}

	// integral to integral; checking overflow.
	template <typename T, typename U>
	void Cast_imp(U src, T &dst, std::true_type, std::true_type)
	{
		if (!msl::utilities::SafeCast(src, dst))
		{
			std::ostringstream errMsg;
			errMsg << "The source value of cast operation exceeds the limit of " <<
				typeid(dst).name() << " data type.";
			throw std::overflow_error(errMsg.str());
		}
	}

	// floating point to integral; checking overflow, suppressing data loss warning.
	template <typename T, typename U>
	void Cast_imp(U src, T &dst, std::false_type, std::true_type)
	{
		if (static_cast<U>(std::numeric_limits<T>::max()) < src)
			throw std::overflow_error("Source value is too high.");
		else if (static_cast<U>(std::numeric_limits<T>::min()) > src)
			throw std::overflow_error("Source value is too low.");
		else
			dst = static_cast<T>(src);
	}

	// integral to floating type; suppressing data loss warning if dst is float.
	template <typename T, typename U>
	void Cast_imp(U src, T &dst, std::true_type, std::false_type)
	{
		dst = static_cast<T>(src);
	}

	// floating to floating; suppressing data loss warning if src is double and dst is float.
	template <typename T, typename U>
	void Cast_imp(U src, T &dst, std::false_type, std::false_type)
	{
		dst = static_cast<T>(src);
	}
}

#endif
