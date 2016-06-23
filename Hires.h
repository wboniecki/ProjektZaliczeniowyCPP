#ifndef HIRES_H
#define HIRES_H
#include "File.h"

#define H_ID 0
#define H_TITLE 1
#define H_HIREDATE 2
#define H_RETURNDATE 3
#define H_DELIVERDATE 4

class Hires : public File
{
    public:
        Hires(char* fileName, int xsize, int ysize);
        virtual ~Hires();
        int currentUserHiresCount(string id);
        void setTitle(string oldVal, string newVal);
        bool isMovieHire(string title);
    protected:

    private:
};

#endif // HIRES_H
