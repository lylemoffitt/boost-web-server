//
//  httpServer.cpp
//  WebSystemsFinal
//
//  Created by Lyle Moffitt on 4/22/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#include "httpServer.h"



void
tcpServer::loop()
{
    for (;;)
    {
        tcp::socket socket(io_service);
        acceptor.accept(socket);
        
        std::string message ;
        
        boost::system::error_code ignored_error;
        boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
    }
}


