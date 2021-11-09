#include <iostream>
#include <string>
#include <map>
#include "Map.hpp"
#include "Vextras.hpp"

int	main()
{
	ft::pair<int, std::string> pair1(2, "Notebook");
	std::cout << pair1.first << ' ' << pair1.second << std::endl;
	Map<int, std::string> myMap;
	myMap.tree_->insert(1, "1.3");
	std::cout << myMap.tree_->root_->index_ << std::endl;
	myMap.tree_->insert(2, "2.3");
	std::cout << myMap.tree_->root_->pright->index_ << std::endl;
	for(int i = 3; i < 1003; i++)
		myMap.tree_->insert(i, "aaa");
	myMap.tree_->remove(1);
	myMap.tree_->remove(3);
	std::cout << "Final: root is: " << myMap.tree_->root_->index_ << ". Size is: " << myMap.tree_->size_ << std::endl;
	std::cout << "height is: " << static_cast<unsigned>(myMap.tree_->root_->height) << std::endl;

	//test.print_tree();
/* 	std::map test1;
	myMap.insert(std::make_pair(1, "phone"));
	myMap.insert(ft::pair<int, std::string>(2, "notebook"));
	std::cout << myMap[1] << std::endl;
	myMap[18] = "TV";
	std::cout << myMap[18] << std::endl; */
	return 0;
}