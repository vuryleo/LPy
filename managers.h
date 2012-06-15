#pragma once
#include "type.h"
#include <vector>

using namespace std;

class variable_mnger
{
public:
	Type_obj* getByName(string name);
	Type_obj* var(string name);
	Type_obj* varCon(string s);
	Type_obj* varCon(int v);
	Type_obj* var();
	bool defined(string);
	variable_mnger(){};
	~variable_mnger();
	static Type_obj* npos;
private:
	typedef map<string,Type_obj*> local;
	local variables;
	local constants;
};



