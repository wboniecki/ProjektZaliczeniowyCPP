#ifndef MOVIES_H
#define MOVIES_H
#include "File.h"

class Movies : public File
{
    public:
        Movies(char* fileName, int xsize, int ysize);
        virtual ~Movies();

    protected:

    private:
};

#endif // MOVIES_H
