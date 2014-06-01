//
//  server.h
//  HTTPserver
//
//  Created by Lyle Moffitt on 5/4/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#ifndef HTTPserver_server_h
#define HTTPserver_server_h

#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>//
#include <boost/bind.hpp>//

#include "connection.h"
#include "request_handler.h"

namespace HTTPserver {


/// The top-level class of the HTTP server.
class server
{
public:
    /// Construct the server to listen on the specified TCP address and port, and
    /// serve up files from the given directory.
    explicit server(std::string                         address, 
                    std::string                         port,
                    std::string                         doc_root, 
                    std::size_t                         thread_pool_size);
    
    /// Run the server's io_service loop.
    void run();
    
private:
    /// Initiate an asynchronous accept operation.
    void start_accept();
    
    /// Handle completion of an asynchronous accept operation.
    void handle_accept(const boost::system::error_code&     err);
    
    /// Handle a request to stop the server.
    void handle_stop();
    
    /// The number of threads that will call io_service::run().
    std::size_t                             thread_pool_size_;
    
    /// The io_service used to perform asynchronous operations.
    boost::asio::io_service                 io_service_;
    
    /// The signal_set is used to register for process termination notifications.
    boost::asio::signal_set                 signals_;
    
    /// Acceptor used to listen for incoming connections.
    boost::asio::ip::tcp::acceptor          acceptor_;
    
    /// The next connection to be accepted.
    connection_ptr                          new_connection_;
    
    /// The handler for all incoming requests.
    request_handler                         request_handler_;
};

} // namespace HTTPserver

#endif // HTTPserver_server_h



