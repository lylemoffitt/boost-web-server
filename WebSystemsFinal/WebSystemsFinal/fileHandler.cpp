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
int 
file_handler::add_file(std::string filename)
{
    auto newfile = new file();
    time_t rawtime;
    struct std::tm * timeinfo;
    
    //check to see if file is in map
    auto it = file_map.find(filename);
    if(it != file_map.end())
        return -1; //if file already exists
    
    ifstream infile;
    infile.open(path + "/" + filename, ofstream::binary | ofstream::ate);
    if(infile.bad())
        return -2; //if file is bad
    
    infile.seekg(0, infile.end);
    newfile->file_size = infile.tellg();
    infile.close();
    
    time ( &rawtime );
	timeinfo = localtime ( &rawtime );
    newfile->access_time = atoi(asctime (timeinfo));
    
    newfile->filename = filename;
    
    newfile->file_text = read_file(filename);
    
    file_map.insert(make_pair(filename, newfile));
    
    return 1;
}

// gets a file out of the map by providing the
// filename you want the value for.
// if file is not in the map, then returns a nullptr
// make sure to handle this return, otherwise the program
// will crash
file* 
file_handler::get_file(std::string filename) 
{
    auto it = file_map.find (filename);
    if(it == file_map.end()){return nullptr;}
    return it->second;
}


// function reads file into a dynamically allocated
// char array
std::string
file_handler::read_file(std::string filename)
{
    std::ifstream is(path + "/" + filename, std::ios::in | std::ios::binary);
    char buf[512];
    std::string file_content;
    while (is.read(buf, sizeof(buf)).gcount() > 0)
        file_content.append(buf, is.gcount());
    
    return file_content;
}









