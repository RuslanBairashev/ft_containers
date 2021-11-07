#ifndef VEXTRAS_HPP
#define VEXTRAS_HPP

template<bool Condition, class T = void>
struct enable_if {};
 
template<class T>
struct enable_if<true, T> { typedef T type; };

template<class T>
bool	is_integral(T){ return false; }

namespace ft {
template <class T1, class T2>
struct pair
{
	typedef	T1	first_type;
	typedef	T2	second_type;
	first_type	first;
	second_type	second;

	pair()
		:first(NULL), second(NULL) {}
	pair (const first_type& a, const second_type& b)
		:first(a), second(b) {}
	template<class U, class V>  //copy constructor
	pair (const pair<U,V>& pr)
		:first(pr.first), second(pr.second) {}
	~pair() {}
	/* operator=
	relational operators (pair) */
	first_type getFirst() { return first; }
	second_type getSecond() { return second; }
};
}


#endif