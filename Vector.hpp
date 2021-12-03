#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <list>
#include <exception>
#include <memory>
#include <iterator>
#include <cstddef>
#include <cmath>
#include "Viterator.hpp"
#include "Reviterator.hpp"
#include "Utility.hpp"

namespace ft
{

template < class T, class Allocator >
class vector;
template < class T, class Allocator >
bool	operator==(const vector<T, Allocator> & lhs, const vector<T, Allocator> & rhs)
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
bool	operator!=(const vector<T, Allocator> & lhs, const vector<T, Allocator> & rhs)
{
	return !(lhs == rhs);
}

template < class T, class Allocator >
bool	operator<(vector<T, Allocator> & lhs, vector<T, Allocator> & rhs)
{
	typedef typename vector<int, std::allocator<T> >::iterator iterator;
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
bool	operator>=(vector<T, Allocator> & lhs, vector<T, Allocator> & rhs)
{
	return !(lhs < rhs);
}

template < class T, class Allocator >
bool	operator>(vector<T, Allocator> & lhs, vector<T, Allocator> & rhs)
{
	return (rhs < lhs);
}

template < class T, class Allocator >
bool	operator<=(vector<T, Allocator> & lhs, vector<T, Allocator> & rhs)
{
	return !(rhs < lhs);
}

template <class T, class Alloc>
void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);

/*************************************************************************/
//**	CLASS DECLARATION START											**/
/*************************************************************************/
template < class T, class Allocator = std::allocator<T> >
class vector
{
public:
	typedef	T											value_type;
	typedef	Allocator									allocator_type;
	typedef typename	allocator_type::reference		reference;
	typedef typename	allocator_type::const_reference	const_reference;
	typedef typename	allocator_type::pointer			pointer;
	typedef typename	allocator_type::const_pointer	const_pointer;
	typedef typename	ft::Viterator<pointer>			iterator; //here was the problem with
	typedef typename	ft::Viterator<const_pointer>	const_iterator; //iterator and const_iterator
	typedef typename	ft::Reviterator<pointer>		reverse_iterator;
	typedef typename	ft::Reviterator<const_pointer>	const_reverse_iterator;
	typedef	size_t										size_type;

private:
	allocator_type	myAlloc_;
	pointer			array_;
	size_type		size_;
	size_type		capacity_;

public:
	//constructor: default(1/4) OK
	// explicit vector(const allocator_type& alloc = allocator_type()): size_(0), capacity_(1)
	// {
	// 	myAlloc_ = alloc;
	// 	array_ = myAlloc_.allocate(capacity_);
	// }
	//constructor: fill(2/4) OK
	// explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
	// : size_(n), capacity_(n + 3)
	// {
	// 	myAlloc_ = alloc;
	// 	array_ = myAlloc_.allocate(capacity_);
	// 	for (size_type i = 0; i < size_; ++i)
	// 		array_[i] = val;
	// }
	//constructor: default(1/4) OK
	explicit vector(const allocator_type& alloc = allocator_type()): myAlloc_(alloc), size_(0), capacity_(0)
	{
		array_ = myAlloc_.allocate(capacity_);
	}
	// //constructor: fill(2/4) OK
	explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
	: myAlloc_(alloc), size_(0), capacity_(0)
	{
		if (n > 0)
		{
			size_ = n;
			capacity_ = n;
			array_ = myAlloc_.allocate(capacity_);
			for (size_type i = 0; i < size_; ++i)
				myAlloc_.construct(array_ + i, val);
		}
		else
			array_ = myAlloc_.allocate(capacity_);
		
	}
	//constructor: range(3/4) OK
	template <class InputIterator>
	vector (InputIterator first, typename ft::enable_if< std::__is_input_iterator<InputIterator>::value,InputIterator >::type last,
	const allocator_type& alloc = allocator_type() )
	{
		size_ = last - first;
		capacity_ = size_ + 0;
		myAlloc_ = alloc;
		array_ = myAlloc_.allocate(capacity_);
		for (size_t i = 0; first < last; i++, first++)
			array_[i] = *first;
	}
	//constructor: copy(4/4) OK
	vector(const vector & rhs): myAlloc_(rhs.myAlloc_), size_(rhs.size_), capacity_(rhs.capacity_)
	{
		array_ = myAlloc_.allocate(capacity_);
		for (size_type i = 0; i < size_; ++i)
				myAlloc_.construct(array_ + i, rhs[i]);
		/* for (size_type i = 0; i < rhs.size(); ++i)
			array_[i] = rhs.array_[i]; */
	}
	~vector()
	{
		myAlloc_.deallocate(array_, size_);
	}
	vector&	operator=(const vector& rhs)
	{
		if (this == &rhs)
			return *this;
		if (rhs.size_ > size_) // >capacity_ ???
		{
			capacity_ = rhs.size_ + 0;
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
	size_type	max_size() const 
	{ 
		size_t ret;
		ret = (pow(2 , sizeof(size_t) * 8) / sizeof(T));
		return (ret -1); 
	}
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
		if (n > capacity_ * 2)
		{
			std::allocator<T>	alloc;
			T* newarray = alloc.allocate(n);
			for (size_t i = 0; i < size_; ++i)
				newarray[i] = array_[i];
			myAlloc_.deallocate(array_, capacity_);
			array_ = newarray;
			capacity_ = n;
		}
		else if (n > capacity_)
		{
			std::allocator<T>	alloc;
			T* newarray = alloc.allocate(capacity_ * 2);
			for (size_t i = 0; i < size_; ++i)
				newarray[i] = array_[i];
			myAlloc_.deallocate(array_, capacity_);
			array_ = newarray;
			capacity_ = capacity_ * 2;
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
	reference		front() { return array_[0]; }
	const_reference	front() const { return array_[0]; }
	reference		back() { return array_[size_ - 1]; }
	const_reference	back() const { return array_[size_ - 1]; }

	//Modifiers all done
	/*************************************************************************/
	//range(1/2) OK
	template <class InputIterator>
	void assign (InputIterator first, typename ft::enable_if< std::__is_input_iterator<InputIterator>::value,InputIterator >::type last)
	{
		size_type	n = last - first;
		if (n > capacity_)
		{
			std::allocator<T>	alloc;
			T* newarray = alloc.allocate(n);
			for (size_t i = 0; i < n; ++i, ++first)
				newarray[i] = *first;
			myAlloc_.deallocate(array_, capacity_);
			array_ = newarray;
			size_ = n;
			capacity_ = size_;
		}
		else
		{
			for (size_t i = 0; i < n; ++i, ++first)
				array_[i] = *first;
			size_ = n;
			//capacity_ = size_;
		}
	}
	//fill(2/2) OK
	void	assign(size_type n, const value_type & val)
	{
		if (n > capacity_)
		{
			std::allocator<T>	alloc;
			T* newarray = alloc.allocate(n);
			for (size_t i = 0; i < n; ++i)
				newarray[i] = val;
			myAlloc_.deallocate(array_, capacity_);
			array_ = newarray;
			size_ = n;
			capacity_ = size_;
		}
		else
		{
			for (size_t i = 0; i < n; ++i)
				array_[i] = val;
			size_ = n;
			//capacity_ = size_;
		}
	}

	void	push_back(const value_type & value)
	{
		if (size_ == 0)
		{
			capacity_ = 1;
			allocator_type	alloc;
			value_type* newarray = alloc.allocate(capacity_);
			newarray[size_] = value;
			++size_;
			if (array_)
				myAlloc_.deallocate(array_, 0);
			array_ = newarray;
		}
		else if (size_ < capacity_)
		{
			myAlloc_.construct(array_ + size_, value);
			++size_;
		}
		else
		{
			capacity_ *=2;
			allocator_type	alloc;
			value_type* newarray = alloc.allocate(capacity_);
			for (size_t i = 0; i < size_; ++i)
				newarray[i] = array_[i];
			newarray[size_] = value;
			++size_;
			if (array_)
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
		if (size_ == 0)
		{
			capacity_ = 1;
			allocator_type	alloc;
			value_type* newarray = alloc.allocate(capacity_);
			newarray[size_] = val;
			++size_;
			if (array_)
				myAlloc_.deallocate(array_, 0);
			array_ = newarray;
		}
		iterator tmp = position;
		if (size_ < capacity_)
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
	void insert (iterator position, InputIterator first, typename ft::enable_if< std::__is_input_iterator<InputIterator>::value,InputIterator >::type last)
	{
		ptrdiff_t	offset = position - (*this).begin();
		iterator	tmp = position;
		size_type	n = last - first;
		size_t		c_tmp = capacity_;
		size_t		c_size = size_;
		if (size_ + n <= capacity_)
		{
			//size_ += n;
			iterator it = (*this).end();
			size_ += n;
			for (int i = (it - position); i >= 0; --i)
				array_[i + n] = array_[i]; 
			for (; first != last; ++first, ++tmp)
				*tmp = *first;
		}
		else
		{
			reserve(std::max(capacity_ * 2, size_ + n));
			//insert((*this).begin() + offset, first, last);
			try 
			{
				insert((*this).begin() + offset, first, last);
			}
			catch(...)
			{
				myAlloc_.deallocate(array_, capacity_);
				capacity_ = c_tmp;
				size_ = c_size;
				array_ = myAlloc_.allocate(capacity_);
				throw 1;
			}
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
	// void swap (vector & x)
	// {
	// 	/* vector<value_type> 	tmp;
	// 	vector<value_type> &ref = tmp;
	// 	vector<value_type> &refthis = *this;
	// 	refthis = x;
	// 	x = ref; */
	// 	//size_type	tmp_size = this->size_;
	// 	size_type	tmp_capacity = this->capacity_;
	// 	iterator	tmp_first = this->begin();
	// 	iterator	tmp_last = this->end();
	// 	iterator	x_first = x.begin();
	// 	iterator	x_last = x.end();
	// 	this->assign(x_first, x_last);
	// 	this->capacity_ = x.capacity_;
	// 	x.assign(tmp_first, tmp_last);
	// 	x.capacity_ = tmp_capacity;
	// }
/*   	void swap (vector & x)
	{
		vector<value_type>	tmp = *this;
		// copy x to this
		//if (this->capacity_ < x.size_)
			this->reserve(x.size_);
		int i = 0;
		for (iterator it = x.begin(); it != x.end(); ++it, ++i)
			(*this)[i] = *it;
		this->size_ = x.size_;
		this->capacity_ = this->size_;
		// copy tmp to x
		//if (x.capacity_ < tmp.size_)
			x.reserve(tmp.size_);
		i = 0;
		for (iterator itx = tmp.begin(); itx != tmp.end(); ++itx, ++i)
			x[i] = *itx;
		x.size_ = tmp.size_;
		x.capacity_ = x.size_;
	}  */
	void swap (vector & x)
	{
		pointer		tmp = this->array_;
		this->array_ = x.array_;
		x.array_ = tmp;
		size_type	tmp_s = this->size_;
		this->size_ = x.size_;
		x.size_ = tmp_s;
		size_type	tmp_c = this->capacity_;
		this->capacity_ = x.capacity_;
		x.capacity_ = tmp_c;
	}

	void	clear() { size_ = 0; }

	allocator_type get_allocator() const
	{
		return myAlloc_;
	}
	
	//Non-member function overloads
	/*************************************************************************/
	friend	bool	operator== <> (const vector & lhs, const vector & rhs);
	friend	bool	operator!= <> (const vector & lhs, const vector & rhs);
	friend	bool	operator< <> (vector & lhs, vector & rhs); //must be const
	friend	bool	operator> <> (vector & lhs, vector & rhs);
	friend	bool	operator>= <> (vector & lhs, vector & rhs);
	friend	bool	operator<= <> (vector & lhs, vector & rhs);
	// template < class Tx, class Allocatorx >
	// friend	void	swap (vector & x);

	template < class Tx, class Allocatorx >
	friend	std::ostream& operator<<(std::ostream &, const vector<Tx, Allocatorx> &);

};

/***************************************************************************/
//			END OF CLASS													/
/***************************************************************************/

template < class T, class Allocator >
std::ostream& operator<<(std::ostream & os, const vector<T, Allocator> & rhs)
{
	for (size_t i = 0; i < rhs.size(); ++i)
		os << rhs.array_[i] << " ";
	os << "//";
	for (size_t i = rhs.size_; i < rhs.capacity_; ++i)
		os << rhs.array_[i] << " ";
	os << std::endl;

	return os;
}

//template <class T, class Alloc>
// void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
// {
// 	vector<T,Alloc>	tmp;
// 	tmp = x;
// 	x = y;
// 	y = tmp;
// }
// template < class T, class Alloc >
// void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
// {
// 	x.swap(y);
// }
}
namespace std{
template < class T, class Alloc >
void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y)
{
	x.swap(y);
}
}
#endif