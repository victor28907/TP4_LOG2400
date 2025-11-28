#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Point.h"
#include "Nuages.h"
#include "Composante.h"
#include "StrategieConsutruction.h"
#include "StrategieAffichage.h"

const int LARGEUR = 30;
const int HAUTEUR = 20;
/*
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
};*/

// vecotr<Nuage> nuages;

class Gestionnaire {

public:
    Gestionnaire(); //

    void creerPoints(const string& ligne);
    void supprimerPoint(const string& id);
    void deplacerPoint(const string& idDeplacer, int nouveauX, int nouveauY);
    void fusionnerPoints(const string& ligne);

    void setStrategieConstruction(shared_ptr<StrategieConstruction> strategie1);
    void setStrategieAffichage(unique_ptr<AffichageStrategie> strategie2);
    shared_ptr<StrategieConstruction> getStrategieConstruction() const;

    void afficherComposants();
    void imprimerGrille();

    vector<shared_ptr<Nuage>> getNuages() const;
    vector<shared_ptr<Point>> getPoints() const;
    void setPoints(vector<shared_ptr<Point>> nouveauxPoints);
    void setNuages(vector<shared_ptr<Nuage>> nouveauxNuages);

private:

    void tracerLigne(vector<vector<char>>& grille);
    void tracerLigneEntre(vector<vector<char>>& grille, const Point* p1, const Point* p2);
    void placerPointsSurGrille(vector<vector<char>>& grille);
    shared_ptr<Composante> trouverComposante(const string& id) const;

    vector<shared_ptr<Point>> extrairePoints() const;
    vector<shared_ptr<Nuage>> extraireNuages() const;

    vector<shared_ptr<Composante>> composantes;
    
    shared_ptr<StrategieConstruction> strategieConstruction;
    unique_ptr<AffichageStrategie> strategieAffichage;
};