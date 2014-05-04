//
//  allofit.cpp
//  WebSystemsFinal
//
//  Created by Lyle Moffitt on 5/3/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#include "allofit.h"



using namespace std;

std::string handler::send_hello()
{
    file displayFile;
    string usr_pswd, usr, pswd;
    
    displayFile = _aott._file_handler.get_file("intro.md");
    // TCP.writeData();
    usr_pswd = TCP.getData();
    
    size_t newline;
    newline = usr_pswd.find("\n");
    usr = usr_pswd.substr(0,newline-1);
    pswd = usr_pswd.substr(newline+1, usr_pswd.length());
    
    bool login;
    login = _aott._security.chk_id(usr, pswd);
    
    if(login == false)
    {
        _aott._security.mk_user(usr, pswd);
        _aott._logger.log("SignUpForm", 5, "\t\tSignUpForm changed to add" + usr);
    }
        
    _aott._logger.log("IntroForm", 4, "\t\tUserform changed" + usr + "signed in");
    
     return usr_pswd;
    
}

void handler::getJoke(std::string usr_pswd)
{
    box customer;
    file displayFile;
    string usr, pswd;
    
    size_t newline;
    newline = usr_pswd.find("\n");
    usr = usr_pswd.substr(0,newline-1);
    pswd = usr_pswd.substr(newline+1, usr_pswd.length());
    
    while(true)
    {
        displayFile = _aott._file_handler.get_file("joke.md");
    
        //reads filename for joke
        customer.data_sum += displayFile.file_size;
        customer.filename = displayFile.filename;
        //customer.to_user->username = usr;
        //customer.to_user->pswd_hash = str_hasher(pswd);
        //customer.to_user->name_hash = str_hasher(usr);
        _aott._scheduler.add_to_sched(customer);
        usleep(customer.interval);
        _aott._logger.log("Joke", 0,"\t\tUser " + usr + "asked for Joke");
        displayFile = _aott._file_handler.get_file("jokeAgain.md");
        if(displayFile == nullptr)
            break;
    }
}





