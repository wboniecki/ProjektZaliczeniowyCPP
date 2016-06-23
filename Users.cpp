#include "Users.h"

Users::Users(char* fileName, int xsize, int ysize) : File(fileName, xsize, ysize) {
    hires_db = new Hires(HIRES_FILE, MAX_DB_XSIZE, HIRES_DB_SIZE);
    hires_db->readFile();
}

Users::~Users()
{
    delete hires_db;
}

void Users::showUsersByName(string name, string surname) {
    int result = 0;
    for(int i=0;i<rows;i++) {
            if(name=="" || surname=="") {
                if(raw_db[i][U_NAME] == name || raw_db[i][U_SURNAME] == surname) {
                    result++;
                    cout << "#" << raw_db[i][U_ID] <<", " <<
                            raw_db[i][U_NAME] << ", " <<
                            raw_db[i][U_SURNAME] << ", " <<
                            raw_db[i][U_ADDRESS] << ", " <<
                            raw_db[i][U_CITY] << ", " <<
                            raw_db[i][U_PHONE] << endl;
                             //dodac wyporzyczenia
                }
            } else if(raw_db[i][U_NAME] == name && raw_db[i][U_SURNAME] == surname) {
                    result++;
                    cout << "#" << raw_db[i][U_ID] <<", " <<
                            raw_db[i][U_NAME] << ", " <<
                            raw_db[i][U_SURNAME] << ", " <<
                            raw_db[i][U_ADDRESS] << ", " <<
                            raw_db[i][U_CITY] << ", " <<
                            raw_db[i][U_PHONE] << endl;
                             //dodac wyporzyczenia
            }
    }
    if(result==0) {
        cout << "No matches to " << name << " " << surname << ".";
    }
}

bool Users::isUsernameExist(string username) {
    for (int i=0;i<rows;i++) {
        if(raw_db[i][U_LOGIN] == username)
            return true;
    }
    return false;
}

string Users::getUserId(string username) {
    for (int i=0;i<rows;i++) {
        if(raw_db[i][U_LOGIN] == username)
            return raw_db[i][U_ID];
    }
}

bool Users::isPasswordOk(string login, string pass) {
    for (int i=0;i<rows;i++) {
        if(raw_db[i][U_LOGIN] == login)
            if(raw_db[i][U_PASS] == pass) { // tu bedzie funkcja hashujaco-solaca
                //cout << generateSalt("qwertyuiopasdfgh") << endl;
                return true;
            } else {
                return false;
            }
    }
}

string Users::generateSalt(string username) {
    string salt = "";
    for(int i=0;i<username.length();i++) {
        salt += username[username.length()-1-i];
        // string nmb = std::to_string(((i+1)*2+2)/2);
        ostringstream ss;
        ss << ((((i+1)*(i+1)+username.length())/2)*(i+2))/2;
        string nmb = ss.str();
        salt += nmb;
        salt +=username[i];
    }
    cout << salt.length() << endl;
    return salt;
}

void Users::showAllUsers() {
    for(int i=0;i<rows;i++) {
        cout << "#" << raw_db[i][U_ID] <<", " <<
                            raw_db[i][U_NAME] << ", " <<
                            raw_db[i][U_SURNAME] << ", " <<
                            raw_db[i][U_ADDRESS] << ", " <<
                            raw_db[i][U_CITY] << ", " <<
                            raw_db[i][U_PHONE] << endl;
    }
}

bool Users::isUserCanBeDel(string id) {
    if(hires_db->currentUserHiresCount(id) == 0) {
        return true;
    }
    cout << "Przed usunieciem nalezy oddac filmy!" << endl;
    return false;
}

void Users::remUser(string id) {
    bool isDel = false;
    for (int i=0;i<rows;i++) {
        if(raw_db[i][U_ID] == id) {
            isDel = true;
        }
        if(isDel && i<rows-1) {
            raw_db[i][U_ID] = raw_db[i+1][U_ID];
            //etc
            raw_db[i][U_LOGIN] = raw_db[i+1][U_LOGIN];
            raw_db[i][U_PASS] = raw_db[i+1][U_PASS];
            raw_db[i][U_ACCESS] = raw_db[i+1][U_ACCESS];
            raw_db[i][U_NAME] = raw_db[i+1][U_NAME];
            raw_db[i][U_SURNAME] = raw_db[i+1][U_SURNAME];
            raw_db[i][U_ADDRESS] = raw_db[i+1][U_ADDRESS];
            raw_db[i][U_CITY] = raw_db[i+1][U_CITY];
            raw_db[i][U_PHONE] = raw_db[i+1][U_PHONE];
        }
    }
    rows--;
    raw_db[rows][U_ID] = "";
    raw_db[rows][U_LOGIN] = "";
    raw_db[rows][U_PASS] = "";
    raw_db[rows][U_ACCESS] = "";
    raw_db[rows][U_NAME] = "";
    raw_db[rows][U_SURNAME] = "";
    raw_db[rows][U_ADDRESS] = "";
    raw_db[rows][U_CITY] = "";
    raw_db[rows][U_PHONE] = "";
}

bool Users::isIdExist(string id) {
    for(int i=0;i<rows;i++) {
        if(raw_db[i][U_ID] == id) {
            return true;
        }
    }
    cout << id << " <- takie ID nie istnieje!" << endl;
    return false;
}

void Users::modUser(string id) {
    int user_row;
    for(int i=0;i<rows;i++) {
        if(raw_db[i][U_ID] == id) {
            user_row = i;
        }
    }
    START:
        string new_value = "";
        cout << "1. Imie" << endl;
        cout << "2. Naziwsko" << endl;
        cout << "3. Haslo" << endl;
        cout << "4. Adres" << endl;
        cout << "5. Telefon" << endl;
        cout << "0. POWROT DO MENU" << endl;
        cout << "Wybierz co chcesz modyfikowac: ";
        int choice;
        cin >> choice;
        while(!cin.good() || choice < 0 || choice > 5) {
            cin.clear();
            cin.sync();
            cout << "Wrong number." << endl;
            cout << "Wybierz co chcesz modyfikowac: ";
            cin >> choice;
        }
        if(choice==0) {
            goto KONIEC;
        }
        cout << "Podaj nowa wartosc: ";
        cin.ignore(100, '/n');
        getline(cin,new_value);
        //cin >> new_value;
            while(!cin.good()) {
            cin.clear();
            cin.sync();
            cout << "Wrong value." << endl;
            cout << "Podaj nowa wartosc: ";
            //cin >> new_value;
            cin.ignore(100, '\n');
            getline(cin,new_value);
        }

        switch(choice) {
            case 1: //imie
                raw_db[user_row][U_NAME] = new_value;
                break;
            case 2: //nazwisko
                raw_db[user_row][U_SURNAME] = new_value;
                break;
            case 3: //haslo
                raw_db[user_row][U_PASS] = new_value;
                break;
            case 4: //adres
                raw_db[user_row][U_ADDRESS] = new_value;
                break;
            case 5: //telefon
                raw_db[user_row][U_PHONE] = new_value;
                break;
            default:
                goto START;
                break;
        }
        cout << "Chcesz cos jeszcze modyfikowac?" << endl;
        cout << "1. TAK" << endl;
        cout << "2. NIE" << endl;
        cin >> choice;
        while(!cin.good() || choice < 1 || choice > 2) {
            cin.clear();
            cin.sync();
            cout << "Wrong number." << endl;
            cout << "Chcesz cos jeszcze modyfikowac?" << endl;
            cin >> choice;
        }
        KONIEC:
        if(choice==1) {
            goto START;
        }
}

void Users::addUser(string* new_user) {
    int new_id = atoi(raw_db[rows-1][U_ID].c_str());
    new_id++;
    ostringstream ss;
    ss << new_id;
    raw_db[rows][U_ID] = ss.str();
    raw_db[rows][U_LOGIN] = new_user[U_LOGIN];
    raw_db[rows][U_PASS] = new_user[U_PASS];
    raw_db[rows][U_ACCESS] = "1"; //user default
    raw_db[rows][U_NAME] = new_user[U_NAME];
    raw_db[rows][U_SURNAME] = new_user[U_SURNAME];
    raw_db[rows][U_ADDRESS] = new_user[U_ADDRESS];
    raw_db[rows][U_CITY] = new_user[U_CITY];
    raw_db[rows][U_PHONE] = new_user[U_PHONE];
    time_t t;
    time(&t); // pobiera czas kalendarzowy
    string data = ctime(&t);
    stringstream sdata(data);
    //w dacie na koncu znajduje sie enter
    //nalezy go usunac
    getline(sdata,data,'\n');
    raw_db[rows][U_REGDATE] = data;
    rows++;
    cout << "Dodano u¿ytkownika:" << endl;
    cout << "#" << raw_db[rows-1][U_ID] << " , " <<
            raw_db[rows-1][U_LOGIN] << " , " <<
            raw_db[rows-1][U_PASS] << " , " <<
            raw_db[rows-1][U_ACCESS] << " , " <<
            raw_db[rows-1][U_NAME] << " , " <<
            raw_db[rows-1][U_SURNAME] << " , " <<
            raw_db[rows-1][U_ADDRESS] << " , " <<
            raw_db[rows-1][U_CITY] << " , " <<
            raw_db[rows-1][U_PHONE] << endl;
}

string Users::getUserFullName(string id) {
    for(int i=0;i<rows;i++) {
        if(raw_db[i][U_ID]==id) {
            return raw_db[i][U_NAME]+" "+raw_db[i][U_SURNAME];
        }
    }
}

bool Users::isUserAdmin(string id) {
    for(int i=0;i<rows;i++) {
        if(raw_db[i][U_ID]==id) {
            if(raw_db[i][U_ACCESS]=="0") {
                return true;
            } else {
                return false;
            }
        }
    }
}

void Users::makeUserAdmin(string id) {
    for(int i=0;i<rows;i++) {
        if(raw_db[i][U_ID]==id) {
            raw_db[i][U_ACCESS] = "0";
            cout << "Uzytkownik " << raw_db[i][U_NAME] << " " <<
                    raw_db[i][U_SURNAME] << " zostal administratorem" << endl;
        }
    }
}

void Users::makeAdminUser(string id) {
    for(int i=0;i<rows;i++) {
        if(raw_db[i][U_ID]==id) {
            raw_db[i][U_ACCESS] = "1";
            cout << "Administrator " << raw_db[i][U_NAME] << " " <<
                    raw_db[i][U_SURNAME] << " zostal normalnym uzytkownikem" << endl;
        }
    }
}

void Users::showUserById(string id) {
    for(int i=0;i<rows;i++) {
        if(raw_db[i][U_ID] == id) {
                    cout << "#" << raw_db[i][U_ID] <<", " <<
                            raw_db[i][U_NAME] << ", " <<
                            raw_db[i][U_SURNAME] << ", " <<
                            raw_db[i][U_ADDRESS] << ", " <<
                            raw_db[i][U_CITY] << ", " <<
                            raw_db[i][U_PHONE] << endl;
        }
    }
}
