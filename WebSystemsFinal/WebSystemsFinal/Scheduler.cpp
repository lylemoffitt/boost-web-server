//
//  Scheduler.cpp
//  WebSystemsFinal
//
//  Created by Lyle Moffitt on 4/22/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#include "Scheduler.h"

using namespace std;

scheduler::scheduler()
{
    
}

void scheduler::add_to_sched(box &customer)
{
    customer.calcInterval();
    ringBuffer.push(customer);    
}        

Box* scheduler::take_next()
{
    return ringBuffer.pop_front();
}    

void box::calcInterval()
{
    size_t data;
    size_t time; 
    
    for (auto it = _file_handler.file_map.begin();
            it != _file_handler.file_map.end(); it++)
    {
        if(_file_handler.filename == filename)    
            data = _file_handler.file_size;
    }
    
    interval = data/time;
}