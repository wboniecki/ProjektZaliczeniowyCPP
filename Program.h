#ifndef PROGRAM_H
#define PROGRAM_H
#include "Config.h"

class Program
{
    public:
        Program();
        virtual ~Program();
        void start();
        void login(string username, string password);
    protected:

    private:
        bool isLogin = false;
};

#endif // PROGRAM_H
