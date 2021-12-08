#include <iostream>
#include <type_traits>
#include <vector>
#include "Utility.hpp"
#include "Vector.hpp"

template <class T>
typename ft::enable_if<ft::is_integral<T>::value,bool>::type
	is_odd (T i) { return bool(i%2); }


int	main_Utils()
{

std::cout << "	##     ## ######## #### ##        ######  " << std::endl;
std::cout << "	##     ##    ##     ##  ##       ##    ## " << std::endl;
std::cout << "	##     ##    ##     ##  ##       ##       " << std::endl;
std::cout << "	##     ##    ##     ##  ##        ######  " << std::endl;
std::cout << "	##     ##    ##     ##  ##             ## " << std::endl;
std::cout << "	##     ##    ##     ##  ##       ##    ## " << std::endl;
std::cout << "	 #######     ##    #### ########  ######  " << std::endl;


	std::cout << "/* ********************* is_integral *********************** */" << std::endl;
{
	int	error_count = 0;
	(ft::is_integral<float>() == std::is_integral<float>()) ? 0 : ++error_count;
	(ft::is_integral<int>() == std::is_integral<int>()) ? 0 : ++error_count;
	(ft::is_integral<bool>() == std::is_integral<bool>()) ? 0 : ++error_count;
	(ft::is_integral<char>() == std::is_integral<char>()) ? 0 : ++error_count;
	(ft::is_integral<signed char>() == std::is_integral<signed char>()) ? 0 : ++error_count;
	(ft::is_integral<unsigned char>() == std::is_integral<unsigned char>()) ? 0 : ++error_count;
	(ft::is_integral<wchar_t>() == std::is_integral<wchar_t>()) ? 0 : ++error_count;
	(ft::is_integral<char16_t>() == std::is_integral<char16_t>()) ? 0 : ++error_count;
	(ft::is_integral<short>() == std::is_integral<short>()) ? 0 : ++error_count;
	(ft::is_integral<unsigned short>() == std::is_integral<unsigned short>()) ? 0 : ++error_count;
	(ft::is_integral<unsigned int>() == std::is_integral<unsigned int>()) ? 0 : ++error_count;
	(ft::is_integral<long>() == std::is_integral<long>()) ? 0 : ++error_count;
	(ft::is_integral<unsigned long>() == std::is_integral<unsigned long>()) ? 0 : ++error_count;
	(ft::is_integral<long long>() == std::is_integral<long long>()) ? 0 : ++error_count;
	(ft::is_integral<unsigned long long>() == std::is_integral<unsigned long long>()) ? 0 : ++error_count;
	if (error_count == 0)
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* is_integral *********************** */" << std::endl;
	std::cout << "/* ********************* enable_if *********************** */" << std::endl;
{
	int i = 5;

	if (is_odd(i) == 1)
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* enable_if *********************** */" << std::endl;
	std::cout << "/* ********************* equal *********************** */" << std::endl;
{
	std::vector<int>	std_mp;
	ft::vector<int>		ft_mp;

	for (int i = 0; i < 10; ++i)
	{
		std_mp.push_back(i);
		ft_mp.push_back(i);
	}
	if (ft::equal(std_mp.begin(), std_mp.end(), ft_mp.begin() ))
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* equal *********************** */" << std::endl;
	std::cout << "/* ********************* lexicographical **************** */" << std::endl;
{
	std::vector<int>	std_mp;
	ft::vector<int>		ft_mp;

	for (int i = 0; i < 10; ++i)
	{
		if (i < 9)
			std_mp.push_back(i);
		ft_mp.push_back(i);
	}
	if (ft::lexicographical_compare(std_mp.begin(), std_mp.end(), ft_mp.begin(), ft_mp.end() ))
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* lexicographical **************** */" << std::endl;
	return 0;
}
