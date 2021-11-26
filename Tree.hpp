#ifndef TREE_HPP
#define TREE_HPP

#include <cstddef>
#include <unistd.h>
#include <memory>
//#include "Miterator.hpp"
#include "Utility.hpp"

namespace ft {

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
	Node*		quasiBegin_;
	Node*		quasiEnd_;
	//std::allocator<ft::pair<const Key, T> >	pairAlloc_;
	std::allocator<Node>	nodeAlloc_;
	std::less<Key>			comp_;

	Tree(const std::less<Key>& comp, const allocator_type& alloc)
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
	unsigned char	height(Node *p) { return p ? p->height : 0; }
	int				bfactor(Node *p) { return height(p->pright) - height(p->pleft); }
	void			fixheight(Node *p)
	{
		unsigned char hl = height(p->pleft);
		unsigned char hr = height(p->pright);
		p->height = (hl>hr ? hl : hr) + 1;
	}

	Node*			rotateright(Node *b) //right turn around p/b
	{
		Node*	a = b->pleft;
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

	Node*			rotateleft(Node *a) //left turn around p
	{
		Node*	b = a->pright;
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
			nodeAlloc_.construct(root_, Node(val)); //констракт вызывает конструктор
			// root_->value = pairAlloc_.allocate(1); //аллокатор только аллоцирует память
			// pairAlloc_.construct(val); //констракт вызывает конструктор
			quasiBegin_ = nodeAlloc_.allocate(1);
			nodeAlloc_.construct(quasiBegin_, Node(val));
			quasiEnd_ = nodeAlloc_.allocate(1);
			nodeAlloc_.construct(quasiEnd_, Node(val));
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
	Node*			findmax(Node* p) { return p->pright ? findmax(p->pright) : p; }
	Node*			find(Node * p, Key k)
	{
		while (p)
		{
			if (p->value.first == k)
				return p;
			else if (k < p->value.first)
				p = p->pleft;
			else
				p = p->pright;
		}
		return quasiEnd_;
	}
	Node*			removemin(Node *p)
	{
		if (p->pleft == NULL)
			return p->pright;
		p->pleft = removemin(p->pleft);
		return balance(p);
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
			Node*	tmp_parent = p->parent;
			Node*	tmp_left = p->pleft;
			Node*	tmp_right = p->pright;
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
			Node*	min = findmin(tmp_right);
			min->pright = removemin(tmp_right);//3
			min->pleft = tmp_left;//1
			min->parent = tmp_parent;//2
			if (tmp_left)
				tmp_left->parent = min;
			// if (min->pright->parent != min)
			// 	tmp_right->parent = min;
			p = balance(min);
		}
		return balance (p);
	}
	int			remove(Key k)
	{
		Node*	tmp;
		if (!root_)
			return 0;
		tmp = find(root_, k);
		if (tmp  == quasiEnd_)
			return 0;
		remove(tmp);
		size_--;
		return 1;
	}
	void			remove(Node* p)
	{
		Node*	tmp_parent = p->parent;
		Node*	tmp_left = p->pleft;
		Node*	tmp_right = p->pright;

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
			Node*	min = findmin(tmp_right);
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
	void			clear(Node *p)
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