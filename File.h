#ifndef FILE_H
#define FILE_H
#include <string>
#include <fstream>

using namespace std;

class File
{
    public:
        File(char* fileName);
        virtual ~File();
        void openFile();
        void closeFile();
    protected:
        char* fileName;
        //ifstream f;
    private:

};

#endif // FILE_H
