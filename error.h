#pragma once
#include <string>
#include <iostream>

using namespace std;

class Errmsg
{
private:
	string msg;
public:
	Errmsg(string s_msg):msg(s_msg){};
	friend ostream& operator << (ostream& s, Errmsg a)
	{
		s << a.msg << endl;
		return s;
	}
};

