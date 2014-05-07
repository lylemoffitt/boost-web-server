//
//  allofit.cpp
//  WebSystemsFinal
//
//  Created by Lyle Moffitt on 5/3/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#include "allofit.h"



using namespace std;

std::string 
allofit::send_hello()
{
    file* displayFile;
    string usr_pswd, usr, pswd;
    
    displayFile = _file_handler.get_file("intro.md");
    // *** functions to come *** //
    tcp->writeData();
    usr_pswd = tcp->getData();
    
    size_t newline;
    newline = usr_pswd.find("\n");
    usr = usr_pswd.substr(0,newline-1);
    pswd = usr_pswd.substr(newline+1, usr_pswd.length());
    
    bool login;
    login = chk_id(usr, pswd);
    
    if(login == false)
    {
        mk_user(usr, pswd);
        _logger.log("SignUpForm", 5, "\t\tSignUpForm changed to add" + usr);
    }
        
    _logger.log("IntroForm", 4, "\t\tUserform changed" + usr + "signed in");
    
     return usr_pswd;
    
}

void 
allofit::getJoke(std::string usr_pswd)
{
    box customer;
    file* displayFile;
    string usr, pswd;
    
    size_t newline;
    newline = usr_pswd.find("\n");
    usr = usr_pswd.substr(0,newline-1);
    pswd = usr_pswd.substr(newline+1, usr_pswd.length());
    
    while(true)
    {
        displayFile = _file_handler.get_file("joke.md");
    
        //reads filename for joke
        customer.data_sum += displayFile->file_size;
        customer.filename = displayFile->filename;
        //customer.to_user->username = usr;
        //customer.to_user->pswd_hash = str_hasher(pswd);
        //customer.to_user->name_hash = str_hasher(usr);
        add_to_sched(customer);
        usleep(customer.interval);
        _logger.log("Joke", 0,"\t\tUser " + usr + "asked for Joke");
        displayFile = _file_handler.get_file("jokeAgain.md");
        if(displayFile == nullptr)
            break;
    }
}


void 
allofit::add_to_sched(box &customer)
{
    ringBuffer.insert(make_pair(customer.to_user->username,customer));
}        

void 
allofit::update(std::string usr)
{
    file* joke;
    
    while(ringBuffer[usr].tcp->isBusy());
    
    //auto customer = ringBuffer.begin();
    if(ringBuffer[usr].tcp->done())
    {   
        ringBuffer.erase(usr);
        return;
    }
    
    joke = _file_handler.get_file(ringBuffer[usr].filename);
    //check for nullptr
    
    ringBuffer[usr].data_sum += joke->file_size;
    
    if(ringBuffer[usr].data_sum < lowest)
        lowest = ringBuffer[usr].data_sum;
    if(ringBuffer[usr].data_sum > highest)
        highest = ringBuffer[usr].data_sum;
    if(lowest != highest)
        ratio = (ringBuffer[usr].data_sum - lowest)/(highest - ringBuffer[usr].data_sum);
    else
        ratio = 0;
    
    //ringBuffer.at("").calcInterval();
    
}
///////// *** no purpose for this yet *** /////////
void 
box::calcInterval()
{
    
    interval = 0;
    usleep(interval);
}




bool 
allofit::chk_id(string usrnm, string pswd)
{
    
    user* obj = new user(usrnm, pswd);
    
    auto it = _user_set.id_table.find(obj);
    
    if(it == _user_set.id_table.end())
        return false;
    
    return (*it)->authenticate(usrnm, pswd);
    
}


user 
allofit::mk_user(string usrnm, string pswd)
{
    auto *obj =  new user(usrnm, pswd) ;
    _user_set.add_user(obj);
    return *obj;
}

void 
allofit::report_fake(string usrnm, string pswd)
{
    _logger.log("Security", 3, "\t\tFake user detected: " + usrnm + "\t" + pswd);
} 



