//
//  allofit.h
//  WebSystemsFinal
//
//  Created by Lyle Moffitt on 5/3/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#ifndef __WebSystemsFinal__allofit__
#define __WebSystemsFinal__allofit__

#include <iostream>
#include <string> 
#include <boost/circular_buffer.hpp>
#include <queue>
#include <vector>
#include <functional>


class allofit;
class user;
class user_set;
class scheduler;
class file_handler;
class logger;


#include "Logger.h"
#include "users.h"
#include "fileHandler.h"

struct connection_ptr
{
    bool done(){return true;}
    bool isBusy(){return false;}
    void writeData(){return;}
    std::string getData(){return "";}
};

//#include "HTTPserver/connection.h"

class box : public file_handler
{
public:
    user*                   to_user;
    double                  interval;
    std::string             filename;
    size_t                  data_sum;
    connection_ptr*           tcp;
    //allofit*              _aott;
    void 
        calcInterval();
    size_t 
        send_time(){return interval;}
    void 
        serviceLoop();
    box():to_user(nullptr),tcp( nullptr)
    {}
    box(user & usr_ref):to_user(&usr_ref)
    {}
    
};


class allofit
{
public:
    allofit()//: _file_handler (*this)
    {}
    
//    tcpServer      _httpserver; //tcp server
        
    user_set        _user_set;
    
    logger          _logger;
    
    file_handler    _file_handler;
 
    
    
    std::unordered_map<std::string, box> ringBuffer;
    double highest, lowest, median, ratio;
    
public:

    
    void add_to_sched(box &customer);
    // *** don't need this, just index the map with the username *** //
    //box take_next();
    void update(std::string usr);
    

    
    //user* member;
    connection_ptr*             tcp;
    // gets intro file fro file handler
    // passes file through TCP
    // gets response (usrnm and pswd)
    // checks usrnm and pswd with security
    // if correct, enter
    // otherwise, send create user form
    // auto create
    // log size of intro file and signup file 
    // sum should be updated in box in scheduler
    // create send time in box time in scheduler
    std::string send_hello();
    // while{
    //     sends form asking what joke they want
    //     get joke from file handler
    //     record
    //     ask if another
    //     get next joke
    //     wait user's interval 
    // }
    // until exit
    
    
    void getJoke(std::string usr_pswd);
    
    bool chk_id(std::string usrnm, std::string pswd);
    
    user mk_user(std::string usrnm, std::string pswd);
    
    void report_fake(std::string usrnm, std::string pswd);
    
    void interrogate();
};





#endif /* defined(__WebSystemsFinal__allofit__) */
