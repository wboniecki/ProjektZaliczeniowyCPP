#include "File.h"

File::File(char* fileName) {
    File::fileName = fileName;
}

File::~File()
{
    //dtor
}

void File::openFile() {
    //ifstream
    ifstream f(fileName);
    //do {
    //czytanie pliku np do tablicy
    //getline(f,line);
    //} while(!plik.eof())
}

void File::closeFile() {
//    f.close();
}
