#include "Nuages.h"
#include <unordered_set>
#include <algorithm>
#include <cmath>

int Nuage::compteurNuages = 0;
const string Nuage::symboles[3] = {"o", "#", "$"};

Nuage::Nuage() {
    id = generationId();
    indexNuage = compteurNuages++;
    symbole = symboles[indexNuage % 3];
}

int Nuage::getNombreComposants() const {
    int nombre;
    for (const auto& c : enfants) {
        nombre += c->getNombreComposants();
    }
    return nombre;
}

void Nuage::deplacer(int dx, int dy) {
    for (auto& enfant : enfants) {
        enfant->deplacer(dx, dy);
    }
}

void Nuage::setTexture(const string& texture) {
    for (auto& enfant : enfants) {
        enfant->setTexture(texture);
    }
}

void Nuage::ajouter(shared_ptr<Composante> composante) {
    enfants.push_back(composante);
}

void Nuage::retirer(shared_ptr<Composante> composante) {
    enfants.erase(
        remove_if(enfants.begin(), enfants.end(),
            [&](const shared_ptr<Composante>& c) { 
                return c->getId() == composante->getId(); 
            }),
        enfants.end()
    );
}

void Nuage::vider() {
    enfants.clear();
}

vector<shared_ptr<Composante>> Nuage::getPoints() const {
    vector<shared_ptr<Composante>> points;
    for (const auto& enfant : enfants) {
        auto sousPoints = enfant->getPoints();
        points.insert(points.end(), sousPoints.begin(), sousPoints.end());
    }
    return points;
}

void Nuage::reorganiserEnfants(const vector<shared_ptr<Composante>>& nouveauxEnfants) {
    enfants = nouveauxEnfants;
}

string Nuage::getSymbole() const {
    return symbole;
}

void Nuage::retirerNuageCompteur() {
    compteurNuages--;
}