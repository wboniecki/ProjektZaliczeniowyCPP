#include "Program.h"

Program::Program() {
    /*Inicjalizacja programu, wczytanie plików bazy do pamiêci programu*/
    Movies movie_db(MOVIES_FILE, MAX_DB_XSIZE, MOVIES_DB_SIZE);
    movie_db.readFile();
    Users users_db(USERS_FILE, MAX_DB_XSIZE, USERS_DB_SIZE);
    users_db.readFile();
    Hires hires_db(HIRES_FILE, MAX_DB_XSIZE, HIRES_DB_SIZE);
    hires_db.readFile();

    isLogin = false;
    //movie_db.showRawDb();
}

Program::~Program() {
    //dtor
}

void Program::start() {
    /*Glowna petla programu*/
    if(!isLogin) {
        cout << "Witaj w wypozyczalni filmow! Zaloguj sie aby rozpoczac" << endl;
        string username;
        string password;
        cout << "username: ";
        cin >> username;
        while(!cin.good() || username.length() > 16) {
            cin.clear();
            cin.sync();
            cout << "Too long! Try again." << endl;
            cout << "username: ";
            cin >> username;
        }
        cout << "password: ";
        cin >> password;
        while(!cin.good() || password.length() > 16) {
            cin.clear();
            cin.sync();
            cout << "Too long! Try again." << endl;
            cout << "password: ";
            cin >> password;
        }

        login(username,password);
    } else {

    }

}

void Program::login(string username, string password) {

}
