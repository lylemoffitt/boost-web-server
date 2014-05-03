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
	ofstream outfile;
	
	ss << whom << level;
	string Level(ss.str());
	
	outfile.open(Level , ofstream::app);
	
	time ( &rawtime );
	timeinfo = localtime ( &rawtime ); 
	
	outfile << asctime (timeinfo) + info << endl;
	outfile.close();
}
