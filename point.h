#include <string>
#include <iostream>

using namespace std;

class Point {

public:
    Point(int px, int py);
    void deplacerPoint(int dx, int dy);
    int getX() const;
    int getY() const;
    string getId() const;
    string getTexture() const;

private:
    int x;
    int y;
    string id;
    string texture;
    static int compteur;
};