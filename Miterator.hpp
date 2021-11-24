#ifndef Miterator_HPP
#define Miterator_HPP

#include <iostream>
#include <iterator>
#include <cstddef>
#include "Tree.hpp" //error if include
#include "Utility.hpp"

#define	ROOT		tree_ptr->root_
#define	GRANDP		this->currnode_ptr->parent->parent
#define	PARENT		this->currnode_ptr->parent
#define	THIS		this->currnode_ptr
#define	QUASIBEGIN	tree_ptr->quasiBegin_;
#define	QUASIEND	tree_ptr->quasiEnd_;

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
			// std::cout << "currnode_ptr address= " << currnode_ptr << std::endl;
			// std::cout << "        node address= " << node << std::endl;
			// std::cout << "    tree_ptr address= " << tree_ptr << std::endl;
			// std::cout << "        tree address= " << tree << std::endl;
			// std::cout << "constr\n";
			}
	template <class Constornot, class cNode, class cTree>
	Miterator(const Miterator<Constornot, cNode, cTree> & it)
	: m_ptr(it.m_ptr), currnode_ptr(it.currnode_ptr), tree_ptr(it.tree_ptr) {}
	~Miterator() {}

	reference	operator=(const Miterator & rhs)
	{
		m_ptr = rhs.m_ptr;
		currnode_ptr = rhs.currnode_ptr;
		tree_ptr = rhs.tree_ptr;
		return *m_ptr;
	}

	bool		operator== (const Miterator& it) const { return m_ptr == it.m_ptr; };
	bool		operator!= (const Miterator& it) const { return m_ptr != it.m_ptr; };
	reference	operator*() { return *m_ptr; }
	pointer		operator->() { return m_ptr; }
	Miterator&	operator++()
	{
		if (this->currnode_ptr != tree_ptr->quasiEnd_)
		{
			if (this->m_ptr->first == ROOT->value.first)
			{
				if (THIS->pright == NULL)
				{
					THIS = QUASIEND;
				}
				else
				{
					THIS = THIS->pright;
					while (THIS->pleft != NULL)
						THIS = THIS->pleft;
				}
			}
			else
			{
				if (THIS->pright == NULL) // pright == NULL
				{
					while (this->m_ptr->first > this->currnode_ptr->parent->value.first)
					{
						if (this->m_ptr->first == ROOT->value.first)
						{
							THIS = QUASIEND;
							// m_ptr = &(currnode_ptr->value);
							// return *this;
						}
						else
							THIS = PARENT;
					}
					// if (PARENT->parent == NULL)
					// {
					// 	THIS = QUASIEND;
					// }
					// else
					// {
					if (this->currnode_ptr != tree_ptr->quasiEnd_)
						THIS = PARENT; //goto root
					//std::cout << " str131\n";
					// }
				}
				else //pright IS NOT NULL 
				{
					THIS = THIS->pright;
					while (THIS->pleft != NULL)
						THIS = THIS->pleft;
					//std::cout << " str137\n";
				}
			}
			m_ptr = &(currnode_ptr->value);
		}
		return *this;
	}
	Miterator	operator++(int) { Miterator tmp = *this; ++(*this); return tmp; }

	Miterator&	operator--()
	{
		if (this->m_ptr->first == ROOT->value.first)
		{
			if (THIS->pleft == NULL)
			{
				THIS = QUASIBEGIN;
			}
			else
			{
				THIS = THIS->pleft;
				while (THIS->pright != NULL)
					THIS = THIS->pright;
			}
		}
		else
		{
			if (THIS->pleft == NULL) // pleft == NULL
			{
				if (PARENT == GRANDP->pleft) //parent is left branch
				{
					if (THIS == PARENT->pleft)
					{
						if (this->m_ptr->first < ROOT->value.first)
						{
							THIS = QUASIBEGIN;
						}
						else
							THIS = ROOT;
					}
					else
						THIS = PARENT;
				}
				else // parent if right branch
				{
					if (THIS == PARENT->pleft)
						THIS = GRANDP;
					else
						THIS = PARENT;
				}
			}
			else //pleft IS NOT NULL 
			{
				THIS = THIS->pleft;
				while (THIS->pright != NULL)
					THIS = THIS->pright;
			}
		}
		m_ptr = &(currnode_ptr->value);
		return *this;
	}
	Miterator	operator--(int) { Miterator tmp = *this; --(*this); return tmp; }
};

}
#endif

	// Miterator&	operator++()
	// {
	// 	if (this->m_ptr->first == ROOT->value.first)
	// 	{
	// 		if (THIS->pright == NULL)
	// 		{
	// 			THIS = QUASIEND;
	// 		}
	// 		else
	// 		{
	// 			THIS = THIS->pright;
	// 			while (THIS->pleft != NULL)
	// 				THIS = THIS->pleft;
	// 		}
	// 	}
	// 	else
	// 	{
	// 		if (THIS->pright == NULL) // pright == NULL
	// 		{
	// 			if (PARENT == GRANDP->pleft) //parent is left branch
	// 			{
	// 				if (THIS == PARENT->pleft)
	// 					THIS = PARENT;
	// 				else
	// 					THIS = GRANDP;
	// 			}
	// 			else // parent if right branch
	// 			{
	// 				if (THIS == PARENT->pleft)
	// 					THIS = PARENT;
	// 				else
	// 				{
	// 					if (this->m_ptr->first < ROOT->value.first)
	// 						THIS = GRANDP->parent; // ROOT
	// 					else
	// 						THIS = QUASIEND;
	// 				}
	// 			}
	// 		}
	// 		else //pright IS NOT NULL 
	// 		{
	// 			THIS = THIS->pright;
	// 			while (THIS->pleft != NULL)
	// 				THIS = THIS->pleft;
	// 		}
	// 	}
	// 	m_ptr = &(currnode_ptr->value);
	// 	return *this;
	// }