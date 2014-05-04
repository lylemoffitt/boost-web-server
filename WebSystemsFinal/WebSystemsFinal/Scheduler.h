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


class scheduler
{
    boost::circular_buffer<box> ringBuffer;
    
    public:
        scheduler();
        void add_to_sched(box &customer);
        Box* take_next();
       
};


class box
{
    user* to_user;
    size_t interval;
    std::string filename;
    size_t sum;
    public:
        void calcInterval();
        size_t send_time(){return interval}
    
};
#endif /* defined(__WebSystemsFinal__Scheduler__) */
