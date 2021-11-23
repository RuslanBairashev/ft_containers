#include <iostream>
#include <string>
#include <map>
#include "Map.hpp"
#include "Utility.hpp"
#include "Miterator.hpp"
#include "Reviterator.hpp"

void	show_node(ft::Tree<int, std::string, std::less<int>, std::allocator<std::pair<const int, std::string> > >::Node * node, unsigned level)
{
	if (node != NULL)
	{
		std::cout << "LEVEL:" << level << ' ' << node->value.first ;
		std::cout << " Node: " << node ;
		std::cout << " Parent: " << node->parent ;
		std::cout << std::endl;
	}
	if (node->pleft)
		show_node(node->pleft, level + 1);
	if (node->pright)
		show_node(node->pright, level + 1);

}
void	show_tree(ft::map<int, std::string> & mymap)
{
	unsigned	level = 0;
	// unsigned height = static_cast<unsigned>(mymap.tree_->root_->height);
	ft::Tree<int, std::string, std::less<int>, std::allocator<std::pair<const int, std::string> > >::Node * tmp;
	std::cout << "___START SHOW TREE___" << std::endl;
	tmp = mymap.tree_->root_;
	//for (; level < height; ++level)
	show_node(tmp, level);
	std::cout << "___FINISH SHOW TREE___" << std::endl;
}

void	map_info(ft::map<int, std::string> & mymap)
{
	std::cout << "Final: root is: " << mymap.tree_->root_->value.first << ". Size is: " << mymap.tree_->size_;
	std::cout << ". Height is: " << static_cast<unsigned>(mymap.tree_->root_->height) << std::endl;
}

int	main()
{
	ft::pair<int, std::string> pair1(2, "Notebook");
	std::cout << pair1.first << ' ' << pair1.second << std::endl;

	ft::map<int, std::string> mymap;
	mymap.insert(ft::make_pair<int, std::string>(1, "1.3"));
	//std::cout << mymap.tree_->root_->value.first << std::endl;
	mymap.insert(ft::make_pair<int, std::string>(2, "2.3"));
	//std::cout << mymap.tree_->root_->pright->value.first << std::endl;
	for(int i = 3; i < 11; i++)
		mymap.insert(ft::make_pair<int, std::string>(i, "aaa"));
	// mymap.erase(100);
	// mymap.erase(0);
	//show_tree(mymap);
	//std::cout << "        tree address= " << mymap.tree_ << std::endl;
	ft::map<int, std::string>::iterator it;
	it  = mymap.begin();
	if (it == NULL) { std::cout << "\"ITERATOR IS NULL!!!\"" << std::endl; }
	std::cout << "before ++ it.begin= " << it->first << std::endl;
	for(int plus = 0; plus < 5; ++plus)
		++it;
	it++;
	for(int minus = 0; minus < 5; ++minus)
		--it;
	it--;
	std::cout << "after ++ it.begin= " << it->first << std::endl;
	// ft::pair<const int, std::string> &	for_adr = *it;
	// std::cout << "it.begin address= " << &for_adr << std::endl;
	// std::cout << "mymap address= " << &mymap << std::endl;
	ft::map<int, std::string>::iterator it_tmp;
	it_tmp = it;
	for(int plus = 0; plus < 5; ++plus)
		++it_tmp;
	ft::map<int, std::string> newmap(it, it_tmp);

	it  = mymap.end();
	std::cout << "it.end= " << it->first << std::endl;
	// mymap.insert(ft::pair<int, std::string>(1003, "notebook"));
	// mymap.insert(ft::make_pair<int, std::string>(100, "notebook"));
	map_info(mymap);
	map_info(newmap);
	ft::map<int, std::string> copymap;
	copymap = newmap;

	//mymap.clear();
	std::cout /* << "Final: root is: " << mymap.tree_->root_->first */ << ". Size is: " << mymap.tree_->size_ << std::endl;
	ft::map<int, std::string> mp2(mymap.begin(), mymap.end());
	// std::cout << mymap.tree_->root_->first << mymap.tree_->root_->second << std::endl;
	//test.print_tree();
/*  	std::map test1;
	mymap.insert(std::make_pair(1, "phone"));
	mymap.insert(ft::pair<int, std::string>(2, "notebook"));
	std::cout << mymap[1] << std::endl;
	mymap[18] = "TV";
	std::cout << mymap[18] << std::endl;  */
	return 0;
}