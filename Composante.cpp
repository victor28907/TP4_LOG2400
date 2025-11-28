#include "Composante.h"

int Composante::compteurComposant = 0;

string Composante::generationId() {
    return to_string(compteurComposant++);
}

void Composante::retirerElementCompteur() {
    compteurComposant--;
}

const vector<shared_ptr<Composante>>& Composante::getEnfants() const {
    static vector<shared_ptr<Composante>> vide;
    return vide;
}