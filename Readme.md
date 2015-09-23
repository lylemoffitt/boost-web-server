#Boost Web Server

---
######Lyle Moffitt & Tania Nsouli


###Introduction

For the final project in WebSystems we chose to implement option #1 -- a http server in C++. Our original project goal called for an http server with logging, multi-threading, authentication, SSL, and bandwidth throttling.  While code for all of these components was written, putting all of the components together created many unforseen challenges, thus prompting delays and feature cutbacks. 

The final version of this project features HTTP v1.0 server support,  multi-level logging, mulit-threading , server-side scripting, non-blocking IO, and HTTPS compliant SSL.


###Implementation
The HTTP server is implemented through extensive use of the ASIO Boost library. The library provides methods for asynchronous TCP socket reads and writes, thus implementing a non-blocking IO. Futhermore, this asyrnchronous communication is carried out in a serious of threaded function calls, thus making the server multi-threaded. 

Furthermore, the composed modules that handle and parse the HTTP requests and serve the HTML replies are run in a set of threads -- the number of which can be specified at runtime. These are pulled from a thread pool and managed internally by the Boost Thread Library (which works through POSIX threads).

SSL is layered overtop of these TCP connections using an extension of the ASIO Library. The handshake is asynchronous, so again no program execution is blocked.

Multi-level, thread-safe, global logging is implemented through the Boost Logging Library. These logs note the time, thread ID, severity level, and a provided message, which are stored in an HTML table.

This table is in turn sortable with respect to each of the four above attributes. This sorting is carried out through a `sorttable.js` script provided by a third party and carried in the HTML body of each log file.


###Setup

The compiled object files, once individually compiled into `*.o` object files must themselves be crosslinked with the following dynamic libraries: 

	libevent-2.0.5.dylib
	libevent_pthreads-2.0.5.dylib
	libboost_date_time-mt.dylib
	libboost_iostreams-mt.dylib
	libboost_log_setup-mt.dylib
	libboost_log-mt.dylib
	libboost_thread-mt.dylib
	libevent_openssl-2.0.5.dylib
	libcrypto.dylib
	libssl.dylib
	libboost_signals.dylib
	libboost_system.dylib

These can be obtained by donloading, building, and installing the most recent Boost Library source.

###Running

Once compiled, the server can be started with the following obions on the command line:

	HTTPserver <address> <port> <threads> <doc_root>
	
The document root must be the absolute path to the base of a HTML file tree.

Once running, the server can be accesses in any browser by navigating to the url `http://<address>:<port>/<path>`, where `<path>` is the URI-escaped path to a desired file starting after `<doc_root>`.


