#include "FileSystem.h"

using namespace std;

FileSystem::FileSystem() {
    mroot = new directory("/");
    mroot->CreateLink(".", mroot);
    mroot->CreateLink("..", NULL);
    
    mpwd = mroot; // make root as the pwd
}

FileSystem::~FileSystem() {
    delete mroot;
    if (mpwd != mroot) {
        delete mpwd;
    }
}

bool FileSystem::fsChangeDirectory(std::string name) {
    // search for the name in the map.
    // if present, then see if it is a directory
    // if it is a directory, then make mpwd as the directory.
    node* Result = mpwd->Search(name);
    
    while ((Result != NULL) && 
            (Result->GetNType() == SymLink)) {
        Link* symLink = dynamic_cast<Link*> (Result);
        Result = symLink->GetSrc();   
    }
    
    if((Result != NULL) && (Result->GetNType() == Directory)) {
        mpwd = dynamic_cast<directory*> (Result);
        return true; 
    } else {
        return false;
    }
}

string FileSystem::fsPresentWorkingDirectory() {
    return mpwd->GetName();
}

bool FileSystem::fsCreateDirectory(string name) {
    return mpwd->CreateDirectory(name);
}

bool FileSystem::fsDelete(string name) {
    return mpwd->Delete(name);
}

bool FileSystem::fsCreateFile(string name) {
    return mpwd->CreateFile(name);
}

void FileSystem::fsLink(string src, string name) {
    mpwd->CreateLink(src, name);
    return;
}

std::map<std::string,node*> FileSystem::fsListContents() {
    return mpwd->ListContents();
}

