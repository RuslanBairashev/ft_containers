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
#include "Miterator.hpp"
#include "Remiterator.hpp"
#include "Utility.hpp"
#include "Tree.hpp"

namespace ft
{

template < class Key, class T, class Compare, class Allocator >
class map;
template < class Key, class T, class Compare, class Allocator >
bool	operator==(const map<Key, T, Compare, Allocator> & lhs, const map<Key, T, Compare, Allocator> & rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	typename ft::map<Key, T, Compare, Allocator>::const_iterator lit = lhs.begin();
	typename ft::map<Key, T, Compare, Allocator>::const_iterator rit = rhs.begin();
	for (size_t i = 0; i < lhs.size(); ++i, ++lit, ++rit)
	{
		if (*(lit) != *(rit))
			return false;
	}
	return true;
}

template < class Key, class T, class Compare, class Allocator >
bool	operator!=(const map<Key, T, Compare, Allocator> & lhs, const map<Key, T, Compare, Allocator> & rhs)
{
	return !(lhs == rhs);
}

template < class Key, class T, class Compare, class Allocator >
bool	operator<(const map<Key, T, Compare, Allocator> & lhs, const map<Key, T, Compare, Allocator> & rhs)
{
	typedef typename ft::map<Key, T, Compare, Allocator>::const_iterator iterator;
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

template < class Key, class T, class Compare, class Allocator >
bool	operator>=(const map<Key, T, Compare, Allocator> & lhs, const map<Key, T, Compare, Allocator> & rhs)
{
	return !(lhs < rhs);
}

template < class Key, class T, class Compare, class Allocator >
bool	operator>(const map<Key, T, Compare, Allocator> & lhs, const map<Key, T, Compare, Allocator> & rhs)
{
	return (rhs < lhs);
}

template < class Key, class T, class Compare, class Allocator >
bool	operator<=(const map<Key, T, Compare, Allocator> & lhs, const map<Key, T, Compare, Allocator> & rhs)
{
	return !(rhs < lhs);
}

template < class Key, class T, class Compare, class Allocator >
void swap (map<Key, T, Compare, Allocator>& x, map<Key, T, Compare, Allocator>& y);

/*************************************************************************/
//**	CLASS DECLARATION START											**/
/*************************************************************************/
template < class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<pair<const Key, T> > >
class map
{
public:
	typedef	Key											key_type;
	typedef	T											mapped_type;
	typedef	ft::pair<const key_type, mapped_type>		value_type;
	typedef	Allocator									allocator_type;
	typedef Compare										key_compare;
	typedef Tree<Key, T, Compare>						tree_type;
	typedef Node<const Key, T>							node_type;
	typedef typename	allocator_type::reference		reference;
	typedef typename	allocator_type::const_reference	const_reference;
	typedef typename	allocator_type::pointer			pointer;
	typedef typename	allocator_type::const_pointer	const_pointer;
	typedef typename	ft::Miterator<pointer, node_type*>			iterator;
	typedef typename	ft::Miterator<const_pointer, node_type*>	const_iterator;
	typedef typename	ft::Remiterator<pointer, node_type*>		reverse_iterator;
	typedef typename	ft::Remiterator<const_pointer, node_type*>	const_reverse_iterator;
	typedef	size_t										size_type;
	typedef	ptrdiff_t									difference_type;

 	class	value_compare: public std::binary_function<value_type, value_type, bool>
	{
		friend class map;
	protected:
		key_compare comp;
		value_compare(key_compare c) : comp(c) {}
	public:
		bool operator()(const value_type& x, const value_type& y) const
			{return comp(x.first, y.first);}
	};

	tree_type*					tree_;
	std::allocator<tree_type>	myAlloc_;
	private:
		key_compare				comp_;

public:
	//constructor: empty (1/3) //ok
	explicit map (const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type())
	{
		tree_ = myAlloc_.allocate(1); //аллокатор только аллоцирует память
		myAlloc_.construct(tree_,Tree<Key, T, Compare>(comp, alloc)); //констракт вызывает конструктор
	}
	//constructor: range(2/3) //ok
	template <class InputIterator>
	map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),const allocator_type& alloc = allocator_type())
	{
		tree_ = myAlloc_.allocate(1);
		myAlloc_.construct(tree_,Tree<Key, T, Compare>(comp, alloc));
		for( ; first != last ; ++first)
			tree_->insert(*first, comp);
	}
	//constructor: copy(3/3)
	map (const map& x)
	{
		tree_ = myAlloc_.allocate(1);
		myAlloc_.construct(tree_,Tree<Key, T, Compare>(x.comp_, x.myAlloc_));
		const_iterator	first = x.begin();
		const_iterator	last = x.end();
		insert(first, last);
	}
	~map()
	{
		myAlloc_.destroy(tree_);
		myAlloc_.deallocate(tree_, 1);
	}
	map& operator= (const map& rhs)
	{
		if (this == &rhs)
			return *this;
		//this->tree_ = rhs.tree_;
		clear();
		// //map<Key, T> tmp(rhs);
		const_iterator	first = rhs.begin();
		const_iterator	last = rhs.end();
		for( ; first != last ; ++first)
		 	tree_->insert(*first, key_compare());
		return *this;
	} 

	/*************************************************************************/
	//			MEMBER FUNCTIONS										      /
	/*************************************************************************/

	//iterators leaks
	/*************************************************************************/
	iterator	begin()
	{
		node_type*	tmp;
		if (tree_->size_ == 0)
			tmp = tree_->quasiEnd_;
		else
		{
			tmp = tree_->root_;
			while (tmp->pleft != NULL)
				tmp = tmp->pleft;
		}
		return iterator(&(tmp->value), tmp); //pointer,Node*
	}
	iterator	end()
	{
		node_type*	tmp;
		tmp = tree_->quasiEnd_;
		if (tree_->size_ > 0)
		{
			tree_->quasiEnd_->parent = tree_->root_;
			while (tree_->quasiEnd_->parent->pright != NULL)
				tree_->quasiEnd_->parent = tree_->quasiEnd_->parent->pright;
		}
		return iterator(&(tmp->value), tmp);
	}
	const_iterator	begin() const
	{
		node_type*	tmp;
		if (tree_->size_ == 0)
			tmp = tree_->quasiEnd_;
		else
		{
			tmp = tree_->root_;
			while (tmp->pleft != NULL)
				tmp = tmp->pleft;
		}
		return const_iterator(&(tmp->value), tmp); //pointer,Node*
	}
	const_iterator	end() const
	{
		node_type*	tmp;
		tmp = tree_->quasiEnd_;
		if (tree_->size_ > 0)
		{
			tree_->quasiEnd_->parent = tree_->root_;
			while (tree_->quasiEnd_->parent->pright != NULL)
				tree_->quasiEnd_->parent = tree_->quasiEnd_->parent->pright;
		}
		return const_iterator(&(tmp->value), tmp);
	}

	reverse_iterator	rbegin()
	{
		node_type*	tmp;
		if (tree_->size_ == 0)
			tmp = tree_->quasiBegin_;
		else
		{
			tmp = tree_->root_;
			while (tmp->pright != NULL)
				tmp = tmp->pright;
		}
		return reverse_iterator(&(tmp->value), tmp); //pointer,Node*
	}
	reverse_iterator	rend()
	{
		node_type*	tmp;
		tmp = tree_->quasiBegin_;
		if (tree_->size_ > 0)
		{
			tree_->quasiBegin_->parent = tree_->root_;
			while (tree_->quasiBegin_->parent->pleft != NULL)
				tree_->quasiBegin_->parent = tree_->quasiBegin_->parent->pleft;
		}
		return reverse_iterator(&(tmp->value), tmp);
	}
	const_reverse_iterator	rbegin() const
	{
		node_type*	tmp;
		if (tree_->size_ == 0)
			tmp = tree_->quasiBegin_;
		else
		{
			tmp = tree_->root_;
			while (tmp->pright != NULL)
				tmp = tmp->pright;
		}
		return const_reverse_iterator(&(tmp->value), tmp); //pointer,Node*
	}
	const_reverse_iterator	rend() const
	{
		node_type*	tmp;
		tmp = tree_->quasiBegin_;
		if (tree_->size_ > 0)
		{
			tree_->quasiBegin_->parent = tree_->root_;
			while (tree_->quasiBegin_->parent->pleft != NULL)
				tree_->quasiBegin_->parent = tree_->quasiBegin_->parent->pleft;
		}
		return const_reverse_iterator(&(tmp->value), tmp);
	}
	
	//Capacity OK
	/*************************************************************************/
	size_type	size() const { return tree_->size_ ; }
	size_type	max_size() const { return (pow(2 , 64) / sizeof(T) - 1); }
	bool		empty() const { return tree_->size_ == 0; }

	//Element access OK
	/*************************************************************************/
	mapped_type& operator[] (const key_type& k)
	{
		this->insert(ft::make_pair(k,mapped_type()));
		return find(k)->second;
	}

	//Modifiers
	/*************************************************************************/
	//insert: single element (1/3) OK
	pair<iterator,bool> insert (const value_type& val)
	{
		if (find(val.first) != end())
			return (ft::make_pair(find(val.first), false));
		tree_->insert(val, key_compare());
		return (ft::make_pair(find(val.first), true));
	}

	//insert(with hint) (2/3) OK
	iterator insert (iterator position, const value_type& val)
	{
		if (find(val.first) != end())
			return find(val.first);
		tree_->insert(val, key_compare());
		position = find(val.first);
		return position;
	}
	//insert(range) (3/3) leaks
	template <class InputIterator>
	void insert (InputIterator first, InputIterator last)
	{
		for( ; first != last; ++first)
			insert(*first);
	}

	//erase (1/3) leaks
	void erase (iterator position)
	{
		const key_type	k = position.m_ptr->first;
		tree_->root_ = tree_->remove(tree_->root_, k);
		position = lower_bound(k);
	}
	//erase (2/3) leaks
	size_type erase (const key_type& k)
	{
		unsigned len = size();
		tree_->root_ = tree_->remove(tree_->root_, k);
		if (size() == len)
			return 0;
		return 1;
	}
	//erase (3/3) sega on big amount
	void erase (iterator first, iterator last)
	{
		for ( ; first != last; ++first)
			erase(first.m_ptr->first);
	}

	void swap (map& x) //leaks
	{
		tree_type*	tmp = this->tree_;
		this->tree_ = x.tree_;
		x.tree_ = tmp;
		std::allocator<tree_type>	tmp_s = this->myAlloc_;
		this->myAlloc_ = x.myAlloc_;
		x.myAlloc_ = tmp_s;
		key_compare	tmp_c = this->comp_;
		this->comp_ = x.comp_;
		x.comp_ = tmp_c;
	}

	void clear() { tree_->clear(tree_->root_); tree_->size_ = 0; } //OK

	//Observers: OK, no test for value_compare
	/*************************************************************************/
	key_compare key_comp() const { return key_compare(); }

	value_compare value_comp() const { return value_compare(key_compare()); }

	//Operations:
	/*************************************************************************/
	iterator find (const key_type& k) //OK
	{
		node_type*	tmp = tree_->find(tree_->root_, k);
		return iterator(&(tmp->value), tmp);
	}
	const_iterator find (const key_type& k) const
	{
		node_type*	tmp = tree_->find(tree_->root_, k);
		return const_iterator(&(tmp->value), tmp);
	}

	size_type count (const key_type& k) const //OK
	{
		if (tree_->find(tree_->root_, k) == tree_->quasiEnd_)
			return 0;
		return 1;
	}

	iterator lower_bound (const key_type& k) //OK
	{
		node_type*	tmp = tree_->find(tree_->root_, k);
		if (tmp != tree_->quasiEnd_)
			return iterator(&(tmp->value), tmp);
		iterator	it = begin();
		iterator	last = end();
		while (comp_(it->first, k) && it != last)
			++it;
		return it;
	}
	const_iterator lower_bound (const key_type& k) const
	{
		node_type*	tmp = tree_->find(tree_->root_, k);
		if (tmp != tree_->quasiEnd_)
			return const_iterator(&(tmp->value), tmp);
		const_iterator	it = begin();
		const_iterator	last = end();
		while (comp_(it->first, k) && it != last)
			++it;
		return it;
	}

	iterator upper_bound (const key_type& k) //leaks
	{
		node_type*	tmp = tree_->find(tree_->root_, k);
		if (tmp != tree_->quasiEnd_)
			return iterator(&(tmp->parent->value), tmp);
		iterator	it = begin();
		iterator	last = end();
		while (comp_(it->first, k) && it != last)
			++it;
		return it;
	}
	const_iterator upper_bound (const key_type& k) const
	{
		node_type*	tmp = tree_->find(tree_->root_, k);
		if (tmp != tree_->quasiEnd_)
			return const_iterator(&(tmp->parent->value), tmp);
		const_iterator	it = begin();
		const_iterator	last = end();
		while (comp_(it->first, k) && it != last)
			++it;
		return it;
	}

	pair<iterator,iterator>				equal_range (const key_type& k) //OK
	{
		if (find(k) == end())
			return (ft::make_pair(upper_bound(k), upper_bound(k)));
		return (ft::make_pair(lower_bound(k), upper_bound(k)));
	}
	pair<const_iterator,const_iterator>	equal_range (const key_type& k) const
	{
		if (find(k) == end())
			return (ft::make_pair(upper_bound(k), upper_bound(k)));
		return (ft::make_pair(lower_bound(k), upper_bound(k)));
	}

	//Allocator: //TODO in school
	/*************************************************************************/
	allocator_type get_allocator() const
	{
		allocator_type	tmp = allocator_type();
		return tmp;
	}

	//Non-member function overloads
	/*************************************************************************/
	/* template < class Tx, class Allocatorx >
	friend	std::ostream& operator<<(std::ostream &, const vector<Tx, Allocatorx> &); */
};

/***************************************************************************/
//			END OF CLASS													/
/***************************************************************************/
} //end of namespace ft
namespace std{
template < class Key, class T, class Compare, class Allocator >
void swap (ft::map<Key, T, Compare, Allocator>& x, ft::map<Key, T, Compare, Allocator>& y)
{
	x.swap(y);
}
}
#endif