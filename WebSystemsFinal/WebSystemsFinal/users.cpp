//
//  users.cpp
//  WebSystemsFinal
//
//  Created by Lyle Moffitt on 4/22/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#include "users.h"


double  user::get_prio();
{
    return priority;
}

void    user::set_prio(double val)
{
    priority = val;
}

bool authenticate(std::string u_name, std::string u_pswd)
{
    return (u_name == username  &&  str_hasher(u_pswd)==pswd_hash);
}