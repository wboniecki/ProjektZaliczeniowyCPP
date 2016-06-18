#include "Program.h"

Program::Program() {
    /*Inicjalizacja programu, wczytanie plików bazy do pamiêci programu*/
    Movies movie_db(MOVIES_FILE, MAX_DB_XSIZE, MOVIES_DB_SIZE);
    movie_db.readFile();
    Users users_db(USERS_FILE, MAX_DB_XSIZE, USERS_DB_SIZE);
    users_db.readFile();
    Hires hires_db(HIRES_FILE, MAX_DB_XSIZE, HIRES_DB_SIZE);
    hires_db.readFile();
    //movie_db.showRawDb();
}

Program::~Program() {
    //dtor
}

void Program::start() {
    /*Glowna petla programu*/
    cout << "Witaj w wypozyczalni filmow! Zaloguj sie aby rozpoczac" << endl;
    cout << "username: ";
    //cin
    cout << "password: ";
    //cin

}

void Program::login(string username, string password) {

}
