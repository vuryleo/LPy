#include "LPy.h"
#include <iostream>
#include <fstream>

using namespace std;


variable_mnger sentence::v_mnger;
istream* mode::input;
ifstream mode::infile;

void readargs(int argc, char** argv);

int main(int argc, char **argv)
{
	readargs(argc,argv);
	try{
		block mainblock;
		mainblock.load(0);
	}catch(Errmsg themsg)
	{
		cerr << themsg;
		return 1;
	}
	return 0;
}

void readargs(int argc, char** argv)
{
	if(argc==1)
	{
		mode::input=&cin;
		return ;
	}
	else
	{
		string filename(argv[1]);
		mode::infile.open(filename.c_str());
		if(!mode::infile.is_open())
			cerr << string("Can't open file ")+filename << endl;
		mode::input = &mode::infile;
	}
}
