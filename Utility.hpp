#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace ft {

template<bool Condition, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };

template <class T1, class T2>
struct pair
{
	typedef	T1	first_type;
	typedef	T2	second_type;
	first_type	first;
	second_type	second;

	pair()
		:first(), second() {}
	pair (const first_type& a, const second_type& b)
		:first(a), second(b) {}
	template<class U, class V>  //copy constructor
	pair (const pair<U,V>& pr)
		:first(pr.first), second(pr.second) {}
	~pair() {}
	pair&	operator=(const pair& pr)
	{
		first = pr.first;
		second = pr.second;
		return *this;
	}
	first_type getFirst() { return first; }
	second_type getSecond() { return second; }
};

template <class T1, class T2>
bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return lhs.first==rhs.first && lhs.second==rhs.second; }

template <class T1, class T2>
bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return !(lhs==rhs); }

template <class T1, class T2>
bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

template <class T1, class T2>
bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return !(rhs<lhs); }

template <class T1, class T2>
bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return rhs<lhs; }

template <class T1, class T2>
bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return !(lhs<rhs); }

template <class T1, class T2>
pair<T1,T2>	make_pair(T1 x, T2 y)
{
	return ft::pair<T1, T2>(x, y);
}

template<class T, bool v>
struct integral_constant
{
	static const bool value = v;
	typedef	T					value_type;
	typedef	integral_constant	type;
	operator value_type() const { return value; }
};
template <class T> struct is_integral: public ft::integral_constant<T, false> {};
template <> struct is_integral<bool>: public ft::integral_constant<bool, true> {};
template <> struct is_integral<char>: public ft::integral_constant<bool, true> {};
template <> struct is_integral<char16_t>: public ft::integral_constant<bool, true> {};
template <> struct is_integral<char32_t>: public ft::integral_constant<bool, true> {};
template <> struct is_integral<wchar_t>: public ft::integral_constant<bool, true> {};
template <> struct is_integral<signed char>: public ft::integral_constant<bool, true> {};
template <> struct is_integral<short int>: public ft::integral_constant<bool, true> {};
template <> struct is_integral<int>: public ft::integral_constant<bool, true> {};
template <> struct is_integral<long int>: public ft::integral_constant<bool, true> {};
template <> struct is_integral<long long int>: public ft::integral_constant<bool, true> {};
template <> struct is_integral<unsigned char>: public ft::integral_constant<bool, true> {};
template <> struct is_integral<unsigned short int>: public ft::integral_constant<bool, true> {};
template <> struct is_integral<unsigned int>: public ft::integral_constant<bool, true> {};
template <> struct is_integral<unsigned long int>: public ft::integral_constant<bool, true> {};
template <> struct is_integral<unsigned long long int>: public ft::integral_constant<bool, true> {};


} //end of namespace ft

#endif