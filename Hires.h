#ifndef HIRES_H
#define HIRES_H
#include "File.h"

class Hires : public File
{
    public:
        Hires(char* fileName, int xsize, int ysize);
        virtual ~Hires();

    protected:

    private:
};

#endif // HIRES_H