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
                cout << generateSalt("qwertyuiopasdfgh") << endl;
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
