//
//  users.h
//  WebSystemsFinal
//
//  Created by Lyle Moffitt on 4/22/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#ifndef __WebSystemsFinal__users__
#define __WebSystemsFinal__users__

#include <iostream>

//#include <map>
#include <string>
#include <functional>
#include <queue>
#include <unordered_set>

#include <boost/random.hpp>

#include <mutex>

class user;
class user_set;

static 
std::hash<std::string> str_hasher;


class user
{
    // Dynamic information
    double          priority;
    bool            busy;//mutex for priority
    
    std::chrono::time_point<std::chrono::system_clock> last_login;
    
    
    
    friend          user_set;
    
public:
    //Static information
    const 
    std::string     username;
    const
    size_t          pswd_hash;
    const
    size_t          name_hash;
    
    
    user(std::string _username, std::string _password);/*:
    username(_username), pswd_hash( str_hasher(_password) ),
    name_hash( str_hasher(_username) ), busy(false)
    {
    }*/
    
    // check that login matches
    bool authenticate(std::string u_name, std::string u_pswd) const;
    
    double  get_prio();
    
    void    set_prio(double val);
    
    bool operator==(user const& u_ref)const
    {
        return u_ref.name_hash == name_hash ;
    }
    
    
};


// hash specialization needed for user set storage
template <>
struct std::hash<user>
{
    inline size_t operator()(user const& u_ref) const
    {   return u_ref.name_hash ;  
    }
};



struct user_set
{
    std::unordered_set< user > id_table;
    
    void add_user(user & u_ref)
    {
        id_table.insert( u_ref );
    }

};


#endif /* defined(__WebSystemsFinal__users__) */
