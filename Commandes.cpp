#include "Commandes.h"

CommandeAfficher::CommandeAfficher(Gestionnaire& g) : gestionnaire(g) {}
CommandeSupprimer::CommandeSupprimer(Gestionnaire& g, string id) : gestionnaire(g), idSupprimer(id) {}
CommandeDeplacer::CommandeDeplacer(Gestionnaire& g, string id, int x, int y) : gestionnaire(g), idDeplacer(id), positionX(x), positionY(y) {}
CommandeFusionner::CommandeFusionner(Gestionnaire& g, string ligne) : gestionnaire(g), ids(ligne) {}
CommandeConstructionCroissante::CommandeConstructionCroissante(Gestionnaire& g) : gestionnaire(g) {}
CommandeConstructionMinimale::CommandeConstructionMinimale(Gestionnaire& g) : gestionnaire(g) {}
CommandeGrilleTexture::CommandeGrilleTexture(Gestionnaire& g) : gestionnaire(g) {}
CommandeGrilleId::CommandeGrilleId(Gestionnaire& g) : gestionnaire(g) {}


// Executer
void CommandeAfficher::executer() {
    gestionnaire.afficherComposants();
}
void CommandeSupprimer::executer() {
    points = gestionnaire.getPoints();
    nuages = gestionnaire.getNuages();
    contenuNuages.clear();
    for (auto&  n : nuages) {
        contenuNuages.push_back(n->obtenirPoints());
    }
    gestionnaire.supprimerPoint(idSupprimer);
}
void CommandeDeplacer::executer() {
    points = gestionnaire.getPoints();
    for (auto& p : points) {
        if (p->getId() == idDeplacer) {
            ancienX = p->getX();
            ancienY = p->getY();
        }
    }
    gestionnaire.deplacerPoint(idDeplacer, positionX, positionY);
}
void CommandeFusionner::executer() {
    points = gestionnaire.getPoints();
    nuages = gestionnaire.getNuages();
    texturesPoints.clear();
    for (auto& p : points) {
        texturesPoints.push_back(p->getTexture());
    }
    gestionnaire.fusionnerPoints(ids);
}
void CommandeConstructionCroissante::executer() {
    strategie = gestionnaire.getStrategieConstruction();
    gestionnaire.setStrategieConstruction(make_shared<ConstructionCroissante>());
}
void CommandeConstructionMinimale::executer() {
    strategie = gestionnaire.getStrategieConstruction();
    gestionnaire.setStrategieConstruction(make_shared<ConstructionMinimale>());
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
    return make_shared<CommandeSupprimer>(gestionnaire, idSupprimer);
}
shared_ptr<Commande> CommandeDeplacer::clone() const {
    return make_shared<CommandeDeplacer>(gestionnaire, idDeplacer, positionX, positionY);
}
shared_ptr<Commande> CommandeFusionner::clone() const {
    return make_shared<CommandeFusionner>(gestionnaire, ids);
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
    for (int i = 0; i < nuages.size(); ++i) {
        nuages[i]->vider();
        for (auto& c : contenuNuages[i]) {
            nuages[i]->ajouter(c);
        }
    }
}
void CommandeDeplacer::annuler() {
    gestionnaire.deplacerPoint(idDeplacer, ancienX, ancienY);
}
void CommandeFusionner::annuler() {
    Composante::retirerElementCompteur();
    Nuage::retirerNuageCompteur();
    for (int i = 0; i < points.size(); ++i) {
        points[i]->reinitialiserTexture(texturesPoints[i]);
    }
    gestionnaire.setPoints(points);
    gestionnaire.setNuages(nuages);
}