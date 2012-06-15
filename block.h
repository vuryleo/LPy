#pragma once

#include "type.h"
#include "expression.h"
#include "managers.h"
#include <vector>
#include <string>

using namespace std;


class sentence
{
public:
	virtual Type_obj* exec()=0;
	static variable_mnger v_mnger;
protected:
	int indent;
};

class line:public sentence
{
public:
	line& set(string aline);
	line(string aline){set(aline);};
	int get_indent();
	Type_obj* exec();
	bool isIf();
	bool isWhile();
	expression getCondition();
private:
	string origin;
	expression exp;
	vector<word> parseline(string aline);
	string::iterator getOpr(string& aline, string::iterator st);
	string::iterator getVariable(string& aline,string::iterator st);
	string::iterator getNumber(string& aline,string::iterator st);
	string::iterator getPrint(string& aline,string::iterator st);
	string::iterator getWhile(string& aline,string::iterator st);
	string::iterator getIf(string& aline,string::iterator st);
	string::iterator getTrue(string& aline,string::iterator st);
	string::iterator getFalse(string& aline,string::iterator st);
	string::iterator getBlank(string& aline, string::iterator st);
	string::iterator getStr(string& aline, string::iterator st);
	string::iterator getBreak(string& aline, string::iterator st);
};

class block:public sentence
{
public:
	block& push(line&);
	block& push(block&);
	Type_obj* exec();
	Type_obj* run();
	line load(int,int=0,expression=expression());
private:
	int depth;
	int type;
	expression condition;
	vector<line> lines;
	vector<block> blocks;
	vector<int> sentences;
};

