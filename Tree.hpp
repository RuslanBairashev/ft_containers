#ifndef TREE_HPP
#define TREE_HPP

#include <cstddef>
#include <unistd.h>
#include <memory>
//#include "Miterator.hpp"
#include "Utility.hpp"

namespace ft {

template < class Key, class T>
struct Node
{
	typedef	ft::pair<const Key, T>		value_type;
	value_type		value;
	Node*			parent;
	Node*			pleft;
	Node*			pright;
	Node*			pbegin;
	Node*			pend;
	unsigned char	height;
	Node(value_type val)
	 : value(val), parent(NULL), pleft(NULL), pright(NULL), pbegin(NULL), pend(NULL), height(1) {}
	Node&	operator=(const Node& rhs)
	{
		if (this == &rhs)
			return *this;
		this->value = rhs->value;
		this->parent = rhs->parent;
		this->pleft = rhs->pleft;
		this->pright = rhs->pright;
		this->pbegin = rhs->pbegin;
		this->pend = rhs->pend;
		this->height = rhs->height;
		return *this;
	} 
};

template < class Key, class T, class Compare, class Allocator = std::allocator<std::pair<const Key, T> > >
class	Tree
{
public:
	typedef	ft::pair<const Key, T>		value_type;
	typedef Compare						key_compare;
	typedef	Allocator					allocator_type;
	// struct Node
	// {
	// 	value_type		value;
	// 	Node*			parent;
	// 	Node*			pleft;
	// 	Node*			pright;
	// 	unsigned char	height;
	// 	Node(value_type val) : value(val), parent(NULL), pleft(NULL), pright(NULL), height(1) {}
	// 	Node&	operator=(const Node& rhs)
	// 	{
	// 		if (this == &rhs)
	// 			return *this;
	// 		this->value = rhs->value;
	// 		this->parent = rhs->parent;
	// 		this->pleft = rhs->pleft;
	// 		this->pright = rhs->pright;
	// 		this->height = rhs->height;
	// 		return *this;
	// 	} 
	// };
	Node<const Key, T>*		root_;
	unsigned	size_;
	Node<const Key, T>*		quasiBegin_;
	Node<const Key, T>*		quasiEnd_;
	//std::allocator<ft::pair<const Key, T> >	pairAlloc_;
	std::allocator<Node<const Key, T> >	nodeAlloc_;
	key_compare				comp_;

	Tree(const key_compare& comp, const allocator_type& alloc)
	: root_(NULL), size_(0), quasiBegin_(NULL), quasiEnd_(NULL), nodeAlloc_(alloc), comp_(comp)
	{
		// quasiBegin_ = nodeAlloc_.allocate(1);
		// nodeAlloc_.construct(quasiBegin_, Node());
		// quasiEnd_ = nodeAlloc_.allocate(1);
		// nodeAlloc_.construct(quasiEnd_, Node());
	}
	~Tree()
	{
		// nodeAlloc_.destroy(root_); //sega
		// nodeAlloc_.deallocate(root_, 1);
		// nodeAlloc_.destroy(quasiBegin_);
		// nodeAlloc_.deallocate(quasiBegin_, 1);
		// nodeAlloc_.destroy(quasiEnd_);
		// nodeAlloc_.deallocate(quasiEnd_, 1);
	}
	Node<const Key, T>*			find_root(Node<const Key, T> *p)
	{
		if (size_ == 0)
			return NULL;
		while (p->parent)
			p = p->parent;
		return p;
	}
	// Node<const Key, T>*			lower_bound(Key k)
	// {
	// 	Node<const Key, T>*	tmp = findmin(root_);
	// 	while (k < tmp->value.first && tmp != quasiEnd_)

	// }
	unsigned char	height(Node<const Key, T> *p) { return p ? p->height : 0; }
	int				bfactor(Node<const Key, T> *p) { return height(p->pright) - height(p->pleft); }
	void			fixheight(Node<const Key, T> *p)
	{
		unsigned char hl = height(p->pleft);
		unsigned char hr = height(p->pright);
		p->height = (hl>hr ? hl : hr) + 1;
	}

	Node<const Key, T>*			rotateright(Node<const Key, T> *b) //right turn around p/b
	{
		Node<const Key, T>*	a = b->pleft;
		b->pleft = a->pright;
		a->pright = b;
		a->parent = b->parent;
		b->parent = a;
		if (b->pleft)
			b->pleft->parent = b;
		fixheight(b);
		fixheight(a);
		// Node * tmp = findmax(root_);
		// tmp->pright = quasiEnd_;
		// quasiEnd_->parent = tmp;
		return a;
	}

	Node<const Key, T>*			rotateleft(Node<const Key, T> *a) //left turn around p
	{
		Node<const Key, T>*	b = a->pright;
		a->pright = b->pleft;
		b->pleft = a;
		b->parent = a->parent;
		a->parent = b;
		if (a->pright)
			a->pright->parent = a;
		fixheight(a);
		fixheight(b);
		// Node * tmp = findmax(root_);
		// tmp->pright = quasiEnd_;
		// quasiEnd_->parent = tmp;
		return b;
	}

	Node<const Key, T>*			balance(Node<const Key, T>* p)
	{
		fixheight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->pright) < 0)
				p->pright = rotateright(p->pright);
			return rotateleft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->pleft) > 0)
				p->pleft = rotateleft(p->pleft);
			return rotateright(p);
		}
		// Node * tmp = findmax(root_);
		// tmp->pright = quasiEnd_;
		// quasiEnd_->parent = tmp;
		return p;
	}

	void			insert(value_type val, Compare comp)
	{
		if (!root_)
		{
			root_ = nodeAlloc_.allocate(1); //аллокатор только аллоцирует память
			nodeAlloc_.construct(root_, Node<const Key, T>(val)); //констракт вызывает конструктор
			// root_->value = pairAlloc_.allocate(1); //аллокатор только аллоцирует память
			// pairAlloc_.construct(val); //констракт вызывает конструктор
			quasiBegin_ = nodeAlloc_.allocate(1);
			nodeAlloc_.construct(quasiBegin_, Node<const Key, T>(val));
			quasiEnd_ = nodeAlloc_.allocate(1);
			nodeAlloc_.construct(quasiEnd_, Node<const Key, T>(val));
			root_->pbegin = quasiBegin_;
			root_->pend = quasiEnd_;
			quasiBegin_->pbegin = quasiBegin_;
			quasiBegin_->pend = quasiEnd_;
			quasiEnd_->pbegin = quasiBegin_;
			quasiEnd_->pend = quasiEnd_;
			size_++;
			root_ = balance(root_); //maybe can del this
			return ;
		}
		if (find(root_, val.first) == quasiEnd_)
		{
			if (comp(val.first, root_->value.first)) //std::less<Key>
				root_->pleft = insert(root_->pleft, root_, val, comp);
			else
				root_->pright = insert(root_->pright, root_, val, comp);
			size_++;
			root_ = balance(root_);
		}
	}
	Node<const Key, T>*			insert(Node<const Key, T> *p, Node<const Key, T> *parent, value_type val, Compare comp)
	{
		if (!p)
		{
			p = nodeAlloc_.allocate(1); //аллокатор только аллоцирует память
			nodeAlloc_.construct(p, Node<const Key, T>(val)); //констракт вызывает конструктор
			// p->value = pairAlloc_.allocate(1); //аллокатор только аллоцирует память
			// pairAlloc_.construct(val); //констракт вызывает конструктор
			p->parent = parent;
			p->pbegin = quasiBegin_;
			p->pend = quasiEnd_;
			return p;
			// return new Node(k, val);
		}	
		if (comp(val.first,p->value.first)) //std::less<Key>
			p->pleft = insert(p->pleft, p, val, comp);
		else
			p->pright = insert(p->pright, p, val, comp);
		return balance(p);
	}

	Node<const Key, T>*			findmin(Node<const Key, T>* p) { return p->pleft ? findmin(p->pleft) : p; }
	Node<const Key, T>*			findmax(Node<const Key, T>* p) { return p->pright ? findmax(p->pright) : p; }
	Node<const Key, T>*			find(Node<const Key, T> * p, Key k)
	{
		while (p)
		{
			if (p->value.first == k)
				return p;
			//else if (k < p->value.first)//comp?
			else if (comp_(k, p->value.first))
				p = p->pleft;
			else
				p = p->pright;
		}
		return quasiEnd_;
	}
	// Node<const Key, T>*			closest_max(Node<const Key, T> * p, Key k)
	// {
	// 	while (p)
	// 	{
	// 		while (k > p->value.first && p != quasiEnd_)

	// 	}
	// 	return quasiEnd_;
	// }
	Node<const Key, T>*			removemin(Node<const Key, T> *p)
	{
		if (p->pleft == NULL)
			return p->pright;
		p->pleft = removemin(p->pleft);
		return balance(p);
	}
	Node<const Key, T>*			remove(Node<const Key, T>* p, Key k)
	{
		if (!p)
			return 0;
		if (k == p->value.first)
		{
			Node<const Key, T>*	tmp_parent = p->parent;
			Node<const Key, T>*	tmp_left = p->pleft;
			Node<const Key, T>*	tmp_right = p->pright;
			//delete p;
			nodeAlloc_.destroy(p);
			nodeAlloc_.deallocate(p, 1);
			--size_;
			if (!tmp_right)
			{
				if (tmp_left)
					tmp_left->parent = tmp_parent;
				return tmp_left;
			}
			Node<const Key, T>*	min = findmin(tmp_right);
			min->pright = removemin(tmp_right);//3
			min->pleft = tmp_left;//1
			min->parent = tmp_parent;//2
			if (tmp_left)
				tmp_left->parent = min;
			// if (min->pright->parent != min)
			// 	tmp_right->parent = min;
			p = balance(min);
		}
		else if (comp_(k, p->value.first)) // (k < p->value.first)
			p->pleft = remove(p->pleft, k);
		else  //(k > p->value.first)
			p->pright = remove(p->pright, k);
		return balance (p);
	}
	int			remove(Key k)
	{
		Node<const Key, T>*	tmp;
		if (!root_)
			return 0;
		tmp = find(root_, k);
		if (tmp  == quasiEnd_)
			return 0;
		remove(tmp);
		size_--;
		return 1;
	}
	void			remove(Node<const Key, T>* p)
	{
		Node<const Key, T>*	tmp_parent = p->parent;
		Node<const Key, T>*	tmp_left = p->pleft;
		Node<const Key, T>*	tmp_right = p->pright;

		if (!tmp_right)
		{
			if (tmp_parent->pleft == p) //left branch
				tmp_parent->pleft = tmp_left;
			else
				tmp_parent->pright = tmp_left;
			if (tmp_left)
				tmp_left->parent = tmp_parent;
		}
		else
		{
			Node<const Key, T>*	min = findmin(tmp_right);
			min->pright = removemin(tmp_right);
			min->pleft = tmp_left;
			min->parent = tmp_parent;
			tmp_left->parent = min;
			if (tmp_parent)
			{
				if (tmp_parent->pleft == p) //left branch
					tmp_parent->pleft = min;
				else
					tmp_parent->pright = min;
			}
			balance(min);
		}
		nodeAlloc_.destroy(p);
		nodeAlloc_.deallocate(p, 1);
		balance(root_);
	}
	void			print_tree()
	{
		if (root_ && size_ < 10000)
		{
			std::cout << &root_ << "=" << "root_->first=" << root_->value->first << std::endl;
			if (root_->pleft)
				print_tree(root_->pleft);
			if (root_->pright)
				print_tree(root_->pright);
		}
		else
			std::cout << "root_ IS NULL" << std::endl;
	}
	void			print_tree(Node<const Key, T>* p)
	{
		if (p)
		{
			std::cout << &p << "=" << p->value->first << std::endl;
			if (p->pleft)
				print_tree(p->pleft);
			if (p->pright)
				print_tree(p->pright);
		}
	}
	void			clear(Node<const Key, T> *p)
	{
		if (p)
		{
			if (p->pleft)
				clear(p->pleft);
			if (p->pright)
				clear(p->pright);
			nodeAlloc_.destroy(p);
			nodeAlloc_.deallocate(p, 1);
		}
	}
	// 	void			clear()
	// {
	// 	while (size_ > 0)
	// 	{
	// 		remove(root_->value.first);
	// 	}
	// 	root_ = NULL;
	// }

};

} //end of namespace ft

#endif