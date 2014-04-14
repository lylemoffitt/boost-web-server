// WebSystemsFinal.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include "stdafx.h"
#include <time.h>

using namespace std;

int main(int argc, char* argv[])
{
	cout << "Hi Lyle" << endl; 
	int wonerupper = 0;
	while(wonerupper < 5)
	{
		wonerupper = rand()%5 + 1;
			
		srand(time(0));
	
		switch(wonerupper)
		{
		case 1: 
			cout << "You win!" << endl;
			break;
		case 2:
			cout << "Ouch" << endl;
			break;
		case 3:	
			cout << "Just made it" << endl;
			break;
		case 4:
			cout << "Sucks to suck..." << endl;
			break;
		default:
			cout << "HIHIHIHIHIHIHIHIHIHI" << endl;
			break;
		}
	}
	return 0;
}

