//
//  request_parser.h
//  HTTPserver
//
//  Created by Lyle Moffitt on 5/4/14.
//  Copyright (c) 2014 Lyle Moffitt. All rights reserved.
//

#include "request_parser.h"


namespace HTTPserver {

request_parser::request_parser(): state_(method_start)
{
}

void 
request_parser::reset()
{
    state_ = method_start;
}

boost::tribool 
request_parser::consume(request& req, char _c)
{
    using namespace std;
#define _unknown_  boost::indeterminate
    switch (state_)
    {
        case method_start:
            if (!is_char(_c) || iscntrl(_c) || is_meta(_c)){ return false;   }
            state_ = method;
            req.method.push_back(_c);
            return _unknown_;
            
        case method:
            if (_c == ' '){ state_ = uri;                   return _unknown_;}
            if (!is_char(_c) || iscntrl(_c) || is_meta(_c)){ return false;    }
            req.method.push_back(_c);
            return _unknown_;
            
        case uri:
            if (_c == ' '){ state_ = http_v_h;              return _unknown_;}
            if (iscntrl(_c)){                                return false;    }
            req.uri.push_back(_c);
            return _unknown_;
            
        case http_v_h:
            if (_c == 'H'){ state_ = http_v_t_1;            return _unknown_;}
            return false;
            
        case http_v_t_1:
            if (_c == 'T'){ state_ = http_v_t_2;            return _unknown_;}
            return false;
            
        case http_v_t_2:
            if (_c == 'T'){ state_ = http_v_p;              return _unknown_;}
            return false;
            
        case http_v_p:
            if (_c == 'P'){ state_ = http_v_slash;          return _unknown_;}
            return false;
            
        case http_v_slash:
            if (_c == '/')
            {   req.http_v_major = req.http_v_minor = 0;
                state_ = http_v_major_start;                return _unknown_;
            }
            return false;
            
        case http_v_major_start:
            if (!isdigit(_c)){                             return false;   }
            (req.http_v_major *= 10) += (_c - '0');
            state_ = http_v_major;                          return _unknown_;
            
            
        case http_v_major:
            if (_c == '.'){state_ = http_v_minor_start;     return _unknown_;}
            if (!isdigit(_c)){                             return false;    }
            else (req.http_v_major *= 10) += (_c - '0');    return _unknown_;
            
            
        case http_v_minor_start:
            if (!isdigit(_c)){                             return false;   }
            (req.http_v_minor *= 10) += (_c - '0');
            state_ = http_v_minor;                          return _unknown_;
            
        case http_v_minor:
            if (_c == '\r'){ state_ = expecting_newline_1;  return _unknown_;}
            if (isdigit(_c))
            {   (req.http_v_minor *= 10) += (_c - '0');     return _unknown_;
            }
            return false;
    
        case expecting_newline_1:
            if (_c == '\n'){ state_ = header_line_start;    return _unknown_;}
            return false;
            
        case header_line_start:
            if (_c == '\r'){ state_ = expecting_newline_3;  return _unknown_;}
            if (!req.headers.empty() && (_c == ' ' || _c == '\t'))
            {   state_ = header_lws;                        return _unknown_;
            }
            if (!is_char(_c) || iscntrl(_c) || is_meta(_c)){ return false;    }
            req.headers.push_back(header());
            req.headers.back().name.push_back(_c);
            state_ = header_name;
            return _unknown_;
            
        case header_lws:
            if (_c == '\r'){ state_ = expecting_newline_2;  return _unknown_;}
            if (_c == ' ' || _c == '\t'){                   return _unknown_;}
            if (iscntrl(_c)){                                return false;    }
            state_ = header_value;
            req.headers.back().value.push_back(_c);
            return _unknown_;
            
        case header_name:
            if (_c == ':')
            {   state_ = space_before_header_value;
                return _unknown_;
            }
            if (!is_char(_c) || iscntrl(_c) || is_meta(_c)){ return false;   }
            req.headers.back().name.push_back(_c);
            return _unknown_;
            
        case space_before_header_value:
            if (_c == ' '){  state_ = header_value;         return _unknown_;}
            return false;
            
        case header_value:
            if (_c == '\r'){ state_ = expecting_newline_2;  return _unknown_;}
            if (iscntrl(_c)){                                return false;    }
            req.headers.back().value.push_back(_c);
            return _unknown_;
            
        case expecting_newline_2:
            if (_c == '\n'){ state_ = header_line_start;    return _unknown_;}
            return false;
            
        case expecting_newline_3:
            if (_c == '\n'){                                return true;     }
            
        default:
            return false;
    }
#undef _unknown_
}

bool 
request_parser::is_char(int c)
{
    return c >= 0 && c <= 127;
}

bool 
request_parser::is_meta(int c)
{
    
    switch (c)
    {
        case '(':   case ')':   case '<':   case '>' :  case '@':
        case ',':   case ';':   case ':':   case '\\':  case '"':
        case '/':   case '[':   case ']':   case '?' :  case '=':
        case '{':   case '}':   case ' ':   case '\t':
            return true;
            
        default:
            return false;
    }
}


} // namespace HTTPserver


