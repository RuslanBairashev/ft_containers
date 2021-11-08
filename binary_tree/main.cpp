#include <iostream>

struct Node
{
	int		x;
	Node	*l,*r;
};

void	show(Node *&tree)
{
	if (tree != NULL)
	{
		show(tree->l);
		std::cout << tree->x;
		show(tree->r);
	}
}

void	del(Node *&tree)
{
	if (tree != NULL)
	{
		del(tree->l);
		del(tree->r);
		delete tree;
		tree = NULL;
	}
}

void	add_node(int x, Node *&myTree)
{
	if  (NULL == myTree)
	{
		myTree = new Node;
		myTree->x = x;
		myTree->l = myTree->r = NULL;
	}
	if (x < myTree->x)
	{
		if (myTree->l != NULL)
			add_node(x, myTree->l);
		else
		{
			myTree->l = new Node;
			myTree->l->x = x;
			myTree->l->l = myTree->l->r = NULL;
		}
	}
	if (x > myTree->x)
	{
		if (myTree->r != NULL)
			add_node(x, myTree->r);
		else
		{
			myTree->r = new Node;
			myTree->r->x = x;
			myTree->r->l = myTree->r->r = NULL;
		}
	}
}

int	main()
{
	Node	*tree = NULL;

	for (int i = 5; i > 0; i--)
		add_node(i, tree);
	show(tree);
	del(tree);

	return 0;
}
