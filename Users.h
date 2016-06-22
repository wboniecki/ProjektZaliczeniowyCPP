#ifndef USERS_H
#define USERS_H
#include "File.h"

#define U_ID 0
#define U_LOGIN 1
#define U_PASS 2
#define U_ACCESS 3
#define U_NAME 4
#define U_SURNAME 5
#define U_ADDRESS 6
#define U_CITY 7
#define U_PHONE 8
#define U_REGDATE 9

/*INCLUDES*/
#include "time.h"
#include <cstdlib>
#include "Config.h"
#include "Hires.h"


class Users : public File
{
    public:
        Users(char* fileName, int xsize, int ysize);
        virtual ~Users();
        void showUsersByName(string name, string surname);
        bool isUsernameExist(string username);
        bool isPasswordOk(string login, string pass);
        string getUserId(string username);
        void showAllUsers();
        bool isUserCanBeDel(string id);
        void remUser(string id);
        bool isIdExist(string id);
        void modUser(string id);
        void addUser(string* new_user);
        string getUserFullName(string id);
        bool isUserAdmin(string id);
        void makeUserAdmin(string id);
        void makeAdminUser(string id);
        void showUserById(string id);
    protected:

    private:
        Hires* hires_db;
        string generateSalt(string username);
};

#endif // USERS_H
