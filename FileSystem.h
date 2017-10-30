#ifndef __FILESYSTEM__
#define __FILESYSTEM__

#include <string>
#include <map>

#include "FsNode.h"

class FileSystem {
    public:
    FileSystem();
    ~FileSystem();
    
    // functions for user operations
    bool fsChangeDirectory(std::string name);
    std::string fsPresentWorkingDirectory();
    bool fsCreateDirectory(std::string name);
    bool fsDelete(std::string name);
    bool fsCreateFile(std::string name);
    void fsLink(std::string name, std::string Src);
    std::map<std::string,node*> fsListContents();
    
    private:
    directory* mpwd; // present working directory
    directory* mroot;
};

#endif
