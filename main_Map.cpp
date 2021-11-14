#include <iostream>
#include <string>
#include <map>
#include "Map.hpp"
#include "Vextras.hpp"
#include "Viterator.hpp"
#include "Reviterator.hpp"

int	main()
{
	ft::pair<int, std::string> pair1(2, "Notebook");
	std::cout << pair1.first << ' ' << pair1.second << std::endl;
	ft::map<int, std::string> mymap;
	mymap.tree_->insert(1, "1.3");
	std::cout << mymap.tree_->root_->index_ << std::endl;
	mymap.tree_->insert(2, "2.3");
	std::cout << mymap.tree_->root_->pright->index_ << std::endl;
	for(int i = 3; i < 1003; i++)
		mymap.tree_->insert(i, "aaa");
	mymap.tree_->remove(1);
	mymap.tree_->remove(3);
	mymap.insert(std::pair<int, std::string>(1003, "notebook"));
	std::cout << "Final: root is: " << mymap.tree_->root_->index_ << ". Size is: " << mymap.tree_->size_ << std::endl;
	std::cout << "height is: " << static_cast<unsigned>(mymap.tree_->root_->height) << std::endl;

	//test.print_tree();
/* 	std::map test1;
	mymap.insert(std::make_pair(1, "phone"));
	mymap.insert(ft::pair<int, std::string>(2, "notebook"));
	std::cout << mymap[1] << std::endl;
	mymap[18] = "TV";
	std::cout << mymap[18] << std::endl; */
	return 0;
}