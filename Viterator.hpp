#ifndef VViterator_HPP
#define VViterator_HPP

#include <iostream>
//#include <list>
//#include <exception>
//#include <memory>
#include <iterator>
#include <cstddef>

template <class T, class Category = std::random_access_iterator_tag,
class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
struct Viterator
{
public:
	typedef T			value_type;
	typedef Category	Viterator_category;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;

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
	Viterator&	operator+=(int rhs) { m_ptr = m_ptr + rhs; return *this; }//ok
	Viterator&	operator-=(int rhs) { m_ptr = m_ptr - rhs; return *this; }//ok
	bool		operator<(const Viterator& it) const { return m_ptr < it.m_ptr; }//ok
	bool		operator>=(const Viterator& it) const { return !operator<(it); }//ok
	bool		operator>(const Viterator& it) const { return m_ptr > it.m_ptr; }//ok
	bool		operator<=(const Viterator& it) const { return !operator>(it); }//ok
	Viterator&	operator[](int index) { m_ptr = m_ptr + index; return *this; }//ok
	//reference	operator[](int index) { m_ptr = m_ptr + index; return &m_ptr; }//ok

private:
	pointer m_ptr;
};

#endif
