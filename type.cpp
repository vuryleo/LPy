#include "type.h"
#include <sstream>

using namespace std;


Type_obj Type_obj::operator + (const Type_obj& p)
{
	Type_obj ans;
	if(!p.value.empty())
		if(p.value[0]=='\"')
			ans.value=value+p.value;
		else
		{
			stringstream ss,tt;
			ss << value;
			int s,t;
			ss >> s;
			tt << p.value;
			tt >> t;
			int rel=s+t;
			stringstream rr;
			rr << rel;
			rr >> ans.value;
		}
	return ans;
}

Type_obj Type_obj::operator - (const Type_obj& p)
{
	Type_obj ans;
	if(!p.value.empty())
	{
		stringstream ss,tt;
		ss << value;
		int s,t;
		ss >> s;
		tt << p.value;
		tt >> t;
		int rel=s-t;
		stringstream rr;
		rr << rel;
		rr >> ans.value;
	}
	return ans;
}

Type_obj Type_obj::operator * (const Type_obj& p)
{
	Type_obj ans;
	if(!p.value.empty())
	{
		stringstream ss,tt;
		ss << value;
		int s,t;
		ss >> s;
		tt << p.value;
		tt >> t;
		int rel=s*t;
		stringstream rr;
		rr << rel;
		rr >> ans.value;
	}
	return ans;
}

Type_obj Type_obj::operator -()
{
	Type_obj ans;
	if(!value.empty())
	{
		stringstream ss;
		ss << value;
		int s;
		ss >> s;
		int rel=-s;
		stringstream rr;
		rr << rel;
		rr >> ans.value;
	}
	return ans;
}

Type_obj Type_obj::operator / (const Type_obj& p)
{
	Type_obj ans;
	if(!p.value.empty())
	{
		stringstream ss,tt;
		ss << value;
		int s,t;
		ss >> s;
		tt << p.value;
		tt >> t;
		int rel=s/t;
		stringstream rr;
		rr << rel;
		rr >> ans.value;
	}
	return ans;
}

Type_obj Type_obj::operator % (const Type_obj& p)
{
	Type_obj ans;
	ans.value="0";
	if(!p.value.empty())
	{
		stringstream ss,tt;
		ss << value;
		int s,t;
		ss >> s;
		tt << p.value;
		tt >> t;
		int rel=s%t;
		stringstream rr;
		rr << rel;
		rr >> ans.value;
	}
	return ans;
}

Type_obj Type_obj::operator > (const Type_obj& p)
{
	Type_obj ans;
	ans.value="0";
	if(!p.value.empty())
	{
		stringstream ss,tt;
		ss << value;
		int s,t;
		ss >> s;
		tt << p.value;
		tt >> t;
		if(s > t)
			ans.value="1";
	}
	return ans;
}

Type_obj Type_obj::operator < (const Type_obj& p)
{
	Type_obj ans;
	ans.value="0";
	if(!p.value.empty())
	{
		stringstream ss,tt;
		ss << value;
		int s,t;
		ss >> s;
		tt << p.value;
		tt >> t;
		if(s < t)
			ans.value="1";
	}
	return ans;
}

Type_obj Type_obj::operator == (const Type_obj& p)
{
	Type_obj ans;
	ans.value="0";
	if(!p.value.empty())
		if(value == p.value)
			ans.value="1";
	return ans;
}

Type_obj Type_obj::operator != (const Type_obj& p)
{
	Type_obj ans;
	ans.value="0";
	if(!p.value.empty())
		if(value != p.value)
			ans.value="1";
	return ans;
}

Type_obj Type_obj::operator ! ()
{
	Type_obj ans;
	ans.value="0";
	if(!value.empty())
	{
		stringstream ss;
		ss << value;
		int s;
		ss >> s;
		if(!s)
			ans.value="1";
	}
	return ans;
}
