/*
MIT License

Copyright (c) 2020-2024 Lucas Maggi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef _H_VAR_H_
#define _H_VAR_H_

#include <string>
#include <map>
#include "VarData.hpp"

typedef unsigned int uint;

class Var
{
	VarData data;					  // data from construction or assignment
	std::map<std::string, Var> adata; // associative data
	std::map<uint, Var> idata;		  // iterable data

public:
	Var(){};

	template <typename DataType>
	Var(DataType v)
	{
		data = (DataType)v;
	}

	Var &operator[](const uint el)
	{
		return idata[el];
	}
	Var &operator[](const int el)
	{
		return idata[el];
	}

	Var &operator[](const std::string el)
	{
		return adata[el];
	}

	Var &operator[](const char *el)
	{
		return adata[el];
	}

	template <typename DataType>
	DataType &operator=(const DataType v)
	{
		data = (DataType)v;
		return (DataType &)(data);
	}

	template <typename DataType>
	DataType &set(const DataType &v)
	{
		data = (DataType)v;
		return (DataType &)(data);
	}

	template <typename DataType>
	operator DataType &()
	{
		return (DataType &)(data);
	}

	template <typename DataType>
	operator DataType & get()
	{
		return (DataType &)(data);
	}

	int &toInt()
	{
		return static_cast<int &>(data);
	}

	float &toFloat()
	{
		return static_cast<float &>(data);
	}

	double &toDouble()
	{
		return static_cast<double &>(data);
	}

	char &toChar()
	{
		return static_cast<char &>(data);
	}

	long &toLong()
	{
		return static_cast<long &>(data);
	}

	long long &toLongLong()
	{
		return static_cast<long long &>(data);
	}

	std::string &toString()
	{
		return static_cast<std::string &>(data);
	}

	int &operator++(int)
	{
		toInt()++;
		return static_cast<int &>(data);
	}

	size_t size()
	{
		size_t total_size = idata.size() + adata.size();
		return total_size;
	}

	size_t length()
	{
		return idata.size();
	}
};

// Added to_string overload
namespace std
{
	string to_string(Var v)
	{
		return static_cast<string &>(v);
	}
}
typedef Var var;

#endif // _H_VAR_H_