#include "Commandes.h"

CommandeAfficher::CommandeAfficher(Gestionnaire& g) : gestionnaire(g) {}
CommandeSupprimer::CommandeSupprimer(Gestionnaire& g) : gestionnaire(g) {}
CommandeDeplacer::CommandeDeplacer(Gestionnaire& g) : gestionnaire(g) {}
CommandeFusionner::CommandeFusionner(Gestionnaire& g) : gestionnaire(g) {}
CommandeConstructionCroissante::CommandeConstructionCroissante(Gestionnaire& g) : gestionnaire(g) {}
CommandeConstructionMinimale::CommandeConstructionMinimale(Gestionnaire& g) : gestionnaire(g) {}
CommandeGrilleTexture::CommandeGrilleTexture(Gestionnaire& g) : gestionnaire(g) {}
CommandeGrilleId::CommandeGrilleId(Gestionnaire& g) : gestionnaire(g) {}


// Executer
void CommandeAfficher::executer() {
    gestionnaire.afficherPoints();
    gestionnaire.afficherNuages();
}
void CommandeSupprimer::executer() {
    points = gestionnaire.getPoints();
    nuages = gestionnaire.getNuages();
    gestionnaire.supprimerPoint();
}
void CommandeDeplacer::executer() {
    points = gestionnaire.getPoints();
    gestionnaire.deplacerPoint();
}
void CommandeFusionner::executer() {
    nuages = gestionnaire.getNuages();
    gestionnaire.fusionnerPoints();
}
void CommandeConstructionCroissante::executer() {
    strategie = gestionnaire.getStrategieConstruction();
    gestionnaire.setStrategieConstruction(make_unique<ConstructionCroissante>());
}
void CommandeConstructionMinimale::executer() {
    strategie = gestionnaire.getStrategieConstruction();
    gestionnaire.setStrategieConstruction(make_unique<ConstructionMinimale>());
}
void CommandeGrilleTexture::executer() {
    gestionnaire.setStrategieAffichage(make_unique<AffichageTexture>());
    gestionnaire.imprimerGrille();
}
void CommandeGrilleId::executer() {
    gestionnaire.setStrategieAffichage(make_unique<AffichageID>());
    gestionnaire.imprimerGrille();
}

// Clone
shared_ptr<Commande> CommandeAfficher::clone() const {
    return make_shared<CommandeAfficher>(gestionnaire);
}
shared_ptr<Commande> CommandeSupprimer::clone() const {
    return make_shared<CommandeSupprimer>(gestionnaire);
}
shared_ptr<Commande> CommandeDeplacer::clone() const {
    return make_shared<CommandeDeplacer>(gestionnaire);
}
shared_ptr<Commande> CommandeFusionner::clone() const {
    return make_shared<CommandeFusionner>(gestionnaire);
}
shared_ptr<Commande> CommandeConstructionCroissante::clone() const {
    return make_shared<CommandeConstructionCroissante>(gestionnaire);
}
shared_ptr<Commande> CommandeConstructionMinimale::clone() const {
    return make_shared<CommandeConstructionMinimale>(gestionnaire);
}
shared_ptr<Commande> CommandeGrilleTexture::clone() const {
    return make_shared<CommandeGrilleTexture>(gestionnaire);
}
shared_ptr<Commande> CommandeGrilleId::clone() const {
    return make_shared<CommandeGrilleId>(gestionnaire);
}

// Annuler
void CommandeAfficher::annuler() {}
void CommandeGrilleTexture::annuler() {}
void CommandeGrilleId::annuler() {}
void CommandeConstructionCroissante::annuler() {
    gestionnaire.setStrategieConstruction(strategie);
}
void CommandeConstructionMinimale::annuler() {
    gestionnaire.setStrategieConstruction(strategie);
}
void CommandeSupprimer::annuler() {
    gestionnaire.setPoints(points);
    gestionnaire.setNuages(nuages);
}
void CommandeDeplacer::annuler() {
    gestionnaire.setPoints(points);
}
void CommandeFusionner::annuler() {
    gestionnaire.setNuages(nuages);
}