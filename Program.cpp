#include "Program.h"

Program::Program() {
    /*Inicjalizacja programu, wczytanie plików bazy do pamiêci programu*/
    //Movies mb(MOVIES_FILE, MAX_DB_XSIZE, MOVIES_DB_SIZE);
    //mb.readFile();
    movie_db = new Movies(MOVIES_FILE, MAX_DB_XSIZE, MOVIES_DB_SIZE);
    movie_db->readFile();
    //movie_db->showRawDb();
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
    START:
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
        cout << "Witaj, " << users_db->getUserFullName(login_id) << endl; // tu dodac powitanie imienne
        int choice = -1; //basic menu
        cout << "MENU:" << endl;
        cout << "0. KONIEC PROGRAMU." << endl;
        cout << "1. Wypozycz film" << endl;
        cout << "2. Oddaj film" << endl;
        cout << "3. Moje wypozyczenia" << endl;
        cout << "4. Pokaz dostepne filmy" << endl;
        cout << "5. Pokaz wszystkie filmy" << endl;
        cout << "6. Pokaz film szczegolowo" << endl;
        if(users_db->isUserAdmin(login_id)) {
            cout << "OPCJE ADMINISTRATORA:" << endl;
            cout << "101. Dodaj uzytkownika" << endl;
            cout << "102. Usun uzytkownia(po id)" << endl;
            cout << "103. Modyfikuj uzytkownika(po id)" << endl;
            cout << "104. Dodaj film" << endl;
            cout << "105. Usun film" << endl;
            cout << "106. Modyfikuj film" << endl;
            cout << "121. Szukaj uzytkownika(po id)" << endl;
            cout << "122. Szukaj uzytkownika(po imieniu i/lub nazwisku)" << endl;
            cout << "123. Listuj wszystkich uzytkownikow (id/imie/nazwisko)" << endl;
            cout << "124. Listuj wszystkich uzytkownikow (full info)" << endl;
            //pobieranie dla admina
            cout << "Wybierz pozycje menu: ";
            cin >> choice;
            while(!cin.good() ||
                  choice < 0 ||
                  choice > 10 && choice < 101 ||
                  choice > 124) {
            cin.clear();
            cin.sync();
            cout << "Wrong number." << endl;
            cout << "Wybierz raz jeszcze: ";
            cin >> choice;
            }
        } else {
            //pobieranie dla zwyklego usera
            cout << "Wybierz pozycje menu: ";
            cin >> choice;
            while(!cin.good() || choice < 0 || choice > 10) {
            cin.clear();
            cin.sync();
            cout << "Wrong number." << endl;
            cout << "Wybierz raz jeszcze: ";
            cin >> choice;
            }

        }

        switch(choice) {
        case 0: //wyjscie z programu
            cout << "Do zobaczenia!";
            break;
        case 1: // hire movie
            hireMovie();
            goto START;
            break;
        case 101: // Add user
            addUser();
            goto START;
            break;
        case 102: // Rem user
            remUser();
            goto START;
            break;
        case 103: //mod user
            modUser();
            goto START;
            break;
        case 104: //add movie
            addMovie();
            goto START;
            break;
        case 105: //rem movie
            remMovie();
            goto START;
            break;
        case 106: //mod movie
            modMovie();
            goto START;
            break;
        default:
            break;
        }
    }

}

void Program::login(string username, string password) {
    //sprawdzanie
    if(users_db->isUsernameExist(username)){
            if(users_db->isPasswordOk(username, password)) {
                isLogin = true;
                login_id = users_db->getUserId(username);
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

void Program::addUser() {
    string* new_user = new string[USERS_DB_SIZE];
    for(int i=0;i<USERS_DB_SIZE;i++) {
        new_user[i] = "";
    }
    cout << endl;
    cout << "Witaj w kreatorze dodawania uzytkownika!" << endl;
    cout << "W kazdej chwili mozesz zrezygnowac wpisujac: WYJSCIE" << endl;

    /*IMIE*/
    cout << "Podaj imie: ";
    cin >> new_user[U_NAME];
    while(!cin.good() || new_user[U_NAME] == "") {
        cin.clear();
        cin.sync();
        cout << "Wybierz raz jeszcze: ";
        cin >> new_user[U_NAME];
    }
    if(new_user[U_NAME] == "WYJSCIE") {
            goto KONIEC;
    }
    /*NAZWISKO*/
    cout << "Podaj nazwisko: ";
    cin >> new_user[U_SURNAME];
    while(!cin.good() || new_user[U_SURNAME] == "") {
        cin.clear();
        cin.sync();
        cout << "Wybierz raz jeszcze: ";
        cin >> new_user[U_SURNAME];
    }
    if(new_user[U_SURNAME] == "WYJSCIE") {
        goto KONIEC;
    }
    /*LOGIN*/
    cout << "Podaj login: ";
    cin >> new_user[U_LOGIN];
    while(!cin.good() || users_db->isUsernameExist(new_user[U_LOGIN]) ||
          new_user[U_LOGIN] == "") {
        cin.clear();
        cin.sync();
        cout << "Podany login jest zly lub istnieje juz w bazie." <<endl;
        cout << "Wybierz raz jeszcze: ";
        cin >> new_user[U_LOGIN];
    }
    if(new_user[U_LOGIN] == "WYJSCIE") {
        goto KONIEC;
    }
    /*HASLO*/
    cout << "Podaj haslo: ";
    cin >> new_user[U_PASS];
    while(!cin.good() || new_user[U_PASS] == "") {
        cin.clear();
        cin.sync();
        cout << "Wybierz raz jeszcze: ";
        cin >> new_user[U_PASS];
    }
    if(new_user[U_PASS] == "WYJSCIE") {
        goto KONIEC;
    }
    /*MIEJSCOWOSC*/
    cout << "Podaj miejscowosc: ";
    //cin >> new_user[U_CITY];
    cin.ignore(100, '\n');
    getline(cin,new_user[U_CITY]);
    while(!cin.good() || new_user[U_CITY] == "") {
        cin.clear();
        cin.sync();
        cout << "Wybierz raz jeszcze: ";
        cin.ignore(100, '\n');
        getline(cin,new_user[U_CITY]);
    }
    if(new_user[U_CITY] == "WYJSCIE") {
        goto KONIEC;
    }
    /*ADRES*/
    cout << "Podaj adres: ";
    //cin >> new_user[U_ADDRESS];
    cin.ignore(100, '\n');
    getline(cin,new_user[U_ADDRESS]);
    while(!cin.good() || new_user[U_ADDRESS] == "") {
        cin.clear();
        cin.sync();
        cout << "Wybierz raz jeszcze: ";
        cin.ignore(100, '\n');
        getline(cin,new_user[U_ADDRESS]);
    }
    if(new_user[U_ADDRESS] == "WYJSCIE") {
        goto KONIEC;
    }
    /*TELEFON*/
    cout << "Podaj telefon: ";
    cin >> new_user[U_PHONE];
    while(!cin.good()) {
        cin.clear();
        cin.sync();
        cout << "Wybierz raz jeszcze: ";
        cin >> new_user[U_PHONE];
    }
    if(new_user[U_PHONE] == "WYJSCIE") {
        goto KONIEC;
    }
    users_db->addUser(new_user);
    users_db->saveFile();

KONIEC:
    delete[] new_user;
}

void Program::remUser() {
    int rem_id;
    START:
    cout << "Podaj ID uzytkownika do usuniecia: ";
    cin >> rem_id;
    while(!cin.good()) {
        cin.clear();
        cin.sync();
        cout << "Wybierz raz jeszcze: ";
        cin >> rem_id;
    }
    ostringstream rs;
    rs << rem_id;
    if(!users_db->isIdExist(rs.str())) {
        cout << "Uzytkownik o podanym ID nieistnieje!" << endl;
        goto START;
    }
    //users_db->isUserCanBeDel();
    users_db->showUserById(rs.str());
    cout << "Usunac uzytkownika?" << endl;
    cout << "1. TAK" << endl;
    cout << "2. NIE (wybierz ponownie)" << endl;
    cout << "3. Powrot do menu." << endl;
    int choice = 0;
    cin >> choice;
    while(!cin.good() || choice < 1 || choice > 3) {
        cin.clear();
        cin.sync();
        cout << "Wybierz raz jeszcze: ";
        cin >> choice;
    }
    switch(choice) {
    case 1: //TAK
        users_db->remUser(rs.str());
        users_db->saveFile();
        break;
    case 2: // NIE
        goto START;
        break;
    default:
        break;
    }
}

void Program::modUser() {
    int mod_id;
    START:
    cout << "Podaj ID uzytkownika do modyfikacji: ";
    cin >> mod_id;
    while(!cin.good()) {
        cin.clear();
        cin.sync();
        cout << "Wybierz raz jeszcze: ";
        cin >> mod_id;
    }
    ostringstream ms;
    ms << mod_id;
    if(!users_db->isIdExist(ms.str())) {
        cout << "Uzytkownik o podanym ID nieistnieje!" << endl;
        goto START;
    }
    users_db->showUserById(ms.str());
    users_db->modUser(ms.str());
    users_db->saveFile();
    users_db->showUserById(ms.str());
}

void Program::addMovie() {
    string* new_movie = new string[MOVIES_DB_SIZE];
    for(int i=0;i<MOVIES_DB_SIZE;i++) {
        new_movie[i] = "";
    }
    cout << endl;
    cout << "Witaj w kreatorze dodawania filmu!" << endl;
    cout << "W kazdej chwili mozesz zrezygnowac wpisujac: WYJSCIE" << endl;
    /*DATA DODANIA*/
    time_t t;
    time(&t); // pobiera czas kalendarzowy
    string data = ctime(&t);
    stringstream sdata(data);
    //w dacie na koncu znajduje sie enter
    //nalezy go usunac
    getline(sdata,data,'\n');
    new_movie[M_ADDDATE] = data;
    /*TYTUL*/
    cout << "Podaj tytul filmu:" << endl;
    cin.ignore(500, '\n');
    getline(cin,new_movie[M_TITLE]);
    while(!cin.good() || new_movie[M_TITLE] == "") {
        cin.clear();
        cin.sync();
        cout << "Wybierz raz jeszcze: ";
        getline(cin,new_movie[M_TITLE]);
    }
    if(new_movie[M_TITLE] == "WYJSCIE") {
        goto KONIEC;
    }
    /*GATUNEK*/
    cout << "Podaj gatunek filmu:" << endl;
    getline(cin,new_movie[M_TYPE]);
    while(!cin.good() || new_movie[M_TYPE] == "") {
        cin.clear();
        cin.sync();
        cout << "Wybierz raz jeszcze: ";
        getline(cin,new_movie[M_TYPE]);
    }
    if(new_movie[M_TYPE] == "WYJSCIE") {
        goto KONIEC;
    }
    /*DATA PREMIERY*/
    cout << "Podaj date premiery filmu: " << endl;
    getline(cin,new_movie[M_DATE]);
    while(!cin.good() || new_movie[M_DATE] == "") {
        cin.clear();
        cin.sync();
        cout << "Wybierz raz jeszcze: ";
        getline(cin,new_movie[M_DATE]);
    }
    if(new_movie[M_DATE] == "WYJSCIE") {
        goto KONIEC;
    }
    /*REZYSER*/
    cout << "Podaj rezysera filmu: " << endl;
    getline(cin,new_movie[M_DIRECTOR]);
    while(!cin.good() || new_movie[M_DIRECTOR] == "") {
        cin.clear();
        cin.sync();
        cout << "Wybierz raz jeszcze: ";
        getline(cin,new_movie[M_DIRECTOR]);
    }
    if(new_movie[M_DIRECTOR] == "WYJSCIE") {
        goto KONIEC;
    }
    /*CZAS TRWANIA*/
    cout << "Podaj czas trwania filmu w minutach: " << endl;
    getline(cin,new_movie[M_TIME]);
    while(!cin.good() || new_movie[M_TIME] == "") {
        cin.clear();
        cin.sync();
        cout << "Wybierz raz jeszcze: ";
        getline(cin,new_movie[M_TIME]);
    }
    if(new_movie[M_TIME] == "WYJSCIE") {
        goto KONIEC;
    }
    /*OCENA*/
    cout << "Podaj ocene filmu(1-10): " << endl;
    getline(cin,new_movie[M_RATING]);
    while(!cin.good() || new_movie[M_RATING] == "") {
        cin.clear();
        cin.sync();
        cout << "Wybierz raz jeszcze: ";
        getline(cin,new_movie[M_RATING]);
    }
    if(new_movie[M_RATING] == "WYJSCIE") {
        goto KONIEC;
    }
    /*OPIS*/
    cout << "Podaj krotki opis filmu: " << endl;
    getline(cin,new_movie[M_DESCRIPTION]);
    while(!cin.good() || new_movie[M_DESCRIPTION] == "") {
        cin.clear();
        cin.sync();
        cout << "Wybierz raz jeszcze: ";
        getline(cin,new_movie[M_DESCRIPTION]);
    }
    if(new_movie[M_DESCRIPTION] == "WYJSCIE") {
        goto KONIEC;
    }
    /*AKTORZY*/
    cout << "Podaj aktorow filmu: " << endl;
    getline(cin,new_movie[M_ACTORS]);
    while(!cin.good() || new_movie[M_ACTORS] == "") {
        cin.clear();
        cin.sync();
        cout << "Wybierz raz jeszcze: ";
        getline(cin,new_movie[M_ACTORS]);
    }
    if(new_movie[M_ACTORS] == "WYJSCIE") {
        goto KONIEC;
    }

    movie_db->addMovie(new_movie);
    movie_db->saveFile();
    movie_db->showMovieInfoFull(new_movie[M_TITLE]);

    KONIEC:
    delete[] new_movie;
}

void Program::modMovie() {
    cout << "Podaj film ktory chcesz modyfikowac:" << endl;
    string title;
    cin.ignore(100, '\n');
    getline(cin,title);
    while(!cin.good()) {
            cin.clear();
            cin.sync();
            cout << "Wybierz raz jeszcze: ";
            getline(cin,title);
    }
    movie_db->modMovie(movie_db->changeToNonComma(title));
    movie_db->saveFile();
}

void Program::remMovie() {
    cout << "Podaj film ktory chcesz usunac:" << endl;
    string title;
    cin.ignore(100, '\n');
    getline(cin,title);
    while(!cin.good()) {
            cin.clear();
            cin.sync();
            cout << "Wybierz raz jeszcze: ";
            getline(cin,title);
    }
    if(movie_db->isMovieExist(movie_db->changeToNonComma(title))) {
        movie_db->removeMovie(movie_db->changeToNonComma(title));
        movie_db->saveFile();
    }
}

void Program::hireMovie() {
    cout << "Podaj film ktory chcesz wypozyczyc:" << endl;
    string title;
    cin.ignore(100, '\n');
    getline(cin,title);
    while(!cin.good()) {
            cin.clear();
            cin.sync();
            cout << "Wybierz raz jeszcze: ";
            getline(cin,title);
    }
    if(!movie_db->isMovieExist(title)) {
        cout << "Film nie istnieje!" << endl;
        goto KONIEC;
    }
    if(movie_db->hireMovie(login_id,title)) {
        cout << "Wypozyczono: " << title << endl;
    }

    KONIEC:
        cout << endl;
}
