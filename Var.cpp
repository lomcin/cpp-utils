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
	map<uint, Var> b;
	VarData data;
	
	public:
	Var(){};

	template<typename DataType>	
	Var(DataType v) {
		data = (DataType) v;
	}
	Var &operator[](const uint el) {
		return b[el];
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
	
};

int main () {
	Var s;
	s[1]= 4;
	s[2][2]= 333.444f;
	s[0][1][2]= false;
	s[2][3][3][3][4][5][6][10] = 5656;
	s[3][1]= (char) 'k';
	s[3][123] = (string)"draweawe";
	char as = s[3][1];
	int af = s[1];
	string str = s[3][123];
	Var b = 42;
	cout << "b : " << (int) b << endl;
	
	cout << "s[1]: " << af << endl;
	cout << "s[2][2]: " << (float)s[2][2]<< endl;
	cout << "s[2][3][3][3][4][5][6][10]: " << (int)s[2][3][3][3][4][5][6][10] << endl;
	cout << "s[3][1] char : '" << as << "'" << endl;
	cout << "0 1 2 is " << (s[0][1][2]? "" : " NOT") << " true" << endl;
	cout << "s[3][123] string : " << (string&) s[3][123] << " - " << str << endl;
	return 0;
}
