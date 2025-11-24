#pragma once
#include <string>
#include <vector>
#include "point.h"

const int LARGEUR = 30;
const int HAUTEUR = 20;

class AffichageStrategie {
public:
    virtual string getString(const Point& p) const = 0;
    virtual ~AffichageStrategie() = default;
};

class AffichageTexture : public AffichageStrategie {
public:
    string getString(const Point& p) const override;
};

class AffichageID : public AffichageStrategie {
public:
    string getString(const Point& p) const override;
};

class Gestionnaire {

public:
    void creerPoints(const std::string& ligne);
    void tracerLigne(std::vector<std::vector<char>>& grille, int x0, int y0, int x1, int y1, const AffichageStrategie& strategie);
    void imprimerGrille(const std::vector<Point>& points, const AffichageStrategie& strategie);
    void afficherPoints();
    void supprimerPoint();
    void deplacerPoint();
    void fusionnerPoints();
    vector<Point> getPoints();
       
private:
    vector<Point> points;
};

