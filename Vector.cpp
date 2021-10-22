#include "Vector.hpp"

Vector::Vector():
	size_(0),
	capacity_(10),
	array_(new int[capacity_])
{
}

Vector::~Vector()
{
	delete[] array_;
}

Vector::Vector(int elements, int value):
	size_(elements),
	capacity_(elements + 3),
	array_(new int[capacity_])
{
	for (int i = 0; i < size_; ++i)
		array_[i] = value;
}
Vector::Vector(const Vector & rhs):
	size_(rhs.size_),
	capacity_(rhs.capacity_),
	array_(new int[capacity_])
{
	for (int i = 0; i < rhs.size(); ++i)
		array_[i] = rhs.array_[i];
}
/*
Vector::Vector(const std::initializer_list<int> & list):
	size_(0),
	capacity_(list.size() + 3),
	array_(new int[capacity_])
{
	for(int i : list)
		push_back(i);
}
*/
void	Vector::push_back(int value)
{
	if (size_ < capacity_)
	{
		array_[size_] = value;
		++size_;
	}
	else
	{
		capacity_ *= 2;
		int*	newarray = new int[capacity_];
		for (int i = 0; i < size_; ++i)
			newarray[i] = array_[i];
		newarray[size_] = value;
		++size_;
		delete[] array_;
		array_ = newarray;
	}
}

void	Vector::pop_back()
{
	if (size_ == 0)
		throw std::runtime_error("Error: pop_back on empty cont!\n");
	--size_;
}

bool	Vector::empty() const
{
	return size_ == 0;
}

int		Vector::size() const
{
	return size_;
}

int		Vector::capacity() const
{
	return capacity_;
}

/*void	Vector::insert(int index, int value)
{

}*/

void	Vector::erase(int index)
{
	if (index < 0 || index >= size_)
		throw std::runtime_error("Error: (erase) out of range!\n");
	for (int i = index; i < size_; ++i)
		array_[i] = array_[i + 1];
	--size_;
}

void	Vector::clear()
{
	size_ = 0;
}

Vector&	Vector::operator=(const Vector& rhs)
{
	if (rhs.size_ > size_)
	{
		capacity_ = rhs.size_ + 3;
		delete[] array_;
		array_ = new int[capacity_];
	}
	for (int i = 0; i < rhs.size(); ++i)
		array_[i] = rhs.array_[i];
	size_ = rhs.size_;

	return *this;
}

bool	Vector::operator==(const Vector & rhs)	const
{
	if (size() != rhs.size())
		return false;
	for (int i = 0; i < size(); ++i)
	{
		if (array_[i] != rhs.array_[i])
			return false;
	}
	return true;
}

bool	Vector::operator!=(const Vector & rhs)	const
{
	return !(*this == rhs);
}

int&	Vector::operator[](int index)
{
	return array_[index];
}
int&	Vector::at(int index)
{
	if (index < 0 || index >= size_)
		throw std::runtime_error("Error: (at) out of range!\n");
	return array_[index];
}

int&	Vector::front()
{
	return array_[0];
}
int&	Vector::back()
{
	return array_[size_ - 1];
}

std::ostream& operator<<(std::ostream & os, const Vector & rhs)
{
	for (int i = 0; i < rhs.size(); ++i)
		os << rhs.array_[i] << " ";
	os << "//";
	for (int i = rhs.size_; i < rhs.capacity_; ++i)
		os << rhs.array_[i] << " ";
	os << std::endl;

	return os;
}