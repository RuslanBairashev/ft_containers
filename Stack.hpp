#ifndef STACK_HPP
#define STACK_HPP

#include "Vector.hpp"

namespace ft
{
	template < class T, class Container >
	class stack;
	template < class T, class Container >
	bool	operator==(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
	{
		return lhs.cont_ == rhs.cont_;
	}
	template < class T, class Container >
	bool	operator!=(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
	{
		return lhs.cont_ != rhs.cont_;
	}
	template < class T, class Container >
	bool	operator<(stack<T, Container> & lhs, stack<T, Container> & rhs)
	{
		return lhs.cont_ < rhs.cont_;
	}
	template < class T, class Container >
	bool	operator>(stack<T, Container> & lhs, stack<T, Container> & rhs)
	{
		return lhs.cont_ > rhs.cont_;
	}
	template < class T, class Container >
	bool	operator>=(stack<T, Container> & lhs, stack<T, Container> & rhs)
	{
		return lhs.cont_ >= rhs.cont_;
	}
	template < class T, class Container >
	bool	operator<=(stack<T, Container> & lhs, stack<T, Container> & rhs)
	{
		return lhs.cont_ <= rhs.cont_;
	}
	/*************************************************************************/
	//**	CLASS DECLARATION START											**/
	/*************************************************************************/
	template < class T, class Container = ft::vector<T> >
	class stack
	{
	public:
		typedef	T					value_type;
		typedef	Container			container_type;
		typedef	size_t				size_type;
	protected:
		container_type		cont_;
	public:
		//constructor: default
		explicit stack (const container_type& ctnr = container_type()): cont_(ctnr) {}
		~stack() {}

	/*************************************************************************/
	//			MEMBER FUNCTIONS										      /
	/*************************************************************************/
		bool empty() const { return cont_.empty(); }

		void pop()
		{
			cont_.pop_back();
		}

		void push (const value_type& val)
		{
			cont_.push_back(val);
		}

		size_type size() const { return cont_.size(); }

		value_type& top() { return cont_.back(); }
		const value_type& top() const { return cont_.back(); }

		//Non-member function overloads
		/*************************************************************************/
		friend	bool	operator== <> (const stack & lhs, const stack & rhs);
		friend	bool	operator!= <> (const stack & lhs, const stack & rhs);
		friend	bool	operator< <> (stack & lhs, stack & rhs);
		friend	bool	operator> <> (stack & lhs, stack & rhs);
		friend	bool	operator>= <> (stack & lhs, stack & rhs);
		friend	bool	operator<= <> (stack & lhs, stack & rhs);
	};

	/***************************************************************************/
	//			END OF CLASS													/
	/***************************************************************************/

}	//end namespace ft
#endif