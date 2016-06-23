#include "Hires.h"

Hires::Hires(char* fileName, int xsize, int ysize) : File(fileName, xsize, ysize) {
    //ctor
}

Hires::~Hires()
{
    //dtor
}

int Hires::currentUserHiresCount(string id) {
    return 0;
}

void Hires::setTitle(string oldVal, string newVal) {
    for(int i=0;i<rows;i++) {
        if(raw_db[i][H_TITLE] == oldVal) {
            raw_db[i][H_TITLE] == newVal;
        }
    }
}

bool Hires::isMovieHire(string title) {
    for(int i=0;i<rows;i++) {
        if(raw_db[i][H_TITLE] == title) {
            return true;
        }
    }
    return false;
}
