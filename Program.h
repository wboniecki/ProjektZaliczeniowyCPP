#ifndef PROGRAM_H
#define PROGRAM_H
#include "Config.h"
#include <limits>

class Program
{
    public:
        Program();
        virtual ~Program();
        void start();
    protected:

    private:
        void login(string username, string password);
        bool isLogin;
};

#endif // PROGRAM_H
