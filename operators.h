#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class opr
{
public:
	opr(){};
	opr(string s_name):name(s_name){};
	int getImp();
	bool getLeft();
	string name;
	friend ostream& operator << (ostream& s, opr aopr)
	{
		s << aopr.name << ' ';
		return s;
	}
};

