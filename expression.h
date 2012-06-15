#pragma once
#include "operators.h"
#include "managers.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class word
{
public:
	string name;
	string type;
	word(string s_type,string s_name){name=s_name;type=s_type;};
	word(){};
	friend ostream& operator << (ostream& s, word aword)
	{
		s << aword.type << ' ' << aword.name;
		return s;
	}
};

class expression
{
public:
	expression(){};
	expression& set(vector<word>);
	expression(word s_key):key(s_key){};
	expression(opr s_opr,vector<expression> s_sub){mainopr=s_opr;subexpressions=s_sub;};
	~expression(){};
	Type_obj* exec();
	bool isTrue();
	bool isIf();
	bool isWhile();
	expression getCondition();
	friend ostream& operator << (ostream& s, expression exp)
	{
		if(exp.mainopr.name.empty())
			s << exp.key << ' ';
		else
		{
			s << exp.mainopr << ' ';
			for(vector<expression>::iterator i=exp.subexpressions.begin();i!=exp.subexpressions.end();i++)
				s << *i << ' ';
		}
		return s;
	}
private:
	bool isVar();
	opr mainopr;
	word key;
	vector<expression> subexpressions;
};


