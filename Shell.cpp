#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "Shell.h"

using namespace std;

Shell::Shell(FileSystem* fs) {
    mfs = fs;
}

Shell::~Shell() {
    mfs = NULL;
}
//to display user options
void Shell::DisplayUserOptions() {
    cout << "1. cd <dir>\n" \
         << "2. pwd \n" \
         << "3. touch <name>\n" \
         << "4. rm <name>\n" \
         << "5. mkdir <name>\n" \
         << "6. ln <src> <dst>\n" \
         << "7. ls \n"
         << "8. exit \n" \
         << "9. #comment \n" \
         << "Enter commands:" << endl;  
}

bool Shell:: checkargs (const std::vector<string>& tokens, unsigned int argc, std::string usage)
{
    if (tokens.size() < argc) {
        cout << "Error: Insufficient # of arguments" << endl;
        cout << usage << endl;
        return false;
    }
    return true;
}

bool Shell::ExecuteCommands(const string& s) {
    bool bReturn = true;
    
    stringstream ss(s);
    std::string item;
    char delim = ' ';
    std::vector<string> tokens;
    while (std::getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    
    if(tokens.empty()) {
        // no command entered
        //cout << "Please enter a command: "<< endl;
        return true;    
    }
    
    if(tokens[0].compare(0,1,"#") == 0) {
        // comment -> nop
        return true;
    }
    
    if (tokens[0].compare("cd") == 0) {         
        if(checkargs(tokens, 2, "Usage: cd <dir>") &&
            !(mfs->fsChangeDirectory(tokens[1]))) {
            cout << "Error. No such directory: " << tokens[1] << endl;
        }
    }else if (tokens[0].compare("pwd") == 0) {
        string pwd = mfs->fsPresentWorkingDirectory();
        cout << pwd << endl; 
     }else if (tokens[0].compare("touch") == 0) {
        if(checkargs(tokens, 2, "Usage: touch <arg1>") &&
            !(mfs->fsCreateFile(tokens[1]))) {
            cout << "Error in creating file" << endl;
        }    
    }else if (tokens[0].compare("rm") == 0) {
        if(checkargs(tokens, 2, "Usage: rm <name>") &&
            !(mfs->fsDelete(tokens[1]))) {
            cout << "Error in deleting" << endl;
        }    
    }else if (tokens[0].compare("mkdir") == 0) {
        if(checkargs(tokens, 2, "Usage: mkdir <name>") &&
            !(mfs->fsCreateDirectory(tokens[1]))) {
            cout << "Error in creating directory" << endl;
        }             
    }else if (tokens[0].compare("ln") == 0) {
        if((checkargs(tokens, 3, "Usage: ln <src> <dst>"))) {
            mfs->fsLink(tokens[1], tokens[2]);
        }
    }else if (tokens[0].compare("ls") == 0) {
        char tab = '\t';
        std::map<std::string,node*> MyContents = 
        (mfs->fsListContents());
        for(std::map<std::string,node*>::iterator it = 
            MyContents.begin(); it != MyContents.end(); ++it) {
            cout << it->first << tab;
        }
        cout << endl;    
    }else if (tokens[0].compare("exit") == 0) {
        bReturn = false;
    }else {
        cout << "Unknown command" << endl;
    }
    return bReturn;
}

void Shell::run() {  
    cout << "welcome to the File System demo!" << endl;
    DisplayUserOptions();
    string UserInp;
    bool bExecute = true;
    
    while(bExecute){
        cout << "# ";
        cout.flush();
        getline(cin, UserInp);         
        //cout << "You Entered: " << UserInp << endl;
        
        if(!ExecuteCommands(UserInp)) {
            bExecute = false;
        }
    }
    return;
}   
    

