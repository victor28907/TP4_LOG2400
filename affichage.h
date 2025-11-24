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
    void tracerLigne(std::vector<std::vector<char>>& grille, const AffichageStrategie& strategie);
    void imprimerGrille(const std::vector<Point>& points, const AffichageStrategie& strategie);
    void afficherPoints();
    void supprimerPoint();
    void deplacerPoint();
    vector<Point> getPoints();
       
private:
    vector<Point> points;
};

