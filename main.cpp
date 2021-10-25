#include <iostream>
#include "Vector.hpp"

int	main()
{
	std::cout << "Vector with ints:" << std::endl;
	Vector<int>	v;
	for (int i = 1; i < 10; ++i)
		v.push_back(i);
	std::cout << "v contains: " << v ;
	std::cout << ". size_ = " << v.size() << ". capacity_ = " << v.capacity() << std::endl;

	std::cout << "Capacity_tests__________" << std::endl;
	std::cout << "size check: " << v.size() << std::endl;
	std::cout << "max_size check: " << v.max_size() << std::endl;
	v.resize(12);
	std::cout << "resize check: "  << v.size() << ' ' << v.capacity() << std::endl;
	std::cout << "capacity check: " << v.capacity() << std::endl;
	std::cout << "empty check: " << v.empty() << std::endl;
	v.reserve(15);
	std::cout << "reserve check: " << v.capacity() << std::endl;

	std::cout << std::endl << "v contains: " << v << std::endl;
	std::cout << "Element_access_tests____" << std::endl;
	std::cout << "operator[] check: " << v[2] << std::endl;
	std::cout << "at check: " << v.at(3) << std::endl;
	std::cout << "front check: " << v.front() << std::endl;
	std::cout << "back check: " << v.back() << std::endl;
	

	return 0;
}