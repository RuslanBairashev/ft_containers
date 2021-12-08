#include <iostream>
#include "Stack.hpp"
#include "Utility.hpp"
#include <stack>

int	main_Stack()
{

	std::cout << "	 ######  ########    ###     ######  ##    ## " << std::endl;
	std::cout << "	##    ##    ##      ## ##   ##    ## ##   ##  " << std::endl;
	std::cout << "	##          ##     ##   ##  ##       ##  ##   " << std::endl;
	std::cout << "	 ######     ##    ##     ## ##       #####    " << std::endl;
	std::cout << "	      ##    ##    ######### ##       ##  ##   " << std::endl;
	std::cout << "	##    ##    ##    ##     ## ##    ## ##   ##  " << std::endl;
	std::cout << "	 ######     ##    ##     ##  ######  ##    ## " << std::endl;

	std::cout << "/* ********************* constructor(default) *********************** */" << std::endl;
{
	std::stack<int>	std_mp;
	ft::stack<int>	ft_mp;

	std_mp.push(5);
	ft_mp.push(5);
	if (std_mp.size() == ft_mp.size())
		std::cout << "\033[1;32mOK\033[0m" << std::endl;
	else
		std::cout << "\033[1;31mFAILED\033[0m" << std::endl;
}
	std::cout << "/* ********************* constructor(default) *********************** */" << std::endl;
	std::cout << "/* ********************* size() *********************** */" << std::endl;
{
	std::stack<int>	std_mp;
	ft::stack<int>		ft_mp;

	for (int i = 0; i < 21; ++i)
	{
		std_mp.push(i);
		ft_mp.push(i);
	}
	if (std_mp.size() == ft_mp.size())
		std::cout << "\033[1;32mOK\033[0m" << std::endl;
	else
		std::cout << "\033[1;31mFAILED\033[0m" << std::endl;
}
	std::cout << "/* ********************* size() *********************** */" << std::endl;
	std::cout << "/* ********************* empty() *********************** */" << std::endl;
{
	std::stack<int>	std_mp;
	ft::stack<int>		ft_mp;

	for (int i = 0; i < 21; ++i)
	{
		std_mp.push(i);
		ft_mp.push(i);
	}
	if (std_mp.empty() == ft_mp.empty())
		std::cout << "\033[1;32mOK\033[0m" << std::endl;
	else
		std::cout << "\033[1;31mFAILED\033[0m" << std::endl;
}
	std::cout << "/* ********************* empty() *********************** */" << std::endl;
	std::cout << "/* ********************* top() *********************** */" << std::endl;
{
	std::stack<int>	std_mp;
	ft::stack<int>		ft_mp;

	for (int i = 0; i < 21; ++i)
	{
		std_mp.push(i);
		ft_mp.push(i);
	}
	if (std_mp.top() == ft_mp.top())
		std::cout << "\033[1;32mOK\033[0m" << std::endl;
	else
		std::cout << "\033[1;31mFAILED\033[0m" << std::endl;
}
	std::cout << "/* ********************* top() *********************** */" << std::endl;
	std::cout << "/* ********************* push()/pop() *********************** */" << std::endl;
{
	std::stack<int>	std_mp;
	ft::stack<int>		ft_mp;

	for (int i = 0; i < 21; ++i)
	{
		std_mp.push(i);
		ft_mp.push(i);
	}
	std_mp.pop();
	ft_mp.pop();
	if (std_mp.size() == ft_mp.size())
		std::cout << "\033[1;32mOK\033[0m" << std::endl;
	else
		std::cout << "\033[1;31mFAILED\033[0m" << std::endl;
}
	std::cout << "/* ********************* push()/pop() *********************** */" << std::endl;
	
	return 0;
}
