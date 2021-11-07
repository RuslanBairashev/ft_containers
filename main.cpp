#include <iostream>
#include <string>
#include <map>
#include "Map.hpp"
#include "Vextras.hpp"

int	main()
{
	Map<int, std::string> myMap;
	ft::pair<int, std::string> pair1(2, "Notebook");
	std::cout << pair1.first << ' ' << pair1.second << std::endl;
	/*myMap.insert(std::make_pair(1, "phone"));
	myMap.insert(ft::pair<int, std::string>(2, "notebook"));
	std::cout << myMap[1] << std::endl;
	myMap[18] = "TV";
	std::cout << myMap[18] << std::endl;*/
	return 0;
}