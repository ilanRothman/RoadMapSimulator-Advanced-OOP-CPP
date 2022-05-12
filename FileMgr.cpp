//
// Created by iroth on 5/11/2022.
//

#include "FileMgr.h"
#include <fstream>
#include <sstream>
#include <iostream>

struct FileError:public exception{
  FileError()
  {
    std::cerr << "ERROR opening the specified file";
  }
};

FileMgr::FileMgr(int argc, char **argv) {
    files.insert(files.end(), argv, argv + argc);
}

string FileMgr::getConfig() {
    for(auto iter = files.begin(); iter != files.end(); iter++){
        if(*iter == "-c"){
            return *++iter;
        }
        return "";
    }

}
void FileMgr::LoadFile(string &option, string &source, string &target, string &duration) {
  ifstream file;

  try {
    file.open(option);
    if(!file)
      throw FileError();
  }

  catch (FileError&) {
    return;
  }

}

