#ifndef Miterator_HPP
#define Miterator_HPP

#include <iostream>
#include <iterator>
#include <cstddef>
#include "Tree.hpp"
#include "Utility.hpp"

#define	GRANDP		this->currnode_ptr->parent->parent
#define	PARENT		this->currnode_ptr->parent
#define	THIS		this->currnode_ptr
#define	QUASIBEGIN	this->currnode_ptr->pbegin;
#define	QUASIEND	this->currnode_ptr->pend;

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
template< typename T >
struct Miterator_traits<T*>
{
	typedef	std::bidirectional_iterator_tag	iterator_category;
	typedef T								value_type;
	typedef ptrdiff_t						difference_type;
	typedef T*								pointer;
	typedef T&								reference;
};
template< typename T >
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

template <class T, class ptrNode>
class Miterator : public iterator<T>
{
public:
	typedef typename Miterator_traits<T>::value_type		value_type;
	typedef typename Miterator_traits<T>::iterator_category	iterator_category;
	typedef typename Miterator_traits<T>::difference_type	difference_type;
	typedef typename Miterator_traits<T>::pointer			pointer;
	typedef typename Miterator_traits<T>::reference			reference;

	pointer	m_ptr; //pointer to pair
	ptrNode	currnode_ptr;

	Miterator() : m_ptr(NULL), currnode_ptr(NULL) {}
	Miterator(pointer ptr) : m_ptr(ptr) {}
	Miterator(pointer ptr, ptrNode node)
		: m_ptr(ptr), currnode_ptr(node) {}
	template <class Constornot, class cNode>
	Miterator(const Miterator<Constornot, cNode> & it)
	: m_ptr(it.m_ptr), currnode_ptr(it.currnode_ptr) {}
	~Miterator() {}

	reference	operator=(const Miterator & rhs)
	{
		m_ptr = rhs.m_ptr;
		currnode_ptr = rhs.currnode_ptr;
		return *m_ptr;
	}

	bool		operator== (const Miterator& it) const { return m_ptr == it.m_ptr; };
	bool		operator!= (const Miterator& it) const { return m_ptr != it.m_ptr; };
	reference	operator*() { return *m_ptr; }
	pointer		operator->() const { return m_ptr; }
	Miterator&	operator++()
	{
		if (this->currnode_ptr != this->currnode_ptr->pend)
		{
			if (this->currnode_ptr == find_root(THIS))
			{
				if (THIS->pright == NULL)
				{
					this->currnode_ptr->pend->parent = THIS;
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
					while (THIS == PARENT->pright)
					{
						THIS = PARENT;
						if (THIS == find_root(THIS))
							break ;
					}
					if (THIS != find_root(THIS)) //if after iteration not in root
						THIS = PARENT;
					else	// if after iteration in root, go to end
					{
						this->currnode_ptr->pend->parent = THIS;
						THIS = QUASIEND;
					}
				}
				else //pright IS NOT NULL 
				{
					THIS = THIS->pright;
					while (THIS->pleft != NULL)
						THIS = THIS->pleft;
				}
			}
			m_ptr = &(currnode_ptr->value);
		}
		return *this;
	}
	Miterator	operator++(int) { Miterator tmp = *this; ++(*this); return tmp; }

	Miterator&	operator--()
	{
		if (this->currnode_ptr != this->currnode_ptr->pbegin)
		{
			if (this->currnode_ptr == this->currnode_ptr->pend)
			{
				if (this->currnode_ptr->pbegin != NULL)
				{
					//find max key
					THIS = find_root(THIS);
					while (THIS->pright != NULL)
						THIS = THIS->pright;
				}
				else
				{
					THIS = QUASIBEGIN;
				}
			}
			else if (this->currnode_ptr == find_root(THIS))
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
					while (this->m_ptr->first < this->currnode_ptr->parent->value.first)
					{
						THIS = PARENT;
						if (THIS == find_root(THIS))
							break ;
					}
					if (THIS != find_root(THIS))
						THIS = PARENT;
					else
						THIS = QUASIBEGIN;
				}
				else //pleft IS NOT NULL 
				{
					THIS = THIS->pleft;
					while (THIS->pright != NULL)
						THIS = THIS->pright;
				}
			}
			m_ptr = &(currnode_ptr->value);
		}
		return *this;
	}
	Miterator	operator--(int) { Miterator tmp = *this; --(*this); return tmp; }
	
	private:
		ptrNode			find_root(ptrNode p)
		{
			if (p)
			{
				while (p->parent)
					p = p->parent;
			}
			return p;
		}
};

}
#endif
