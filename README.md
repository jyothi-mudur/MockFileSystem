# MockFileSystem
Design classes and write simple methods for Mock File System
Used Ubuntu 12.04 running as VM on windows PC to do this project. Here are the details:
$ g++ --version
g++ (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3
$ make --version
GNU Make 3.81
This program built for i686-pc-linux-gnu

Here are the assumptions / known issues and todos for the project. Please pass this file also to the team.
Assumptions:
+/ user will not use any special characters
+/ user will not use relative paths or absolute paths with "/" in any file or directory name. This limits linking to files with in the same parent directory.
+/ list of commands supported printed on program invocation. No fancy error checks. Only basic protection against SEGV.
+/ Errors are printed. Not detailed error handling using exceptions. Just basic PASS / FAIL.
+/ More than necessary parameters are ignored. Ex: 'ls' ignores any parameter and lists full contents of the directory

Known issues:
+/ If the linked file/directory (src) is deleted before the link, then accessing link will crash. To fix this, we need to do reference counting at each node. 
+/ Input is not sanitized for extra spaces, trailing spaces.
+/ pwd does not print full path. Only prints the current directory name. Omitted due to time.
+/ While linking files/directories, "." and ".." are not protected. They can be over-written. They are protected in 'rm' though.
+/ Of course there are unknown bugs.

Instructions:
+/ Binary that need to run: ./mockFs from the src directory
+/ Please use make clean, make to re-generate the binaries for your environment. Please get back to me if you face compilation issues.
+/ use runTest.sh in test directory to run all the automated tests - 15. Results have to be manualy verified though.

