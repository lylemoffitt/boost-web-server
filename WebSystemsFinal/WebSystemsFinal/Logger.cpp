//
//  Logger.cpp
//  WebSystemsFinal
//
//  Created by Lyle Moffitt on 4/22/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#include "Logger.h"
#define SIZE 1000
using namespace std;

void logger::log(std::string whom, int level, std::string info)
{
	stringstream ss;
	ss << level;
	string Level(ss.str());
	int i = 0;
	ifstream infile;
	infile.open(Level);

	string doc[SIZE];

	while(!infile.eof)
	{
		infile >> doc[i];
		i++;
	}

	infile.close();

	ofstream outfile;

	outfile.open(Level);
	
	while(i>-1)
	{
		outfile << doc[i];	
	}
	outfile << whom + info;

	outfile.close();
	


}
