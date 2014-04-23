//
//  httpServer.h
//  WebSystemsFinal
//
//  Created by Lyle Moffitt on 4/22/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#ifndef __WebSystemsFinal__httpServer__
#define __WebSystemsFinal__httpServer__

#include <iostream>


#include <boost/asio.hpp>

struct other_end
{
    //contains everyhing needed for tcp
    boost::asio::ip::address    addr;
    
    size_t          connection_number;
};



class httpServer
{
    boost::asio::io_service serv;
    
    void
    loop_handler();
    
    
};


#endif /* defined(__WebSystemsFinal__httpServer__) */
