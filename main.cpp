#include <iostream>
#include "Vector.hpp"

int	main()
{
	/*Vector	v(11);
	std::cout << v << std::endl;
	v.push_back(123);
	std::cout << v << std::endl;
	v.push_back(45);
	std::cout << v << std::endl;*/
	Vector<int>	v;
	for (int i = 1; i < 22; ++i)
	{
		v.push_back(i);
		std::cout << v;
	}
	return 0;
}