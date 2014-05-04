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
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

#define PORT 8080

struct other_end
{
    //contains everyhing needed for tcp
    boost::asio::ip::address    addr;
    
    size_t          connection_number;
};


struct tcpConnection
{
    tcp::socket _socket;
    std::string message ;
    boost::system::error_code ignored_error;

    tcpConnection(boost::asio::io_service io_serv);
    
    void send(){
        boost::asio::write(socket, 
                           boost::asio::buffer(message), 
                           ignored_error);
    }
    
    bool done();
};


class tcpServer
{
    boost::asio::io_service io_service;
    
    tcp::acceptor acceptor;
    
    tcpServer():acceptor(io_service, 
                         tcp::endpoint(tcp::v4(), PORT))
    {}
    

    
    void
    loop();
    
    
};


#endif /* defined(__WebSystemsFinal__httpServer__) */








int main()
{
    try
    {
        boost::asio::io_service io_service;
        
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));
        
        for (;;)
        {
            tcp::socket socket(io_service);
            acceptor.accept(socket);
            
            std::string message = make_daytime_string();
            
            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}



