//
//  security.cpp
//  WebSystemsFinal
//
//  Created by Lyle Moffitt on 4/22/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#include "security.h"
#include <ctime>

using namespace std;

bool security::chk_id(string usrnm, string pswd)
{
    
    int i = 0;
    for (const string& x: all_users) 
    {
        if(all_users.id_table[i].username == usrnm)
            if(all_users.id_table[i].pswd_hash == str_hasher(pswd))
                return true;
        i++;
    }
    report_fake(usrnm, pswd);
    return false;
}
    

user security::mk_user(string usrnm, string pswd)
{
    user obj = new user(usrnam, pswd);
    all_users.add_user(&obj);
}
    
void security::report_fake(string usrnm, string pswd)
{
    log("Security", 3, "\t\tFake user detected: " + usrnm + "\t" + pswd);
} 