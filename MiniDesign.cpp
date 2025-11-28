#include "Gestionnaire.h"
#include "Commandes.h"
#include "Invoker.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <limits>  

using namespace std;

int main(int argc, char* argv[]) {
    Gestionnaire gestionnaire;
    Invoker invoker;
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
 
    // TODO: Il faudrait les placer dans des classes appropriées.
    gestionnaire.creerPoints(args);

    // Ce sont différentes textures possibles. Seules les 2 premières sont utilisées dans les scénarios du TP.
    //vector<char> texturesNuages = { 'o', '#', '$' };
    string cmd;

    unordered_map<string, function<void()>> commandesMap {
        { "a", [&]() {invoker.executer(make_shared<CommandeAfficher>(gestionnaire));}},
        { "o1",[&]() {invoker.executer(make_shared<CommandeGrilleTexture>(gestionnaire));}},
        { "o2",[&]() {invoker.executer(make_shared<CommandeGrilleId>(gestionnaire));}},
        { "c1",[&]() {invoker.executer(make_shared<CommandeConstructionCroissante>(gestionnaire));}},
        { "c2",[&]() {invoker.executer(make_shared<CommandeConstructionMinimale>(gestionnaire));}},
        { "r", [&]() {invoker.redo();}},
        { "u", [&]() {invoker.undo();}},
        { "f", [&]() {
            cout << "Entrez les IDs des points a fusionner (ex: 0 2 4) : ";
            string ligne;
            getline(cin >> ws, ligne);
            invoker.executer(make_shared<CommandeFusionner>(gestionnaire, ligne));
        }},
        { "d", [&]() {
            string idDeplacer;
            int nouveauX, nouveauY;
            cout << "ID du point a deplacer: ";
            cin >> idDeplacer;
            cout << "Nouvelle position (x y): ";
            if (!(cin >> nouveauX >> nouveauY)) {
                cout << "Erreur : Coordonnees invalides";
            } else {
                invoker.executer(make_shared<CommandeDeplacer>(gestionnaire, idDeplacer, nouveauX, nouveauY));
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }},
        { "s", [&]() {
            string idSupprimer;
            cout << "ID du point a supprimer: ";
            cin >> idSupprimer;
            invoker.executer(make_shared<CommandeSupprimer>(gestionnaire, idSupprimer));
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }},
    };

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
            << "r  - Refaire la derniere commande annulee\n"
            << "u  - Annuler la derniere commande\n"
            << "q  - Quitter\n> ";
        getline(std::cin, cmd);

        if (cmd == "q") break;
        auto it = commandesMap.find(cmd);
        if (it != commandesMap.end()) it->second();
        }

    return 0;
}