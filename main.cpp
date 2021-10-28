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

	std::cout << std::endl << "Viterators_tests_________" << std::endl;
	/*************************************************************************/
	std::cout << "begin check: " << *(v.begin()) << std::endl;
	std::cout << "end check: " << *(v.end()) << std::endl;
	std::cout << std::endl << "Viterator_class_tests_________" << std::endl;
	Vector<int>::iterator it = v.begin();
	std::cout << "*a check: " << *it << std::endl;
	*it = 42;
	std::cout << "*a= check: " << *it << std::endl;
	std::cout << "++a check: " << *(it++) << std::endl;
	std::cout << "a++ check: " << *(++it) << std::endl;
	std::cout << "a+ check: " << *(it + 2) << std::endl;
	std::cout << "a- check: " << *(it - 1) << std::endl;
	std::cout << "a+= check: " << *(it+=2) << std::endl;
	std::cout << "a-= check: " << *(it-=1) << std::endl;
	Vector<int>::iterator it2 = it + 3;
	std::cout << "Current positions: " << "*it= " << *it << " *it2= " << *it2 << std::endl;
	std::cout << "a<b check: " << (*it < *it2) << std::endl;
	std::cout << "a>b check: " << (*it > *it2) << std::endl;
	std::cout << "a<=b check: " << (*it <= *it2) << std::endl;
	std::cout << "a>=b check: " << (*it >= *it2) << std::endl;
	std::cout << "a[0] check: " << it[0] << ". a[5] check: " << it[5] << std::endl;

	std::vector<int> std_v;
	for (int i = 11; i < 20; ++i)
		std_v.push_back(i);
	std::vector<int>::iterator it10 = std_v.begin();
	std::cout << "*std_v check: " << *it10 << std::endl;
	std::cout << "max_size check: " << std_v.max_size() << std::endl;

	std::cout << std::endl << "Capacity_tests__________" << std::endl;
	/*************************************************************************/
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
	/*************************************************************************/
	std::cout << "operator[] check: " << v[2] << std::endl;
	std::cout << "at check: " << v.at(3) << std::endl;
	std::cout << "front check: " << v.front() << std::endl;
	std::cout << "back check: " << v.back() << std::endl;

	Vector<int>::iterator it3 = v.begin();
	std::cout << "Modifiers_tests____" << std::endl;
	/*************************************************************************/
	std::cout << "assign check: " << std::endl;
	Vector<int> first;
	Vector<int> second;
	first.assign (7,100);             // 7 ints with a value of 100
	std::cout << std::endl << "first contains: " << first << std::endl;

	Vector<int>::iterator its = first.begin()+1;
	second.assign (its,first.end()-1); // the 5 central values of first
	std::cout << std::endl << "second contains: " << second << std::endl;

	//int myints[] = {1776,7,4};
	//third.assign (myints,myints+3);   // assigning from array.

	std::cout << "push_back check: " << std::endl;
	first.push_back(50);
	std::cout << std::endl << "first contains: " << first << std::endl;
	std::cout << "pop_back check: " << std::endl;
	first.pop_back();
	std::cout << std::endl << "first contains: " << first << std::endl;
	std::cout << "insert check: " << std::endl;
	std::cout << std::endl << "1.v contains: " << v << std::endl;
	v.insert(it3, 1);
	std::cout << std::endl << "2.v contains: " << v << std::endl;
	v.insert(it3, 5, 300);
	std::cout << std::endl << "3.v contains: " << v << std::endl;
	Vector<int>	plus;
	for (int i = 0; i < 25; ++i)
		plus.push_back(i + 101);
	it3 = v.begin();
	v.insert(it3 + 3, plus.begin(), plus.end());
	std::cout << std::endl << "4.v contains: " << v << std::endl;
	std::cout << "erase check: " << std::endl;
	it3 = v.begin();
	v.erase(it3 + 5);
	std::cout << std::endl << "v contains: " << v << std::endl;
	v.erase(it3, it3 + 3);
	std::cout << std::endl << "v contains: " << v << std::endl;
	std::cout << "swap check: " << std::endl;
	Vector<int> foo (3,100);   // three ints with a value of 100
	Vector<int> bar (5,200);   // five ints with a value of 200
	foo.swap(bar);
	std::cout << "foo contains: " << foo;
	std::cout << "bar contains: " << bar << std::endl;

	return 0;
}