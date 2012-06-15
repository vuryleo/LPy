#include "error.h"
#include "expression.h"
#include "managers.h"
#include "block.h"
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

bool expression::isVar()
{
	return mainopr.name.empty() && key.type=="VAR";
}

bool expression::isTrue()
{
	return exec()->value!="0";
}

bool expression::isIf()
{
	return mainopr.name=="#" && subexpressions[0].mainopr.name=="IF";
}

bool expression::isWhile()
{
	return mainopr.name=="#" && subexpressions[0].mainopr.name=="WHILE";
}

expression expression::getCondition()
{
	if(isIf() || isWhile())
		return subexpressions[0].subexpressions[0];
	return expression();
}

Type_obj* expression::exec()
{
	//cout << *this << endl;
	if (mainopr.name.empty())
	{
		if (key.type=="VAR")
		{
			Type_obj* rel = sentence::v_mnger.getByName(key.name);
			if(!rel)
				throw Errmsg(string("Error: Variable \"")+ key.name+"\" not defined");
			return rel;
		}
		else if(key.type=="NUM")
		{
			sentence::v_mnger.varCon(key.name);
			return sentence::v_mnger.getByName(key.name);
		}
	}
	else if(mainopr.name=="#")
	{
		if(!subexpressions.empty())
			return subexpressions.front().exec();
		return NULL;
	}
	else
	{
		vector<expression>::iterator i=subexpressions.begin();
		vector<Type_obj*> results;
		if(mainopr.name=="=")
			i++;
		for(;i!=subexpressions.end();i++)
			results.push_back(i->exec());
		if(mainopr.name=="BREAK")
			throw 1;
		else if(mainopr.name=="=")
		{
			if(subexpressions.front().isVar() && !sentence::v_mnger.defined(subexpressions.front().key.name))
				sentence::v_mnger.var(subexpressions.front().key.name);
			(sentence::v_mnger.getByName(subexpressions.front().key.name)->value=results.front()->value);
			return sentence::v_mnger.getByName(subexpressions.front().key.name);
		}
		else if(mainopr.name=="PRINT")
		{
			cout << *results.back() << endl;
			return results.back();
		}
		else if(mainopr.name=="+")
			return sentence::v_mnger.varCon((*results.front()+*results.back()).value);
		else if(mainopr.name=="-")
			return sentence::v_mnger.varCon((*results.front()-*results.back()).value);
		else if(mainopr.name=="*")
			return sentence::v_mnger.varCon((*results.front()* *results.back()).value);
		else if(mainopr.name=="/")
			return sentence::v_mnger.varCon((*results.front()/ *results.back()).value);
		else if(mainopr.name=="%")
			return sentence::v_mnger.varCon((*results.front()% *results.back()).value);
		else if(mainopr.name=="--")
			return sentence::v_mnger.varCon((- *results.back()).value);
		else if(mainopr.name=="<")
			return sentence::v_mnger.varCon((*results.front()<*results.back()).value);
		else if(mainopr.name==">")
			return sentence::v_mnger.varCon((*results.front()>*results.back()).value);
		else if(mainopr.name=="==")
			return sentence::v_mnger.varCon((*results.front()==*results.back()).value);
		else if(mainopr.name=="!=")
			return sentence::v_mnger.varCon((*results.front()!=*results.back()).value);
		else if(mainopr.name=="!")
			return sentence::v_mnger.varCon((! *results.back()).value);
	}
	return NULL;
}

expression& expression::set(vector<word> words)
{
	stack<expression> exp;
	stack<opr> oprs;
	oprs.push(opr("#"));
	for(vector<word>::iterator i=words.begin();i!=words.end();i++)
	{
		if(i->type=="VAR")
			exp.push(expression(*i));
		else if(i->type=="OR")
			if(i->name=="(")
				oprs.push(opr(i->name));
			else if(i->name==":")
			{
				while(oprs.top().name!="IF" && oprs.top().name!="WHILE")
				{
					vector<expression> subs;
					if(oprs.top().name=="--" || oprs.top().name=="IF" || oprs.top().name=="WHILE")
					{
						subs.push_back(exp.top());
						exp.pop();
					}else{
						subs.push_back(exp.top());
						exp.pop();
						subs.push_back(exp.top());
						exp.pop();
						reverse(subs.begin(),subs.end());
					}
					exp.push(expression(oprs.top(),subs));
					oprs.pop();
				}
				vector<expression> subs;
				subs.push_back(exp.top());
				exp.pop();
				exp.push(expression(oprs.top(),subs));
				oprs.pop();
			}
			else if(i->name==")")
			{
				while(oprs.top().name!="(")
				{
					vector<expression> subs;
					if(oprs.top().name=="--" || oprs.top().name=="IF" || oprs.top().name=="WHILE" || oprs.top().name=="PRINT")
					{
						subs.push_back(exp.top());
						exp.pop();
					}else{
						subs.push_back(exp.top());
						exp.pop();
						subs.push_back(exp.top());
						exp.pop();
						reverse(subs.begin(),subs.end());
					}
					exp.push(expression(oprs.top(),subs));
					oprs.pop();
				}
				oprs.pop();
			}
			else
			{
				opr buf(i->name);
				while(oprs.top().getImp() > buf.getImp() || 
						(oprs.top().getImp() == buf.getImp() && buf.getLeft()))
				{
					vector<expression> subs;
					if(oprs.top().name=="--" || oprs.top().name=="IF" || oprs.top().name=="WHILE" || oprs.top().name=="PRINT")
					{
						subs.push_back(exp.top());
						exp.pop();
					}else{
						subs.push_back(exp.top());
						exp.pop();
						subs.push_back(exp.top());
						exp.pop();
						reverse(subs.begin(),subs.end());
					}
					exp.push(expression(oprs.top(),subs));
					oprs.pop();
				}
				oprs.push(buf);
			}
		else if(i->type=="NUM")
			exp.push(expression(*i));
	}
	while(oprs.top().name!="#")
	{
		vector<expression> subs;
		if(oprs.top().name=="BREAK")
			;
		else if(oprs.top().name=="--" || oprs.top().name=="IF" || oprs.top().name=="WHILE" || oprs.top().name=="PRINT")
		{
			subs.push_back(exp.top());
			exp.pop();
		}else{
			subs.push_back(exp.top());
			exp.pop();
			subs.push_back(exp.top());
			exp.pop();
			reverse(subs.begin(),subs.end());
		}
		exp.push(expression(oprs.top(),subs));
		oprs.pop();
	}
	oprs.pop();
	mainopr.name="#";
	if(!exp.empty())
		subexpressions.push_back(exp.top());
	return *this;
}

