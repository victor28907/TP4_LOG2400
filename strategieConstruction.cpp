#include "StrategieConsutruction.h"

// COnstruction en ordre croissant des Id
void ConstructionCroissante::construireNuages(shared_ptr<Composante> composante) const {
    auto points = composante->getPoints();
    sort(points.begin(), points.end(), 
        [](const shared_ptr<Composante>& a, const shared_ptr<Composante>& b) {
            return a->getId() < b->getId();
        });
    composante->reorganiserEnfants(points);
}

// Construction en fonction de la distance minimale entre les points
void ConstructionMinimale::construireNuages(shared_ptr<Composante> composante) const {
    auto points = composante->getPoints();
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
                double d1 = hypot(pa->getX() - dernierPoint->getX(),pa->getY() - dernierPoint->getY());
                double d2 = hypot(pb->getX() - dernierPoint->getX(),pb->getY() - dernierPoint->getY());
                return d1 < d2;
            });
        tri.push_back(*it);
        ids.erase(it);
    }
    composante->reorganiserEnfants(tri);
}
