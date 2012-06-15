#include "managers.h"
#include "type.h"
#include <sstream>
#include <iostream>

using namespace std;

bool variable_mnger::defined(string name)
{
	return getByName(name)!=npos;
}

Type_obj* variable_mnger::varCon(int v)
{
	string s;
	stringstream ss;
	ss << v;
	ss >> s;
	Type_obj* rel;
	if((rel=getByName(s))!=npos)
		return rel;
	Type_obj* newCon=var();
	newCon->value=v;
	constants.insert(pair<string,Type_obj*>(s,newCon));
	return newCon;
}

Type_obj* variable_mnger::varCon(string s)
{
	Type_obj* rel;
	if((rel=getByName(s))!=npos)
		return rel;
	if(!s.empty())
	{
		Type_obj* newCon;
		newCon=var();
		newCon->value=s;
		constants.insert(pair<string,Type_obj*>(s,newCon));
		return newCon;
	}
	return npos;
};

Type_obj* variable_mnger::getByName(string name)
{
//	cout << "Get: " << name << endl;
	if(name.empty())
		return npos;
	if((name[0]>='a' && name[0] <='z')||(name[0]>='A' && name[0]<='Z') || name[0]=='_')
	{
		local::iterator rel(variables.find(name));
		if(rel!=variables.end())
			return rel->second;
	}
	else
	{
		local::iterator rel(constants.find(name));
		if(rel!=constants.end())
			return rel->second;
	}
	return npos;
}

Type_obj* variable_mnger::var()
{
	return new Type_obj;
}

Type_obj* variable_mnger::var(string name)
{
	if(getByName(name)!=npos)
		return NULL;//throw Errmsg("Variable " +name+ " have been defined");
	Type_obj* newvariable=var();
	variables.insert(pair<string,Type_obj*>(name,newvariable));
	return newvariable;
}

variable_mnger::~variable_mnger()
{
	for(local::iterator i=constants.begin();i!=constants.end();i++)
		delete i->second;
	for(local::iterator i=variables.begin();i!=variables.end();i++)
		delete i->second;

}

Type_obj* variable_mnger::npos=NULL;
