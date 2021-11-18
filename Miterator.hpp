#ifndef Miterator_HPP
#define Miterator_HPP

#include <iostream>
#include <iterator>
#include <cstddef>
//#include "Tree.hpp" //error if include
#include "Utility.hpp"

namespace ft
{
template< class Iter >
struct Miterator_traits
{
	typedef typename	Iter::value_type		value_type;
	typedef typename	Iter::difference_type	difference_type;
	typedef typename	Iter::pointer			pointer;
	typedef typename	Iter::reference			reference;	
	typedef typename	Iter::iterator_category	iterator_category;
};
template< typename T > //like in library (almost)
struct Miterator_traits<T*>
{
	typedef	std::bidirectional_iterator_tag	iterator_category;
	typedef T								value_type;
	typedef ptrdiff_t						difference_type;
	typedef T*								pointer;
	typedef T&								reference;
};
template< typename T > //like in library (almost)
struct Miterator_traits<const T*>
{
	typedef	std::bidirectional_iterator_tag	iterator_category;
	typedef T								value_type;
	typedef ptrdiff_t						difference_type;
	typedef const T*						pointer;
	typedef const T&						reference;
};

template <class T, class Category = std::bidirectional_iterator_tag,
class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
class iterator: public std::bidirectional_iterator_tag
{
public:
	typedef T			value_type;
	typedef Category	iterator_category;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
};

template <class T>
class Miterator : public iterator<T>
{
public:
	typedef typename Miterator_traits<T>::value_type		value_type;
	typedef typename Miterator_traits<T>::iterator_category	iterator_category;
	typedef typename Miterator_traits<T>::difference_type	difference_type;
	typedef typename Miterator_traits<T>::pointer			pointer;
	typedef typename Miterator_traits<T>::reference			reference;
	// typedef typename	Tree<Key, T, Compare>::Node		node_type;

	pointer m_ptr; //pointer to pair
	// node_type	node_ptr;

	Miterator() : m_ptr(NULL)/* , node_ptr(NULL) */ {}
	Miterator(pointer ptr) : m_ptr(ptr) {}
	template <class Constornot>
	Miterator(const Miterator<Constornot> & it) : m_ptr(it.m_ptr) {}
	~Miterator() {}

	reference	operator=(const Miterator & rhs) { m_ptr = rhs.m_ptr; return *m_ptr; }//ok

	bool		operator== (const Miterator& it) const { return m_ptr == it.m_ptr; };//ok
	bool		operator!= (const Miterator& it) const { return m_ptr != it.m_ptr; };//ok
	reference	operator*() { return *m_ptr; } //ok
	pointer		operator->() { return m_ptr; }
	//Miterator&	operator++() { m_ptr = m_ptr->parent; return *this; }//
	//Miterator	operator++(int) { Miterator tmp = *this; ++(*this); return tmp; }//
	Miterator&	operator--() { --m_ptr; return *this; }//
	Miterator	operator--(int) { Miterator tmp = *this; --(*this); return tmp; }//
};

}
#endif
