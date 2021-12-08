#include <iostream>
#include "Map.hpp"
#include "Utility.hpp"
#include <map>

void	std_fill_map(std::map<int, int> & mp)
{
	mp.insert(std::make_pair(1,1));
	mp.insert(std::make_pair(3,3));
	mp.insert(std::make_pair(21,21));
	mp.insert(std::make_pair(100,100));
	mp.insert(std::make_pair(15,15));
}
void	ft_fill_map(ft::map<int, int> & mp)
{
	mp.insert(ft::make_pair(1,1));
	mp.insert(ft::make_pair(3,3));
	mp.insert(ft::make_pair(21,21));
	mp.insert(ft::make_pair(100,100));
	mp.insert(ft::make_pair(15,15));
}

int	main_Map()
{

	std::cout << "	##     ##    ###    ########  " << std::endl;
	std::cout << "	###   ###   ## ##   ##     ## " << std::endl;
	std::cout << "	#### ####  ##   ##  ##     ## " << std::endl;
	std::cout << "	## ### ## ##     ## ########  " << std::endl;
	std::cout << "	##     ## ######### ##        " << std::endl;
	std::cout << "	##     ## ##     ## ##        " << std::endl;
	std::cout << "	##     ## ##     ## ##        " << std::endl;

	std::cout << "/* ********************* constructor(empty) *********************** */" << std::endl;
{
	std::map<int, int>	std_mp;
	ft::map<int, int>	ft_mp;

	std_mp.insert(std::make_pair(5,5));
	ft_mp.insert(ft::make_pair(5,5));
	if (std_mp.size() == ft_mp.size())
		std::cout << "\033[1;32mOK\033[0m" << std::endl;
	else
		std::cout << "\033[1;31mFAILED\033[0m" << std::endl;
}
	std::cout << "/* ********************* constructor(empty) *********************** */" << std::endl;
	std::cout << "/* ********************* constructor(range) *********************** */" << std::endl;
{
	std::map<int, int>	pre_std_mp;
	ft::map<int, int>	pre_ft_mp;
	std_fill_map(pre_std_mp);
	ft_fill_map(pre_ft_mp);

	std::map<int, int>	std_mp(pre_std_mp.begin(), --(pre_std_mp.end()));
	ft::map<int, int>		ft_mp(pre_ft_mp.begin(), --(pre_ft_mp.end()));

	if (std_mp.size() == ft_mp.size())
		std::cout << "\033[1;32mOK\033[0m" << std::endl;
	else
		std::cout << "\033[1;31mFAILED\033[0m" << std::endl;
}
	std::cout << "/* ********************* constructor(range) *********************** */" << std::endl;
	std::cout << "/* ********************* constructor(copy) *********************** */" << std::endl;
{
	std::map<int, int>		pre_std_mp;
	ft::map<int, int>		pre_ft_mp;
	std_fill_map(pre_std_mp);
	ft_fill_map(pre_ft_mp);

	std::map<int, int>	std_mp(pre_std_mp);
	ft::map<int, int>		ft_mp(pre_ft_mp);

	if (std_mp.size() == ft_mp.size())
		std::cout << "\033[1;32mOK\033[0m" << std::endl;
	else
		std::cout << "\033[1;31mFAILED\033[0m" << std::endl;
}
	std::cout << "/* ********************* constructor(copy) *********************** */" << std::endl;
	std::cout << "/* ********************* operator(=) *********************** */" << std::endl;
{
	std::map<int, int>		pre_std_mp;
	ft::map<int, int>		pre_ft_mp;
	std_fill_map(pre_std_mp);
	ft_fill_map(pre_ft_mp);

	std::map<int, int>	std_mp;
	ft::map<int, int>	ft_mp;

	std_mp = pre_std_mp;
	ft_mp = pre_ft_mp;
	if (std_mp.size() == ft_mp.size())
		std::cout << "\033[1;32mOK\033[0m" << std::endl;
	else
		std::cout << "\033[1;31mFAILED\033[0m" << std::endl;
}
	std::cout << "/* ********************* operator(=) *********************** */" << std::endl;
	std::cout << "/* ********************* begin()/end() *********************** */" << std::endl;
{
	std::map<int, int>	std_mp;
	ft::map<int, int>	ft_mp;

	for (int i = 0; i < 10; ++i)
	{
		std_mp.insert(std::make_pair(i,i));
		ft_mp.insert(ft::make_pair(i,i));
	}
	std::map<int, int>::iterator	beginit = std_mp.begin();
	std::map<int, int>::iterator	endit = std_mp.end();
	ft::map<int, int>::iterator		beginit2 = ft_mp.begin();
	ft::map<int, int>::iterator		endit2 = ft_mp.end();
	if ((beginit->first == 0 && beginit2->first == 0) &&
	 ((--endit)->first == 9 && (--endit2)->first == 9))
		std::cout << "\033[1;32mOK\033[0m" << std::endl;
	else
		std::cout << "\033[1;31mFAILED\033[0m" << std::endl;
}
	std::cout << "/* ********************* begin()/end() *********************** */" << std::endl;
	std::cout << "/* ********************* rbegin()/rend() *********************** */" << std::endl;
{
	std::map<int, int>	std_mp;
	ft::map<int, int>	ft_mp;

	for (int i = 0; i < 10; ++i)
	{
		std_mp.insert(std::make_pair(i,i));
		ft_mp.insert(ft::make_pair(i,i));
	}
	std::map<int, int>::reverse_iterator	beginit = std_mp.rbegin();
	std::map<int, int>::reverse_iterator	endit = std_mp.rend();
	ft::map<int, int>::reverse_iterator		beginit2 = ft_mp.rbegin();
	ft::map<int, int>::reverse_iterator		endit2 = ft_mp.rend();
	if ((beginit->first == 9 && beginit2->first == 9) &&
	 ((--endit)->first == 0 && (--endit2)->first == 0))
		std::cout << "\033[1;32mOK\033[0m" << std::endl;
	else
		std::cout << "\033[1;31mFAILED\033[0m" << std::endl;
}
	std::cout << "/* ********************* rbegin()/rend() *********************** */" << std::endl;
	std::cout << "/* ********************* size() *********************** */" << std::endl;
{
	std::map<int, int>	std_mp;
	ft::map<int, int>	ft_mp;

	std_fill_map(std_mp);
	ft_fill_map(ft_mp);
	if (std_mp.size() == ft_mp.size())
		std::cout << "\033[1;32mOK\033[0m" << std::endl;
	else
		std::cout << "\033[1;31mFAILED\033[0m" << std::endl;
}
	std::cout << "/* ********************* size() *********************** */" << std::endl;
	std::cout << "/* ********************* max_size() *********************** */" << std::endl;
{
	std::map<int, int>	std_mp;
	ft::map<int, int>	ft_mp;

	std::cout << "std_mp.max_size = " << std_mp.max_size() << std::endl;
	std::cout << " ft_mp.max_size = " << ft_mp.max_size() << std::endl;
}
	std::cout << "/* ********************* max_size() *********************** */" << std::endl;
	std::cout << "/* ********************* empty() *********************** */" << std::endl;
{
	std::map<int, int>	std_mp;
	ft::map<int, int>	ft_mp;

	std_fill_map(std_mp);
	ft_fill_map(ft_mp);
	if (std_mp.empty() == ft_mp.empty())
		std::cout << "\033[1;32mOK\033[0m" << std::endl;
	else
		std::cout << "\033[1;31mFAILED\033[0m" << std::endl;
}
	std::cout << "/* ********************* empty() *********************** */" << std::endl;
	std::cout << "/* ********************* operator[] *********************** */" << std::endl;
{
	std::map<int, int>	std_mp;
	ft::map<int, int>	ft_mp;

	std_fill_map(std_mp);
	ft_fill_map(ft_mp);
	if (std_mp[1] == ft_mp[1])
		std::cout << "\033[1;32mOK\033[0m" << std::endl;
	else
		std::cout << "\033[1;31mFAILED\033[0m" << std::endl;
}
	std::cout << "/* ********************* operator[] *********************** */" << std::endl;
	std::cout << "/* ********************* insert(element) *********************** */" << std::endl;
{
	std::map<int, int>	std_mp;
	ft::map<int, int>		ft_mp;

	std_fill_map(std_mp);
	ft_fill_map(ft_mp);
	std::map<int, int>::iterator	it = std_mp.begin();
	ft::map<int, int>::iterator		it2 = ft_mp.begin();
	std_mp.insert(std::make_pair(50,50));
	ft_mp.insert(ft::make_pair(50,50));
	std_mp.insert(it, std::make_pair(42,42));
	ft_mp.insert(it2, ft::make_pair(42,42));
	if (std_mp.size() == ft_mp.size())
		std::cout << "\033[1;32mOK\033[0m" << std::endl;
	else
		std::cout << "\033[1;31mFAILED\033[0m" << std::endl;
}
	std::cout << "/* ********************* insert(element) *********************** */" << std::endl;
	std::cout << "/* ********************* insert(range) *********************** */" << std::endl;
{
	std::map<int, int>	pre_std_mp;
	ft::map<int, int>	pre_ft_mp;
	std_fill_map(pre_std_mp);
	ft_fill_map(pre_ft_mp);

	std::map<int, int>	std_mp;
	ft::map<int, int>	ft_mp;

	for (int i = 0; i < 21; ++i)
	{
		std_mp.insert(std::make_pair(i,i));
		ft_mp.insert(ft::make_pair(i,i));
	}
	std_mp.insert(pre_std_mp.begin(), pre_std_mp.end());
	ft_mp.insert(pre_ft_mp.begin(), pre_ft_mp.end());
	if (std_mp.size() == ft_mp.size())
		std::cout << "\033[1;32mOK\033[0m" << std::endl;
	else
		std::cout << "\033[1;31mFAILED\033[0m" << std::endl;
}
	std::cout << "/* ********************* insert(range) *********************** */" << std::endl;
	std::cout << "/* ********************* erase(position) *********************** */" << std::endl;
{
	std::map<int, int>	std_mp;
	ft::map<int, int>	ft_mp;

	std_fill_map(std_mp);
	ft_fill_map(ft_mp);
	std::map<int, int>::iterator	it = std_mp.begin();
	ft::map<int, int>::iterator		it2 = ft_mp.begin();
	std_mp.erase(it);
	ft_mp.erase(it2);
	if (std_mp.size() == ft_mp.size())
		std::cout << "\033[1;32mOK\033[0m" << std::endl;
	else
		std::cout << "\033[1;31mFAILED\033[0m" << std::endl;
}
	std::cout << "/* ********************* erase(position) *********************** */" << std::endl;
	std::cout << "/* ********************* erase(element) *********************** */" << std::endl;
{
	std::map<int, int>	std_mp;
	ft::map<int, int>	ft_mp;

	std_fill_map(std_mp);
	ft_fill_map(ft_mp);
	std_mp.erase(21);
	ft_mp.erase(21);
	if (std_mp.size() == ft_mp.size())
		std::cout << "\033[1;32mOK\033[0m" << std::endl;
	else
		std::cout << "\033[1;31mFAILED\033[0m" << std::endl;
}
	std::cout << "/* ********************* erase(element) *********************** */" << std::endl;
	std::cout << "/* ********************* erase(range) *********************** */" << std::endl;
{
	std::map<int, int>	std_mp;
	ft::map<int, int>	ft_mp;

	std_fill_map(std_mp);
	ft_fill_map(ft_mp);
	std::map<int, int>::iterator	beginit = std_mp.begin();
	std::map<int, int>::iterator	endit = std_mp.end();
	ft::map<int, int>::iterator		beginit2 = ft_mp.begin();
	ft::map<int, int>::iterator		endit2 = ft_mp.end();
	std_mp.erase(beginit, --endit);
	ft_mp.erase(beginit2, --endit2);
	if (std_mp.size() == ft_mp.size())
		std::cout << "\033[1;32mOK\033[0m" << std::endl;
	else
		std::cout << "\033[1;31mFAILED\033[0m" << std::endl;
}
	std::cout << "/* ********************* erase(range) *********************** */" << std::endl;
	std::cout << "/* ********************* swap() *********************** */" << std::endl;
{
	std::map<int, int>	pre_std_mp;
	ft::map<int, int>	pre_ft_mp;
	std_fill_map(pre_std_mp);
	ft_fill_map(pre_ft_mp);

	std::map<int, int>	std_mp;
	ft::map<int, int>	ft_mp;
	for (int i = 0; i < 21; ++i)
	{
		std_mp.insert(std::make_pair(i,i));
		ft_mp.insert(ft::make_pair(i,i));
	}
	std_mp.swap(pre_std_mp);
	ft_mp.swap(pre_ft_mp);
	if (std_mp.size() == ft_mp.size())
		std::cout << "\033[1;32mOK\033[0m" << std::endl;
	else
		std::cout << "\033[1;31mFAILED\033[0m" << std::endl;
}
	std::cout << "/* ********************* swap() *********************** */" << std::endl;
	std::cout << "/* ********************* clear() *********************** */" << std::endl;
{
	std::map<int, int>	std_mp;
	ft::map<int, int>	ft_mp;

	for (int i = 0; i < 21; ++i)
	{
		std_mp.insert(std::make_pair(i,i));
		ft_mp.insert(ft::make_pair(i,i));
	}
	std_mp.clear();
	ft_mp.clear();
	if (std_mp.size() == ft_mp.size())
		std::cout << "\033[1;32mOK\033[0m" << std::endl;
	else
		std::cout << "\033[1;31mFAILED\033[0m" << std::endl;
}
	std::cout << "/* ********************* clear() *********************** */" << std::endl;
	std::cout << "/* ********************* find() *********************** */" << std::endl;
{
	std::map<int, int>	std_mp;
	ft::map<int, int>	ft_mp;

	std_fill_map(std_mp);
	ft_fill_map(ft_mp);
	std_mp.erase(std_mp.find(21));
	ft_mp.erase(ft_mp.find(21));
	if (std_mp[1] == ft_mp[1])
		std::cout << "\033[1;32mOK\033[0m" << std::endl;
	else
		std::cout << "\033[1;31mFAILED\033[0m" << std::endl;
}
	std::cout << "/* ********************* find() *********************** */" << std::endl;
	std::cout << "/* ********************* count() *********************** */" << std::endl;
{
	std::map<int, int>	std_mp;
	ft::map<int, int>	ft_mp;

	std_fill_map(std_mp);
	ft_fill_map(ft_mp);
	if (std_mp.count(21) == ft_mp.count(21))
		std::cout << "\033[1;32mOK\033[0m" << std::endl;
	else
		std::cout << "\033[1;31mFAILED\033[0m" << std::endl;
}
	std::cout << "/* ********************* count() *********************** */" << std::endl;
	std::cout << "/* ********************* lower_bound()/upper_bound() **** */" << std::endl;
{
	std::map<int, int>	std_mp;
	ft::map<int, int>	ft_mp;

	std_fill_map(std_mp);
	ft_fill_map(ft_mp);
	std::map<int, int>::iterator	beginit = std_mp.lower_bound(3);
	std::map<int, int>::iterator	endit = std_mp.upper_bound(21);
	ft::map<int, int>::iterator		beginit2 = ft_mp.lower_bound(3);
	ft::map<int, int>::iterator		endit2 = ft_mp.upper_bound(21);
	std_mp.erase(beginit, endit);
	ft_mp.erase(beginit2, endit2);
	if (std_mp.size() == ft_mp.size())
		std::cout << "\033[1;32mOK\033[0m" << std::endl;
	else
		std::cout << "\033[1;31mFAILED\033[0m" << std::endl;
}
	std::cout << "/* ********************* lower_bound(/upper_bound() **** */" << std::endl;
	std::cout << "/* ********************* equal_range() ***************** */" << std::endl;
{
	std::map<int, int>	std_mp;
	ft::map<int, int>	ft_mp;

	std_fill_map(std_mp);
	ft_fill_map(ft_mp);
	std::map<int, int>::iterator	beginit = (std_mp.equal_range(3)).first;
	ft::map<int, int>::iterator		beginit2 = (ft_mp.equal_range(3)).first;
	if (beginit->first == beginit2->first)
		std::cout << "\033[1;32mOK\033[0m" << std::endl;
	else
		std::cout << "\033[1;31mFAILED\033[0m" << std::endl;
}
	std::cout << "/* ********************* equal_range() ***************** */" << std::endl;
	std::cout << "/* ********************* erase(it) from tester*********** */" << std::endl;
{
	// ft::map<int, int> mp;
    // for (int i = 0, j = 0; i < 500000; ++i, ++j)
    //     mp.insert(ft::make_pair(i, j));
    // ft::map<int, int>::iterator	last = mp.end();
	// --last;
	// mp.erase(mp.begin(), last);
}	
	std::cout << "/* ********************* erase(it) from tester*********** */" << std::endl;

	return 0;
}
