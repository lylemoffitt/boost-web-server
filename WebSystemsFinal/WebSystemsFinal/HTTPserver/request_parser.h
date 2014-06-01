//
//  request_parser.h
//  HTTPserver
//
//  Created by Lyle Moffitt on 5/4/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#ifndef HTTPserver_request_parser_h
#define HTTPserver_request_parser_h

#include <boost/logic/tribool.hpp>
#include <boost/tuple/tuple.hpp>

#include "Formatting.h"//

namespace HTTPserver {

    
struct request;

/// Parser for incoming requests.
class request_parser
{
public:
    /// Construct ready to parse the request method.
    request_parser();
    
    /// Reset to initial parser state.
    void reset();
    
    /// Parse some data. The tribool return value is true when a complete request
    /// has been parsed, false if the data is invalid, indeterminate when more
    /// data is required. The InputIterator return value indicates how much of the
    /// input has been consumed.
    template <typename InputIterator>
    boost::tuple<boost::tribool, InputIterator> 
    parse(request& req, InputIterator begin, InputIterator end)
    {
        while (begin != end)
        {
            boost::tribool result = consume(req, *begin++);
            if (result || !result)
                return boost::make_tuple(result, begin);
        }
        boost::tribool result = boost::indeterminate;
        return boost::make_tuple(result, begin);
    }
    
private:
    /// Handle the next character of input.
    boost::tribool consume(request& req, char input);
    
    /// Check if a byte is an HTTP character.
    static inline
    bool 
    is_char(int c);
    
    /// Check if a byte is defined as an HTTP meta character.
    static inline 
    bool 
    is_meta(int c);
    
    /// The current state of the parser.
    enum state
    {
        method_start,
        method,
        uri,
        http_v_h,
        http_v_t_1,
        http_v_t_2,
        http_v_p,
        http_v_slash,
        http_v_major_start,
        http_v_major,
        http_v_minor_start,
        http_v_minor,
        expecting_newline_1,
        header_line_start,
        header_lws,
        header_name,
        space_before_header_value,
        header_value,
        expecting_newline_2,
        expecting_newline_3
    } state_;
};

} // namespace HTTPserver


#endif // HTTPserver_request_parser_h



