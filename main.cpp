#include <iostream>


#include "FileSystem.h"
#include "Shell.h"

using namespace std;
//adding another line of comment`
int main() 
{
    FileSystem* fs = new FileSystem();
    Shell* sh = new Shell(fs);
    
    sh->run();
    
    // Deletion in the reverse order
    delete sh;
    delete fs;

    return 0;
}


