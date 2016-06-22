#include "Movies.h"

Movies::Movies(char* fileName, int xsize, int ysize) : File(fileName, xsize, ysize) {
    hires_db = new Hires(HIRES_FILE, MAX_DB_XSIZE, HIRES_DB_SIZE);
    hires_db->readFile();
}

Movies::~Movies() {
    delete hires_db;
}
string Movies::changeToComma(string movie_nc) {
    replace(movie_nc.begin(),movie_nc.end(),'/',',');
    return movie_nc;
}

string Movies::changeToNonComma(string movie_c) {
    replace(movie_c.begin(),movie_c.end(),',','/');
    return movie_c;
}

void Movies::addMovie(string* new_movie_c) {
    raw_db[rows][M_TITLE] = changeToNonComma(new_movie_c[M_TITLE]);
    raw_db[rows][M_TYPE] = changeToNonComma(new_movie_c[M_TYPE]);
    raw_db[rows][M_DATE] = changeToNonComma(new_movie_c[M_DATE]);
    raw_db[rows][M_DIRECTOR] = changeToNonComma(new_movie_c[M_DIRECTOR]);
    raw_db[rows][M_TIME] = changeToNonComma(new_movie_c[M_TIME]);
    raw_db[rows][M_RATING] = changeToNonComma(new_movie_c[M_RATING]);
    raw_db[rows][M_DESCRIPTION] = changeToNonComma(new_movie_c[M_DESCRIPTION]);
    raw_db[rows][M_ACTORS] = changeToNonComma(new_movie_c[M_ACTORS]);
    raw_db[rows][M_ADDDATE] = changeToNonComma(new_movie_c[M_ADDDATE]);
    rows++;
}

void Movies::showMovieInfoFull(string title) {
    bool isFind = false;
    for(int i=0;i<rows;i++) {
        if(raw_db[i][M_TITLE] == title) {
            isFind = true;
            cout << changeToComma(raw_db[i][M_TITLE]) << endl;
            cout << "Gatunek: " << changeToComma(raw_db[i][M_TYPE]) << endl;
            cout << "Data premiery: " << changeToComma(raw_db[i][M_DATE]) << endl;
            cout << "Rezyser: " << changeToComma(raw_db[i][M_DIRECTOR]) << endl;
            cout << "Czas trwania: " << changeToComma(raw_db[i][M_TIME]) << " minut" << endl;
            cout << "Ocena: " << changeToComma(raw_db[i][M_RATING]) << endl;
            cout << "Opis:" << endl;
            cout << changeToComma(raw_db[i][M_DESCRIPTION]) << endl;
            cout << "Aktorzy: " << changeToComma(raw_db[i][M_ACTORS]) << endl;
            cout << "Dodano: " << changeToComma(raw_db[i][M_ADDDATE]) << endl;
        }
    }
    if(!isFind) {
        cout << title << " not found in database! :(";
    }
}
