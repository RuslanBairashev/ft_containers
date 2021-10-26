#include <iostream>
#include "Vector.hpp"
#include <vector>

int	main()
{
	std::cout << "Vector with ints:" << std::endl;
	Vector<int>	v;
	for (int i = 1; i < 10; ++i)
		v.push_back(i);
	std::cout << "v contains: " << v ;
	std::cout << ". size_ = " << v.size() << ". capacity_ = " << v.capacity() << std::endl;

	std::cout << std::endl << "Iterators_tests_________" << std::endl;
	std::cout << "begin check: " << *(v.begin()) << std::endl;
	std::cout << "end check: " << *(v.end()) << std::endl;
	std::cout << std::endl << "Iterator_class_tests_________" << std::endl;
	Vector<int>::Iterator<int> it = v.begin();
	std::cout << "*a check: " << *it << std::endl;
	*it = 42;
	std::cout << "*a= check: " << *it << std::endl;
	std::cout << "++a check: " << *(it++) << std::endl;
	std::cout << "a++ check: " << *(++it) << std::endl;
	std::cout << "a+ check: " << *(it + 2) << std::endl;
	std::cout << "a- check: " << *(it - 1) << std::endl;
	std::cout << "a+= check: " << *(it+=2) << std::endl;
	std::cout << "a-= check: " << *(it-=1) << std::endl;
	Vector<int>::Iterator<int> it2 = it + 3;
	std::cout << "Current positions: " << "*it= " << *it << " *it2= " << *it2 << std::endl;
	std::cout << "a<b check: " << (*it < *it2) << std::endl;
	std::cout << "a>b check: " << (*it > *it2) << std::endl;
	std::cout << "a<=b check: " << (*it <= *it2) << std::endl;
	std::cout << "a>=b check: " << (*it >= *it2) << std::endl;
	std::cout << "a[0] check: " << *it[0] << ". a[5] check: " << *it[5] << std::endl;

	Vector<int>::iterator it3 = v.begun();
	std::cout << "*a check: " << *it3 << std::endl;

	std::cout << std::endl << "Capacity_tests__________" << std::endl;
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