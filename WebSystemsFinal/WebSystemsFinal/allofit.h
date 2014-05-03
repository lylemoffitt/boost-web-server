//
//  allofit.h
//  WebSystemsFinal
//
//  Created by Lyle Moffitt on 5/3/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#ifndef __WebSystemsFinal__allofit__
#define __WebSystemsFinal__allofit__


#include "httpServer.h"
#include "security.h"
#include "users.h"
#include "Logger.h"
#include "Scheduler.h"



struct allofit
{
    httpServer  _httpserver;
    
    security    _security;
    
    user_set    _user_set;
    
};




#endif /* defined(__WebSystemsFinal__allofit__) */
