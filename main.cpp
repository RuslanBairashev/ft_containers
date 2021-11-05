#include <iostream>
#include <string>
#include <map>

int	main()
{
	std::map<int, std::string> myMap;
	myMap.insert(std::make_pair(1, "phone"));
	myMap.insert(std::pair<int, std::string>(2, "notebook"));
	std::cout << myMap[1] << std::endl;
	myMap[18] = "TV";
	std::cout << myMap[18] << std::endl;
	return 0;
}