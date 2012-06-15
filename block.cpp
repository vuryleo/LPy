#include "mode.h"
#include "error.h"
#include "block.h"
#include "managers.h"
#include <string>
#include <iostream>

using namespace std;

bool line::isIf()
{
	return exp.isIf();
}

bool line::isWhile()
{
	return exp.isWhile();
}

expression line::getCondition()
{
	return exp.getCondition();
}

line& line::set(string aline)
{
	origin=aline;
	indent=0;
	if(aline.empty())
		return *this;
	vector<word> words=parseline(aline);
	exp.set(words);
	return *this;
}

vector<word> line::parseline(string aline)
{
	string::iterator i;
	for(i=aline.begin();i!=aline.end();i++)
		if(*i!='\t' && *i!=' ')
			break;
		else
			indent++;
	aline.erase(aline.begin(),i);
	aline.append(" ");
	i=aline.begin();
	vector<word> words;
	while(i!=aline.end())
	{
		string::iterator end;
		if((end=getBlank(aline,i))!=aline.end())
		{
			i=end;
		}
		else if(getTrue(aline,i)!=aline.end())
		{
			words.push_back(word("NUM","1"));
			i+=string("True").length();
		}
		else if(getFalse(aline,i)!=aline.end())
		{
			words.push_back(word("NUM","0"));
			i+=string("False").length();
		}
		else if(getIf(aline,i)!=aline.end())
		{
			words.push_back(word("OR","IF"));
			i+=string("if").length();
		}
		else if(getWhile(aline,i)!=aline.end())
		{
			words.push_back(word("OR","WHILE"));
			i+=string("while").length();
		}
		else if((end=getPrint(aline,i))!=aline.end())
		{
			words.push_back(word("OR","PRINT"));
			i+=string("print").length();
		}
		else if((end=getBreak(aline,i))!=aline.end())
		{
			words.push_back(word("OR","BREAK"));
			i+=string("break").length();
		}
		else if((end=getNumber(aline,i))!=aline.end())
		{
			words.push_back(word("NUM",string(i,end)));
			i=end;
		}
		else if((end=getVariable(aline,i))!=aline.end())
		{
			words.push_back(word("VAR",string(i,end)));
			i=end;
		}else if((end=getOpr(aline,i))!=aline.end())
		{
			string buf(i,end);
			if(buf=="-" && words.back().type != "NUM" && words.back().type!="VAR")
				buf+="-";
			words.push_back(word("OR",buf));
			i=end;
		}
		else if((end=getStr(aline,i))!=aline.end())
		{
			words.push_back(word("NUM",string(i,end)));
			i=end;
			i=end;
		}else{
			break;
		}
	}
	return words;
}

string::iterator line::getStr(string& aline, string::iterator st)
{
	if(*st=='\"')
	{
		st++;
		while(st!=aline.end() && *st!='\"')
			st++;
		if(*st=='\"')
			st++;
		return st;
	}
	return aline.end();
}

string::iterator line::getOpr(string& aline, string::iterator st)
{
	if(*st=='<' || *st=='>' || *st=='+' || *st=='-' || *st=='*' || *st=='/' || *st=='%' || *st=='=' || *st=='!')
	{
		st++;
		if(*st=='=')
			st++;
		return st;
	}
	if(*st=='(' || *st==')' || *st=='[' || *st==']' || *st==':')
		return ++st;
	return aline.end();
}

string::iterator line::getVariable( string& aline,string::iterator st)
{
	if((*st>='a' && *st<='z') || (*st>='A' && *st<='Z') || *st=='_')
	{
		st++;
		while((*st>='a' && *st<='z') || (*st>='A' && *st<='Z') || *st=='_' || (*st>='0' && *st<='9'))
			st++;
		return st;
	}
	return aline.end();
}

string::iterator line::getNumber( string& aline,string::iterator st)
{
	if(*st>='0' && *st<='9')
	{
		while(*st>='0' && *st<='9')
			st++;
		return st;
	}
	return aline.end();
}

string::iterator line::getBreak( string& aline,string::iterator st)
{
	string w("break");
	if(aline.end()-st<w.length())
		return aline.end();
	string::iterator ed=st+w.length();
	string buf(st,ed);
	if(w==buf && (ed==aline.end() || !((*ed>='a' && *ed<='z') || (*ed>='A' && *ed<='Z') || (*ed>='0' && *ed<='9') || *ed=='_')))
		return st+w.length();
	return aline.end();
}

string::iterator line::getTrue( string& aline,string::iterator st)
{
	string w("True");
	if(aline.end()-st<w.length())
		return aline.end();
	string::iterator ed=st+w.length();
	string buf(st,ed);
	if(w==buf && (ed==aline.end() || !((*ed>='a' && *ed<='z') || (*ed>='A' && *ed<='Z') || (*ed>='0' && *ed<='9') || *ed=='_')))
		return st+w.length();
	return aline.end();
}

string::iterator line::getFalse( string& aline,string::iterator st)
{
	string w("False");
	if(aline.end()-st<w.length())
		return aline.end();
	string::iterator ed=st+w.length();
	string buf(st,ed);
	if(w==buf && (ed==aline.end() || !((*ed>='a' && *ed<='z') || (*ed>='A' && *ed<='Z') || (*ed>='0' && *ed<='9') || *ed=='_')))
		return st+w.length();
	return aline.end();
}

string::iterator line::getPrint( string& aline,string::iterator st)
{
	string w("print");
	if(aline.end()-st<w.length())
		return aline.end();
	string::iterator ed=st+w.length();
	string buf(st,ed);
	if(w==buf && (ed==aline.end() || !((*ed>='a' && *ed<='z') || (*ed>='A' && *ed<='Z') || (*ed>='0' && *ed<='9') || *ed=='_')))
		return st+w.length();
	return aline.end();
}

string::iterator line::getWhile( string& aline,string::iterator st)
{
	string w("while");
	if(aline.end()-st<w.length())
		return aline.end();
	string buf(st,st+w.length());
	if(w==buf && (st+w.length()==aline.end() || *(st+w.length())=='\t' || *(st+w.length())==' '))
		return st+w.length();
	return aline.end();
}

string::iterator line::getIf( string& aline,string::iterator st)
{
	string w("if");
	if(aline.end()-st<w.length())
		return aline.end();
	string buf(st,st+w.length());
	if(w==buf && (st+w.length()==aline.end() || *(st+w.length())=='\t' || *(st+w.length())==' '))
		return st+w.length();
	return aline.end();
}

string::iterator line::getBlank( string& aline, string::iterator st)
{
	if(*st!='\t' && *st!=' ')
		return aline.end();
	while(st!=aline.end() && (*st=='\t' || *st==' '))
		st++;
	return st;
}

int line::get_indent()
{
	return indent;
}

block& block::push(line& aline)
{
	lines.push_back(aline);
	sentences.push_back(bool(false));
	return *this;
}

block& block::push(block& ablock)
{
	blocks.push_back(ablock);
	sentences.push_back(bool(true));
	return *this;
}

Type_obj* line::exec()
{
	return exp.exec();
}

Type_obj* block::run()
{
	int ln=0,bn=0;
	for(int i=0;i<sentences.size();i++)
		if(sentences[i])
			blocks[bn++].exec();
		else
			lines[ln++].exec();
	return NULL;
}

Type_obj* block::exec()
{
	if(type==0)
		run();
	else if(type==1 && condition.isTrue())
		run();
	else if(type==2)
	{
		try{
			while(condition.isTrue())
				run();
		}catch(int breaksignal){}
	}
	return NULL;
}

line block::load(int s_indent, int s_type, expression s_expression)
{
	depth=s_indent;
	type=s_type;
	condition=s_expression;
	while(!mode::input->eof())
	{
		string aline;
		getline(*mode::input,aline);
		line newline(aline);
		int indent=newline.get_indent();
		if(indent==depth)
		{
			while(true)
			{
				if(newline.isIf())
				{
					block subblock;
					newline=subblock.load(depth+1,1,newline.getCondition());
					if(depth==0)
						subblock.exec();
					else
						push(subblock);
				}
				else if(newline.isWhile())
				{
					block subblock;
					newline=subblock.load(depth+1,2,newline.getCondition());
					if(depth==0)
						subblock.exec();
					else
						push(subblock);
				}else
					break;
			}
			if(type==0)
				newline.exec();
			else if(newline.get_indent()==depth)
				push(newline);
			else
				return newline;
		}
		else
			return newline;
	}
	return line("");
}
