#include <iostream>
#include <string>
#include <map>
#include "Map.hpp"
#include "Utility.hpp"
#include "Miterator.hpp"
#include "Reviterator.hpp"

int	main()
{
	ft::pair<int, std::string> pair1(2, "Notebook");
	std::cout << pair1.first << ' ' << pair1.second << std::endl;

	ft::map<int, std::string> mymap;
	mymap.insert(ft::make_pair<int, std::string>(1, "1.3"));
	std::cout << mymap.tree_->root_->value.first << std::endl;
	mymap.insert(ft::make_pair<int, std::string>(2, "2.3"));
	std::cout << mymap.tree_->root_->pright->value.first << std::endl;
	for(int i = 3; i < 1003; i++)
		mymap.insert(ft::make_pair<int, std::string>(i, "aaa"));
	mymap.erase(1);
	mymap.erase(0);
	ft::map<int, std::string>::iterator it;
	it  = mymap.begin();
	if (it == NULL) { std::cout << "\"ITERATOR IS NULL!!!\"" << std::endl; }
	std::cout << "it.begin= " << it->first << std::endl;
	it  = mymap.end();
	std::cout << "it.end= " << it->first << std::endl;
	mymap.insert(ft::pair<int, std::string>(1003, "notebook"));
	mymap.insert(ft::make_pair<int, std::string>(100, "notebook"));
	std::cout << "Final: root is: " << mymap.tree_->root_->value.first << ". Size is: " << mymap.tree_->size_ << std::endl;
	std::cout << "height is: " << static_cast<unsigned>(mymap.tree_->root_->height) << std::endl;
	mymap.clear();
	std::cout /* << "Final: root is: " << mymap.tree_->root_->first */ << ". Size is: " << mymap.tree_->size_ << std::endl;
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