#ifndef Viterator_HPP
#define Viterator_HPP

#include <iostream>
#include <iterator>
#include <cstddef>

namespace ft
{
template< class Iter >
struct Viterator_traits
{
	typedef typename	Iter::value_type		value_type;
	typedef typename	Iter::difference_type	difference_type;
	typedef typename	Iter::pointer			pointer;
	typedef typename	Iter::reference			reference;	
	typedef typename	Iter::iterator_category	iterator_category;
};
template< typename T >
struct Viterator_traits<T*>
{
	typedef	std::random_access_iterator_tag	iterator_category;
	typedef T								value_type;
	typedef ptrdiff_t						difference_type;
	typedef T*								pointer;
	typedef T&								reference;
};
template< typename T >
struct Viterator_traits<const T*>
{
	typedef	std::random_access_iterator_tag	iterator_category;
	typedef T								value_type;
	typedef ptrdiff_t						difference_type;
	typedef const T*						pointer;
	typedef const T&						reference;
};

template <class T, class Category = std::random_access_iterator_tag,
class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
class iterator: public std::random_access_iterator_tag
{
public:
	typedef T			value_type;
	typedef Category	iterator_category;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
};

template <class T>
class Viterator : public iterator<T>
{
public:
	typedef typename Viterator_traits<T>::value_type		value_type;
	typedef typename Viterator_traits<T>::iterator_category	iterator_category;
	typedef typename Viterator_traits<T>::difference_type	difference_type;
	typedef typename Viterator_traits<T>::pointer			pointer;
	typedef typename Viterator_traits<T>::reference			reference;
	typedef T												iterator_type;

	pointer m_ptr;

	Viterator() : m_ptr(NULL) {}
	Viterator(pointer ptr) : m_ptr(ptr) {}
	template <class M>
	Viterator(const Viterator<M> & it) : m_ptr(it.m_ptr) {}
	~Viterator() {}

	reference	operator=(const Viterator & rhs) { m_ptr = rhs.m_ptr; return *m_ptr; }

	bool		operator== (const Viterator& it) const { return m_ptr == it.m_ptr; };
	bool		operator!= (const Viterator& it) const { return m_ptr != it.m_ptr; };
	reference	operator*() { return *m_ptr; }
	pointer		operator->() { return m_ptr; }
	Viterator&	operator++() { ++m_ptr; return *this; }
	Viterator	operator++(int) { Viterator tmp = *this; ++(*this); return tmp; }
	Viterator&	operator--() { --m_ptr; return *this; }
	Viterator	operator--(int) { Viterator tmp = *this; --(*this); return tmp; }
	Viterator	operator+(int rhs) { return (m_ptr + rhs); }
	Viterator	operator-(int rhs) { return (m_ptr - rhs); }
	difference_type	operator-(const Viterator& it) { return (m_ptr - it.m_ptr); }
	Viterator&	operator+=(int rhs) { m_ptr = m_ptr + rhs; return *this; }
	Viterator&	operator-=(int rhs) { m_ptr = m_ptr - rhs; return *this; }
	bool		operator<(const Viterator& it) const { return m_ptr < it.m_ptr; }
	bool		operator>=(const Viterator& it) const { return !operator<(it); }
	bool		operator>(const Viterator& it) const { return m_ptr > it.m_ptr; }
	bool		operator<=(const Viterator& it) const { return !operator>(it); }
	reference	operator[] (difference_type n) const
	{
		pointer	tmp(NULL);
		tmp = m_ptr + n; return *tmp;
	}
};

}
#endif
