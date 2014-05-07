#ifndef __WebSystemsFinal__fileHandler__
#define __WebSystemsFinal__fileHandler__


#include <iostream>
#include <fstream>
#include <string> 
#include <sstream>
#include <unordered_map>
#include <iterator>
#include <vector>
//#include <functional>


//#include "allofit.h"
 
static const std::string path;

struct fileInfo
{
    char* data;
    size_t size;
};



class file
{
public:
    size_t          file_size;
    std::string     filename;
    size_t          access_time;
    //passes open file stream object
    //log when file was opened
    std::vector<char> readfile();
    
    file(){file_size = 0; filename = ""; access_time = 0;}
};

class file_handler
{
    std::unordered_map<std::string,file> file_map;
    fileInfo _fileInfo;
    
public:
//    file_handler(allofit &_alloi);

    file_handler();
    fileInfo save_file(std::string filename);
    int add_file(std::string filename);
    file* get_file(std::string filename);
        
};

#endif