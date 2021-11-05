#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <list>
#include <exception>
#include <memory>
#include <iterator>
#include <cstddef>
#include <cmath>
#include <utility>
#include "Viterator.hpp"
#include "Reviterator.hpp"
#include "Vextras.hpp"

/* template < class T, class Allocator >
class Vector;
template < class T, class Allocator >
bool	operator==(const Vector<T, Allocator> & lhs, const Vector<T, Allocator> & rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	for (size_t i = 0; i < lhs.size(); ++i)
	{
		if (lhs.array_[i] != rhs.array_[i])
			return false;
	}
	return true;
}

template < class T, class Allocator >
bool	operator!=(const Vector<T, Allocator> & lhs, const Vector<T, Allocator> & rhs)
{
	return !(lhs == rhs);
}

template < class T, class Allocator >
bool	operator<(Vector<T, Allocator> & lhs, Vector<T, Allocator> & rhs)
{
	typedef typename Vector<int, std::allocator<T> >::iterator iterator;
	iterator first1 = lhs.begin();
	iterator last1 = lhs.end();
	iterator first2 = rhs.begin();
	iterator last2 = rhs.end();
	while (first1!=last1)
	{
		if (first2==last2 || *first2<*first1) return false;
		else if (*first1<*first2) return true;
		++first1; ++first2;
	}
	return (first2!=last2);
}

template < class T, class Allocator >
bool	operator>=(Vector<T, Allocator> & lhs, Vector<T, Allocator> & rhs)
{
	return !(lhs < rhs);
}

template < class T, class Allocator >
bool	operator>(Vector<T, Allocator> & lhs, Vector<T, Allocator> & rhs)
{
	return (rhs < lhs);
}

template < class T, class Allocator >
bool	operator<=(Vector<T, Allocator> & lhs, Vector<T, Allocator> & rhs)
{
	return !(rhs < lhs);
} */

template < class Key, class T>
class Node
{
	public:
	Key		index_;
	T		data_;
	Node*	pleft;
	Node*	pright;
};

/*************************************************************************/
//**	CLASS DECLARATION START											**/
/*************************************************************************/
template < class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
class Map
{
public:
	typedef	Key											key_type;
	typedef	T											mapped_type;
	typedef	std::pair<const Key, T>						value_type;
	typedef	Allocator									allocator_type;
	type	std::less<key_type>							key_compare;
	typedef typename	allocator_type::reference		reference;
	typedef typename	allocator_type::const_reference	const_reference;
	typedef typename	allocator_type::pointer			pointer;
	typedef typename	allocator_type::const_pointer	const_pointer;
	typedef typename	ft::Viterator<pointer>			iterator;
	typedef typename	ft::Viterator<const_pointer>	const_iterator;
	typedef typename	ft::Reviterator<pointer>		reverse_iterator;
	typedef typename	ft::Reviterator<const_pointer>	const_reverse_iterator;
	typedef	size_t										size_type;

private:
	allocator_type	myAlloc_;
	pointer			array_;
	size_type		size_;
	size_type		capacity_;
	Node			mapa_;
//https://medium.com/@vgasparyan1995/how-to-write-an-stl-compatible-container-fc5b994462c6
public:
	//constructor: empty (1/3)
	explicit Map (const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type());
	//constructor: range(2/3)
	template <class InputIterator>
	Map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type());
	//constructor: copy(3/3)
	Map (const map& x);


	//constructor: default(1/4) OK
	explicit Vector(const allocator_type& alloc = allocator_type()): size_(0), capacity_(1)
	{
		myAlloc_ = alloc;
		array_ = myAlloc_.allocate(capacity_);
	}
	//constructor: fill(2/4) OK
	explicit Vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
	: size_(n), capacity_(n + 3)
	{
		myAlloc_ = alloc;
		array_ = myAlloc_.allocate(capacity_);
		for (size_type i = 0; i < size_; ++i)
			array_[i] = val;
	}
	//constructor: range(3/4) OK
	template <class InputIterator>
	Vector (InputIterator first, typename std::enable_if< std::__is_input_iterator<InputIterator>::value,InputIterator >::type last,
	const allocator_type& alloc = allocator_type() )
	{
		size_ = last - first;
		capacity_ = size_ + 3;
		myAlloc_ = alloc;
		array_ = myAlloc_.allocate(capacity_);
		for (size_t i = 0; first < last; i++, first++)
			array_[i] = *first;
	}
	//constructor: copy(4/4) OK
	Vector(const Vector & rhs): size_(rhs.size_), capacity_(rhs.capacity_)
	{
		array_ = myAlloc_.allocate(capacity_);
		for (size_type i = 0; i < rhs.size(); ++i)
			array_[i] = rhs.array_[i];
	}
	~Vector()
	{
		myAlloc_.deallocate(array_, capacity_);
	}
	Vector&	operator=(const Vector& rhs)
	{
		if (this == &rhs)
			return *this;
		if (rhs.size_ > size_) // >capacity_ ???
		{
			capacity_ = rhs.size_ + 3;
			myAlloc_.deallocate(array_, capacity_);
			array_ = myAlloc_.allocate(capacity_);
		}
		for (size_type i = 0; i < rhs.size(); ++i)
			array_[i] = rhs.array_[i];
		size_ = rhs.size_;
		return *this;
	}
	/*************************************************************************/
	//			MEMBER FUNCTIONS										      /
	/*************************************************************************/

	//iterators
	iterator	begin() { return iterator(array_); }
	iterator	end() { return iterator(array_ + size_); }
	const_iterator	begin() const { return const_iterator(array_); }
	const_iterator	end() const { return const_iterator(array_ + size_); }
	reverse_iterator	rbegin() { return reverse_iterator(array_ + size_); }
	reverse_iterator	rend() { return reverse_iterator(array_); }
	const_reverse_iterator	rbegin() const { return const_reverse_iterator(array_); }
	const_reverse_iterator	rend() const { return const_reverse_iterator(array_ + size_); }
	//TODO rbegin
	//TODO rend

	//Capacity all done
	/*************************************************************************/
	size_type	size() const { return size_; }
	size_type	max_size() const { return (pow(2 , 64) / sizeof(T) - 1); }
	void		resize(size_t n, value_type val = value_type())
	{
		if (n < size_)
			size_ = n;
		else
		{
			if (n > capacity_)
				this->reserve(n);
			for (size_t i = size_; i < n; ++i)
				array_[i] = val;
			size_ = n;
		}
	}
	size_t		capacity() const { return capacity_; }
	bool		empty() const { return size_ == 0; }
	void		reserve(size_type n)
	{
		if (n > capacity_)
		{
			std::allocator<T>	alloc;
			T* newarray = alloc.allocate(n);
			for (size_t i = 0; i < size_; ++i)
				newarray[i] = array_[i];
			myAlloc_.deallocate(array_, capacity_);
			array_ = newarray;
			capacity_ = n;
		}
	}

	//Element access all done
	/*************************************************************************/
	reference	operator[](size_type index)
	{
		return array_[index];
	}
	const_reference	operator[](size_type index) const
	{
		return array_[index];
	}
	reference	at(size_type index)
	{
		if (index < 0 || index >= size_)
			throw std::runtime_error("Error: (at) out of range!\n");
		return array_[index];
	}
	const_reference	at(size_type index) const
	{
		if (index < 0 || index >= size_)
			throw std::runtime_error("Error: (at) out of range!\n");
		return array_[index];
	}
	reference	front() { return array_[0]; }
	const_reference	front() const { return array_[0]; }
	reference	back() { return array_[size_ - 1]; }
	const_reference	back() const { return array_[size_ - 1]; }

	//Modifiers all done
	/*************************************************************************/
	//range(1/2) OK
	template <class InputIterator>
	void assign (InputIterator first, typename std::enable_if< std::__is_input_iterator<InputIterator>::value,InputIterator >::type last)
	{
		size_type	n = last - first;
		std::allocator<T>	alloc;
		T* newarray = alloc.allocate(n + 3);
		for (size_t i = 0; i < n; ++i, ++first)
			newarray[i] = *first;
		myAlloc_.deallocate(array_, capacity_);
		array_ = newarray;
		size_ = n;
		capacity_ = size_ + 3;
	}
	//fill(2/2) OK
	void	assign(size_type n, const value_type & val)
	{
		std::allocator<T>	alloc;
		T* newarray = alloc.allocate(n + 3);
		for (size_t i = 0; i < n; ++i)
			newarray[i] = val;
		myAlloc_.deallocate(array_, capacity_);
		array_ = newarray;
		size_ = n;
		capacity_ = size_ + 3;
	}

	void	push_back(const value_type & value)
	{
		if (size_ < capacity_)
		{
			array_[size_] = value;
			++size_;
		}
		else
		{
			capacity_ *= 2;
			std::allocator<value_type>	alloc;
			value_type* newarray = alloc.allocate(capacity_);
			for (size_t i = 0; i < size_; ++i)
				newarray[i] = array_[i];
			newarray[size_] = value;
			++size_;
			myAlloc_.deallocate(array_, capacity_ / 2);
			array_ = newarray;
		}
	}
	void	pop_back()
	{
		if (size_ == 0)
			throw std::runtime_error("Error: pop_back on empty cont!\n");
		--size_;
	}
	//single element(1/3) OK
	iterator insert (iterator position, const value_type& val)
	{
		iterator tmp = position;
		if (size_ != capacity_)
		{
			iterator it = (*this).end();
			++size_;
			for (int i = (it - position); (position - 1) != it; --i, ++position)
				array_[i] = array_[i - 1];
			array_[tmp - (*this).begin()] = val;
		}
		else
		{
			reserve(capacity_ * 2);
			insert(position, val);
		}
		return tmp;
	}
	//fill(2/3) OK
	void insert (iterator position, size_type n, const value_type& val)
	{
		ptrdiff_t	offset = position - (*this).begin();
		if (size_ + n <= capacity_)
		{
			iterator it = (*this).end();
			size_ += n;
			for (int i = (it - position); i >= 0; --i)
				array_[i + n] = array_[i]; 
			for (size_type i = 0; i < n; i++)
				array_[offset + i] = val;
		}
		else
		{
			reserve((size_ + n) * 2);
			insert((*this).begin() + offset, n, val);
		}
	}
	//range(3/3) OK
	template <class InputIterator>
	void insert (iterator position, InputIterator first, typename std::enable_if< std::__is_input_iterator<InputIterator>::value,InputIterator >::type last)
	{
		ptrdiff_t	offset = position - (*this).begin();
		iterator tmp = position;
		size_type	n = last - first;
		if (size_ + n <= capacity_)
		{
			iterator it = (*this).end();
			size_ += n;
			for (int i = (it - position); i >= 0; --i)
				array_[i + n] = array_[i]; 
			for (; first != last; ++first, ++tmp)
				*tmp = *first;
		}
		else
		{
			reserve((size_ + n) * 2);
			insert((*this).begin() + offset, first, last);
		}
	}
	iterator	erase(iterator position)
	{
		iterator tmp = position;
		iterator it = (*this).end();
		for (int i = (position - (*this).begin()); position != it; ++i, ++position)
			array_[i] = array_[i + 1];
		--size_;
		return tmp;
	}
	iterator	erase(iterator first, iterator last)
	{
		iterator tmp = last;
		ptrdiff_t	range = last - first;
		iterator it = (*this).end();
		for (int i = (first - (*this).begin()); last != it; ++i, ++last)
			array_[i] = array_[i + range];
		size_ -= range;
		return tmp;
	}
	void swap (Vector & x)
	{
		Vector<value_type>	tmp = *this;
		// copy x to this
		if (this->capacity_ < x.size_)
			this->reserve(x.size_ * 2);
		int i = 0;
		for (iterator it = x.begin(); it != x.end(); ++it, ++i)
			(*this)[i] = *it;
		this->size_ = x.size_;
		// copy tmp to x
		if (x.capacity_ < tmp.size_)
			x.reserve(tmp.size_ * 2);
		i = 0;
		for (iterator itx = tmp.begin(); itx != tmp.end(); ++itx, ++i)
			x[i] = *itx;
		x.size_ = tmp.size_;
	}

	void	clear() { size_ = 0; }

	allocator_type get_allocator() const
	{
		return myAlloc_;
	}
	
	//Non-member function overloads
	/*************************************************************************/
	friend	bool	operator== <> (const Vector & lhs, const Vector & rhs);
	friend	bool	operator!= <> (const Vector & lhs, const Vector & rhs);
	friend	bool	operator< <> (Vector & lhs, Vector & rhs);
	friend	bool	operator> <> (Vector & lhs, Vector & rhs);
	friend	bool	operator>= <> (Vector & lhs, Vector & rhs);
	friend	bool	operator<= <> (Vector & lhs, Vector & rhs);
	template < class Tx, class Allocatorx >
	friend	void	swap (Vector & x);

	template < class Tx, class Allocatorx >
	friend	std::ostream& operator<<(std::ostream &, const Vector<Tx, Allocatorx> &);
};

/***************************************************************************/
//			END OF CLASS													/
/***************************************************************************/

/* template < class T, class Allocator >
std::ostream& operator<<(std::ostream & os, const Vector<T, Allocator> & rhs)
{
	for (size_t i = 0; i < rhs.size(); ++i)
		os << rhs.array_[i] << " ";
	os << "//";
	for (size_t i = rhs.size_; i < rhs.capacity_; ++i)
		os << rhs.array_[i] << " ";
	os << std::endl;

	return os;
}
template < class T, class Allocator >
void swap (Vector<T, Allocator> & x) { x.swap(x); } */

#endif