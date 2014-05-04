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
#include "allofit.h"
//point in times
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
    
    public:
        scheduler();
        void add_to_sched(box &customer);
        box take_next();
        void update();
       
};



#endif /* defined(__WebSystemsFinal__Scheduler__) */



