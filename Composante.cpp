#include "Composante.h"

int Composante::compteurComposant = 0;

string Composante::generationId() {
    return to_string(compteurComposant++);
}

void Composante::retirerElementCompteur() {
    compteurComposant--;
}