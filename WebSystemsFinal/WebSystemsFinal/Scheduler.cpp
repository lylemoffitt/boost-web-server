//
//  Scheduler.cpp
//  WebSystemsFinal
//
//  Created by Lyle Moffitt on 4/22/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#include "Scheduler.h"

using namespace std;

void scheduler::add_to_sched(box &customer)
{
    customer.calcInterval();
    ringBuffer.push_back(customer);
}        

box scheduler::take_next()
{
    box customer = ringBuffer.front();
    ringBuffer.pop_front();
    return customer;
}    

void scheduler::update()
{
    box customer;
    file joke;
    time_t rawtime;
    struct tm * timeinfo;
    
    customer = ringBuffer.front();
    ringBuffer.pop_front();
    if(customer.tcp->done())
    {   
        delete &customer;
        return;
    }

    joke = _aott._file_handler.get_file(customer.filename);
    
    customer. data_sum += joke.file_size;
    
    time ( &rawtime );
	timeinfo = localtime ( &rawtime );
    joke.access_time = atoi(asctime (timeinfo));
    
    customer.age_time += (joke.access_time - customer.time_point);
    
    customer.calcInterval();
    
}

void box::calcInterval()
{
    interval = data_sum/age_time;
    usleep(interval);
}


/*
 size_t data;
 size_t time;
 
 for (auto it = _file_handler.file_map.begin();
 it != _file_handler.file_map.end(); it++)
 {
 if(_file_handler.filename == filename)
 {
 data = _file_handler.data_sum;
 time = _file_handler.age_time;
 }
 }
 */



