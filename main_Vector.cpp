#include <iostream>
#include "Vector.hpp"
#include "Utility.hpp"
#include <vector>
#include <sys/time.h>

class B {
public:
	char *l;
	int i;
	B():l(nullptr), i(1) {};
	B(const int &ex) {
		this->i = ex;
		this->l = new char('a');
	};
	virtual ~B() {
		delete this->l;
		this->l = nullptr;
	};
};

class A : public B {
public:
	A():B(){};
	A(const B* ex){
		this->l = new char(*(ex->l));
		this->i = ex->i;
		if (ex->i == -1) throw "n";
	}
	~A() {
		delete this->l;
		this->l = nullptr;
	};
};



time_t timer() {
   struct timeval start = {};
   gettimeofday(&start, nullptr);
   time_t msecs_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
   return msecs_time;
}

time_t g_start1;
time_t g_end1;
time_t g_start2;
time_t g_end2;

int	main_Vector()
{

	std::cout << "	##     ## ########  ######  ########  #######  ########  " << std::endl;
	std::cout << "	##     ## ##       ##    ##    ##    ##     ## ##     ## " << std::endl;
	std::cout << "	##     ## ##       ##          ##    ##     ## ##     ## " << std::endl;
	std::cout << "	##     ## ######   ##          ##    ##     ## ########  " << std::endl;
	std::cout << "	 ##   ##  ##       ##          ##    ##     ## ##   ##   " << std::endl;
	std::cout << "	  ## ##   ##       ##    ##    ##    ##     ## ##    ##  " << std::endl;
	std::cout << "	   ###    ########  ######     ##     #######  ##     ## " << std::endl;

	std::cout << "/* ********************* constructor(default) *********************** */" << std::endl;
{
	std::vector<int>	std_mp;
	ft::vector<int>	ft_mp;

	std_mp.push_back(5);
	ft_mp.push_back(5);
	if (std_mp.size() == ft_mp.size())
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* constructor(default) *********************** */" << std::endl;
	std::cout << "/* ********************* constructor(fill) *********************** */" << std::endl;
{
	std::vector<int>	std_mp(21, 42);
	ft::vector<int>	ft_mp(21, 42);

	if (std_mp.size() == ft_mp.size())
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* constructor(fill) *********************** */" << std::endl;
	std::cout << "/* ********************* constructor(range) *********************** */" << std::endl;
{
	std::vector<int>	pre_std_mp(21, 42);
	ft::vector<int>		pre_ft_mp(21, 42);

	std::vector<int>	std_mp(pre_std_mp.begin(), --(pre_std_mp.end()));
	ft::vector<int>		ft_mp(pre_ft_mp.begin(), --(pre_ft_mp.end()));

	if (std_mp.size() == ft_mp.size())
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* constructor(range) *********************** */" << std::endl;
	std::cout << "/* ********************* constructor(copy) *********************** */" << std::endl;
{
	std::vector<int>	pre_std_mp(21, 42);
	ft::vector<int>		pre_ft_mp(21, 42);

	std::vector<int>	std_mp(pre_std_mp);
	ft::vector<int>		ft_mp(pre_ft_mp);

	if (std_mp.size() == ft_mp.size())
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* constructor(copy) *********************** */" << std::endl;
	std::cout << "/* ********************* operator(=) *********************** */" << std::endl;
{
	std::vector<int>	pre_std_mp(21, 42);
	ft::vector<int>		pre_ft_mp(21, 42);

	std::vector<int>	std_mp;
	ft::vector<int>		ft_mp;

	std_mp = pre_std_mp;
	ft_mp = pre_ft_mp;
	if (std_mp.size() == ft_mp.size())
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* operator(=) *********************** */" << std::endl;
	std::cout << "/* ********************* begin()/end() *********************** */" << std::endl;
{
	std::vector<int>	std_mp;
	ft::vector<int>		ft_mp;

	for (int i = 0; i < 10; ++i)
	{
		std_mp.push_back(i);
		ft_mp.push_back(i);
	}
	if ((*(std_mp.begin()) == 0 && *(ft_mp.begin()) == 0) && (*(--std_mp.end()) == 9 && *(--ft_mp.end()) == 9))
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* begin()/end() *********************** */" << std::endl;
	std::cout << "/* ********************* rbegin()/rend() *********************** */" << std::endl;
{
	std::vector<int>	std_mp;
	ft::vector<int>		ft_mp;

	for (int i = 0; i < 10; ++i)
	{
		std_mp.push_back(i);
		ft_mp.push_back(i);
	}
	if ((*(std_mp.rbegin()) == 9 && *(ft_mp.rbegin()) == 9) && (*(--std_mp.rend()) == 0 && *(--ft_mp.rend()) == 0))
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* rbegin()/rend() *********************** */" << std::endl;
	std::cout << "/* ********************* size() *********************** */" << std::endl;
{
	std::vector<int>	std_mp;
	ft::vector<int>		ft_mp;

	for (int i = 0; i < 21; ++i)
	{
		std_mp.push_back(i);
		ft_mp.push_back(i);
	}
	if (std_mp.size() == ft_mp.size())
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* size() *********************** */" << std::endl;
	std::cout << "/* ********************* max_size() *********************** */" << std::endl;
{
	std::vector<int>	std_mp;
	ft::vector<int>		ft_mp;

	if (std_mp.max_size() == ft_mp.max_size())
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* max_size() *********************** */" << std::endl;
	std::cout << "/* ********************* resize() *********************** */" << std::endl;
{
	std::vector<int>	std_mp;
	ft::vector<int>		ft_mp;

	for (int i = 0; i < 21; ++i)
	{
		std_mp.push_back(i);
		ft_mp.push_back(i);
	}
	// std::cout << "cap= " << std_mp.capacity() << std::endl;
	// std::cout << "cap= " << ft_mp.capacity() << std::endl;
	// std::cout << "size= " << std_mp.size() << std::endl;
	// std::cout << "size= " << ft_mp.size() << std::endl;
	std_mp.resize(100);
	ft_mp.resize(100);
	// std::cout << "cap= " << std_mp.capacity() << std::endl;
	// std::cout << "cap= " << ft_mp.capacity() << std::endl;
	// std::cout << "size= " << std_mp.size() << std::endl;
	// std::cout << "size= " << ft_mp.size() << std::endl;
	if (std_mp.size() == ft_mp.size())
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* resize() *********************** */" << std::endl;
	std::cout << "/* ********************* capacity() *********************** */" << std::endl;
{
	std::vector<int>	std_mp;
	ft::vector<int>		ft_mp;

	for (int i = 0; i < 21; ++i)
	{
		std_mp.push_back(i);
		ft_mp.push_back(i);
	}
	if (std_mp.capacity() == ft_mp.capacity())
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* capacity() *********************** */" << std::endl;
	std::cout << "/* ********************* empty() *********************** */" << std::endl;
{
	std::vector<int>	std_mp;
	ft::vector<int>		ft_mp;

	for (int i = 0; i < 21; ++i)
	{
		std_mp.push_back(i);
		ft_mp.push_back(i);
	}
	if (std_mp.empty() == ft_mp.empty())
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* empty() *********************** */" << std::endl;
	std::cout << "/* ********************* reserve() *********************** */" << std::endl;
{
	std::vector<int>	std_mp;
	ft::vector<int>		ft_mp;

	for (int i = 0; i < 21; ++i)
	{
		std_mp.push_back(i);
		ft_mp.push_back(i);
	}
	// std::cout << "cap= " << std_mp.capacity() << std::endl;
	// std::cout << "cap= " << ft_mp.capacity() << std::endl;
	std_mp.reserve(64);
	ft_mp.reserve(64);
	// std::cout << "cap= " << std_mp.capacity() << std::endl;
	// std::cout << "cap= " << ft_mp.capacity() << std::endl;
	if (std_mp.capacity() == ft_mp.capacity())
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* reserve() *********************** */" << std::endl;
	std::cout << "/* ********************* operator[] *********************** */" << std::endl;
{
	std::vector<int>	std_mp;
	ft::vector<int>		ft_mp;

	for (int i = 0; i < 21; ++i)
	{
		std_mp.push_back(i);
		ft_mp.push_back(i);
	}
	if (std_mp[10] == ft_mp[10])
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* operator[] *********************** */" << std::endl;
	std::cout << "/* ********************* at() *********************** */" << std::endl;
{
	std::vector<int>	std_mp;
	ft::vector<int>		ft_mp;

	for (int i = 0; i < 21; ++i)
	{
		std_mp.push_back(i);
		ft_mp.push_back(i);
	}
	if (std_mp.at(10) == ft_mp.at(10))
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* at() *********************** */" << std::endl;
	std::cout << "/* ********************* front()/back() *********************** */" << std::endl;
{
	std::vector<int>	std_mp;
	ft::vector<int>		ft_mp;

	for (int i = 0; i < 21; ++i)
	{
		std_mp.push_back(i);
		ft_mp.push_back(i);
	}
	if ((std_mp.front() == ft_mp.front()) && (std_mp.back() == ft_mp.back()))
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* front()/back() *********************** */" << std::endl;
	std::cout << "/* ********************* assign(range) *********************** */" << std::endl;
{
	std::vector<int>	pre_std_mp(21, 42);
	ft::vector<int>		pre_ft_mp(21, 42);

	std::vector<int>	std_mp;
	ft::vector<int>		ft_mp;

	std_mp.assign(pre_std_mp.begin(), --(pre_std_mp.end()));
	ft_mp.assign(pre_ft_mp.begin(), --(pre_ft_mp.end()));
	if (std_mp[0] == ft_mp[0])
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* assign(range) *********************** */" << std::endl;
	std::cout << "/* ********************* assign(fill) *********************** */" << std::endl;
{
	std::vector<int>	std_mp;
	ft::vector<int>		ft_mp;

	std_mp.assign(21, 42);
	ft_mp.assign(21, 42);
	if (std_mp[0] == ft_mp[0])
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* assign(fill) *********************** */" << std::endl;
	std::cout << "/* ********************* push_back()/pop_back() *********************** */" << std::endl;
{
	std::vector<int>	std_mp;
	ft::vector<int>		ft_mp;

	for (int i = 0; i < 21; ++i)
	{
		std_mp.push_back(i);
		ft_mp.push_back(i);
	}
	std_mp.pop_back();
	ft_mp.pop_back();
	if (std_mp.size() == ft_mp.size())
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* push_back()/pop_back() *********************** */" << std::endl;
	std::cout << "/* ********************* insert(value) *********************** */" << std::endl;
{
	// ft::vector<int> vector;
    // std::vector<int> v;
    // vector.assign(26000000, 1);

    // v.push_back(*(vector.insert(vector.end() - 8000000, 44)));

    // v.push_back(vector.size());
    // v.push_back(vector.capacity());
    // std::unique_ptr<B> k2(new B(3));
    // std::unique_ptr<B> k3(new B(4));
    // std::unique_ptr<B> k4(new B(-1));
    // ft::vector<A> vv;
    // ft::vector<B*> v1;

    // v1.push_back(&(*k2));
    // v1.push_back(&(*k3));
    // v1.push_back(&(*k4));
    // try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
    // catch (...) {
    // 	v.push_back(vv.size());
    // 	v.push_back(vv.capacity());
    // }
}
	std::cout << "/* ********************* insert(value) *********************** */" << std::endl;
	std::cout << "/* ********************* insert(element) *********************** */" << std::endl;
{
	std::vector<int>	std_mp;
	ft::vector<int>		ft_mp;

	for (int i = 0; i < 21; ++i)
	{
		std_mp.push_back(i);
		ft_mp.push_back(i);
	}
	std::vector<int>::iterator	it = std_mp.begin();
	ft::vector<int>::iterator	it2 = ft_mp.begin();
	std_mp.insert(it, 42);
	ft_mp.insert(it2, 42);
	if (std_mp.size() == ft_mp.size())
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* insert(element) *********************** */" << std::endl;
	std::cout << "/* ********************* insert(fill) *********************** */" << std::endl;
{
	std::vector<int>	std_mp;
	ft::vector<int>		ft_mp;

	for (int i = 0; i < 21; ++i)
	{
		std_mp.push_back(i);
		ft_mp.push_back(i);
	}
	std::vector<int>::iterator	it = std_mp.begin();
	ft::vector<int>::iterator	it2 = ft_mp.begin();
	std_mp.insert(it, 10, 42);
	ft_mp.insert(it2, 10, 42);
	if (std_mp.size() == ft_mp.size())
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* insert(fill) *********************** */" << std::endl;
	std::cout << "/* ********************* insert(range) *********************** */" << std::endl;
{
	std::vector<int>	pre_std_mp(21, 42);
	ft::vector<int>		pre_ft_mp(21, 42);

	std::vector<int>	std_mp;
	ft::vector<int>		ft_mp;

	for (int i = 0; i < 21; ++i)
	{
		std_mp.push_back(i);
		ft_mp.push_back(i);
	}
	std_mp.insert(std_mp.begin(), pre_std_mp.begin(), pre_std_mp.end());
	ft_mp.insert(ft_mp.begin(), pre_ft_mp.begin(), pre_ft_mp.end());
	if (std_mp.size() == ft_mp.size())
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* insert(range) *********************** */" << std::endl;
	std::cout << "/* ********************* erase(element) *********************** */" << std::endl;
{
	std::vector<int>	std_mp;
	ft::vector<int>		ft_mp;

	for (int i = 0; i < 21; ++i)
	{
		std_mp.push_back(i);
		ft_mp.push_back(i);
	}
	std::vector<int>::iterator	it = std_mp.begin();
	ft::vector<int>::iterator	it2 = ft_mp.begin();
	std_mp.erase(it);
	ft_mp.erase(it2);
	if (std_mp.size() == ft_mp.size())
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* erase(element) *********************** */" << std::endl;
	std::cout << "/* ********************* erase(range) *********************** */" << std::endl;
{
	std::vector<int>	std_mp;
	ft::vector<int>		ft_mp;

	for (int i = 0; i < 21; ++i)
	{
		std_mp.push_back(i);
		ft_mp.push_back(i);
	}
	std::vector<int>::iterator	it = std_mp.begin();
	ft::vector<int>::iterator	it2 = ft_mp.begin();
	std_mp.erase(it, --(std_mp.end()));
	ft_mp.erase(it2, --(ft_mp.end()));
	if (std_mp.size() == ft_mp.size())
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* erase(range) *********************** */" << std::endl;
	std::cout << "/* ********************* swap() *********************** */" << std::endl;
{
	std::vector<int>	pre_std_mp(21, 42);
	ft::vector<int>		pre_ft_mp(21, 42);

	std::vector<int>	std_mp;
	ft::vector<int>		ft_mp;

	// std::vector<int>	std_mp2(pre_std_mp);
	// ft::vector<int>		ft_mp2(pre_ft_mp);

	for (int i = 0; i < 21; ++i)
	{
		std_mp.push_back(i);
		ft_mp.push_back(i);
	}
	std_mp.swap(pre_std_mp);
	ft_mp.swap(pre_ft_mp);
	// std::swap(std_mp, std_mp2);
	// ft::swap(ft_mp, ft_mp2);
	
	if (std_mp.size() == ft_mp.size())
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* swap() *********************** */" << std::endl;
	std::cout << "/* ********************* clear() *********************** */" << std::endl;
{
	std::vector<int>	std_mp;
	ft::vector<int>		ft_mp;

	for (int i = 0; i < 21; ++i)
	{
		std_mp.push_back(i);
		ft_mp.push_back(i);
	}
	std_mp.clear();
	ft_mp.clear();
	if (std_mp.size() == ft_mp.size())
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}
	std::cout << "/* ********************* clear() *********************** */" << std::endl;

	return 0;
}
