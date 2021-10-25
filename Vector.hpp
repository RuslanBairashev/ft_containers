#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <list>
#include <exception>
#include <memory>
#include <iterator>

template < class T, class Allocator = std::allocator<T> >
class Vector
{

typedef typename std::iterator<T>	iterator;

public:
	Vector();
	Vector(int elements, T value = 0);
	Vector(const Vector & rhs);
	//Vector(const std::initializer_list<int> & list);

	~Vector();

	//Capacity all done
	int		size() const;
	int		max_size() const;
	void	resize(int n, T val = T());
	int		capacity() const;
	bool	empty() const;
	void	reserve(int n);

	//Element access all done
	int&	operator[](int index);
	int&	at(int index);
	int&	front();
	int&	back();

	//Modifiers

	void	push_back(const T & value);
	void	pop_back();
	void	insert(int index, T value);
	void	erase(int index);

	void	clear();
		
	Vector&	operator=(const Vector& rhs);
	bool	operator==(const Vector & rhs)	const;
	bool	operator!=(const Vector & rhs)	const;
	

	///template < class Tx, class Allocator = std::allocator<Tx> >
	///friend	std::ostream& operator<<(std::ostream &, const Vector &);
	//friend	std::ostream& operator<<(std::ostream & os, const Vector & rhs);
	template < class Tx, class Allocatorx >
	friend std::ostream& operator<<(std::ostream & os, const Vector<Tx, Allocatorx > & rhs)
	{
		for (int i = 0; i < rhs.size(); ++i)
			os << rhs.array_[i] << " ";
		os << "//";
		for (int i = rhs.size_; i < rhs.capacity_; ++i)
			os << rhs.array_[i] << " ";
		//os << std::endl;

		return os;
	}
private:
	std::allocator<T>	myAlloc_;
	int					size_;
	int					capacity_;
	T*					array_;
};

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
void	Vector<T, Allocator >::push_back(const T & value)
{
	if (size_ < capacity_)
	{
		array_[size_] = value;
		++size_;
	}
	else
	{
		capacity_ *= 2;
		std::allocator<T>	alloc;
		//T* newarray = std::allocator<T>::allocate(capacity_);
		T* newarray = alloc.allocate(capacity_);
		//int*	newarray = new int[capacity_];
		for (int i = 0; i < size_; ++i)
			newarray[i] = array_[i];
		newarray[size_] = value;
		++size_;
		myAlloc_.deallocate(array_, capacity_ / 2);
		//delete[] array_;
		array_ = newarray;
	}
}

template < class T, class Allocator >
void	Vector<T, Allocator >::reserve(int n)
{
	if (n > capacity_)
	{
		std::allocator<T>	alloc;
		T* newarray = alloc.allocate(n);
		for (int i = 0; i < size_; ++i)
			newarray[i] = array_[i];
		myAlloc_.deallocate(array_, capacity_);
		array_ = newarray;
		capacity_ = n;
	}
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
		myAlloc_.deallocate(array_, capacity_);
		//delete[] array_;
		array_ = myAlloc_.allocate(capacity_);
		//array_ = new int[capacity_];
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

template < class T, class Allocator >
void	Vector<T, Allocator >::resize(int n, T val)
{
	if (n < size_)
		size_ = n;
	else
	{
		if (n > capacity_)
			this->reserve(n);
		for (int i = size_; i < n; ++i)
			array_[i] = val;
		size_ = n;
	}
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



#endif