#include "File.h"

File::File(char* fileName, int xsize, int ysize) {
    File::fileName = fileName;
    File::xsize = xsize;
    File::ysize = ysize;

    raw_db = new string*[xsize];
    for(int i=0; i<xsize;i++) {
        raw_db[i] = new string[ysize];
    }

    for(int i=0;i<xsize;i++) {
        for(int j=0;j<ysize;j++) {
            raw_db[i][j]= ' ';
        }
    }

}

File::~File()
{
    for(int i =0;i<xsize; i++) {
        delete[] raw_db[i];
    }
    delete[] raw_db;
}

void File::readFile() {
    ifstream f(fileName);
    rows = 0;
    do {
    //czytanie pliku do tablicy
        getline(f,line,';');
        stringstream ss(line);
        cols = 0;
        if(line != "") {
            while(getline(ss,line,',')) {
                raw_db[rows][cols] = line;
                if(cols+1 < ysize) {
                    cols++;
                }
            }
        } else {
            break;
        }
        rows++;
    } while(!f.eof());
    f.close();
}

void File::saveFile() {
    ofstream f(fileName);
    cout << "Please do not close program." << endl;
    cout << "Saving..." << endl;
    //zapis tablicy do pliku
    for(int i=0;i<rows;i++) {
        for(int j=0;j<ysize;j++) {
            if(j<ysize-1) {
                f << raw_db[i][j] <<",";
            } else {
                f << raw_db[i][j] <<";";
            }
        }
    }
    cout << "Saving done!" << endl;
    f.close();
}

void File::showRawDb() {
    for(int i=0;i<rows;i++) {
        for(int j=0;j<ysize;j++) {
            cout << raw_db[i][j] <<endl;
        }
    }
}

void File::showRawRecord(int n) {
    if(n<rows && n>0) {
        for(int i=0;i<ysize;i++) {
            cout << raw_db[n][i] << endl;
        }
    }
    else {
        cout << "Wrong record number." << endl;
    }
}
