#include <bits/stdc++.h>
#include "var.hpp"

using namespace std;

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
