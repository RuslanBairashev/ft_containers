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
#include "Reviterator.hpp"
#include "Utility.hpp"
#include "Tree.hpp"

namespace ft
{

/* template < class T, class Allocator >
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
} */

/*************************************************************************/
//**	CLASS DECLARATION START											**/
/*************************************************************************/
template < class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<pair<const Key, T> > >
class map
{
public:
	typedef	Key											key_type;
	typedef	T											mapped_type;
	typedef	ft::pair<const Key, T>						value_type;
	typedef	Allocator									allocator_type;
	typedef Compare										key_compare;
	typedef Tree<Key, T, Compare>						tree_type;
	typedef typename	Tree<Key, T, Compare>::Node		node_type;
	typedef typename	allocator_type::reference		reference;
	typedef typename	allocator_type::const_reference	const_reference;
	typedef typename	allocator_type::pointer			pointer;
	typedef typename	allocator_type::const_pointer	const_pointer;
	typedef typename	ft::Miterator<pointer, node_type*, tree_type*>			iterator;
	typedef typename	ft::Miterator<const_pointer, node_type*, tree_type*>	const_iterator;
	typedef typename	ft::Reviterator<pointer>		reverse_iterator;
	typedef typename	ft::Reviterator<const_pointer>	const_reverse_iterator;
	typedef	size_t										size_type;
	typedef	ptrdiff_t									difference_type;

/* 	class	value_compare: public std::binary_function<value_type, value_type, bool>
	{
		friend class map;
	protected:
		key_compare comp;
		value_compare(key_compare c) : comp(c) {}
	public:
		bool operator()(const value_type& x, const value_type& y) const
			{return comp(x.first, y.first);}
	}; */

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
		for(unsigned i = 0 ; first != last ; ++i, ++first)
			tree_->insert(*first, comp_);
	}
	//constructor: copy(3/3)
	// map (const map& x)
	// {
	// 	tree_ = myAlloc_.allocate(1);
	// 	myAlloc_.construct(tree_,Tree<Key, T, Compare>(comp, alloc));
	// 	iterator	first = x.begin();
	// 	iterator	last = x.end();
	// 	for(unsigned i = 0 ; first->first != last->first ; ++i, ++first)
	// 		tree_->insert(*first, comp_);
	// }
	~map()
	{
		myAlloc_.destroy(tree_);
		myAlloc_.deallocate(tree_, 1);
	}
	map& operator= (const map& rhs)
	{
		if (this == &rhs)
			return *this;
		clear();
		return *this;
	} 

	iterator	begin()
	{
		node_type*	tmp = tree_->root_;
		while (tmp->pleft != NULL)
			tmp = tmp->pleft;
		// if (tmp == NULL) { std::cout << "\"tmp ITERATOR IS NULL!!!\"" << std::endl; }
		// std::cout << tmp << std::endl;
		// std::cout << &(tmp->value) << std::endl;
		return iterator(&(tmp->value), tmp, tree_); //pointer,Node*,Tree*
	}
	iterator	end()
	{
		node_type*	tmp = tree_->root_;
		while (tmp->pright != NULL)
			tmp = tmp->pright;
		return iterator(&(tmp->value), tmp, tree_);
	}




	/*************************************************************************/
	//			MEMBER FUNCTIONS										      /
	/*************************************************************************/

	//iterators
	
	// const_iterator	begin() const { ; }
	// const_iterator	end() const { ;}
	// reverse_iterator	rbegin() { ; }
	// reverse_iterator	rend() {  ;}
	// const_reverse_iterator	rbegin() const { ; }
	// const_reverse_iterator	rend() const { ;}
/* 	iterator	begin() { return iterator(array_); }
	iterator	end() { return iterator(array_ + size_); }
	const_iterator	begin() const { return const_iterator(array_); }
	const_iterator	end() const { return const_iterator(array_ + size_); }
	reverse_iterator	rbegin() { return reverse_iterator(array_ + size_); }
	reverse_iterator	rend() { return reverse_iterator(array_); }
	const_reverse_iterator	rbegin() const { return const_reverse_iterator(array_); }
	const_reverse_iterator	rend() const { return const_reverse_iterator(array_ + size_); }
 */
	//Capacity
	/*************************************************************************/
	size_type	size() const { return tree_->size_ ; }
	size_type	max_size() const { return (pow(2 , 64) / sizeof(T) - 1); }
	bool		empty() const { return tree_->size_ == 0; }

	//Element access
	/*************************************************************************/
	mapped_type& operator[] (const key_type& k); // depends on find
	// reference	operator[](size_type index)
	// {
	// 	return array_[index];
	// }

	//Modifiers
	/*************************************************************************/
	//insert: single element (1/3)	
	pair<iterator,bool> insert (const value_type& val)
	{
		tree_->insert(val, comp_);
		return (ft::make_pair(&(tree_->root_->value), true));
	}

	//insert(with hint) (2/3)	
	//iterator insert (iterator position, const value_type& val);
	//insert(range) (3/3)	
	// template <class InputIterator>
	// void insert (InputIterator first, InputIterator last)
	// {

	// }

	//erase (1/3)	
	void erase (iterator position);
	//erase (2/3)	
	size_type erase (const key_type& k) { tree_->remove(k); return 1;}
	//erase (3/3)	
	void erase (iterator first, iterator last);

	// void swap (map& x);
	// {
	// 	pointer		tmp = this->array_;
	// 	this->array_ = x.array_;
	// 	x.array_ = tmp;
	// 	size_type	tmp_s = this->size_;
	// 	this->size_ = x.size_;
	// 	x.size_ = tmp_s;
	// 	size_type	tmp_c = this->capacity_;
	// 	this->capacity_ = x.capacity_;
	// 	x.capacity_ = tmp_c;
	// }

	void clear() { tree_->clear(); }

	//Observers:
	/*************************************************************************/
	key_compare key_comp() const { return comp_; }

	//value_compare value_comp() const;

	//Operations:
	/*************************************************************************/
	iterator find (const key_type& k)
	{
		node_type*	tmp = tree_->find(tree_->root_, k);
		return iterator(&(tmp->value), tmp, tree_);
	}
	const_iterator find (const key_type& k) const;

	size_type count (const key_type& k) const
	{
		if (tree_->isnot_dublicate(k, tree_->root_))
			return 0;
		return 1;
	}

	iterator lower_bound (const key_type& k);
	const_iterator lower_bound (const key_type& k) const;

	iterator upper_bound (const key_type& k);
	const_iterator upper_bound (const key_type& k) const;

	pair<const_iterator,const_iterator>	equal_range (const key_type& k) const;
	pair<iterator,iterator>				equal_range (const key_type& k);

	//Allocator:
	/*************************************************************************/
	allocator_type get_allocator() const
	{
		return tree_->nodeAlloc_;
	}

	//Non-member function overloads
	/*************************************************************************/
	// friend	bool	operator== <> (const map & lhs, const map & rhs);
	// friend	bool	operator!= <> (const map & lhs, const map & rhs);
	// friend	bool	operator< <> (map & lhs, map & rhs);
	// friend	bool	operator> <> (map & lhs, map & rhs);
	// friend	bool	operator>= <> (map & lhs, map & rhs);
	// friend	bool	operator<= <> (map & lhs, map & rhs);
	//Non-member function overloads
	/*************************************************************************/
	/* template < class Tx, class Allocatorx >
	friend	std::ostream& operator<<(std::ostream &, const vector<Tx, Allocatorx> &); */
};

/***************************************************************************/
//			END OF CLASS													/
/***************************************************************************/

/* template < class T, class Allocator >
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
template < class T, class Allocator >
void swap (vector<T, Allocator> & x) { x.swap(x); } */
}
#endif