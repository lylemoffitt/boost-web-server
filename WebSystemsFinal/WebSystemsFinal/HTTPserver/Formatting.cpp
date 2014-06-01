//
//  Formatting.cpp
//  HTTPserver
//
//  Created by Lyle Moffitt on 5/7/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#include "Formatting.h"

namespace HTTPserver {


std::vector<boost::asio::const_buffer>  
reply::to_buffers()
{
    using namespace boost::asio;
    std::vector<const_buffer> vect_buff (headers.size()*4+3);
    // Add http status tag
    vect_buff.emplace_back(buffer(stat_type.to_http()));
    // Add header couplets; one per line
    for (size_t i = 0; i < headers.size(); ++i)
    {
        header& h = headers[i];
        vect_buff.emplace_back(buffer(h.name));
        vect_buff.emplace_back(buffer(misc_strings::name_value_separator));
        vect_buff.emplace_back(buffer(h.value));
        vect_buff.emplace_back(buffer(misc_strings::crlf));
    }
    vect_buff.emplace_back(buffer(misc_strings::crlf));
    // Add file-contents
    vect_buff.emplace_back(buffer(content));
    return vect_buff;
}


reply::reply(status::type     stat):
    stat_type(stat)
{
//    if (stat_type._num == status::type::ok){  return; }
    content = stat_type.to_html();
    headers.resize(2);
    headers[0].name  = "Content-Length";
    headers[0].value = stringf("%d",content.size());
    headers[1].name  = "Content-Type";
    headers[1].value = "text/html";
}

} // namespace HTTPserver


