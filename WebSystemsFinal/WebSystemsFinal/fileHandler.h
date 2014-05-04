#include "allofit.h"
#include <iostream>
#include <fstream>
#include <string> 
#include <sstream>
#include <unordered_map>
#include <iterator>
 
static const std::string path;

class file_handler
{
    std::unordered_map<std::string,file> file_map;
    
    public:
        file_handler(allofit &_alloi);
        int add_file(std::string filename);
        file& get_file(std::string filename);  
        
};

class file
{
    size_t file_size;
    std::string filename;
    size_t access_time;
    
    public:
        //passes open file stream object
        //log when file was opened
        vector<char> readfile();
        
    
};