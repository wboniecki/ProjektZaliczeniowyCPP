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
        int login_id;
        bool isLogin;
        Movies* movie_db;
        Users* users_db;
};

#endif // PROGRAM_H
