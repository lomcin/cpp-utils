#ifndef _H_VAR_H_
#define _H_VAR_H_

#include "BasicTypes.hpp"
#include "VarData.hpp"

class Var {
	VarData data; // data from construction or assignment
	std::unordered_map<std::string, Var> adata; // associative data
	std::unordered_map<uint, Var> idata; // iterable data
	
	public:
	Var(){};

	template<typename DataType>	
	Var(DataType v) {
		data = (DataType) v;
	}

	Var &operator[](const uint el) {
		return idata[el];
	}
	Var &operator[](const int el) {
		return idata[el];
	}

	Var &operator[](const std::string el) {
		return adata[el];
	}

	Var &operator[](const char* el) {
		return adata[el];
	}
	
	template<typename DataType>	
	DataType &operator=(const DataType v) {
		data = (DataType) v;
		return (DataType&)(data);
	}
	
	template<typename DataType>	
	operator DataType&() {
		return (DataType&)(data);
	}

	int &toInt() {
		return static_cast<int&>(data);
	}

	float &toFloat() {
		return static_cast<float&>(data);
	}

	double &toDouble() {
		return static_cast<double&>(data);
	}

	char &toChar() {
		return static_cast<char&>(data);
	}

	long &toLong() {
		return static_cast<long&>(data);
	}

	long long  &toLongLong() {
		return static_cast<long long &>(data);
	}

	std::string  &toString() {
		return static_cast<std::string &>(data);
	}
	
	int& operator++(int) {
		toInt()++;
		return static_cast<int&>(data);
	}

	size_t size() {
		size_t total_size = idata.size()
						  + adata.size();
		return total_size;
	}

	size_t length() {
		return idata.size();
	}
};

// Added to_string overload
namespace std {
	string to_string(Var v) {
		return static_cast<string&>(v);
	}
}
typedef Var var;

#endif // _H_VAR_H_