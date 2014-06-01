//
//  main.cpp
//  HTTPserver
//
//  Created by Lyle Moffitt on 5/4/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#include <iostream>
#include <string>
#include <boost/asio.hpp>

#include "server.h"

int main(int argc, char* argv[])
{
  try
  {
    // Check command line arguments.
    if (argc != 5)
    {
      std::cerr << "Usage: http_server <address> <port> <threads> <doc_root>\n";
      std::cerr << "  For IPv4, try:\n";
      std::cerr << "    receiver 0.0.0.0 80 1 .\n";
      std::cerr << "  For IPv6, try:\n";
      std::cerr << "    receiver 0::0 80 1 .\n";
      return 1;
    }

    // Initialise the server.
      std::size_t num_threads = std::strtoull(argv[3], nullptr, 10);
    HTTPserver::server s(argv[1], argv[2], argv[4], num_threads);

    // Run the server until stopped.
    s.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "exception: " << e.what() << "\n";
  }

  return 0;
}
