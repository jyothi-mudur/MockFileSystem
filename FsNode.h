#ifndef __NODEHEADER__
#define __NODEHEADER__


#include <string>
#include <map>
#include <cstddef>
#include <new>
#define TODO(x) //x

enum NodeType{File, Directory, SymLink};

class file;
class directory;
class Link;

class node {
    protected:
    std::string mName;
    NodeType mType;
    int mSize;
  
    public:
    node(std::string name, NodeType type, int size = 0);
    virtual ~node();
    NodeType GetNType();
    std::string GetName()const;
};

class file : public node {
    private:
    char* mBuffer;
    
    public:
    file(std::string name);
    ~file(); 
};

class Link : public node {
    private:
    node* mSrc;
    
    public:
    Link(std::string name, node* Src);
    ~Link();
    node* GetSrc() const;
};

class directory : public node {
    private:
    std::map<std::string,node*> mNodes;
    bool DeleteFile(std::string name);
    bool DeleteDirectory(std::string name); 
    
    public:
    directory(std::string name);
    ~directory();
    bool IsEmpty();
    bool CreateFile(std::string name);
    bool CreateDirectory(std::string name);
    bool Delete(std::string name);
    void CreateLink(std::string name, node* Src);
    bool CreateLink(std::string name, std::string Src);
    node* Search(std::string name);
    std::map<std::string,node*> ListContents() const;
};

#endif
