#include <bits/stdc++.h>

using namespace std;
typedef unsigned int uint;

class VarData {
	int *data;
	
	public:
	VarData() {
		data = NULL;
	}

	template<typename DataType>	
	VarData(DataType v) {
		data = (int*)new DataType(v);
	}

	~VarData() {
		if(data) delete data;
		data = NULL;
	}
	
	template<typename DataType>	
	DataType &operator=(const DataType v) {
		if (data) delete data;
		data = (int*)new DataType(v);
		return (DataType&)(*((DataType*)data));
	}
	
	template<typename DataType>	
	operator DataType&() {
		return (DataType&)(*((DataType*)this->data));
	}
};

class Var {
	VarData data; // data from construction or assignment
	map<string, Var> adata; // associative data
	map<uint, Var> idata; // iterable data
	
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

	Var &operator[](const string el) {
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

	string  &toString() {
		return static_cast<string &>(data);
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

namespace std {
	string to_string(Var v) {
		return static_cast<string&>(v);
	}
}
typedef Var var;

int main () {
	Var s;
	s[1]= 4;
	s[2][2]= 333.444f;
	s[0][1][2]= false;
	s[2][3][3][3][4][5][6][10] = 5656;
	s[3][1]= (char) 'k';
	s[3][123] = (string) "draweawe";
	char as = s[3][1];
	int af = s[1];
	string str = s[3][123];
	Var b = 42;
	cout << "b : " << (int) b << endl;
	var hello = string("Hello World");
	var i = 0;
	var limit = 3;


	cout << hello.toString() 		<< endl;
	cout << std::to_string(hello) 	<< endl;

	while (i.toInt() < limit.toInt()) {
		cout << i.toInt() << endl;
		i++;
	}
	
	var points;
	for (var k = 0; k.toInt() < 3; k++) {
		points[k.toInt()]["x"] = k.toInt()*1;
		points[k.toInt()]["y"] = k.toInt()*1;
		points[k.toInt()]["z"] = k.toInt()*1;
	}

	for (var l = 0; l.toInt() < points.length(); l++) {
		cout 
		<< "(" << points[l.toInt()]["x"].toInt()
		<< " " << points[l.toInt()]["y"].toInt()
		<< " " << points[l.toInt()]["z"].toInt()
		<< ")" << endl;
	}
	
	cout << "s[1]: " << af << endl;
	cout << "s[2][2]: " << (float)s[2][2]<< endl;
	cout << "s[2][3][3][3][4][5][6][10]: " << (int)s[2][3][3][3][4][5][6][10] << endl;
	cout << "s[3][1] char : '" << as << "'" << endl;
	cout << "0 1 2 is " << (s[0][1][2]? "" : " NOT") << " true" << endl;
	cout << "s[3][123] string : " << (string&) s[3][123] << " - " << str << endl;
	return 0;
}
