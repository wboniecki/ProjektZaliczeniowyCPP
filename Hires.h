#ifndef HIRES_H
#define HIRES_H
#include "File.h"

#define H_ID 0
#define H_TITLE 1
#define H_HIREDATE 2
#define H_RETURNDATE 3
#define H_DELIVERDATE 4

#define USERLIMIT 2

#include "time.h"

class Hires : public File
{
    public:
        Hires(char* fileName, int xsize, int ysize);
        virtual ~Hires();
        void hireMovie(string id, string title);
        int currentUserHiresCount(string id);
        bool canUserHire(string id);
        void setTitle(string oldVal, string newVal);
        bool isMovieHire(string title);
        void showUserHires(string id);
        bool isUserHaveThisMovie(string id, string title);
        void returnMovie(string id, string title);
    protected:

    private:
};

#endif // HIRES_H
