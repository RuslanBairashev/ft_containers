#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Map.hpp"
#include "Utility.hpp"
#include "Miterator.hpp"
#include "Reviterator.hpp"

static std::multimap<int, int> multi;
static std::multimap<int, int> multi2;

void	show_node(ft::Tree<int, std::string, std::less<int>, std::allocator<std::pair<const int, std::string> > >::Node * node, unsigned level)
{
	if (node != NULL)
	{
		std::cout << "LEVEL:" << level << ' ' << node->value.first ;
		std::cout << " Node: " << node ;
		std::cout << " Parent: " << node->parent ;
		std::cout << std::endl;
		multi.insert(std::make_pair(level, node->value.first));
	}
	if (node->pleft)
		show_node(node->pleft, level + 1);
	if (node->pright)
		show_node(node->pright, level + 1);
}
void	show_node(ft::Tree<int, int, std::less<int>, std::allocator<std::pair<const int, int> > >::Node * node, unsigned level)
{
	if (node != NULL)
	{
		std::cout << "LEVEL:" << level << ' ' << node->value.first ;
		std::cout << " Node: " << node ;
		std::cout << " Parent: " << node->parent ;
		std::cout << std::endl;
		multi2.insert(std::make_pair(level, node->value.first));
	}
	if (node->pleft)
		show_node(node->pleft, level + 1);
	if (node->pright)
		show_node(node->pright, level + 1);

}

void	show_tree(ft::map<int, std::string> & mymap)
{
	int	level = 0;
	int height = static_cast<int>(mymap.tree_->root_->height);
	ft::Tree<int, std::string, std::less<int>, std::allocator<std::pair<const int, std::string> > >::Node * tmp;
	std::cout << "___START SHOW TREE___" << std::endl;
	tmp = mymap.tree_->root_;
	show_node(tmp, level);
	
	for (; level < height; ++level)
	{
		std::multimap<int,int>::iterator it1 = multi.begin();
		std::multimap<int,int>::iterator it2 = multi.end();
		for( ; it1 != it2; ++it1)
		{
			if (it1->first == level)
				std::cout << ' ' << it1->second << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << "___FINISH SHOW TREE___" << std::endl;
}
void	show_tree(ft::map<int, int> & mymap)
{
	int	level = 0;
	int height = static_cast<int>(mymap.tree_->root_->height);
	ft::Tree<int, int, std::less<int>, std::allocator<std::pair<const int, int> > >::Node * tmp;
	std::cout << "___START SHOW TREE___" << std::endl;
	tmp = mymap.tree_->root_;
	show_node(tmp, level);

	for (; level < height; ++level)
	{
		std::multimap<int,int>::iterator it1 = multi2.begin();
		std::multimap<int,int>::iterator it2 = multi2.end();
		for( ; it1 != it2; ++it1)
		{
			if (it1->first == level)
				std::cout << ' ' << it1->second << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << "___FINISH SHOW TREE___" << std::endl;
}

template <class T, class U>
void	map_info(ft::map<T, U> & mymap)
{
	std::cout << "Final: root is: " << mymap.tree_->root_->value.first << ". Size is: " << mymap.tree_->size_;
	std::cout << ". Height is: " << static_cast<unsigned>(mymap.tree_->root_->height) << std::endl;
}

int	main()
{
	// ft::pair<int, std::string> pair1(2, "Notebook");
	// std::cout << pair1.first << ' ' << pair1.second << std::endl;

	std::cout << "/* ********************* insert() *********************** */" << std::endl;
	{
		// ft::map<int, std::string> mymap;
		// mymap.insert(ft::make_pair<int, std::string>(1, "1.3"));
		// mymap.insert(ft::make_pair<int, std::string>(2, "2.3"));
		// for(int i = 0; i < 10; i++)
		// 	mymap.insert(ft::make_pair<int, std::string>(i, "aaa"));
		// std::cout << ". Size is: " << mymap.tree_->size_ << std::endl;
	}
	{
		// ft::map<int, int> mp;
		// std::vector<int> v;
		// mp.insert(ft::make_pair(7, 7));
		// mp.insert(ft::make_pair(9, 9));
		// std::cout << "size: " << mp.size() << std::endl;
		// ft::map<int, int>::iterator itx = mp.begin();
		// for (; itx != mp.end(); ++itx) {
		// 	std::cout << itx->first << ' ';
		// }
		// std::cout << std::endl;
		// show_tree(mp);
		// for (int i = 0, j = 0; i < 10; ++i, ++j) { //default 500
		// 	mp.insert(ft::make_pair(i, j));
		// }
		// show_tree(mp);
		// ft::map<int, int>::iterator it3 = mp.begin();
		// for (; it3 != mp.end(); ++it3) {
		// 	v.push_back(it3->first);
		// 	v.push_back(it3->second);
		// }
		// v.push_back(mp.size());
		// std::cout << "size: " << mp.size() << std::endl;
		// ft::map<int, int>::iterator ity = mp.begin();
		// for (; ity != mp.end(); ++ity) {
		// 	std::cout << ity->first << ' ';
		// }
		// std::cout << std::endl;
	}
	std::cout << "/* ********************* insert() *********************** */" << std::endl;
	std::cout << "/* ********************* iterator *********************** */" << std::endl;

	ft::map<int, int> mp;
    std::vector<int> v;
    std::cout << mp.size() << '\n';

    ft::map<int, int> mp0;
	mp0.insert(ft::make_pair<int, int>(3,3));
    //ft::map<int, int>::iterator ii = mp0.insert(ft::make_pair(3, 3)).first; //sega
	ft::map<int, int>::iterator ii = mp0.begin();
    ii++;
    v.push_back((--ii)->first);
	std::cout << "/* ********************* iterator *********************** */" << std::endl;
	std::cout << "/* ********************* erase() *********************** */" << std::endl;
	// mymap.erase(3);
	// mymap.erase(5);
	// mymap.erase(1);
	// mymap.erase(2);
	// mymap.erase(6);
	// mymap.erase(7);
	// mymap.erase(8);
	// mymap.erase(9);
	// //mymap.erase(4);
	// map_info<int, std::string>(mymap);
	// show_tree(mymap);
	{
	// 	ft::map<int, int> mp;
	// 	std::vector<int> v;
	// 	v.push_back(mp.erase(3));
	// 	for (int i = 0, j = 0; i < 300000 ; ++i, ++j)
	// 		mp.insert(ft::make_pair(i, j));
	// 	ft::map<int, int>::iterator it = mp.begin();
	// 	v.push_back(it->first);
	// 	v.push_back(mp.erase(-5));
	// 	v.push_back(mp.size());
	// 	v.push_back(mp.erase(0));
	// 	v.push_back(mp.size());
	// 	it = mp.begin();
	// 	v.push_back(it->first);
	// 	ft::map<int, int>::iterator it4 = mp.begin();
	// 	for (; it4 != mp.end(); it4 = mp.begin())
	// 		mp.erase(it4->first);
	// 	ft::map<int, int>::iterator it2 = mp.end();
    // 	it2--;
	// 	ft::map<int, int> mp2;
	// 	for (int i = 0, j = 0; i < 10 ; ++i, ++j) //default 10
	// 		mp2.insert(ft::make_pair(i, j));
	// 	mp2.erase(2);
	// 	mp2.erase(7);
	// 	show_tree(mp2);
	// 	std::cout << "size=" << mp2.size() << '\n';
	// 	ft::map<int, int>::iterator it3 = mp2.begin();
	// 	for (; it3 != mp2.end(); ++it3) {
	// 		std::cout << "it3->first=" << it3->first << '\n';
	// 		sleep(1);
	// 	}
	}
	std::cout << "/* ********************* erase() *********************** */" << std::endl;
	std::cout << "/* ********************* clear() *********************** */" << std::endl;
	{
		// ft::map<int, int> mp;
		// std::vector<int> v;
		// mp.clear();
		// for (int i = 0, j = 0; i < 250000; ++i, ++j)
		// 	mp.insert(ft::make_pair(i, j));
		// v.push_back(mp.size());
		// mp.clear();
		// v.push_back(mp.size());
		// std::cout << "size =" << mp.size() << '\n';
		// ft::map<int, int>::iterator it = mp.begin();
		// if (it == mp.end())
		// 	v.push_back(1);
	}
	std::cout << "/* ********************* clear() *********************** */" << std::endl;
	std::cout << "/* ********************* size() *********************** */" << std::endl;

	std::cout << "/* ********************* size() *********************** */" << std::endl;
	// map_info<int, std::string>(mymap);
	// show_tree(mymap);

	// std::cout << "        tree address= " << mymap.tree_ << std::endl;
	// std::cout << "        root address= " << mymap.tree_->root_ << std::endl;
	// std::cout << "       value address= " << &mymap.tree_->root_->value << std::endl;
	// std::cout << "       begin address= " << mymap.tree_->quasiBegin_ << std::endl;
	// std::cout << "         end address= " << mymap.tree_->quasiEnd_ << std::endl;

	// ft::map<int, std::string>::iterator it;
	// it  = mymap.begin();
	// if (it == NULL) { std::cout << "\"ITERATOR IS NULL!!!\"" << std::endl; }
	// for(int plus = 0; plus < 5; ++plus)
	// 	++it;
	// it++;
	// for(int minus = 0; minus < 5; ++minus)
	// 	--it;
	// it--;

	// std::cout << "after ++ it.begin= " << it->first << std::endl;
	// ft::pair<const int, std::string> &	for_adr = *it;
	// std::cout << "it.begin address= " << &for_adr << std::endl;
	// std::cout << "mymap address= " << &mymap << std::endl;

	// ft::map<int, std::string>::iterator it_tmp;
	// it_tmp = it;
	// for(int plus = 0; plus < 5; ++plus)
	// 	++it_tmp;
	// ft::map<int, std::string> newmap(it, it_tmp);

	// it  = mymap.end();

	// std::cout << "it.end= " << it->first << std::endl;
	// mymap.insert(ft::pair<int, std::string>(1003, "notebook"));
	// mymap.insert(ft::make_pair<int, std::string>(100, "notebook"));
	// map_info<int, std::string>(mymap);
	// map_info<int, std::string>(newmap);
	// ft::map<int, std::string> copymap;
	// copymap = newmap;

	// std::cout << "it.find= " << (mymap.find(100))->first << std::endl;
	// mymap.clear();
	// std::cout << ". Size is: " << mymap.tree_->size_ << std::endl;
	
	// ft::map<int, int> mp;
	
    // std::vector<int> v;

    // mp.insert(ft::make_pair<int, int>(1, 5));
	// std::cout << "         end address= " << mp.tree_->quasiEnd_ << std::endl;
    // for (int i = 0, j = 10; i < 10; ++i, ++j) { //default 300000
    //     mp.insert(ft::make_pair(i, j));
    // }
	// ft::map<int, int>::iterator it_mp00 = mp.begin();

	// for (int i = 0; i < 10; ++i)
	// {
	// 	++it_mp00;
	// 	std::cout << "it_mp00= " << it_mp00->first << std::endl;
	// }

	// ft::map<int, int>::iterator it_mp01 = mp.end();// --it_mp01;
	// std::cout << "it_mp01= " << it_mp01->first << std::endl;
	// std::cout << "         end address= " << mp.tree_->quasiEnd_ << std::endl;




	return 0;
}