#ifndef Reviterator_HPP
#define Reviterator_HPP

#include <iostream>
#include <iterator>
#include <cstddef>

namespace ft
{
template< class Iter >
struct Reviterator_traits
{
	typedef typename	Iter::value_type		value_type;
	typedef typename	Iter::difference_type	difference_type;
	typedef typename	Iter::pointer			pointer;
	typedef typename	Iter::reference			reference;	
	typedef typename	Iter::iterator_category	iterator_category;
};
template< typename T >
struct Reviterator_traits<T*>
{
	typedef	std::random_access_iterator_tag	iterator_category;
	typedef T								value_type;
	typedef ptrdiff_t						difference_type;
	typedef T*								pointer;
	typedef T&								reference;
};
template< typename T >
struct Reviterator_traits<const T*>
{
	typedef	std::random_access_iterator_tag	iterator_category;
	typedef T								value_type;
	typedef ptrdiff_t						difference_type;
	typedef const T*						pointer;
	typedef const T&						reference;
};

template <class T>
class Reviterator : public ft::iterator<T>
{
public:
	typedef typename Reviterator_traits<T>::value_type			value_type;
	typedef typename Reviterator_traits<T>::iterator_category	iterator_category;
	typedef typename Reviterator_traits<T>::difference_type		difference_type;
	typedef typename Reviterator_traits<T>::pointer				pointer;
	typedef typename Reviterator_traits<T>::reference			reference;

	pointer m_ptr;

	Reviterator() : m_ptr(NULL) {}
	Reviterator(pointer ptr) : m_ptr(ptr) {}
	template <class M>
	Reviterator(const Reviterator<M> & it) : m_ptr(it.m_ptr) {}
	~Reviterator() {}

	reference	operator=(const Reviterator & rhs) { m_ptr = rhs.m_ptr; return *m_ptr; }

	bool		operator== (const Reviterator& it) const { return m_ptr == it.m_ptr; };
	bool		operator!= (const Reviterator& it) const { return m_ptr != it.m_ptr; };
	reference	operator*() { return *(m_ptr - 1); }
	pointer		operator->() { return m_ptr; }
	Reviterator&	operator++() { --m_ptr; return *this; }
	Reviterator	operator++(int) { Reviterator tmp = *this; ++(*this); return tmp; }
	Reviterator&	operator--() { ++m_ptr; return *this; }
	Reviterator	operator--(int) { Reviterator tmp = *this; --(*this); return tmp; }
	Reviterator	operator+(int rhs) { return (m_ptr - rhs); }
	Reviterator	operator-(int rhs) { return (m_ptr + rhs); }
	difference_type	operator-(const Reviterator& it) { return (m_ptr - it.m_ptr); }
	Reviterator&	operator+=(int rhs) { m_ptr = m_ptr - rhs; return *this; }
	Reviterator&	operator-=(int rhs) { m_ptr = m_ptr + rhs; return *this; }
	bool		operator<(const Reviterator& it) const { return m_ptr < it.m_ptr; }
	bool		operator>=(const Reviterator& it) const { return !operator<(it); }
	bool		operator>(const Reviterator& it) const { return m_ptr > it.m_ptr; }
	bool		operator<=(const Reviterator& it) const { return !operator>(it); }
	reference	operator[] (difference_type n) const
	{
		pointer	tmp(NULL);
		tmp = m_ptr - 1 - n; return *tmp;
	}
};

}
#endif
