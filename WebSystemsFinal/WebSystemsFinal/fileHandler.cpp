#include "fileHandler.h"

using namespace std;

file_handler(allofit &_alloi)
{
    ifstream infile;
    infile.open(path + "/index");
    string line;
    
    while(infile.good())
    {
        line << infile;
        add_file(line);
    }
    infile.close();    
}

int file_handler::add_file(std::string filename)
{
    iterator it;
    file &newfile = new file_handler(); 
    time_t rawtime;
    struct tm * timeinfo;
    
    //check to see if file is in map
    it = file_map.find(filename);
    if(it != file_map.end())
        return -1; //if file already exists
    
    ifstream infile;
    infile.open(path + "/" + filename, ofstream::binary | ofstream::ate);
    if(infile.bad())
        return -2; //if file is bad
    
    size_t file_size =  infile.seekg(0, infile.end);
    newfile.file_size = file_size;
    
    time ( &rawtime );
	timeinfo = localtime ( &rawtime );
    newfile.access_time = asctime (timeinfo);
    
    newfile.filename = filename;
    
    file_map.insert(filename, newfile);
    infile.close();
    return 1;
}

file& file_handler::get_file(std::string filename) 
{
    for(auto it = file_map.begin(); it != file_map.end(); ++it )
        if(*it.filename == filename)
            return *it;
    
}

vector<char> file::readfile()
{
    ifstream infile;
    infile.open(path + "/" + this.filename);
    
    vector<char> joke;
    joke.reserve(this.file_size);
    char letter;
    while(infile.good())
    {
        letter = infile.get();
        joke.push_back(letter);
    }
    infile.close();
    return joke;
}











