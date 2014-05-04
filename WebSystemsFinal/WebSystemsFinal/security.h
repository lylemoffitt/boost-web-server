//
//  security.h
//  WebSystemsFinal
//
//  Created by Lyle Moffitt on 4/22/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#ifndef __WebSystemsFinal__security__
#define __WebSystemsFinal__security__

#include <iostream>
#include <string>
#include <ctime>
#include <functional>

#include "allofit.h"


class security
{
    allofit     &       _aott;
    
public:
    
    security(allofit & _all):_aott(_all)
    {}
    
    
    
    bool chk_id(std::string usrnm, std::string pswd);
    
    user mk_user(std::string usrnm, std::string pswd);
    
    void report_fake(std::string usrnm, std::string pswd);
    
    void interrogate();
};


#endif /* defined(__WebSystemsFinal__security__) */

