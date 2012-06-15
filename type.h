#pragma once

#include <map>
#include <string>
#include <iostream>

using namespace std;

class Type_obj
{
public:
	Type_obj(){};
	virtual ~Type_obj(){};
	string value;
	Type_obj operator + (const Type_obj&);
	Type_obj operator - (const Type_obj&);
	Type_obj operator - ();
	Type_obj operator * (const Type_obj&);
	Type_obj operator / (const Type_obj&);
	Type_obj operator % (const Type_obj&);
	Type_obj operator ! ();
	Type_obj operator < (const Type_obj&);
	Type_obj operator > (const Type_obj&);
	Type_obj operator == (const Type_obj&);
	Type_obj operator != (const Type_obj&);
	friend ostream & operator << (ostream& s, Type_obj p)
	{
		if(!p.value.empty())
			if(p.value[0]=='\"')
				s << string(p.value.begin()+1,p.value.end()-1);
			else
				s << p.value;
		return s;
	}
};

