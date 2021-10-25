#include "Vector.hpp"

template < class T, class Allocator >
Vector<T, Allocator >::Vector():
	size_(0),
	capacity_(10)//,
	//array_(new int[capacity_])
{
	//std::allocator<int>	myalloc;
	array_ = myAlloc_.allocate(capacity_);
}

template < class T, class Allocator >
Vector<T, Allocator >::~Vector()
{
	//delete[] array_;
	myAlloc_.deallocate(array_, capacity_);
}

template < class T, class Allocator >
Vector<T, Allocator >::Vector(int elements, T value):
	size_(elements),
	capacity_(elements + 3)//,
	//array_(new int[capacity_])
{
	array_ = myAlloc_.allocate(capacity_);
	for (int i = 0; i < size_; ++i)
		array_[i] = value;
}

template < class T, class Allocator >
Vector<T, Allocator >::Vector(const Vector & rhs):
	size_(rhs.size_),
	capacity_(rhs.capacity_)//,
	//array_(new int[capacity_])
{
	array_ = myAlloc_.allocate(capacity_);
	for (int i = 0; i < rhs.size(); ++i)
		array_[i] = rhs.array_[i];
}
/*
Vector::Vector(const std::initializer_list<int> & list):
	size_(0),
	capacity_(list.size() + 3),
	array_(new int[capacity_])
{
	for(int i : list)
		push_back(i);
}
*/
template < class T, class Allocator >
int&	Vector<T, Allocator >::at(int index)
{
	if (index < 0 || index >= size_)
		throw std::runtime_error("Error: (at) out of range!\n");
	return array_[index];
}

template < class T, class Allocator >
int&	Vector<T, Allocator >::back()
{
	return array_[size_ - 1];
}

template < class T, class Allocator >
int		Vector<T, Allocator >::capacity() const
{
	return capacity_;
}

template < class T, class Allocator >
void	Vector<T, Allocator >::clear()
{
	size_ = 0;
}

template < class T, class Allocator >
bool	Vector<T, Allocator >::empty() const
{
	return size_ == 0;
}

template < class T, class Allocator >
void	Vector<T, Allocator >::erase(int index)
{
	if (index < 0 || index >= size_)
		throw std::runtime_error("Error: (erase) out of range!\n");
	for (int i = index; i < size_; ++i)
		array_[i] = array_[i + 1];
	--size_;
}

template < class T, class Allocator >
int&	Vector<T, Allocator >::front()
{
	return array_[0];
}

template < class T, class Allocator >
void	Vector<T, Allocator >::insert(int index, T value)
{
	if (index < 0 || index >= size_)
		throw std::runtime_error("Error: (index) out of range!\n");
	if (size_ != capacity_)
	{
		for (int i = size_ - 1; i >= index; --i)
			array_[i + 1] = array_[i];
		array_[index] = value;
		++size_;
	}
	else
	{
		capacity_ *= 2;
		
		T* newarray = std::allocator<T>::allocate(capacity_);
		//int* newarray = new int[capacity_];
		//array_ = myAlloc_.allocate(capacity_);
		for (int i = 0; i < size_; ++i)
			newarray[i] = array_[i];
		//delete[] array_;
		myAlloc_.deallocate(array_, capacity_ / 2);
		array_ = newarray;
		insert(index, value);
	}
}

template < class T, class Allocator >
int		Vector<T, Allocator >::max_size() const
{
	return capacity_;
}

template < class T, class Allocator >
void	Vector<T, Allocator >::pop_back()
{
	if (size_ == 0)
		throw std::runtime_error("Error: pop_back on empty cont!\n");
	--size_;
}

template < class T, class Allocator >
void	Vector<T, Allocator >::push_back(const int & value)
{
	if (size_ < capacity_)
	{
		array_[size_] = value;
		++size_;
	}
	else
	{
		capacity_ *= 2;
		int*	newarray = new int[capacity_];
		for (int i = 0; i < size_; ++i)
			newarray[i] = array_[i];
		newarray[size_] = value;
		++size_;
		delete[] array_;
		array_ = newarray;
	}
}

template < class T, class Allocator >
void	Vector<T, Allocator >::reserve(int n)
{
	if (n > capacity_)
		capacity_ = n;
	//todo reallocate
}

template < class T, class Allocator >
int		Vector<T, Allocator >::size() const
{
	return size_;
}

template < class T, class Allocator >
Vector<T, Allocator >&	Vector<T, Allocator >::operator=(const Vector<T, Allocator >& rhs)
{
	if (rhs.size_ > size_)
	{
		capacity_ = rhs.size_ + 3;
		delete[] array_;
		array_ = new int[capacity_];
	}
	for (int i = 0; i < rhs.size(); ++i)
		array_[i] = rhs.array_[i];
	size_ = rhs.size_;

	return *this;
}

template < class T, class Allocator >
bool	Vector<T, Allocator >::operator==(const Vector & rhs)	const
{
	if (size() != rhs.size())
		return false;
	for (int i = 0; i < size(); ++i)
	{
		if (array_[i] != rhs.array_[i])
			return false;
	}
	return true;
}

template < class T, class Allocator >
bool	Vector<T, Allocator >::operator!=(const Vector & rhs)	const
{
	return !(*this == rhs);
}

template < class T, class Allocator >
int&	Vector<T, Allocator >::operator[](int index)
{
	return array_[index];
}
/*
template < class T, class Allocator >
std::ostream& operator<<(std::ostream & os, const Vector<T, Allocator > & rhs)
{
	for (int i = 0; i < rhs.size(); ++i)
		os << rhs.array_[i] << " ";
	os << "//";
	for (int i = rhs.size_; i < rhs.capacity_; ++i)
		os << rhs.array_[i] << " ";
	os << std::endl;

	return os;
}
*/
template class Vector< int >;

