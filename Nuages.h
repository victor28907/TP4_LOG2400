#ifndef NUAGES_H
#define NUAGES_H

#include <vector>
#include <string>
#include "point.h"  

using namespace std;

class Nuages {
public:
    Nuages(const vector<Point>& points);

    const vector<Point>& getO() const;
    const vector<Point>& getHash() const;
    void afficherNuages() const;
private:
    vector<Point> o;     
    vector<Point> hash;  
};

#endif 