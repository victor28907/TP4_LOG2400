#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Point.h"
#include "Nuages.h"
#include "StrategieConsutruction.h"
#include "StrategieAffichage.h"

const int LARGEUR = 30;
const int HAUTEUR = 20;

class Gestionnaire {

public:
    Gestionnaire();
    void setStrategieConstruction(shared_ptr<StrategieConstruction> strategie1);
    shared_ptr<StrategieConstruction> getStrategieConstruction() const;
    void setStrategieAffichage(unique_ptr<AffichageStrategie> strategie2);
    void setPoints(vector<Point> nouveauxPoints);
    void setNuages(Nuages nouveauxNuages);
    Nuages getNuages() const;
    vector<Point> getPoints() const;
    void creerPoints(const string& ligne);
    void tracerLigne(vector<std::vector<char>>& grille);
    void imprimerGrille();
    void afficherPoints();
    void afficherNuages();
    void supprimerPoint(string idSupprimer);
    void deplacerPoint(string idDeplacer, int nouveauX, int nouveauY);
    void fusionnerPoints(string ligne);
private:
    vector<Point> points;
    Nuages nuages;
    shared_ptr<StrategieConstruction> strategieConstruction;
    unique_ptr<AffichageStrategie> strategieAffichage;
};

