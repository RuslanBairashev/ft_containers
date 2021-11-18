#ifndef TREE_HPP
#define TREE_HPP

#include <cstddef>
#include <unistd.h>
#include <memory>
#include "Miterator.hpp"

struct Node;

template < class Key, class T, class Compare, class Allocator = std::allocator<std::pair<const Key, T> > >
class	Tree
{
public:
	typedef	ft::pair<const Key, T>		value_type;
	typedef	Allocator					allocator_type;
	struct Node
	{
		value_type		value;
		Node*			parent;
		Node*			pleft;
		Node*			pright;
		unsigned char	height;
		Node(value_type val) : value(val), parent(NULL), pleft(NULL), pright(NULL), height(1) {}
		Node&	operator=(const Node& rhs)
		{
			if (this == &rhs)
				return *this;
			this->value = rhs->value;
			this->parent = rhs->parent;
			this->pleft = rhs->pleft;
			this->pright = rhs->pright;
			this->height = rhs->height;
			return *this;
		} 
	};
	Node*		root_;
	unsigned	size_;

	Node*		first_;
	Node*		last_;
	//std::allocator<ft::pair<const Key, T> >	pairAlloc_;
	std::allocator<Node>	nodeAlloc_;
	std::less<Key>			comp_;

	Tree(const std::less<Key>& comp, const allocator_type& alloc)
	: root_(NULL), size_(0), nodeAlloc_(alloc), comp_(comp) {}
	~Tree() {}
	unsigned char	height(Node *p) { return p ? p->height : 0; }
	int				bfactor(Node *p) { return height(p->pright) - height(p->pleft); }
	void			fixheight(Node *p)
	{
		unsigned char hl = height(p->pleft);
		unsigned char hr = height(p->pright);
		p->height = (hl>hr ? hl : hr) + 1;
	}

	Node*			rotateright(Node *p) //right turn around p
	{
		Node*	q = p->pleft;
		p->pleft = q->pright;
		q->pright = p;
		q->parent = NULL;
		p->parent = q;
		fixheight(p);
		fixheight(q);
		return q;
	}

	Node*			rotateleft(Node *q) //left turn around p
	{
		Node*	p = q->pright;
		q->pright = p->pleft;
		p->pleft = q;
		p->parent = NULL;
		q->parent = p;
		fixheight(q);
		fixheight(p);
		return p;
	}
	Node*			balance(Node* p)
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
	bool			isnot_dublicate(Key k, Node* nod)
	{
		if (nod->value.first == k)
			return false;
		if (nod->pleft != NULL)
		{
			if (!isnot_dublicate(k, nod->pleft))
				return false;
		}
		if (nod->pright != NULL)
		{
			if (!isnot_dublicate(k, nod->pright))
				return false;
		}
		return true;
	}

	void			insert(value_type val, Compare comp)
	{
		if (!root_)
		{
			root_ = nodeAlloc_.allocate(1); //аллокатор только аллоцирует память
			nodeAlloc_.construct(root_, Node(val)); //констракт вызывает конструктор
			// root_->value = pairAlloc_.allocate(1); //аллокатор только аллоцирует память
			// pairAlloc_.construct(val); //констракт вызывает конструктор
			size_++;
			root_ = balance(root_); //maybe can del this
			return ;
		}
		if (isnot_dublicate(val.first, root_))
		{
			if (comp(val.first, root_->value.first)) //std::less<Key>
				root_->pleft = insert(root_->pleft, root_, val, comp);
			else
				root_->pright = insert(root_->pright, root_, val, comp);
			size_++;
			root_ = balance(root_);
		}
	}
	Node*			insert(Node *p, Node *parent, value_type val, Compare comp)
	{
		if (!p)
		{
			p = nodeAlloc_.allocate(1); //аллокатор только аллоцирует память
			nodeAlloc_.construct(p, Node(val)); //констракт вызывает конструктор
			// p->value = pairAlloc_.allocate(1); //аллокатор только аллоцирует память
			// pairAlloc_.construct(val); //констракт вызывает конструктор
			p->parent = parent;
			return p;
			// return new Node(k, val);
		}	
		if (comp(val.first,root_->value.first)) //std::less<Key>
			p->pleft = insert(p->pleft, p, val, comp);
		else
			p->pright = insert(p->pright, p, val, comp);
		return balance(p);
	}

	Node*			findmin(Node* p) { return p->pleft ? findmin(p->pleft) : p; }
	Node			*removemin(Node *p)
	{
		if (p->pleft == NULL)
			return p->pright;
		p->pleft = removemin(p->pleft);
		return balance(p);
	}
	void			remove(Key k)
	{
		if (!root_)
			return ;
		if (!isnot_dublicate(k, root_))
		{
			root_ = remove(root_, k);
			size_--;
		}
	}
	Node*			remove(Node* p, Key k)
	{
		if (!p)
			return 0;
		if (k < p->value.first)
			p->pleft = remove(p->pleft, k);
		else if (k > p->value.first)
			p->pright = remove(p->pright, k);
		else
		{
			Node*	q = p->pleft;
			Node*	r = p->pright;
			nodeAlloc_.destroy(p);
			nodeAlloc_.deallocate(p, 1);
			//delete p;
			if (!r)
				return q;
			Node*	min = findmin(r);
			min->pright = removemin(r);
			min->pleft = q;
			return balance(min);
		}
		return balance(p);
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
	void			print_tree(Node* p)
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
	void			clear()
	{
		while (size_ > 0)
		{
			remove(root_->value.first);
		}
	}
};

#endif