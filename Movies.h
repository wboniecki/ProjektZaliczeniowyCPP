#ifndef MOVIES_H
#define MOVIES_H
#include "File.h"

#define M_TITLE 0
#define M_TYPE 1
#define M_DATE 2
#define M_DIRECTOR 3
#define M_TIME 4
#define M_RATING 5
#define M_DESCRIPTION 6
#define M_ACTORS 7
#define M_ADDDATE 8

#include "Config.h"
#include "Hires.h"
#include <algorithm>

class Movies : public File
{
    public:
        Movies(char* fileName, int xsize, int ysize);
        virtual ~Movies();
        string changeToComma(string movie_nc);
        string changeToNonComma(string movie_c);
        void addMovie(string* new_movie_c);
        void modMovie(string title);
        void removeMovie(string title);
        void showAllMovies();
        void showNonHiresMovies();
        void showMovieInfoFull(string title);
        bool isMovieExist(string title);
        bool hireMovie(string id, string title);
        void showUserHiredMovie(string id);
        bool isUserHaveHiredMovie(string id);
        void returnMovie(string id, string title);
        void showAllHires();
    protected:

    private:
        Hires* hires_db;

};

#endif // MOVIES_H
