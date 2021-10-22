#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <ostream>
#include <list>
#include <exception>

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

	friend	std::ostream& operator<<(std::ostream & os, const Vector & rhs);
private:
	int		size_;
	int		capacity_;
	int*	array_;
};

#endif