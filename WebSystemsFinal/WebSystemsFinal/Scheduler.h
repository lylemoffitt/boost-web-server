//
//  Scheduler.h
//  WebSystemsFinal
//
//  Created by Lyle Moffitt on 4/22/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#ifndef __WebSystemsFinal__Scheduler__
#define __WebSystemsFinal__Scheduler__

#include <iostream>

#include <boost/circular_buffer.hpp>
#include <queue>
#include <vector>
#include <functional>

#include "httpServer.h"
#include "security.h"
#include "users.h"
#include "Logger.h"
//#include "Scheduler.h"
#include "fileHandler.h"

#include "allofit.h"
//point in time
#define timestamp size_t
#define thepresent

class box
{
public:
    user* to_user;
    double interval;
    std::string filename;
    size_t data_sum;
    size_t age_time;
    timestamp time_point;
    tcpConnection* tcp;
    
    void calcInterval();
    size_t send_time(){return interval;}
    
};


class scheduler
{
    boost::circular_buffer<box> ringBuffer;
    double highest, lowest, median;
    allofit     &       _aott;
    
public:
    scheduler(allofit &_alloi):_aott(_alloi){}
    
    void add_to_sched(box &customer);
    box take_next();
    void update();
       
};



#endif /* defined(__WebSystemsFinal__Scheduler__) */



