#ifndef PROGRAM_H
#define PROGRAM_H
#include "Config.h"
#include <limits>
#include <cstdlib>

class Program
{
    public:
        Program();
        virtual ~Program();
        void start();
    protected:

    private:
        void login(string username, string password);
        string login_id;
        bool isLogin;
        void addUser();
        void remUser();
        void modUser();
        void addMovie();
        Movies* movie_db;
        Users* users_db;
};

#endif // PROGRAM_H
