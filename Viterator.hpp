#ifndef VViterator_HPP
#define VViterator_HPP

#include <iostream>
//#include <list>
//#include <exception>
//#include <memory>
#include <iterator>
#include <cstddef>

template< class Iter >
struct Viterator_traits
{
	typedef typename	Iter::difference_type	difference_type;
	typedef typename	Iter::value_type		value_type;
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


template <class T>
struct Viterator: public std::random_access_iterator_tag
{
public:
	typedef T								value_type;
	typedef std::random_access_iterator_tag	iterator_category;
	typedef ptrdiff_t						difference_type;
	typedef T*								pointer;
	typedef T&								reference;

	Viterator(pointer ptr) : m_ptr(ptr) {}
	Viterator(const Viterator & it) : m_ptr(it.m_ptr) {}

	bool		operator== (const Viterator& it) const { return m_ptr == it.m_ptr; };//ok
	bool		operator!= (const Viterator& it) const { return m_ptr != it.m_ptr; };//ok
	reference	operator*() { return *m_ptr; } //ok
	pointer		operator->() { return m_ptr; }
	reference	operator=(const value_type & rhs) { *m_ptr = rhs; return *m_ptr; }
	Viterator&	operator++() { ++m_ptr; return *this; }//ok
	Viterator	operator++(int) { Viterator tmp = *this; ++(*this); return tmp; }//ok
	Viterator&	operator--() { m_ptr--; return *this; }//ok
	Viterator	operator--(int) { Viterator tmp = *this; --(*this); return tmp; }//ok
	Viterator	operator+(int rhs) { return (m_ptr + rhs); }//ok
	Viterator	operator-(int rhs) { return (m_ptr - rhs); }//ok
	difference_type	operator-(const Viterator& it) { return (m_ptr - it.m_ptr); }//ok
	Viterator&	operator+=(int rhs) { m_ptr = m_ptr + rhs; return *this; }//ok
	Viterator&	operator-=(int rhs) { m_ptr = m_ptr - rhs; return *this; }//ok
	bool		operator<(const Viterator& it) const { return m_ptr < it.m_ptr; }//ok
	bool		operator>=(const Viterator& it) const { return !operator<(it); }//ok
	bool		operator>(const Viterator& it) const { return m_ptr > it.m_ptr; }//ok
	bool		operator<=(const Viterator& it) const { return !operator>(it); }//ok
	//Viterator&	operator[](int index) { m_ptr = m_ptr + index; return *this; }//ok
	reference	operator[] (difference_type n) const //ok
	{
		pointer	tmp(NULL);
		tmp = m_ptr + n; return *tmp;
	}
private:
	pointer m_ptr;
};

#endif
