#include "Point.h"

Point::Point(int px, int py) : x(px), y(py) {
    id = generationId();
    texture = "";
}

void Point::deplacer(int dx, int dy) {
    x = dx;
    y = dy;
}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

string Point::getId() const {
    return id;
}

string Point::getTexture() const {
    return texture;
}

void Point::setTexture(const string& t) {
    if (texture.find(t) != string::npos) return;
    texture += t;
}

void Point::reinitialiserTexture(const string& t) {
    texture = t;
}

int Point::getNombreComposants() const {
    return 1;
}

vector<shared_ptr<Composante>> Point::getPoints() const {
    auto self = const_pointer_cast<Point>(shared_from_this());
    return {self};
}