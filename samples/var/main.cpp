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

#include <bits/stdc++.h>
#include "Var.hpp"

using namespace std;

void mixedSample()
{
	Var s;
	s[1] = 4;
	s[2][2] = 333.444f;
	s[0][1][2] = false;
	s[2][3][3][3][4][5][6][10] = 5656;
	s[3][1] = (char)'k';
	s[3][123] = (string) "draweawe";
	char as = s[3][1];
	int af = s[1];
	string str = s[3][123];

	cout << "s[1]: " << af << endl;
	cout << "s[2][2]: " << (float)s[2][2] << endl;
	cout << "s[2][3][3][3][4][5][6][10]: " << (int)s[2][3][3][3][4][5][6][10] << endl;
	cout << "s[3][1] char : '" << as << "'" << endl;
	cout << "0 1 2 is " << (s[0][1][2] ? "" : " NOT") << " true" << endl;
	cout << "s[3][123] string : " << (string &)s[3][123] << " - " << str << endl;
}

void intSample()
{
	// int assignment doesn't require defining the cast
	var b = 42;
	// But recovering it, does require defining the cast
	cout << "b : " << (int)b << endl;
	cout << "b : " << b.toInt() << endl;
}

void stringSample()
{
	// Example of how to save or use string from c++
	var hello = string("Hello World");
	// Example of how many ways of recovering a string from Var
	cout << hello.toString() << endl;
	cout << to_string(hello) << endl;
	cout << std::to_string(hello) << endl;
}

void loopVarSample()
{
	// For example using only "var"
	var i = 0;
	var limit = 3;
	while (i.toInt() < limit.toInt())
	{
		cout << i.toInt() << endl;
		i++;
	}
}

void iterableDataSample()
{
	// Iterable data
	var points;
	for (var k = 0; k.toInt() < 3; k++)
	{
		points[k.toInt()]["x"] = k.toInt() * 1;
		points[k.toInt()]["y"] = k.toInt() * 1;
		points[k.toInt()]["z"] = k.toInt() * 1;
	}

	// Recover iterable data
	for (var l = 0; l.toInt() < points.length(); l++)
	{ // Note that we use length() here
		cout
			<< "(" << points[l.toInt()]["x"].toInt()
			<< " " << points[l.toInt()]["y"].toInt()
			<< " " << points[l.toInt()]["z"].toInt()
			<< ")" << endl;
	}
}

int main()
{

	mixedSample();
	intSample();
	// stringSample();
	loopVarSample();
	iterableDataSample();

	return 0;
}
