#include "Hires.h"

Hires::Hires(char* fileName, int xsize, int ysize) : File(fileName, xsize, ysize) {
    //ctor
}

Hires::~Hires()
{
    //dtor
}

int Hires::currentUserHiresCount(string id) {
    int counter=0;
    for(int i=0;i<rows;i++) {
        if(raw_db[i][H_ID] == id) {
            counter++;
        }
    }
    return counter;
}

bool Hires::canUserHire(string id) {
    if(currentUserHiresCount(id)<USERLIMIT) {
        return true;
    } else {
        cout << "Osiagnales limit wypozyczen!" << endl;
        return false;
    }
}

void Hires::hireMovie(string id, string title) {
    raw_db[rows][H_ID] = id;
    raw_db[rows][H_TITLE] = title;
    time_t t;
    time(&t); // pobiera czas kalendarzowy
    string data = ctime(&t);
    stringstream sdata(data);
    //w dacie na koncu znajduje sie enter
    //nalezy go usunac
    getline(sdata,data,'\n');
    raw_db[rows][H_HIREDATE] = data;
    raw_db[rows][H_RETURNDATE] = "placeholder";
    raw_db[rows][H_DELIVERDATE] = "placeholder";
    rows++;
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
            cout << "Film juz jest wypozyczony!" << endl;
            return true;
        }
    }
    return false;
}
