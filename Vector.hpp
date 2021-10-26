#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <list>
#include <exception>
#include <memory>
#include <iterator>
#include <cstddef>

template < class T, class Allocator = std::allocator<T> >
class Vector
{
public:
	template <class iT, class Category = std::random_access_iterator_tag,
	class Distance = ptrdiff_t, class Pointer = iT*, class Reference = iT&>
	struct Iterator //*** Iterator starts here ***//
	{
	public:
		typedef iT			value_type;
		typedef Category	iterator_category;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;

		Iterator(pointer ptr) : m_ptr(ptr) {}
		Iterator(const Iterator & it) : m_ptr(it.m_ptr) {}

		bool		operator== (const Iterator& it) const { return m_ptr == it.m_ptr; };//ok
		bool		operator!= (const Iterator& it) const { return m_ptr != it.m_ptr; };//ok
		reference	operator*() { return *m_ptr; } //ok
		pointer		operator->() { return m_ptr; }
		reference	operator=(const value_type & rhs) { *m_ptr = rhs; return *m_ptr; }
		Iterator&	operator++() { ++m_ptr; return *this; }//ok
		Iterator	operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }//ok
		Iterator&	operator--() { m_ptr--; return *this; }//ok
		Iterator	operator--(int) { Iterator tmp = *this; --(*this); return tmp; }//ok
		Iterator	operator+(int rhs) { return (m_ptr + rhs); }//ok
		Iterator	operator-(int rhs) { return (m_ptr - rhs); }//ok
		Iterator&	operator+=(int rhs) { m_ptr = m_ptr + rhs; return *this; }//ok
		Iterator&	operator-=(int rhs) { m_ptr = m_ptr - rhs; return *this; }//ok
		bool		operator<(const Iterator& it) const { return m_ptr < it.m_ptr; }//ok
		bool		operator>=(const Iterator& it) const { return !operator<(it); }//ok
		bool		operator>(const Iterator& it) const { return m_ptr > it.m_ptr; }//ok
		bool		operator<=(const Iterator& it) const { return !operator>(it); }//ok
		Iterator&	operator[](int index) { m_ptr = m_ptr + index; return *this; }//ok

	private:
		pointer m_ptr;
	}; //*** Iterator ends here ***//

public:
	typedef	T										value_type;
	typedef	Allocator								allocator_type;
	typedef typename	allocator_type::reference	reference;
	typedef typename	allocator_type::pointer		pointer;
	typedef Iterator<int>							iterator;

	Vector(): size_(0), capacity_(10)
	{
		array_ = myAlloc_.allocate(capacity_);
	}
	Vector(int elements, T value = 0): size_(elements), capacity_(elements + 3)
	{
		array_ = myAlloc_.allocate(capacity_);
		for (int i = 0; i < size_; ++i)
			array_[i] = value;
	}
	Vector(const Vector & rhs): size_(rhs.size_), capacity_(rhs.capacity_)
	{
		array_ = myAlloc_.allocate(capacity_);
		for (int i = 0; i < rhs.size(); ++i)
			array_[i] = rhs.array_[i];
	}
	~Vector()
	{
		myAlloc_.deallocate(array_, capacity_);
	}

	//Iterators
	typename std::allocator<T>::pointer	begin() { return array_; } //pointer == iT*
	iterator	begun() { return Iterator<int>(array_); }
	pointer	end() { return (array_ + size_); }

	//Capacity all done
	int		size() const;
	int		max_size() const;
	void	resize(int n, value_type val = value_type());
	int		capacity() const;
	bool	empty() const;
	void	reserve(int n);

	//Element access all done
	int&	operator[](int index);
	int&	at(int index);
	int&	front();
	int&	back();

	//Modifiers
	//assign
	void	push_back(const T & value);
	void	pop_back();
	void	insert(int index, T value);
	void	erase(int index);
	//swap
	void	clear();
		
	Vector&	operator=(const Vector& rhs);
	bool	operator==(const Vector & rhs)	const;
	bool	operator!=(const Vector & rhs)	const;
	

	template < class Tx, class Allocatorx >
	friend	std::ostream& operator<<(std::ostream &, const Vector<Tx, Allocatorx > &);

private:
	std::allocator<T>	myAlloc_;
	int					size_;
	int					capacity_;
	pointer				array_;
	///T*				array_;
};

//template < class T, class Allocator >
//T*	Vector<T, Allocator >::begin() { return array_; }

////*******************???????????//////
//template < class T, class Allocator >
//typename Vector<T, Allocator >::iterator Vector<T, Allocator >::begun() { return array_; }

//template < class T, class Allocator >
//T*	Vector<T, Allocator >::end() { return (array_ + size_); }

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




#endif