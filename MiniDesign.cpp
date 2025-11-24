#include "affichage.h"
#include "nuages.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    Gestionnaire gestionnaire;
    string args;
    // On accepte des points en entrée.
    if (argc > 1) {
        ostringstream oss;
        for (int i = 1; i < argc; ++i) oss << argv[i] << " ";
        args = oss.str();
    }
    else {
        cout << "Entrez les points au format (x,y) :\n> ";
        getline(cin, args);
    }

    // Voici des fonctions utiles pour réaliser le TP. 
    // TODO: Il faudrait les placer dans des classes appropriées.
    gestionnaire.creerPoints(args);
    //gestionnaire.imprimerGrille();

    // Ce sont différentes textures possibles. Seules les 2 premières sont utilisées dans les scénarios du TP.
    vector<char> texturesNuages = { 'o', '#', '$' };
    string cmd;

    // Menu
    while (true) {
        cout << "\nCommandes:\n"
            << "a  - Afficher les points et les nuages\n"
            << "o1 - Afficher l'orthèse avec les textures des points\n"
            << "o2 - Afficher l'orthèse avec les IDs des points\n"
            << "f  - Fusionner des points dans un nuage (et appliquer texture)\n"
            << "d  - Deplacer un point (ID)\n"
            << "s  - Supprimer un point (ID)\n"
            << "c1 - Créer les surfaces selon l'ordre des IDs\n"
            << "c2 - Créer les surfaces selon la distance minimale\n"
            << "q  - Quitter\n> ";
        getline(std::cin, cmd);
        if (cmd == "o1") {
            AffichageTexture strategie;  
            gestionnaire.imprimerGrille(gestionnaire.getPoints(), strategie);
        }
        if (cmd == "o2") {
            AffichageID strategie;
            gestionnaire.imprimerGrille(gestionnaire.getPoints(), strategie);
        }
        if (cmd == "f") gestionnaire.fusionnerPoints();
        if (cmd == "q") break;
        if (cmd == "a") {
            gestionnaire.afficherPoints();
            Nuages nuage(gestionnaire.getPoints());

            const auto& oPoints = nuage.getO();
            const auto& hashPoints = nuage.getHash();

            if (!oPoints.empty()) {
                cout << "Nuage \"o\" contient les points: ";
                for (size_t i = 0; i < oPoints.size(); ++i) {
                    cout << oPoints[i].getId();
                    if (i != oPoints.size() - 1) cout << ", ";
                }
                cout << "\n";
            }

            if (!hashPoints.empty()) {
                cout << "Nuage \"#\" contient les points: ";
                for (size_t i = 0; i < hashPoints.size(); ++i) {
                    cout << hashPoints[i].getId();
                    if (i != hashPoints.size() - 1) cout << ", ";
                }
                cout << "\n";
            }
        }
        if (cmd == "s") gestionnaire.supprimerPoint();
        if (cmd == "d") gestionnaire.deplacerPoint();
    }

    return 0;
}