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

	void	push_back(int value);
	void	pop_back();
	bool	empty() const;
	int		size() const;
	int		capacity() const;
	int&	at(int index);
	int&	front();
	int&	back();
	void	insert(int index, int value);
	void	erase(int index);
	void	clear();

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