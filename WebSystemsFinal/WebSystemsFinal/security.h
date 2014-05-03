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
#include <chrono>

#include <functional>

#include "users.h"


class security
{
    
public:
    static
    bool chk_id(string usrnm, string pswd);
    
    static
    user mk_user(string usrnm, string pswd);
    
    void report_fake(string usrnm, string pswd);
    
};


#endif /* defined(__WebSystemsFinal__security__) */
