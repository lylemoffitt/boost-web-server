//
//  main.cpp
//  WebSystemsFinal
//
//  Created by Lyle Moffitt on 4/22/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#include <iostream>

#include "allofit.h"

using namespace std;

int main(int argc, const char * argv[])
{
    allofit _a;
    string usr_pswd;
    while(true)
    {
        // connect client to server
    
    
    
        // open page asking for what joke
    
    
    
    
        // use file handler to retrieve page
        _a.getJoke(usr_pswd);
    
    
        // ask if want another joke
        bool again = false;

    
        //if yes, repeat. otherwise close connection
        if(again == true)
        {
            _a.getJoke(usr_pswd);
        }
    
    
        //wait for more clients
    }
    
    std::cout << "Hello, World!\n";
    return 0;
}

