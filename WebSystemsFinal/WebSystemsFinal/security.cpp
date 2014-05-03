//
//  security.cpp
//  WebSystemsFinal
//
//  Created by Lyle Moffitt on 4/22/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#include "security.h"

using namespace std;

bool security::chk_id(string usrnm, string pswd)
{
    int i = 0;
    for (const string& x: user_set) 
    {
        if(user_set.id_table[i].username == usrnm)
            if(user_set.id_table[i].pswd_hash == str_hasher(pswd))
                return true;
        i++;
    }
    return false;
}
    

user security::mk_user(string usrnm, string pswd)
{
    user obj = new user(usrnam, pswd);
    user_set.add_user(&obj);
}
    
void security::report_fake()
{
    
}