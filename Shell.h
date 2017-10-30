#ifndef __SHELLHEADER__
#define __SHELLHEADER__

#include <istream>
#include <sstream>
#include <vector>


#include "FileSystem.h"

class Shell {
    private:
    FileSystem* mfs;
       
    public:
    Shell(FileSystem* fs);
    ~Shell();
    
    void run();
    void DisplayUserOptions();
    
    bool ExecuteCommands(const std::string& UserInp);
    bool checkargs (std::vector<std::string> const & tokens, 
                    unsigned int argc, 
                    std::string usage);
};

#endif

