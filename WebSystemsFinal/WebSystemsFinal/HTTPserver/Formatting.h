//
//  Formatting.h
//  HTTPserver
//
//  Created by Lyle Moffitt on 5/4/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#ifndef HTTPserver_Formatting_h
#define HTTPserver_Formatting_h

#include <iostream>
#include <string>
#include <vector>
#include <boost/asio/buffer.hpp>



namespace HTTPserver {
 
    template<class ... var_t> 
    inline 
    std::string & 
    stringf( const char * format, var_t ... f_args )
    {
        char * buf = new char[sizeof...(f_args)*sizeof(size_t) + strlen(format)];
        sprintf(buf, format, f_args... );
        return *new std::string( std::move(buf) );
    }
    

    class mime_types 
    {
        struct mapping{
            const char* extension;
            const char* mime_type;
        };
        /// Convert a file extension into a MIME type.
    public:
        static 
        std::string &
        extension_to_type(std::string file_ext)
        {
            static
            mapping maps[] =
            {
                { "gif" , "image/gif" },
                { "htm" , "text/html" },
                { "html", "text/html" },
                { "jpg" , "image/jpeg"},
                { "png" , "image/png" },
                { NULL  , NULL } // Marks end of list.
            };
            for (auto i=0; maps[i].extension; ++i){
                if (maps[i].extension == file_ext)
                    return *new std::string(maps[i].mime_type);
            }
            return *new std::string("text/plain");
        }
    };




namespace status{

/// The status of the reply.
enum type
{
    ok                      = 200,
    created                 = 201,
    accepted                = 202,
    no_content              = 204,
    multiple_choices        = 300,
    moved_permanently       = 301,
    moved_temporarily       = 302,
    not_modified            = 304,
    bad_request             = 400,
    unauthorized            = 401,
    forbidden               = 403,
    not_found               = 404,
    internal_server_error   = 500,
    not_implemented         = 501,
    bad_gateway             = 502,
    service_unavailable     = 503,
    null                    = 0
};  


struct message
{
    type                    _num;
    std::string             _text;
    
    std::string&
    to_http()
    {
        return stringf("HTTP/1.0 %d %s\r\n",_num,_text.c_str());
    }
    std::string&
    to_html()
    {
        if(_num==null || _num==ok){return stringf("");}
        return stringf("<html>"
                       "<head><title>%s</title></head>"
                       "<body><h1>%d %s</h1></body>"
                       "</html>",_text.c_str(),_num,_text.c_str());
    }
    message(type     the_type):_num(the_type),
    _text(
         _num==type::ok                   ?"OK"                   :
         _num==type::created              ?"Created"              :
         _num==type::accepted             ?"Accepted"             :
         _num==type::no_content           ?"No Content"           :
         _num==type::multiple_choices     ?"Multiple Choices"     :
         _num==type::moved_permanently    ?"Moved Permanently"    :
         _num==type::moved_temporarily    ?"Moved Temporarily"    :
         _num==type::not_modified         ?"Not Modified"         :
         _num==type::bad_request          ?"Bad Request"          :
         _num==type::unauthorized         ?"Unauthorized"         :
         _num==type::forbidden            ?"Forbidden"            :
         _num==type::not_found            ?"Not Found"            :
         _num==type::internal_server_error?"Internal Server Error":
         _num==type::not_implemented      ?"Not Implemented"      :
         _num==type::bad_gateway          ?"Bad Gateway"          :
         _num==type::service_unavailable  ?"Service Unavailable"  : ""                     
         )
    {}
    message(): _num(type::null), _text(""){}
};


} // namespace status_strings

namespace misc_strings {

    const char name_value_separator[] = { ':', ' ' };
    const char crlf[] = { '\r', '\n' };

} // namespace misc_strings

                            

struct header
{
    std::string         name;
    std::string         value;
    header():name(128,0),value(128,0){}
};
    
    
/// A reply to be sent to a client.
struct reply
{
    /// The status of the reply.
    status::message                 stat_type;

    /// The headers to be included in the reply.
    std::vector<header>             headers;

    /// The content to be sent in the reply.
    std::string                     content;

    /// Convert the reply into a vector of buffers. The buffers do not own the
    /// underlying memory blocks, therefore the reply object must remain valid and
    /// not be changed until the write operation has completed.
    std::vector<boost::asio::const_buffer>  
    to_buffers();

    /// Get a stock reply.
    reply(status::type   stat);
    reply():reply(status::type::ok){}
//    reply(reply & r);
//    reply &     operator= (reply & r);
};
    

/// A request received from a client.
struct request
{
    std::string             method;
    std::string             uri;
    int                     http_v_major;
    int                     http_v_minor;
    std::vector<header>     headers;
};

        
    
} // namespace HTTPserver

#endif // HTTPserver_Formatting_h



