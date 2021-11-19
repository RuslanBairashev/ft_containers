#ifndef Miterator_HPP
#define Miterator_HPP

#include <iostream>
#include <iterator>
#include <cstddef>
#include "Tree.hpp" //error if include
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

template <class T, class ptrNode, class ptrTree>
class Miterator : public iterator<T>
{
public:
	typedef typename Miterator_traits<T>::value_type		value_type;
	typedef typename Miterator_traits<T>::iterator_category	iterator_category;
	typedef typename Miterator_traits<T>::difference_type	difference_type;
	typedef typename Miterator_traits<T>::pointer			pointer;
	typedef typename Miterator_traits<T>::reference			reference;
	//typedef typename	Tree<Key, T, Compare>::Node		node_type;

	pointer m_ptr; //pointer to pair
	ptrNode	currnode_ptr;
	ptrTree	tree_ptr;

	Miterator() : m_ptr(NULL), currnode_ptr(NULL), tree_ptr(NULL) {}
	Miterator(pointer ptr) : m_ptr(ptr) {}
	Miterator(pointer ptr, ptrNode node, ptrTree tree)
		: m_ptr(ptr), currnode_ptr(node), tree_ptr(tree)
		 { 
			std::cout << "currnode_ptr address= " << currnode_ptr << std::endl;
			std::cout << "        node address= " << node << std::endl;
			std::cout << "    tree_ptr address= " << tree_ptr << std::endl;
			std::cout << "        tree address= " << tree << std::endl;
			std::cout << "constr\n";}
	template <class Constornot, class cNode, class cTree>
	Miterator(const Miterator<Constornot, cNode, cTree> & it)
	: m_ptr(it.m_ptr), currnode_ptr(it.currnode_ptr), tree_ptr(it.tree_ptr) {}
	~Miterator() {}

	reference	operator=(const Miterator & rhs) { m_ptr = rhs.m_ptr; return *m_ptr; }//ok

	bool		operator== (const Miterator& it) const { return m_ptr == it.m_ptr; };//ok
	bool		operator!= (const Miterator& it) const { return m_ptr != it.m_ptr; };//ok
	reference	operator*() { return *m_ptr; } //ok
	pointer		operator->() { return m_ptr; }
	Miterator&	operator++()
	{
		std::cout << "azaza\n";
		//std::cout << typeid(this).name() << std::endl;
		//std::cout << this <<std::endl;
		std::cout << " ++it       tree address= " << tree_ptr << std::endl;
		if (this->currnode_ptr == NULL) { std::cout << "\"ITERATOR IS NULL!!!\"" << std::endl; }
		std::cout << "it. " << this->m_ptr->first << std::endl;
		if (this->tree_ptr == NULL) { std::cout << "\"ITERATOR IS NULL!!!\"" << std::endl; }
		if (currnode_ptr != NULL)
		{
			currnode_ptr = currnode_ptr->parent;
			m_ptr = &(currnode_ptr->value);
		}
		return *this;
	}
	//Miterator	operator++(int) { Miterator tmp = *this; ++(*this); return tmp; }//
	Miterator&	operator--() { --m_ptr; return *this; }//
	Miterator	operator--(int) { Miterator tmp = *this; --(*this); return tmp; }//
};

}
#endif
