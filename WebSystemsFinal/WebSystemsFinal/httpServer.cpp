//
//  httpServer.cpp
//  WebSystemsFinal
//
//  Created by Lyle Moffitt on 4/22/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#include "httpServer.h"

void
TimeRequestHandler::handleRequest(Poco::Net::HTTPServerRequest &request,
                                  Poco::Net::HTTPServerResponse &response)
{
    Application& app = Application::instance();
    app.logger().information("Request from "
                             + request.clientAddress().toString());
    
    Timestamp now;
    std::string dt(DateTimeFormatter::format(now, _format));
    
    response.setChunkedTransferEncoding(true);
    response.setContentType("text/html");
    
    std::ostream& ostr = response.send();
    ostr << "<html><head><title>HTTPTimeServer powered by "
    "POCO C++ Libraries</title>";
    ostr << "<meta http-equiv=\"refresh\" content=\"1\"></head>";
    ostr << "<body><p style=\"text-align: center; "
    "font-size: 48px;\">";
    ostr << dt;
    ostr << "</p></body></html>";
}