#pragma once

#include "Export.h"
#include <iostream>
#include <initializer_list>
#include <exception>
#include <math.h>
#include "Vec3.h"

template<class T, unsigned int line=3, unsigned int column=line>
class Matrix
{
public:
	static Matrix<T, line> identity()
	{

		Matrix<T, line> result;
		for (int i = 0; i < line; ++i)
		{
			result.tab[i][i] = static_cast<T>(1);
		}

		return result;
	}
	// Constructeurs
	Matrix(const T& t = static_cast<T>(0))
		: tab(nullptr)
	{
		allocateTab();
		for (int i = 0; i < line; i++)
		{
			for (int j = 0; j < column; j++)
			{
				this->tab[i][j] = t;
			}
		}
	}
	template<class T1>
	Matrix(const Matrix<T1, line, column>& m)
		: tab(nullptr)
	{
		allocateTab();
		for (int i = 0; i < line; ++i)
		{
			for (int j = 0; j < column; ++j)
			{
				this->tab[i][j] = static_cast<T>(m(i, j));
			}
		}
	}
	template<class T1>
	Matrix(Matrix<T1, line, column>&& m)
		: tab(nullptr)
	{
		allocateTab();
		for (int i = 0; i < line; ++i)
		{
			for (int j = 0; j < column; ++j)
			{
				this->tab[i][j] = static_cast<T>(m(i, j));
			}
		}
	}
	Matrix(const std::initializer_list<T> list)
		: tab(nullptr)
	{
		allocateTab();
		try
		{
			if (list.size() != line * column)
			{
				throw std::exception("Invalid number of arguments\n");
			}
			else
			{
				int i = 0;

				auto it = std::begin(list);

				while (it != std::end(list))
				{
					for (int j = 0; j < column; j++)
					{
						this->tab[i][j] = *it++;
					}
					i++;
				}
			}
		}
		catch (const std::exception & e)
		{
			std::cerr << e.what();
		}
	}
	~Matrix()
	{
		for (unsigned int i = 0; i < line; ++i)
		{
			delete[] tab[i];
 		}
		delete[] tab;
	}

	// Operators
	Matrix<T, line, column>& operator=(const Matrix<T, line, column>& m)
	{
		for (int i = 0; i < line; i++)
		{
			for (int j = 0; j < column; j++)
			{
				this->tab[i][j] = m(i, j);
			}
		}

		return *this;
	}
	Matrix<T, line, column>& operator=(Matrix<T, line, column>&& m)
	{
		for (int i = 0; i < line; ++i)
		{
			for (int j = 0; j < column; ++j)
			{
				this->tab[i][j] = m(i, j);
			}
		}

		return *this;
	}
	T operator()(const unsigned int& i, const unsigned int& j) const
	{
		try
		{
			if (i >= line || j >= column)
			{
				throw std::exception("Case non existante\n");
			}
			return this->tab[i][j];
		}
		catch (std::exception & e)
		{
			std::cerr << e.what();
		}
	}
	T& operator()(const unsigned int& i, const unsigned int& j)
	{
		try
		{
			if (i >= line || j >= column)
			{
				throw std::out_of_range("Out of range\n");
			}
			return this->tab[i][j];
		}
		catch (std::out_of_range & e)
		{
			std::cerr << e.what();
		}
	}
	template<class T1>
	Matrix<T, line, column>& operator+=(const T1& t)
	{
		operate([](T& mValue, T1 value) { return (static_cast<T>(mValue += value)); }, t);

		return *this;
	}
	template<class T1>
	Matrix<T, line, column>& operator-=(const T1& t)
	{
		operate([](T& mValue, T1 value) { return (static_cast<T>(mValue -= value)); }, t);

		return *this;
	}
	template<class T1>
	Matrix<T, line, column>& operator*=(const T1& t)
	{
		operate([](T& mValue, T1 value) { return (static_cast<T>(mValue *= value)); }, t);

		return *this;
	}
	template<class T1>
	Matrix<T, line, column>& operator/=(const T1& t)
	{
		try
		{
			if (t == 0)
			{
				throw std::exception("Can't divide by 0");
			}
			else
			{
				operate([](T& mValue, T1 value) { return (static_cast<T>(mValue /= value)); }, t);

				return *this;
			}
		}
		catch (std::exception & e)
		{
			std::cerr << e.what();
		}
	}
	template<class T1>
	void operator+=(const Matrix<T1, line, column>& m)
	{
		{
			for (int i = 0; i < line; ++i)
			{
				for (int j = 0; j < column; ++j)
				{
					this->tab[i][j] += m(i, j);
				}
			}
		}
	}
	template<class T1>
	void operator-=(const Matrix<T1, line, column>& m)
	{
		for (int i = 0; i < line; ++i)
		{
			for (int j = 0; j < column; ++j)
			{
				this->tab[i][j] += m(i, j);
			}
		}
	}
	// this.column must be equal to M2.line
	template<class T1, unsigned int column_2>
	auto operator*(const Matrix<T1, column, column_2>& m2)
	{
		// We must use a pointer, otherwise result.tab gets deleted
		Matrix<decltype(this->tab[0][0] * m2(0, 0)), line, column_2> result;
		for (int i = 0; i < line; ++i)
		{
			for (int j_2 = 0; j_2 < column_2; ++j_2)
			{
				for (int i_2 = 0; i_2 < column; ++i_2)
				{
					result(i, j_2) += this->tab[i][i_2] * m2(i_2, j_2);
				}
			}
		}

		return result;
	}

	//Functions 
	static Matrix<T, column, line> transpose(const Matrix<T, line, column>& m)
	{
		Matrix<T, column, line> result;

		for (int i = 0; i < line; i++)
		{
			for (int j = 0; j < column; j++)
			{
				result(j, i) = m(i, j);
			}
		}

		return result;
	}
	template<class T1>
	static Matrix<T, 4> translate(Matrix<T, 4>& m, const Vec3<T1>& translation)
	{
		m(3, 0) = translation.x;
		m(3, 1) = translation.y;
		m(3, 2) = translation.z;

		return m;
	}
	template<class T1, class T2>
	static Matrix<T, 4> rotate(Matrix<T, 4>& m, const T1& rotation, const Vec3<T2>& axis)
	{
		if (axis.x)
		{
			m.rotateX(rotation);
		}
		else if (axis.y)
		{
			m.rotateX(rotation);
		}
		else if (axis.z)
		{
			m.rotateX(rotation);
		}
	}
	template<class T1>
	static Matrix<T, 4> scale(Matrix<T, 4>& m, const Vec3<T1>& scale)
	{
		m(0, 0) += scale.x;
		m(1, 1) += scale.y;
		m(2, 2) += scale.z;

		return m;
	}
	template<class T1>
	static Matrix<T, 4> rotateX(Matrix<T, 4>& m, const T1& rotation)
	{
		m(1, 1) += cos(rotation);
		m(1, 2) += sin(rotation);
		m(2, 1) -= sin(rotation);
		m(2, 2) += cos(rotation);

		return m;
	}
	template<class T1>
	static Matrix<T, 4> rotateY(Matrix<T, 4>& m, const T1& rotation)
	{
		m(0, 0) += cos(rotation);
		m(2, 0) += sin(rotation);
		m(0, 2) -= sin(rotation);
		m(2, 2) += cos(rotation);

		return m;
	}
	template<class T1>
	static Matrix<T, 4> rotateZ(Matrix<T, 4>& m, const T1& rotation)
	{
		m(0, 0) += cos(rotation);
		m(0, 1) += sin(rotation);
		m(1, 0) -= sin(rotation);
		m(1, 1) += cos(rotation);

		return m;
	}
	template<class T1, class T2, class T3>
	static Matrix<double, 4> tranformation(const Vec3<T1>& translation, const Vec3<T2>& rotation, const Vec3<T3>& scale)
	{
		Matrix<double, 4> m = Matrix<double, 4>::identity();
		m = Matrix<double, 4>::translate(m, translation);
		m = Matrix<double, 4>::rotateX(m, rotation.x);
		m = Matrix<double, 4>::rotateY(m, rotation.y);
		m = Matrix<double, 4>::rotateZ(m, rotation.z);
		m = Matrix<double, 4>::scale(m, scale);

		return m;
	}
	
private:
	T **tab;

	void allocateTab()
	{
		tab = new T* [line];
		for (unsigned int i = 0; i < line; ++i)
			tab[i] = new T[column];
	}
	// The template parameter can be either a functor or a lambda function
	template <class Function>
	Matrix<T, line, column>& operate(Function op, const double& value)
	{
		for (int i = 0; i < line; i++)
		{
			for (int j = 0; j < column; j++)
			{
				op(this->tab[i][j], value);
			}
		}
		return *this;
	}
};

template<class T, unsigned int line, unsigned int column, class T1>
Matrix<T, line, column> operator+(const Matrix<T, line, column>& m, const T1& t)
{
	Matrix<T, line, column> result;
	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j < column; j++)
		{
			result(i, j) = m(i, j) + t;
		}
	}

	return result;
}
template<class T, unsigned int line, unsigned int column, class T1>
Matrix<T, line, column> operator-(const Matrix<T, line, column>& m, const T1& t)
{
	Matrix<T, line, column> result;
	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j < column; j++)
		{
			result(i, j) = m(i, j) - t;
		}
	}

	return result;
}
template<class T, unsigned int line, unsigned int column, class T1>
Matrix<T, line, column> operator*(const Matrix<T, line, column>& m, const T1& t)
{
	Matrix<T, line, column> result;
	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j < column; j++)
		{
			result(i, j) = m(i, j) * t;
		}
	}

	return result;
}
template<class T, unsigned int line, unsigned int column, class T1>
Matrix<T, line, column> operator/(const Matrix<T, line, column>& m, const T1& t)
{
	try
	{
		if (t == 0)
		{
			throw std::exception("Can't divide by 0");
		}
		else
		{
			Matrix<T, line, column> result;
			for (int i = 0; i < line; i++)
			{
				for (int j = 0; j < column; j++)
				{
					result(i, j) = m(i, j) / t;
				}
			}

			return result;
		}
	}
	catch (std::exception & e)
	{
		std::cerr << e.what();
	}
}
template<class T = int, unsigned int line, unsigned int column>
std::ostream& operator<<(std::ostream& os, const Matrix<T, line, column>& m)
{
	for (int i = 0; i < line; i++)
	{
		os << "[";
		for (int j = 0; j < column; j++)
		{
			T t = m(i, j);
			os << t << ((j == column - 1) ? "" : " ");
		}
		os << "]" << std::endl;
	}

	return os;
}

// Usefull type def
typedef Matrix<float, 3>		Mat3f;
typedef Matrix<double, 3>		Mat3d;
typedef Matrix<unsigned int, 3>	Mat3u;
typedef Matrix<int, 3>			Mat3i;
typedef Matrix<float, 4>		Mat4f;
typedef Matrix<double, 4>		Mat4d;
typedef Matrix<unsigned int, 4>	Mat4u;
typedef Matrix<int, 4>			Mat4i;

