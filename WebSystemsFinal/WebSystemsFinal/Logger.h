//
//  Logger.h
//  WebSystemsFinal
//
//  Created by Lyle Moffitt on 4/22/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#ifndef __WebSystemsFinal__Logger__
#define __WebSystemsFinal__Logger__

#include <iostream>
#include <string>
#include <unordered_map>

#include <functional>
#include <fstream>
#include <sstream>


template<class ... var_t> 
inline 
std::string 
stringf( const char * format, var_t ... f_args )
{
    char * buf = new char[sizeof...(f_args)*sizeof(size_t) + strlen(format)];
    sprintf(buf, format, f_args... );
    return std::string( buf );
}


class logger
{
    std::string     base_path;
    std::unordered_map<std::string, std::fstream> files;
    
    time_t rawtime;
    struct tm * timeinfo;
    
    logger(){
        
        std::fstream conf ("config");
        
    }
    
public:
    
    void    log(std::string whom, int level, std::string info);
    
    
};



#endif /* defined(__WebSystemsFinal__Logger__) */
