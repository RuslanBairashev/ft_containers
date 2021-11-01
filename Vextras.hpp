#ifndef VEXTRAS_HPP
#define VEXTRAS_HPP

template <class T1, class T2>
struct Vpair
{
	typedef	T1	first_type;
	typedef	T2	second_type;
	first_type	first;
	second_type	second;

	Vpair()
		:first(NULL), second(NULL) {}
	Vpair (const first_type& a, const second_type& b)
		:first(a), second(b) {}
	template<class U, class V>  //copy constructor
	Vpair (const Vpair<U,V>& pr)
		:first(pr.first), second(pr.second) {}
	/* operator=
	relational operators (pair) */

	
};


#endif