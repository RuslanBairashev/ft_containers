#ifndef TREE_HPP
#define TREE_HPP

#include <cstddef>
#include <unistd.h>
#include <memory>
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
	~Node() {}
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

template < class Key, class T, class Compare, class Allocator = std::allocator<ft::pair<const Key, T> > >
class	Tree
{
public:
	typedef	ft::pair<const Key, T>		value_type;
	typedef Compare						key_compare;
	typedef	Allocator					allocator_type;

	Node<const Key, T>*		root_;
	unsigned	size_;
	Node<const Key, T>*		quasiBegin_;
	Node<const Key, T>*		quasiEnd_;
	std::allocator<Node<const Key, T> >	nodeAlloc_;
	key_compare				comp_;

	Tree(const key_compare& comp, const allocator_type& alloc)
	: root_(NULL), size_(0), quasiBegin_(NULL), quasiEnd_(NULL), comp_(comp)
	{
		allocator_type	tmp = alloc;
		(void)tmp;
	}
	~Tree()
	{
		clear(root_);
	}
	Node<const Key, T>*			find_root(Node<const Key, T> *p)
	{
		if (size_ == 0)
			return NULL;
		while (p->parent)
			p = p->parent;
		return p;
	}
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
		return p;
	}

	void			insert(value_type val, Compare comp)
	{
		if (!root_)
		{
			root_ = nodeAlloc_.allocate(1); //?????????????????? ???????????? ???????????????????? ????????????
			nodeAlloc_.construct(root_, Node<const Key, T>(val)); //?????????????????? ???????????????? ??????????????????????
			if (quasiBegin_ == NULL)
			{
				quasiBegin_ = nodeAlloc_.allocate(1);
				nodeAlloc_.construct(quasiBegin_, Node<const Key, T>(val));
			}
			if (quasiEnd_ == NULL)
			{
				quasiEnd_ = nodeAlloc_.allocate(1);
				nodeAlloc_.construct(quasiEnd_, Node<const Key, T>(val));
			}
			root_->pbegin = quasiBegin_;
			root_->pend = quasiEnd_;
			quasiBegin_->pbegin = quasiBegin_;
			quasiBegin_->pend = quasiEnd_;
			quasiEnd_->pbegin = quasiBegin_;
			quasiEnd_->pend = quasiEnd_;
			size_++;
			root_ = balance(root_);
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
			p = nodeAlloc_.allocate(1); //?????????????????? ???????????? ???????????????????? ????????????
			nodeAlloc_.construct(p, Node<const Key, T>(val)); //?????????????????? ???????????????? ??????????????????????
			p->parent = parent;
			p->pbegin = quasiBegin_;
			p->pend = quasiEnd_;
			return p;
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
			else if (comp_(k, p->value.first))
				p = p->pleft;
			else
				p = p->pright;
		}
		return quasiEnd_;
	}
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
			min->pright = removemin(tmp_right);
			min->pleft = tmp_left;
			min->parent = tmp_parent;
			if (tmp_left)
				tmp_left->parent = min;
			p = balance(min);
		}
		else if (comp_(k, p->value.first))
			p->pleft = remove(p->pleft, k);
		else
			p->pright = remove(p->pright, k);
		return balance (p);
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
		if (size_ != 0 && p)
		{
			if (p->pleft)
				clear(p->pleft);
			if (p->pright)
				clear(p->pright);
			nodeAlloc_.destroy(p);
			nodeAlloc_.deallocate(p, 1);
		}
		if (size_ != 0 && p == root_)
		{
			nodeAlloc_.destroy(quasiBegin_);
			nodeAlloc_.deallocate(quasiBegin_, 1);
			nodeAlloc_.destroy(quasiEnd_);
			nodeAlloc_.deallocate(quasiEnd_, 1);
			root_ = quasiBegin_ = quasiEnd_ = NULL;
			size_ = 0;
		}
	}
	void			clear_quasi()
	{
		nodeAlloc_.destroy(quasiBegin_);
		nodeAlloc_.deallocate(quasiBegin_, 1);
		nodeAlloc_.destroy(quasiEnd_);
		nodeAlloc_.deallocate(quasiEnd_, 1);
		nodeAlloc_.destroy(root_);
		nodeAlloc_.deallocate(root_, 1);
		
		root_ = quasiBegin_ = quasiEnd_ = NULL;
	}
};

} //end of namespace ft

#endif