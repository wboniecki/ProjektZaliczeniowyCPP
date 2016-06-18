#ifndef USERS_H
#define USERS_H
#include "File.h"

class Users : public File
{
    public:
        Users(char* fileName, int xsize, int ysize);
        virtual ~Users();

    protected:

    private:
};

#endif // USERS_H
