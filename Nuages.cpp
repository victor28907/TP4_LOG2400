#include "nuages.h"

Nuages::Nuages(const vector<Point>& points) {
    for (const auto& p : points) {
        string tex = p.getTexture();
        if (tex.find('o') != string::npos) { 
            o.push_back(p);
        }
        if (tex.find('#') != string::npos) { 
            hash.push_back(p);
        }
    }
}

const vector<Point>& Nuages::getO() const {
    return o;
}

const vector<Point>& Nuages::getHash() const {
    return hash;
}
