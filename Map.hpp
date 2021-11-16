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

/* template < class Key, class T>
class Node
{
	public:
	Key		index_;
	T		data_;
	Node*	pleft;
	Node*	pright;
}; */

/*************************************************************************/
//**	CLASS DECLARATION START											**/
/*************************************************************************/
template < class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
class map
{
public:
	typedef	Key											key_type;
	typedef	T											mapped_type;
	typedef	ft::pair<const Key, T>				value_type;
	typedef	Allocator									allocator_type;
	typedef Compare										key_compare;
	typedef typename	allocator_type::reference		reference;
	typedef typename	allocator_type::const_reference	const_reference;
	typedef Tree<Key, T, Compare>*			pointer;
	typedef typename Tree<Key, T, Compare>::Node*		node_;
	//typedef typename	allocator_type::pointer			pointer;
	typedef typename	allocator_type::const_pointer	const_pointer;
	typedef typename	ft::Miterator<node_>			iterator;
	typedef typename	ft::Miterator<const_pointer>	const_iterator;
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

	Tree<Key, T, Compare>*					tree_;
	std::allocator<Tree<Key, T, Compare> >	myAlloc_;
	private:
		key_compare	comp_;

public:
	//constructor: empty (1/3)
	explicit map (const key_compare& comp = key_compare()
					/* const allocator_type& alloc = allocator_type() */)
	 :comp_(comp)
	{
		tree_ = myAlloc_.allocate(1); //аллокатор только аллоцирует память
		myAlloc_.construct(tree_); //констракт вызывает конструктор
		//tree_ = new Tree<Key, T>(); //аллоцирует память и вызывает конструктор типа
	}

	pair<iterator,bool> insert (const value_type& val)
	{
		//node_	tmp;
		tree_->insert(val.first, val.second, comp_);
		return (make_pair(tree_->root_, true));
	}

	iterator	begin()
	{
		node_	tmp = tree_->root_;
		while (tmp->pleft != NULL)
			tmp = tmp->pleft;
		return iterator(tmp);
	}
	iterator	end()
	{
		node_	tmp = tree_->root_;
		while (tmp->pright != NULL)
			tmp = tmp->pright;
		return iterator(tmp);
	}
/* 	    explicit map(const key_compare& __comp, const allocator_type& __a)
        : tree_(__vc(__comp), typename __base::allocator_type(__a)) {} */
	
	//constructor: range(2/3)
	template <class InputIterator>
	map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type());
	//constructor: copy(3/3)
	map (const map& x);
	~map() {}
	// ~vector()
	// {
	// 	myAlloc_.deallocate(array_, capacity_);
	// }

	//insert: single element (1/3)	
/* 	ft::pair<iterator,bool> insert (const value_type& val)
	{
		if (size_ == 0)
		{
			Node<key_type, mapped_type> tmp;
			tmp.index_ = val.first;
			tmp.data_ = val.second;
			tmp.pleft = tmp.pright = NULL;
		}
		else
		{

		}
	} */
	map& operator= (const map& x);
/*	vector&	operator=(const vector& rhs)
	{
		if (this == &rhs)
			return *this;
		if (rhs.size_ > size_) // >capacity_ ???
		{
			capacity_ = rhs.size_ + 3;
			myAlloc_.deallocate(array_, capacity_);
			array_ = myAlloc_.allocate(capacity_);
		}
		for (size_type i = 0; i < rhs.size(); ++i)
			array_[i] = rhs.array_[i];
		size_ = rhs.size_;
		return *this;
	} */
	/*************************************************************************/
	//			MEMBER FUNCTIONS										      /
	/*************************************************************************/

	//iterators
	
	// iterator	end() {  ;}
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
	//Capacity all done
	/*************************************************************************/
	size_type	size() const { return tree_->size_ ; }
	size_type	max_size() const { return (pow(2 , 64) / sizeof(T) - 1); }
	bool		empty() const { return tree_->size_ == 0; }

	//Element access all done
	/*************************************************************************/
	mapped_type& operator[] (const key_type& k);
	// reference	operator[](size_type index)
	// {
	// 	return array_[index];
	// }

	//Modifiers all done
	/*************************************************************************/

	//insert(single element) (1/3)	
	//pair<iterator,bool> insert (const value_type& val)

	//insert(with hint) (2/3)	
	//iterator insert (iterator position, const value_type& val);
	//insert(range) (3/3)	
	//template <class InputIterator>
	//	void insert (InputIterator first, InputIterator last);

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

	void clear()
	{
		tree_->clear();
	}

	//Observers:
	/*************************************************************************/
	key_compare key_comp() const;

	//value_compare value_comp() const;

	//Operations:
	/*************************************************************************/
	iterator find (const key_type& k);
	const_iterator find (const key_type& k) const;

	size_type count (const key_type& k) const;

	iterator lower_bound (const key_type& k);
	const_iterator lower_bound (const key_type& k) const;

	iterator upper_bound (const key_type& k);
	const_iterator upper_bound (const key_type& k) const;

	pair<const_iterator,const_iterator>	equal_range (const key_type& k) const;
	pair<iterator,iterator>				equal_range (const key_type& k);

	//Allocator:
	/*************************************************************************/
	allocator_type get_allocator() const;
	// allocator_type get_allocator() const
	// {
	// 	return myAlloc_;
	// }

	//Non-member function overloads
	/*************************************************************************/
	// friend	bool	operator== <> (const vector & lhs, const vector & rhs);
	// friend	bool	operator!= <> (const vector & lhs, const vector & rhs);
	// friend	bool	operator< <> (vector & lhs, vector & rhs);
	// friend	bool	operator> <> (vector & lhs, vector & rhs);
	// friend	bool	operator>= <> (vector & lhs, vector & rhs);
	// friend	bool	operator<= <> (vector & lhs, vector & rhs);
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