#ifndef FILE_H
#define FILE_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class File
{
    public:
        File(char* fileName, int xsize, int ysize);
        virtual ~File();
        void readFile();
        void saveFile();
        void showRawDb();
        void showRawRecord(int n);
    protected:
        char* fileName;
        int xsize;
        int ysize;
        string** raw_db;
        string line;
        int rows;
        int cols;
    private:

};

#endif // FILE_H
