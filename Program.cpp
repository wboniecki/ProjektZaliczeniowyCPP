#include "Program.h"

Program::Program() {
    /*Inicjalizacja programu, wczytanie plików bazy do pamiêci programu*/
    //Movies mb(MOVIES_FILE, MAX_DB_XSIZE, MOVIES_DB_SIZE);
    //mb.readFile();
    movie_db = new Movies(MOVIES_FILE, MAX_DB_XSIZE, MOVIES_DB_SIZE);
    movie_db->readFile();
    users_db = new Users(USERS_FILE, MAX_DB_XSIZE, USERS_DB_SIZE);
    users_db->readFile();

    isLogin = false;
    //movie_db->showRawDb();
}

Program::~Program() {
    //dtor
    delete movie_db;
    delete users_db;
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
        cout << "Witaj" << endl; // tu dodac powitanie imienne
        //users_db.showRawDb();
        movie_db->showRawRecord(1);
    }

}

void Program::login(string username, string password) {
    //sprawdzanie
    if(users_db->isUsernameExist(username)){
            if(users_db->isPasswordOk(username, password)) {
                isLogin = true;
                login_id = atoi(users_db->getUserId(username).c_str());
                cout << "ZALOGOWANO!" << endl;
            }
            else {
                cout << "Wrong username or password. Try again." << endl;
            }
    } else {
        cout << "Wrong username or password. Try again." << endl;
    }

    start();
}
