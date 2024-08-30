#pragma once
#include <array>
#include <initializer_list>
#include <stdexcept>
#include <format>
template<typename T = double, size_t N = 2>
class Vector
{
public:
	Vector()
	{
		if (N < 1) throw std::length_error("Number of dimensions of a vector couldn't be zero.");
	}
	Vector(std::initializer_list<T> l)
	{
		if (N < 1) throw std::length_error("Number of dimensions of a vector couldn't be zero.");
		if (l.size() < N) throw std::length_error(std::format("The input must be equal or greater than {}.", N));
		for (int i = 0; i < N; i++)
		{
			v.at(i) = l.begin()[i];
		}
	}
	

	//T& x() { return v.at(0); }
	//T& y() { return v.at(1); }

	T& at(size_t idx) { return v.at(idx); }
	const T& at(size_t idx) const { return v.at(idx); }

	T& operator[](size_t idx) { return v[idx]; }
	const T& operator[](size_t idx) const { return v[idx]; }

	Vector<T, N>& operator=(const Vector<T, N>& vec)
	{
		for (int i = 0; i < N; i++)
		{
			this->at(i) = vec.at(i);
		}
		return *this;
	}

	bool operator==(const Vector<T, N>& val)
	{
		return (this->at(0) == val.at(0) && this->at(1) == val.at(1));
	}

	// operator
	Vector<T, N> operator+(const Vector<T, N>& val) const
	{
		Vector<T, N> ans;
		for (int i = 0; i < N; i++)
		{
			ans.at(i) = this->at(i) + val.at(i);
		}
		return ans;
	}
	Vector<T, N>& operator+=(const Vector<T, N>& val)
	{
		for (int i = 0; i < N; i++)
		{
			this->at(i) += val.at(i);
		}
		return *this;
	}

	Vector<T, N> operator-(const Vector<T, N>& val) const
	{
		Vector<T, N> ans;
		for (int i = 0; i < N; i++)
		{
			ans.at(i) = this->at(i) - val.at(i);
		}
		return ans;
	}
	Vector<T, N>& operator-=(const Vector<T, N>& val)
	{
		for (int i = 0; i < N; i++)
		{
			this->at(i) -= val.at(i);
		}
		return *this;
	}

	Vector<T, N> operator*(const T& val) const
	{
		Vector<T, N> ans;
		for (int i = 0; i < N; i++)
		{
			ans.at(i) = this->at(i) * val;
		}
		return ans;
	}
	Vector<T, N>& operator*=(const T& val)
	{
		for (int i = 0; i < N; i++)
		{
			this->at(i) *= val;
		}
		return *this;
	}

	Vector<T, N> operator/(const T& val) const
	{
		Vector<T, N> ans;
		for (int i = 0; i < N; i++)
		{
			ans.at(i) = this->at(i) / val;
		}
		return ans;
	}
	Vector<T, N>& operator/=(const T& val)
	{
		for (int i = 0; i < N; i++)
		{
			this->at(i) /= val;
		}
		return *this;
	}




	T dot(const Vector<T, N>& val) const
	{
		T ans = (T)0;
		for (int i = 0; i < N; i++)
		{
			ans += this->at(i) * val.at(i);
		}
		return ans;
	}
	static T dot(const Vector<T, N>& vec1, const Vector<T, N>& vec2)
	{
		return vec1.dot(vec2);
	}

	T distance(const Vector<T, N>& point)
	{
		T ans=0;
		T tmp;
		for(int i = 0; i < N; i++)
		{
			tmp = this->at(i)-point.at(i);
			ans += tmp*tmp;
		}
		return std::sqrt(ans);
	}
	static T distance(const Vector<T, N>& point1, const Vector<T, N>& point2)
	{
		return point1.distance(point2);
	}

	T length()
	{
		T ans=0;
		for(int i = 0; i < N; i++)
		{
			ans += this->at(i)*this->at(i);
		}
		return std::sqrt(ans);
	}
	// warning: check if length != 0
	Vector<T, N> unit()
	{
		if (this->length() == (T)0)
		{
			Vector<T, N> ans;
			ans.at(0) = 1;
			for (int i = 0; i < N; i++)
			{
				ans.at(0) = 0;
			}
			return ans;
		}
		return (*this) / this->length();
	}
	static Vector<T, N> unit(const Vector<T, N>& vec)
	{
		return vec.unit();
	}



private:
	std::array<T, N> v;
};

template<typename T = double, size_t N = 2>
Vector<T, N> operator*(const T& val, const Vector<T, N> vec)
{
	return vec * val;
}

template<typename T = double, size_t N = 2>
Vector<T, N> operator/(const T& val, const Vector<T, N> vec)
{
	return vec / val;
}

template<typename T, size_t N>
std::ostream& operator<<(std::ostream& out, const Vector<T, N>& vec)
{
	out << "Vector(";
	for (int i = 0; i < N - 1; i++)
	{
		out << vec.at(i);
	}
	out << vec.at(N - 1) << ")";
}