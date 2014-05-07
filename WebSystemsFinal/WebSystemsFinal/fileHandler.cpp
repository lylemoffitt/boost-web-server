#include "fileHandler.h"

using namespace std;

//constructor, calls add_file
file_handler::file_handler()//(allofit &_alloi)//:_aott(_alloi)
{
    
    ifstream infile;
    infile.open(path + "/index.txt");
    string line;
    
    while(infile.good())
    {
        infile >> line;
        add_file(line);
    }
    infile.close();    
}

// takes a filename, and builds the value in the map
// based off of the file and then stores it in the map
int file_handler::add_file(std::string filename)
{
    file &newfile = *new file();
    time_t rawtime;
    struct tm * timeinfo;
    
    //check to see if file is in map
    auto it = file_map.find(filename);
    if(it != file_map.end())
        return -1; //if file already exists
    
    ifstream infile;
    infile.open(path + "/" + filename, ofstream::binary | ofstream::ate);
    if(infile.bad())
        return -2; //if file is bad
    
    infile.seekg(0, infile.end);
    newfile.file_size = infile.tellg();
    
    time ( &rawtime );
	timeinfo = localtime ( &rawtime );
    newfile.access_time = atoi(asctime (timeinfo));
    
    newfile.filename = filename;
    
    file_map.insert(make_pair(filename, newfile));
    infile.close();
    return 1;
}

// gets a file out of the map by providing the
// filename you want the value for.
// if file is not in the map, then returns a nullptr
// make sure to handle this return, otherwise the program
// will crash
file* file_handler::get_file(std::string filename) 
{
    unordered_map<string,file>::iterator it = file_map.find (filename);
    if(it == file_map.end()){return nullptr;}
    return &(it->second);
}

// does same thing as "save_file" below, however the filename
// would have ot be provided prior to calling this function
// it woul dhave to be saved within the 'file' object calling this
// function calling it
vector<char> file::readfile()
{
    ifstream infile;
    infile.open(path + "/" + this->filename, ofstream::binary | ofstream::ate);
    infile.seekg(0, infile.end);
    file_size = infile.tellg();
    infile.close();
    
    infile.open(path + "/" + filename);
    vector<char> joke;
    joke.reserve(file_size);
    while(infile.good())
    {
        joke.push_back(infile.get());
    }
    joke.push_back('\0');
    infile.close();
    
    
    return joke;
}

// function reads file into a dynamically allocated
// char array
fileInfo file_handler::save_file(std::string filename)
{
    ifstream infile;
    int i = 0;
    infile.open(path + "/" + filename, ofstream::binary | ofstream::ate);
    infile.seekg(0, infile.end);
    _fileInfo.size = infile.tellg();
    infile.close();
    infile.open(path + "/" + filename);
    _fileInfo.data = new char[_fileInfo.size];
    while(i < _fileInfo.size){
        _fileInfo.data[i] = infile.get();
        i++;
    }
    _fileInfo.data[i] = '\0';
    infile.close();
    return _fileInfo;
}









