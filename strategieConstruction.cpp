#include "StrategieConsutruction.h"
#include <algorithm>
#include <cmath>
#include "Point.h"
#include <unordered_set>
/*
void ConstructionCroissante::construireNuages(vector<string> (&textures)[3],
                                            vector<Point>& points) const {

    for (int i = 0; i < 3; ++i) {
        sort(textures[i].begin(), textures[i].end());
    }
}

void ConstructionMinimale::construireNuages(vector<string> (&textures)[3],
                                            vector<Point>& points) const {
    
    for (int i = 0; i < 3; ++i) {

        vector<string>& ids = textures[i];
        if (ids.size() < 2) continue;

        vector<string> tri;
        tri.push_back(ids[0]);
        ids.erase(ids.begin());

        while (!ids.empty()) {
            const string& comparaisonId = tri.back();

            auto it = min_element(ids.begin(), ids.end(), [&](const string& a, const string& b) {
                const Point* pa = nullptr;
                const Point* pb = nullptr;
                const Point* pComparaison = nullptr;
                for (const auto& p : points) {
                    if (p.getId() == a) pa = &p;
                    else if (p.getId() == b) pb = &p;
                    else if (p.getId() == comparaisonId) pComparaison = &p;
                }
                double distance1 = hypot(
                    pa->getX()-pComparaison->getX(),
                    pa->getY()-pComparaison->getY());
                double distance2 = hypot(
                    pb->getX()-pComparaison->getX(), 
                    pb->getY()-pComparaison->getY());

                return distance1 < distance2;
            });
            tri.push_back(*it);
            ids.erase(it);
        }
        ids = tri;
    }
}*/

void ConstructionCroissante::construireNuages(shared_ptr<Composante> composante) const {
    auto points = composante->obtenirPoints();

    sort(points.begin(), points.end(), 
        [](const shared_ptr<Composante>& a, const shared_ptr<Composante>& b) {
            return a->getId() < b->getId();
        });
    
    composante->reorganiserEnfants(points);
}


void ConstructionMinimale::construireNuages(shared_ptr<Composante> composante) const {
    auto points = composante->obtenirPoints();

    if (points.empty()) return;

    vector<shared_ptr<Composante>> ids = points;
    vector<shared_ptr<Composante>> tri;

    tri.push_back(ids[0]);
    ids.erase(ids.begin());

     while (!ids.empty()) {
        auto dernierPoint = dynamic_cast<Point*>(tri.back().get());
        if (!dernierPoint) break;
        
        auto it = min_element(ids.begin(), ids.end(),
            [&](const shared_ptr<Composante>& a, const shared_ptr<Composante>& b) {
                auto pa = dynamic_cast<Point*>(a.get());
                auto pb = dynamic_cast<Point*>(b.get());
                if (!pa || !pb) return false;
                
                double d1 = hypot(pa->getX() - dernierPoint->getX(),
                                 pa->getY() - dernierPoint->getY());
                double d2 = hypot(pb->getX() - dernierPoint->getX(),
                                 pb->getY() - dernierPoint->getY());
                return d1 < d2;
            });
        
        tri.push_back(*it);
        ids.erase(it);
    }
    
    composante->reorganiserEnfants(tri);
}
