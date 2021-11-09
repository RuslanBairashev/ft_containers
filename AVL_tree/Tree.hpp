#ifndef TREE_HPP
#define TREE_HPP

#include <cstddef>
#include <unistd.h>

template < class Key, class T>
class	Tree
{
public:
	struct Node
	{
		Key		index_;
		T		data_;
		Node*	pleft;
		Node*	pright;
		unsigned char	height;
		Node(Key k, T val) { index_ = k; data_ = val; pleft = NULL; pright = NULL; height = 1; }
	};
	Node*		root_;
	unsigned	size_;

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
	void			insert(Key k, T val)
	{
		size_++;
		if (!root_)
		{
			root_ = new Node(k, val);
			root_ = balance(root_);
			return ;
		}
		if (k < root_->index_)
			root_->pleft = insert(root_->pleft, k, val);
		else
			root_->pright = insert(root_->pright, k, val);
		root_ = balance(root_);
	}
	Node*			insert(Node *p, Key k, T val)
	{
		if (!p)
			return new Node(k, val);
		if (k < p->index_)
			p->pleft = insert(p->pleft, k, val);
		else
			p->pright = insert(p->pright, k, val);
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
		root_ = remove(root_, k);
		size_--;
	}
	Node*			remove(Node* p, Key k)
	{
		if (!p)
			return 0;
		if (k < p->index_)
			p->pleft = remove(p->pleft, k);
		else if (k > p->index_)
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
			std::cout << &root_ << "=" << "root_->index_=" << root_->index_ << std::endl;
			if (root_->pleft)
				print_tree(root_->pleft);
			if (root_->pright)
				print_tree(root_->pright);
		}
	}
	void			print_tree(Node* p)
	{
		if (p)
		{
			std::cout << &p << "=" << p->index_ << std::endl;
			if (p->pleft)
				print_tree(p->pleft);
			if (p->pright)
				print_tree(p->pright);
		}
	}
};

#endif