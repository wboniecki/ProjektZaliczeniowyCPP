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
            return true;
        }
    }
    return false;
}

void Hires::showUserHires(string id) {
    for(int i=0;i<rows;i++) {
        if(raw_db[i][H_ID] == id) {
            cout << raw_db[i][H_TITLE] << ", wypozyczono: " << raw_db[i][H_HIREDATE] <<endl;
        }
    }
}

bool Hires::isUserHaveThisMovie(string id, string title) {
    for(int i=0;i<rows;i++) {
        if(raw_db[i][H_ID]==id && raw_db[i][H_TITLE]==title) {
            return true;
        }
    }
    return false;
}

void Hires::returnMovie(string id, string title) {
    bool isDel = false;
    for (int i=0;i<rows;i++) {
        if(raw_db[i][H_ID] == id && raw_db[i][H_TITLE]==title) {
            isDel = true;
        }
        if(isDel && i<rows-1) {
            raw_db[i][H_ID] = raw_db[i+1][H_ID];
            raw_db[i][H_TITLE] = raw_db[i+1][H_TITLE];
            raw_db[i][H_HIREDATE] = raw_db[i+1][H_HIREDATE];
            raw_db[i][H_RETURNDATE] = raw_db[i+1][H_RETURNDATE];
            raw_db[i][H_DELIVERDATE] = raw_db[i+1][H_DELIVERDATE];
        }
    }
    rows--;
    raw_db[rows][H_ID] = "";
    raw_db[rows][H_TITLE] = "";
    raw_db[rows][H_HIREDATE] = "";
    raw_db[rows][H_RETURNDATE] = "";
    raw_db[rows][H_DELIVERDATE] = "";
}
