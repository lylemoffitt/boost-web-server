//
//  server.cpp
//  HTTPserver
//
//  Created by Lyle Moffitt on 5/4/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#include "server.h"


namespace HTTPserver {

server::server(std::string                      address, 
               std::string                      port,
               std::string                      doc_root,
               std::size_t                      thread_pool_size):
thread_pool_size_   (thread_pool_size),
signals_            (io_service_),
acceptor_           (io_service_),
new_connection_     (),
request_handler_    (doc_root)
{
    using namespace boost::asio::ip;
    // Register to handle the signals that indicate when the server should exit.
    // It is safe to register for the same signal multiple times in a program,
    // provided all registration for the specified signal is made through Asio.
    signals_.add(SIGINT);
    signals_.add(SIGTERM);
    signals_.add(SIGQUIT);
    /*
    signals_.add(SIGSEGV);
    signals_.add(SIGHUP);
    signals_.add(SIGILL);
    signals_.add(SIGABRT);
    */
    signals_.async_wait(boost::bind(&server::handle_stop, this));
    
    // Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
    tcp::resolver           resolver(io_service_);
    tcp::resolver::query    query(address, port);
    tcp::endpoint           endpoint( *resolver.resolve(query) );
    
    acceptor_.open(endpoint.protocol());
    acceptor_.set_option( tcp::acceptor::reuse_address(true) );
    acceptor_.bind(endpoint);
    acceptor_.listen();
    
    start_accept();
}

void 
server::run()
{
    // Create a pool of threads to run all of the io_services.
    std::vector<boost::shared_ptr<boost::thread> > threads;
    for (std::size_t i = 0; i < thread_pool_size_; ++i)
    {
        boost::shared_ptr<boost::thread> thread(new boost::thread(
                                                                  boost::bind(&boost::asio::io_service::run, &io_service_)));
        threads.push_back(thread);
    }
    
    // Wait for all threads in the pool to exit.
    for (std::size_t i = 0; i < threads.size(); ++i)
        threads[i]->join();
}

void 
server::start_accept()
{
    new_connection_.reset(new connection(io_service_, request_handler_));
    acceptor_.async_accept(new_connection_->socket(),
                           boost::bind(&server::handle_accept, this,
                                       boost::asio::placeholders::error));
}

void 
server::handle_accept(const boost::system::error_code&     err)
{
    if (!err)
    {
        new_connection_->start();
    }
    
    start_accept();
}

void 
server::handle_stop()
{
    io_service_.stop();
}

} // namespace HTTPserver



