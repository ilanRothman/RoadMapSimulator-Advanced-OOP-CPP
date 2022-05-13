
#ifndef EX2_FILEMGR_H
#define EX2_FILEMGR_H
#include <string>
#include <vector>
using namespace std;

class FileMgr{
    private:
    vector<string> files;
    public:
    FileMgr(int argc , char** argv);

    void checkJunc(string& option,string& source,string& target,string& duration);
    void LoadFile(string& option,string& source,string& target,string& duration);
    void checkArgs();
    string getConfig();
};


#endif //EX2_FILEMGR_H
