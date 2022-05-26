
#ifndef EX2_FILEMGR_H
#define EX2_FILEMGR_H
//#define TEST
#include <string>
#include <vector>
using namespace std;

class FileMgr{
    private:
    vector<string> files; // holds the file paths.
    public:

    /**
     * constructor.
     * argc- the main argument count.
     * argv - the main arguments.
     * **/
    FileMgr(int argc , char** argv);


    /*
     * check if arguments are legal.
     * */
    void checkJunc(string& option,string& source,string& target,string& duration);

    /*
     * load the file from the files vector.
     * */
    void LoadFile(string& option,string& source,string& target,string& duration);

    /*
     * check argument count.
     * */
    void checkArgs();

    /*
     * return the path to the configuration txt file.
     * */
    string getConfig();


#ifdef TEST
    vector<string>& loadAll();
#endif
};


#endif //EX2_FILEMGR_H
