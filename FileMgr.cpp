
#include "FileMgr.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

struct FileError:public exception{
  explicit FileError(const string& err)
  {
    std::cerr << err;
#ifndef TEST
    exit(1);
#endif
  }
};

FileMgr::FileMgr(int argc, char **argv) {
    files.insert(files.end(), argv, argv + argc);
    checkArgs();
#ifdef TEST
    files.erase(files.begin());
#endif
}


string FileMgr::getConfig() {
    for(auto iter = files.begin(); iter != files.end(); iter++){
        if(*iter == "-c"){
            return *++iter;
        }
    }
    return "";

}
void FileMgr::LoadFile(string &filePath, string &source, string &target, string &duration) {
    string line;
    try {
        auto val =  find(files.begin(),files.end(),filePath);
        if(val == files.end())
            throw FileError("ERROR opening the specified file\n");

        ifstream file(filePath);
        getline(file,line);
        istringstream ss(line);
        ss >> source >> target >> duration;
        if(ss.rdbuf()->in_avail()){
            throw FileError("Too many arguments.\n");
          }
        }
    catch (FileError&) {
        return;
    }
    checkJunc(filePath,source,target,duration);
}

void FileMgr::checkArgs() {
    try{
        if (files.size() < 2)
            throw FileError("Need at least one argument file to start.");

    }
    catch (FileError&){}
}

void FileMgr::checkJunc(string &option, string &source, string &target, string &duration) {

    try{
        if (source.length() > 32 || target.length() > 32 || stoi(duration) < 0)
            throw FileError("Invalid File Arguments.");

        switch (option[0])
        {
            case 'b':
            {
                if(option.rfind("bus", 0) != 0)
                    throw FileError("Invalid File Arguments.");
                break;
            }
            case 't':
            {
                if(option.rfind("tram",0) != 0)
                    throw FileError("Invalid File Arguments.");
                break;
            }
            case 's':
            {
                if(option.rfind("sprinter",0) != 0)
                    throw FileError("Invalid File Arguments.");
                break;
            }
            case 'r':
            {
                if(option.rfind("rail",0) != 0)
                    throw FileError("Invalid File Arguments.");
                break;
            }
        }
    }

    catch(FileError& ){
#ifdef TEST
      return;
#endif
    }
    catch (invalid_argument&) {
        cerr << "Invalid Arguments.";
        exit(1);
#ifdef TEST
      return;
#endif

    }
}

#ifdef TEST
vector<string>& FileMgr::loadAll() {
  return files;
}
#endif

