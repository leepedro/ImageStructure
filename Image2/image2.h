#if !defined(IMAGE_H)
#define IMAGE_H

/* Minimal image class

Use a raw pointer instead of st::vector<T> to prevent resizing.
In order to prevent memory resizing, size information can be modified only through a member
function and memory is access through a const reference.
This makes impossible to change data from out side. (good or bad?)
Every write operation needs to be done by a member function. (good or bad?)

Wait a minute!
If the protected raw pointer can be resized by calling std::free() + std::malloc() or
delte[] + new at the inside of the class, how is it any different from using std::vector<T>
as a protected member?
It is NOT!!!
-> Use std::vector<T> as a protected member instead of a raw pointer!

Q. Is range checking necessary?
A. Let the user of this class worry, just like IPP.

Q. How to prevent out of range?
A. Always define two functions, func1() and func1_s(). func1_s() checks range.

*/

#include <cstddef>
#include <cstdlib>

/* Padding bytes.
In order to implement padding bytes, the low level data nees to be allocated as byte data
type, such as char, unsigned char, or signed char.
It doesn't matter whether data is declared as a raw pointer std::vecotr<T>.
*/

template <typename T>
class ImageFrameT
{
public:
	////////////////////////////////////////////////////////////////////////////////////////
	// Methods.
	void Reset(std::size_t w, std::size_t h, std::size_t d);
	void Reset(void);	

	////////////////////////////////////////////////////////////////////////////////////////
	// Accessors.
	//T *&data = this->data_;
	const T *const &dataC = this->data_;
	const std::size_t &width = this->width_;
	const std::size_t &height = this->height_;
	const std::size_t &depth = this->depth_;

protected:
	////////////////////////////////////////////////////////////////////////////////////////
	// Methods.
	void ResetSize(void);

	T *data_ = nullptr;
	std::size_t width_ = 0;
	std::size_t height_ = 0;
	std::size_t depth_ = 0;
};

template <typename T>
void ImageFrameT<T>::Reset(std::size_t w, std::size_t h, std::size_t d)
{
	//if (this->data_ != nullptr)
	//	std::free(this->data_);
	//this->data_ = reinterpret_cast<T *>(std::malloc(w * h * d * sizeof(T)));
	delete [] this->data_;
	this->data_ = new T[w * h * d];
}

template <typename T>
void ImageFrameT<T>::Reset(void)
{
	//if (this->data_ != nullptr)
	//	std::free(this->data_);
	delete[] this->data_;
	this->ResetSize();
}

template <typename T>
void ImageFrameT<T>::ResetSize(void)
{
	this->width_ = 0;
	this->height_ = 0;
	this->depth_ = 0;
}

#endif
