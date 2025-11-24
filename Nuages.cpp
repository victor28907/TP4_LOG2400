#include "nuages.h"

void Nuages::afficherNuages() const {
    if (!o.empty()) {
        cout << "Nuage \"o\" contient les points: ";
        for (size_t i = 0; i < o.size(); ++i) {
            cout << o[i].getId();
            if (i != o.size() - 1) cout << ", ";
        }
        cout << "\n";
    }

    if (!hash.empty()) {
        cout << "Nuage \"#\" contient les points: ";
        for (size_t i = 0; i < hash.size(); ++i) {
            cout << hash[i].getId();
            if (i != hash.size() - 1) cout << ", ";
        }
        cout << "\n";
    }
}

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
