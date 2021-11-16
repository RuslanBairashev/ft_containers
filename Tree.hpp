#ifndef TREE_HPP
#define TREE_HPP

#include <cstddef>
#include <unistd.h>
#include "Miterator.hpp"

template < class Key, class T, class Compare>
class	Tree
{
public:
	struct Node
	{
		Key		first;
		T		second;
		Node*	pleft;
		Node*	pright;
		unsigned char	height;
		Node(Key k, T val) : first(k), second(val), pleft(NULL), pright(NULL), height(1) {}
	};
	Node*		root_;
	unsigned	size_;
	Node*		first_;
	Node*		last_;

	Tree() : root_(NULL), size_(0) {}
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
		fixheight(p);
		fixheight(q);
		return q;
	}

	Node*			rotateleft(Node *q) //left turn around p
	{
		Node*	p = q->pright;
		q->pright = p->pleft;
		p->pleft = q;
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
		if (nod->first == k)
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

	void			insert(Key k, T val, Compare comp)
	{
		if (!root_)
		{
			root_ = new Node(k, val);
			size_++;
			root_ = balance(root_);
			return ;
		}
		if (isnot_dublicate(k, root_))
		{
			if (comp(k,root_->first)) //std::less<Key>
				root_->pleft = insert(root_->pleft, k, val, comp);
			else
				root_->pright = insert(root_->pright, k, val, comp);
			size_++;
			root_ = balance(root_);
		}
	}
	Node*			insert(Node *p, Key k, T val, Compare comp)
	{
		if (!p)
			return new Node(k, val);
		if (comp(k,root_->first)) //std::less<Key>
			p->pleft = insert(p->pleft, k, val, comp);
		else
			p->pright = insert(p->pright, k, val, comp);
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
		if (k < p->first)
			p->pleft = remove(p->pleft, k);
		else if (k > p->first)
			p->pright = remove(p->pright, k);
		else
		{
			Node*	q = p->pleft;
			Node*	r = p->pright;
			delete p;
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
			std::cout << &root_ << "=" << "root_->first=" << root_->first << std::endl;
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
			std::cout << &p << "=" << p->first << std::endl;
			if (p->pleft)
				print_tree(p->pleft);
			if (p->pright)
				print_tree(p->pright);
		}
	}
	void			clear()
	{
		Node*	tmp;
		while (size_ > 1)
		{
			tmp = findmin(root_);
			remove(tmp->first);
		}
		delete root_;
	}
};

#endif