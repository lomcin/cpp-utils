#include <bits/stdc++.h>
#include "var.hpp"

using namespace std;

void mixedSample() {
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

	cout << "s[1]: " 						<< af 								<< endl;
	cout << "s[2][2]: " 					<< (float)s[2][2] 					<< endl;
	cout << "s[2][3][3][3][4][5][6][10]: " 	<< (int)s[2][3][3][3][4][5][6][10] 	<< endl;
	cout << "s[3][1] char : '" 				<< as 								<< "'" 		<< endl;
	cout << "0 1 2 is " 					<< (s[0][1][2]? "" : " NOT") 		<< " true" 	<< endl;
	cout << "s[3][123] string : " 			<< (string&) s[3][123] 				<< " - " 	<< str << endl;
}

void intSample() {
	// int assignment doesn't require defining the cast
	var b = 42;
	// But recovering it, does require defining the cast
	cout << "b : " << (int) b 	<< endl;
	cout << "b : " << b.toInt() << endl;
}

void stringSample() {
	// Example of how to save or use string from c++
	var hello = string("Hello World");
	// Example of how many ways of recovering a string from Var
	cout << hello.toString() 		<< endl;
	cout << to_string(hello)		<< endl;
	cout << std::to_string(hello) 	<< endl;
}

void loopVarSample() {
	// For example using only "var"
	var i = 0;
	var limit = 3;
	while (i.toInt() < limit.toInt()) {
		cout << i.toInt() << endl;
		i++;
	}
}

void iterableDataSample() {
	// Iterable data
	var points;
	for (var k = 0; k.toInt() < 3; k++) {
		points[k.toInt()]["x"] = k.toInt()*1;
		points[k.toInt()]["y"] = k.toInt()*1;
		points[k.toInt()]["z"] = k.toInt()*1;
	}

	// Recover iterable data
	for (var l = 0; l.toInt() < points.length(); l++) { // Note that we use length() here
		cout 
		<< "(" << points[l.toInt()]["x"].toInt()
		<< " " << points[l.toInt()]["y"].toInt()
		<< " " << points[l.toInt()]["z"].toInt()
		<< ")" << endl;
	}
}

int main () {

	mixedSample();
	intSample();
	stringSample();
	loopVarSample();
	iterableDataSample();
	
	return 0;
}
