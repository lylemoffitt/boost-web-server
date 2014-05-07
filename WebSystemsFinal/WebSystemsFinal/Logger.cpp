//
//  Logger.cpp
//  WebSystemsFinal
//
//  Created by Lyle Moffitt on 4/22/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#include "Logger.h"
#define SIZE 1000
using namespace std;

void logger::log(std::string whom, int level, std::string info)
{
	stringstream ss;
	ofstream outfile;
	
	ss << whom << level;
	string Level(ss.str());
	
	outfile.open(Level , ofstream::app);
	
	time ( &rawtime );
	string time = ctime(&rawtime);
    time.at(time.size() - 1) = '\0';
	
	outfile << time + info << endl;
	outfile.close();
}
#endif