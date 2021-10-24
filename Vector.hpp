#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <list>
#include <exception>
#include <memory>

template < class T, class Allocator = std::allocator<T> >
class Vector
{
public:
	Vector();
	Vector(int elements, int value = 0);
	Vector(const Vector & rhs);
	//Vector(const std::initializer_list<int> & list);

	~Vector();

	int&	at(int index);
	int&	back();
	int		capacity() const;
	void	clear();
	bool	empty() const;
	void	erase(int index);
	int&	front();
	void	insert(int index, int value);
	int		max_size() const;
	void	pop_back();
	void	push_back(const int & value);
	void	reserve(int n);
	int		size() const;
	
	Vector&	operator=(const Vector& rhs);
	bool	operator==(const Vector & rhs)	const;
	bool	operator!=(const Vector & rhs)	const;
	int&	operator[](int index);

	///template < class Tx, class Allocator = std::allocator<Tx> >
	///friend	std::ostream& operator<<(std::ostream &, const Vector &);
	//friend	std::ostream& operator<<(std::ostream & os, const Vector & rhs);
	template < class Tx, class Allocatorx >
	friend std::ostream& operator<<(std::ostream & os, const Vector<Tx, Allocatorx > & rhs)
	{
		for (int i = 0; i < rhs.size(); ++i)
			os << rhs.array_[i] << " ";
		os << "//";
		for (int i = rhs.size_; i < rhs.capacity_; ++i)
			os << rhs.array_[i] << " ";
		os << std::endl;

		return os;
	}
private:
	int		size_;
	int		capacity_;
	int*	array_;
	std::allocator<T>	myAlloc_;
};

#endif