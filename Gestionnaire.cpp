#include "Gestionnaire.h"

using namespace std;

Gestionnaire::Gestionnaire() : strategieConstruction(nullptr), strategieAffichage(nullptr) {}

// Création des points
void Gestionnaire::creerPoints(const string& ligne) {
    istringstream iss(ligne);
    string token;
    while (iss >> token) {
        if (token.size() >= 3 && token.front() == '(' && token.back() == ')') {
            token = token.substr(1, token.size() - 2);
            replace(token.begin(), token.end(), ',', ' ');
            istringstream pair(token);
            int x, y;
            if (pair >> x >> y) {
                composantes.push_back(make_shared<Point>(x, y));
            }
        }
    }
}

// Supprimer un point 
void Gestionnaire::supprimerPoint(const string& id) {
    auto composante = trouverComposante(id);
    if (!composante) {
        cout << "Erreur : ID invalide\n";
        return;
    }
    for (auto& comp : composantes) {
        comp->retirer(composante);
    }
    composantes.erase(
        remove_if(composantes.begin(), composantes.end(),
            [&](const shared_ptr<Composante>& c) { return c->getId() == id; }),
        composantes.end()
    );
}

// Déplacer un point
void Gestionnaire::deplacerPoint(const string& id, int nouveauX, int nouveauY) {
    auto composante = trouverComposante(id);
    if (!composante) {
        cout << "Erreur : ID invalide\n";
        return;
    }
    composante->deplacer(nouveauX, nouveauY);
}

// Fusionner des composantes pour créer un nuage
void Gestionnaire::fusionner(const string& ligne) {
    istringstream iss(ligne);
    string id;
    auto nuage = make_shared<Nuage>();
    while (iss >> id) {
        auto composante = trouverComposante(id);
        if (composante && composante->getNombreComposants() >= 1) {
            nuage->ajouter(composante);
        } else {
            cout << "ID invalide: " << id << "\n";
        }
    }
    if (nuage->getNombreComposants() == 0) {
        return;
    }
    nuage->setTexture(nuage->getSymbole());
    composantes.push_back(nuage);
}

// Setter pour la strategie de construction
void Gestionnaire::setStrategieConstruction(shared_ptr<StrategieConstruction> strategie) {
    strategieConstruction = strategie;
    if (!strategieConstruction) {
        return;
    }
    for (auto& comp : composantes) {
        if (comp->getNombreComposants() > 1) {
            strategieConstruction->construireNuages(comp);
        }
    }
}

// Setter pour la strategie d'affichage
void Gestionnaire::setStrategieAffichage(unique_ptr<AffichageStrategie> strategie) {
    strategieAffichage = move(strategie);
}

// Getter pour la strategie de construction
shared_ptr<StrategieConstruction> Gestionnaire::getStrategieConstruction() const {
    return strategieConstruction;
}

// Fonction pour afficher (commande a)
void Gestionnaire::afficherComposants() {
    cout << "\nListe:\n";
    for (const auto& comp : composantes) {
        if (comp->getNombreComposants() == 1) {
            if (auto point = dynamic_pointer_cast<Point>(comp)) {
                cout << point->getId() + ": (" 
                    + to_string(point->getX()) + ","
                    + to_string(point->getY()) + ")   textures: '"
                    + point->getTexture() + "'\n";
            }
        } else if (comp->getNombreComposants() > 1) {
               if (auto nuage = dynamic_pointer_cast<Nuage>(comp)) {
                cout << comp->getId() + ": Nuage '" 
                + nuage->getSymbole() 
                + "' contient les elements: ";
                auto enfants = nuage->getEnfants();
                for (size_t i = 0; i < enfants.size(); ++i) {
                    cout << enfants[i]->getId();
                    if (i < enfants.size() - 1) cout << " ";
                }
                cout << "\n";
            }             
        }
    }
}

// Afficher la grille avec les points et les nuages
void Gestionnaire::imprimerGrille() {
    vector<vector<char>> grille(HAUTEUR, vector<char>(LARGEUR, ' '));
    if (strategieConstruction) {
        tracerLigne(grille);
    }
    placerPointsSurGrille(grille);
    for (int y = HAUTEUR - 1; y >= 0; --y) {
        for (int x = 0; x < LARGEUR; ++x) {
            cout << grille[y][x];
        }
        cout << '\n';
    }
}

// Tracer les lignes sur la grille
void Gestionnaire::tracerLigne(vector<vector<char>>& grille) {
    for (auto& comp : composantes) {
        if (comp->getNombreComposants() > 1) {
            if (auto nuage = dynamic_pointer_cast<Nuage>(comp)) {
                auto enfants = nuage->getEnfants();
                if (enfants.size() < 2) continue;
                for (size_t i = 0; i < enfants.size(); ++i) {
                    auto p1 = dynamic_pointer_cast<Point>(enfants[i]);
                    auto p2 = dynamic_pointer_cast<Point>(enfants[(i + 1) % enfants.size()]);
                    if (p1 && p2) {
                        tracerLigneEntre(grille, p1.get(), p2.get());
                    }
                }
            }
        }
    }
}

// Tracer les lignes entres les points faisant partie d'un même nuage
void Gestionnaire::tracerLigneEntre(vector<vector<char>>& grille, const Point* p1, const Point* p2) {
    int dx = p2->getX() - p1->getX();
    int dy = p2->getY() - p1->getY();
    // Ligne verticale
    if (dx == 0) {
        int yMin = min(p1->getY(), p2->getY());
        int yMax = max(p1->getY(), p2->getY());
        for (int y = yMin; y <= yMax; ++y) {
            if (p1->getX() >= 0 && p1->getX() < LARGEUR && y >= 0 && y < HAUTEUR) {
                grille[y][p1->getX()] = '|';
            }
        }
        return;
    }
    // Ligne horizontale
    if (dy == 0) {
        int xMin = min(p1->getX(), p2->getX());
        int xMax = max(p1->getX(), p2->getX());
        for (int x = xMin; x <= xMax; ++x) {
            if (p1->getY() >= 0 && p1->getY() < HAUTEUR && x >= 0 && x < LARGEUR) {
                grille[p1->getY()][x] = '-';
            }
        }
        return;
    }
    // Ligne diagonale
    double pente = (double)dy / dx;
    for (int i = 0; i <= abs(dy); ++i) {
        double t = (double)i / abs(dy);
        // On fait une interpolation lineaire
        int x = round(p1->getX() + t * (p2->getX() - p1->getX()));
        int y = round(p1->getY() + t * (p2->getY() - p1->getY()));
        int debut = 0, fin = 0;
        if (abs(pente) < PETITE_PENTE) {
            debut = x-1;
            fin = x+1;
        } else if (abs(pente) < MOYENNE_PENTE) {
            debut = x-1;
            fin = x;
        } else {
            debut = x;
            fin = x;
        }
        for (int k = debut; k <= fin; ++k) {
            if (k >= 0 && k < LARGEUR && y >= 0 && y < HAUTEUR) {
                grille[y][k] = (pente > 0) ? '/' : '\\';
            }
        }
    }
}

// Placer les point en fonction de la strategie d'affichage
void Gestionnaire::placerPointsSurGrille(vector<vector<char>>& grille) {
    for (const auto& comp : composantes) {
        if (comp->getNombreComposants() == 1) {
            if (auto p = dynamic_pointer_cast<Point>(comp)) {
                int x = p->getX();
                int y = p->getY();
                if (x >= 0 && x < LARGEUR && y >= 0 && y < HAUTEUR) {
                    string texture;
                    if (strategieAffichage) {
                        texture = strategieAffichage->getString(*p);
                    }
                    for (size_t i = 0; i < texture.length() && x + i < LARGEUR; ++i) {
                        grille[y][x + i] = texture[i];
                    }
                }
            }
        }
    }
}

// Trouver une composante avec son Id
shared_ptr<Composante> Gestionnaire::trouverComposante(const string& id) const {
    auto it = find_if(composantes.begin(), composantes.end(),
        [&](const shared_ptr<Composante>& c) { return c->getId() == id; });
    return (it != composantes.end()) ? *it : nullptr;
}

// Getter pour les points
vector<shared_ptr<Point>> Gestionnaire::getPoints() const {
    vector<shared_ptr<Point>> points;
    for (const auto& comp : composantes) {
        if (comp->getNombreComposants() == 1) {
            if (auto point = dynamic_pointer_cast<Point>(comp)) {
                points.push_back(point);
            }
        }
    }
    return points;
}

// Getter pour les nuages
vector<shared_ptr<Nuage>> Gestionnaire::getNuages() const {
    vector<shared_ptr<Nuage>> nuages;
    for (const auto& comp : composantes) {
        if (comp->getNombreComposants() > 1) {
            if (auto nuage = dynamic_pointer_cast<Nuage>(comp)) {
                nuages.push_back(nuage);
            }
        }
    }
    return nuages;
}

// Setter pour les points
void Gestionnaire::setPoints(vector<shared_ptr<Point>> nouveauxPoints) {
    composantes.erase(remove_if(composantes.begin(), composantes.end(),
        [](const shared_ptr<Composante>& c) { return c->getNombreComposants() == 1; }),
        composantes.end());
    for (auto& p : nouveauxPoints) {
        composantes.push_back(p);
    }
}

// Setter pour les nuages
void Gestionnaire::setNuages(vector<shared_ptr<Nuage>> nouveauxNuages) {
    composantes.erase(remove_if(composantes.begin(), composantes.end(),
        [](const shared_ptr<Composante>& c) { return c->getNombreComposants() > 1; }),
        composantes.end());
    for (auto& n : nouveauxNuages) {
        composantes.push_back(n);
    }
}