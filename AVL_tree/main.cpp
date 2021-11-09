#include <iostream>
#include "Tree.hpp"

int	main()
{
	Tree<int, double> test;

	test.insert(1, 1.3);
	std::cout << test.root_->index_ << std::endl;
	test.insert(2, 2.3);
	std::cout << test.root_->pright->index_ << std::endl;
	for(int i = 3; i < 10; i++)
		test.insert(i, i + 0.3);
	test.remove(1);
	test.remove(3);
	std::cout << "Final: root is: " << test.root_->index_ << ". Size is: " << test.size_ << std::endl;
	std::cout << "height is: " << static_cast<unsigned>(test.root_->height) << std::endl;
	//test.print_tree();

	return 0;
}