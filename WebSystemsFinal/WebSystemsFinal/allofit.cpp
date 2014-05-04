//
//  allofit.cpp
//  WebSystemsFinal
//
//  Created by Lyle Moffitt on 5/3/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#include "allofit.h"
std::string handler::send_hello()
{
    file displayFile;
    string usr-pswd, usr, pswd;
    
    displayFile = _file_handler.get_file("intro.md");
    TCP.writeData();
    usr-pswd = TCP.getData();    
    
    size_t newline;
    newline = usr-pswd.find("\n");
    usr = usr-pswd.substr(0,newline-1);
    pswd = usr-pswd.substr(newline+1, usr-pswd.length());
    
    bool login;
    login = _security.chk_id(usr, pswd);
    
    if(login == false)
    {
        _security.mk_user(usr, pswd);
        _logger.log("SignUpForm", 5, "\t\tSignUpForm changed to add" + usr);    
    }
        
    _logger.log("IntroForm", 4, "\t\tUserform changed" + usr + "signed in");
    
     return usr-pswd;
    
}

void handler::getJoke(std::string usr-pswd)
{
    box customer;
    file displayFile;
    string usr, pswd;
    
    size_t newline;
    newline = usr-pswd.find("\n");
    usr = usr-pswd.substr(0,newline-1);
    pswd = usr-pswd.substr(newline+1, usr-pswd.length());
    
    while(true)
    {
        displayFile = _file_handler.get_file("joke.md");
    
        //reads filename for joke
        customer. sum += customer.displayFile.file_size;
        customer.filename = displayFile.filename;
        customer.to_user->user(usr, pswd);
         
        _scheduler.add_to_sched(customer); 
        usleep(customer.interval);
        _logger.log("Joke", 0,"\t\tUser " + usr + "asked for Joke");
        displayFile = _file_handler.get_file("jokeAgain.md");
        if(displayFile == nullptr)
            break;
    }
}





