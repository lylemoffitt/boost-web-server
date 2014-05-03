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
    for (auto i = _aott._user_set.id_table.begin(); 
         i != _aott._user_set.id_table.end(); i++) 
    {
        i->
        
        if( (*i).username == usrnm)
            if( (*i).pswd_hash == str_hasher(pswd))
                return true;
    }
    report_fake(usrnm, pswd);
    return false;
}
    

user security::mk_user(string usrnm, string pswd)
{
    auto obj =  new user(usrnm, pswd) ;
    _aott._user_set.add_user(*obj);
}
    
void security::report_fake(string usrnm, string pswd)
{
    log("Security", 3, "\t\tFake user detected: " + usrnm + "\t" + pswd);
} 