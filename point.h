#ifndef POINT_H
#define POINT_H

#include <string>
#include <iostream>
#include "Composante.h"
#include <memory>

using namespace std;

class Point : public Composante, public enable_shared_from_this<Point> {

public:
    Point(int px, int py);
    void deplacer(int dx, int dy) override;
    int getX() const;
    int getY() const;
    string getId() const override;
    string getTexture() const override;
    void setTexture(const string& t) override;
    void reinitialiserTexture(const string& t);
    int getNombreComposants() const override;
    vector<shared_ptr<Composante>> getPoints() const override;

private:
    int x;
    int y;
    string id;
    string texture;
};

#endif // POINT_H