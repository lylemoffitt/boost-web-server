//
//  connection.h
//  HTTPserver
//
//  Created by Lyle Moffitt on 5/4/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#ifndef HTTPserver_connection_h
#define HTTPserver_connection_h

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>//

#include <vector>//
#include <string>

#include "Formatting.h"
#include "request_handler.h"
#include "request_parser.h"

namespace HTTPserver {

/// Represents a single connection from a client.
class connection:
    //private boost::noncopyable,
    public  boost::enable_shared_from_this<connection>
    
{
public:
    /// Construct a connection with the given io_service.
    explicit connection(boost::asio::io_service&    io_service,
                        request_handler&            handler     );
    
    /// Get the socket associated with the connection.
    boost::asio::ip::tcp::socket& 
    socket();
    
    /// Start the first asynchronous operation for the connection.
    void 
    start();
    
private:
    /// Handle completion of a read operation.
    void 
    handle_read(const boost::system::error_code&    err,
                std::size_t                         bytes_transferred   );
    
    /// Handle completion of a write operation.
    void 
    handle_write(const boost::system::error_code&   err);
    
    /// Strand to ensure the connection's handlers are not called concurrently.
    boost::asio::io_service::strand         strand_;
    
    /// Socket for the connection.
    boost::asio::ip::tcp::socket            socket_;
    
    /// The handler used to process the incoming request.
    request_handler           &             request_handler_;
    
    /// Buffer for incoming data.
    boost::array<char, 8192>                buffer_;
    
    /// The incoming request.
    request                                 request_;
    
    /// The parser for the incoming request.
    request_parser                          request_parser_;
    
    /// The reply to be sent back to the client.
    reply                                   reply_;
};

typedef boost::shared_ptr<connection> connection_ptr;

} // namespace HTTPserver

#endif // HTTPserver_connection_h
