#ifndef GESTIONNAIRE_H
#define GESTIONNAIRE_H

#include <string>
#include <memory>
#include <vector>
#include "Point.h"
#include "Nuages.h"
#include "Composante.h"
#include "StrategieConsutruction.h"
#include "StrategieAffichage.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <limits>  
#include <algorithm>

const int LARGEUR = 30;
const int HAUTEUR = 20;
const double PETITE_PENTE = 0.4;
const double MOYENNE_PENTE = 0.8;

class Gestionnaire {

public:
    Gestionnaire();
    void creerPoints(const string& ligne);
    void supprimerPoint(const string& id);
    void deplacerPoint(const string& idDeplacer, int nouveauX, int nouveauY);
    void fusionner(const string& ligne);
    void setStrategieConstruction(shared_ptr<StrategieConstruction> strategie1);
    void setStrategieAffichage(unique_ptr<AffichageStrategie> strategie2);
    shared_ptr<StrategieConstruction> getStrategieConstruction() const;
    void afficherComposants();
    void imprimerGrille();
    vector<shared_ptr<Nuage>> getNuages() const;
    vector<shared_ptr<Point>> getPoints() const;
    void setPoints(vector<shared_ptr<Point>> nouveauxPoints);
    void setNuages(vector<shared_ptr<Nuage>> nouveauxNuages);
    void tracerLigne(vector<vector<char>>& grille);
    void tracerLigneEntre(vector<vector<char>>& grille, const Point* p1, const Point* p2);
    void placerPointsSurGrille(vector<vector<char>>& grille);
    shared_ptr<Composante> trouverComposante(const string& id) const;

private:
    vector<shared_ptr<Composante>> composantes;
    shared_ptr<StrategieConstruction> strategieConstruction;
    unique_ptr<AffichageStrategie> strategieAffichage;
};

#endif // GESTIONNAIRE_H