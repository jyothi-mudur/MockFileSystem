#include "FsNode.h"

//#include <iostream>
using namespace std;

node::node(string name, NodeType nType, int size) : 
        mName(name), mType(nType), mSize(size) {
        }

node::~node() {
    mName.clear();
}

NodeType node::GetNType() {
    return mType;
}

std::string node::GetName() const {
    return mName;
}

file::file(string name): 
        node(name, File) {
    mBuffer = NULL;
    
}

file::~file() {
    // cout << "~File: " << mName << endl; 
    mBuffer = NULL;
}

Link::Link(std::string name,  node* Src) : 
        node(name, SymLink) {
    mSrc = Src;
}


Link::~Link() {
   // cout << "~Link: " << mName << endl; 
    mSrc = NULL;
}

node* Link::GetSrc() const{
    return mSrc;
}

directory::directory(string name) : 
        node(name, Directory) {
}

directory::~directory() {
    // cout << "~Directory: " << mName << endl; 
    
    mNodes.clear();    
}

bool directory::CreateFile(std::string name) {
    bool bReturn = true;
    
    // check if a file with a similar name exists
    if(mNodes.count(name) > 0) {
        bReturn = false; // file does exist, return error
    } else {
        file * newFile = new file(name);
        mNodes.insert(std::pair<std::string,node*>(name, newFile));
    }
    return bReturn;;
}

bool directory::DeleteFile(std::string name) {
    bool bReturn = false;

    // check if the file exists
    std::map<std::string,node*>::iterator it;
    
    it = mNodes.find(name);
    if(it != mNodes.end()) {
        
        mNodes.erase(it);
        bReturn = true;
    }
    
    return bReturn;
}

bool directory::CreateDirectory(std::string name) {
    bool bReturn = true;
    
    // Check if the directory exists
    if(mNodes.count(name) > 0) {
        bReturn = false; // directory with a similar name exists
    } else {
        directory * newDir = new directory(name);
        newDir->CreateLink(".", newDir);
        newDir->CreateLink("..", this);
    
        mNodes.insert(std::pair<std::string,node*>(name, newDir));
    }    
    return bReturn;
}

bool directory::DeleteDirectory(std::string name) {
    bool bReturn = false;

    // check if the directory exists
    std::map<std::string,node*>::iterator it;
    
    it = mNodes.find(name);
    if(it != mNodes.end()) {
        mNodes.erase(it);
        bReturn = true;
    }
    
    return bReturn;
}    

bool directory::Delete(std::string name) {
    bool bReturn = false;
    
    if ((name.compare(".") == 0) ||
        (name.compare("..")  == 0) ){
        //Should never delete . and ..
        return false;    
    }
    
    bool toDelete = false;
    node* Result = Search(name);
    if(Result != NULL) {
        if ((Result->GetNType() == File) ||
            (Result->GetNType() == SymLink) ){
            toDelete = true;
        } else if ( Result->GetNType() == Directory ){
            directory* dir = dynamic_cast<directory*> (Result);
            toDelete = dir->IsEmpty();           
        }
    }
    
    if (toDelete)
    {
        std::map<std::string,node*>::iterator it;
          
        it = mNodes.find(name);
        if(it != mNodes.end()) {
            node* toDelete = it->second;
            mNodes.erase(it);
            delete toDelete;
            bReturn = true;
        }
    }
    return bReturn;
}

bool directory::IsEmpty() {
    if (mNodes.size() <= 2 )
        return true;
    else
        return false;
}

void directory::CreateLink(std::string name, node* src) {
    Link* newNode = new Link(name, src);
    mNodes.insert(std::pair<std::string,node*>(name, newNode));

    /*
    if (src != NULL)
    {
        cout << "creating link from: " \
        << src->GetName() << " to: " << name << endl;
    }
    */
}

node* directory::Search(std::string name) {
    std::map<std::string,node*>::iterator it;
    
    it = mNodes.find(name);
    
    if(it != mNodes.end()) {
        return (it->second);
    } 
    return NULL;
}

bool directory::CreateLink(std::string src, std::string name) {
    bool bReturn = false;
    
    node* Result = Search(src);
    
    if(Result != NULL) {
        // create a link
        CreateLink(name, Result);
        bReturn = true;
    } 
    return bReturn;
}

std::map<std::string,node*> directory::ListContents() const {
    return mNodes;
}



