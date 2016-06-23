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

void Movies::modMovie(string title) {
    int m_pos = -1;
    string new_value;
    if(!isMovieExist(title)) {
        goto KONIEC;
    }
    for(int i=0;i<rows;i++) {
        if(raw_db[i][M_TITLE] == title) {
            m_pos = i;
        }
    }
    START:
    cout << "Wybierz co chcesz modyfikowac" << endl;
    cout << "1. Tytul" << endl;
    cout << "2. Typ" << endl;
    cout << "3. Data" << endl;
    cout << "4. Rezyser" << endl;
    cout << "5. Czas" << endl;
    cout << "6. Ocena" << endl;
    cout << "7. Aktorzy" << endl;
    cout << "0. Powrot do menu" << endl;
    int choice;
    cin >> choice;
    while(!cin.good() || choice < 0 || choice > 7) {
            cin.clear();
            cin.sync();
            cout << "Wrong number." << endl;
            cout << "Wybierz raz jeszcze: ";
            cin >> choice;
    }
    if(choice!=0) {
        cout << "Wprowadz nowa wartosc:" << endl;
        cin.ignore(100, '\n');
        getline(cin,new_value);
        while(!cin.good()) {
                cin.clear();
                cin.sync();
                cout << "Blad. Wybierz raz jeszcze: ";
                getline(cin,new_value);
        }
    }
    new_value = changeToNonComma(new_value);
    switch (choice) {
    case 0:
        goto KONIEC;
        break;
    case 1: //Tytul
        raw_db[m_pos][M_TITLE] = new_value;
        hires_db->setTitle(title, new_value);
        hires_db->saveFile();
        break;
    case 2: //Typ
        raw_db[m_pos][M_TYPE] = new_value;
        break;
    case 3: //Data
        raw_db[m_pos][M_DATE] = new_value;
        break;
    case 4: //Rezyser
        raw_db[m_pos][M_DIRECTOR] = new_value;
        break;
    case 5: //Czas
        raw_db[m_pos][M_TIME] = new_value;
        break;
    case 6: //Ocena
        raw_db[m_pos][M_RATING] = new_value;
        break;
    case 7: //Akotrzy
        raw_db[m_pos][M_ACTORS] = new_value;
        break;
    default:
        break;
    }
    goto START;
    KONIEC:
    showMovieInfoFull(raw_db[m_pos][M_TITLE]);
}

void Movies::removeMovie(string title) {
    bool isDel = false;
    //sprawdzenie czy tytul jest wyporzyczony
    if(hires_db->isMovieHire(changeToNonComma(title))) {
        cout << "Nie mozna usunac. Film jest wypozyczony!" << endl;
        goto KONIEC;
    }
    for (int i=0;i<rows;i++) {
        if(raw_db[i][M_TITLE] == title) {
            isDel = true;
        }
        if(isDel && i<rows-1) {
            raw_db[i][M_TITLE] = raw_db[i+1][M_TITLE];
            raw_db[i][M_TYPE] = raw_db[i+1][M_TYPE];
            raw_db[i][M_DATE] = raw_db[i+1][M_DATE];
            raw_db[i][M_DIRECTOR] = raw_db[i+1][M_DIRECTOR];
            raw_db[i][M_TIME] = raw_db[i+1][M_TIME];
            raw_db[i][M_RATING] = raw_db[i+1][M_RATING];
            raw_db[i][M_DESCRIPTION] = raw_db[i+1][M_DESCRIPTION];
            raw_db[i][M_ACTORS] = raw_db[i+1][M_ACTORS];
            raw_db[i][M_ADDDATE] = raw_db[i+1][M_ADDDATE];
        }
    }
    rows--;
    raw_db[rows][M_TITLE] = "";
    raw_db[rows][M_TYPE] = "";
    raw_db[rows][M_DATE] = "";
    raw_db[rows][M_DIRECTOR] = "";
    raw_db[rows][M_TIME] = "";
    raw_db[rows][M_RATING] = "";
    raw_db[rows][M_DESCRIPTION] = "";
    raw_db[rows][M_ACTORS] = "";
    raw_db[rows][M_ADDDATE] = "";
    KONIEC:
    cout << endl;
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
        cout << changeToComma(title) << " not found in database! :(";
    }
    cout << endl;
}

bool Movies::isMovieExist(string title) {
    for(int i=0;i<rows;i++) {
        if(raw_db[i][M_TITLE] == title) {
            return true;
        }
    }
    cout << title << " is not exist in database" << endl;
    return false;
}

bool Movies::hireMovie(string id, string title) {
    if(!hires_db->isMovieHire(title)) {
            if(hires_db->canUserHire(id)) {
                hires_db->hireMovie(id,title);
                hires_db->saveFile();
                return true;
            } else {
                return false;
            }
    } else {
        cout << "Film juz jest wypozyczony!" << endl;
        return false;
    }
}

bool Movies::isUserHaveHiredMovie(string id) {
    if(hires_db->currentUserHiresCount(id)<1) {
        cout << "Nie masz zadnych aktywnych wypozyczen!" << endl;
        return false;
    }
    return true;
}

void Movies::showUserHiredMovie(string id) {
    hires_db->showUserHires(id);
}

void Movies::returnMovie(string id, string title) {
    if(!hires_db->isUserHaveThisMovie(id,title)) {
        cout << "Nie masz filmu: " << changeToComma(title);
        goto KONIEC;
    }
    hires_db->returnMovie(id,title);
    hires_db->saveFile();
    KONIEC:
        cout << endl;
}

void Movies::showNonHiresMovies() {
    for(int i=0;i<rows;i++) {
        if(!hires_db->isMovieHire(raw_db[i][M_TITLE])) {
            cout << changeToComma(raw_db[i][M_TITLE]) <<
                    ",(" << changeToComma(raw_db[i][M_TYPE]) << "), " <<
                    changeToComma(raw_db[i][M_DIRECTOR]) << ", " <<
                    changeToComma(raw_db[i][M_TIME]) << "min." << endl;
        }
    }
}

void Movies::showAllMovies() {
    for(int i=0;i<rows;i++) {
        if(!hires_db->isMovieHire(raw_db[i][M_TITLE])) {
            cout << "WYPOZYCZONE!!! ";
        }
        cout << changeToComma(raw_db[i][M_TITLE]) <<
                ",(" << changeToComma(raw_db[i][M_TYPE]) << "), " <<
                changeToComma(raw_db[i][M_DIRECTOR]) << ", " <<
                changeToComma(raw_db[i][M_TIME]) << "min." << endl;
    }
}

void Movies::showAllHires() {
    hires_db->showRawDb();
}
