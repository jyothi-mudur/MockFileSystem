# make file for Mock File system
CXX = g++
CFLAGS = -Wall -Wextra -g

default: mockFs

mockFs: main.cpp FsNode.o FileSystem.o Shell.o
	$(CXX) $(CFLAGS) -o mockFs main.cpp \
			FsNode.o FileSystem.o Shell.o


FsNode.o: FsNode.h FsNode.cpp
	$(CXX) $(CFLAGS) -c FsNode.cpp
FileSystem.o: FileSystem.h FileSystem.cpp
	$(CXX) $(CFLAGS) -c FileSystem.cpp
Shell.o: Shell.h Shell.cpp
	$(CXX) $(CFLAGS) -c Shell.cpp

clean:
	@rm -rf mockFs *.o
