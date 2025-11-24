#include "affichage.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

void Gestionnaire::tracerLigne(vector<vector<char>>& grille, const AffichageStrategie& strategie) {

    for (size_t i = 0; i + 1 < points.size(); ++i) {
        const auto& p1 = points[i];
        const auto& p2 = points[i+1];
        int dx = p2.getX() - p1.getX();
        int dy = p2.getY() - p1.getY();
        double pente;

        // Si la ligne est verticale
        if (dx == 0) {
            for (int j = 0; j <= abs(dy); ++j) {
                int y = (p1.getY() < p2.getY()) ? p1.getY() + j : p1.getY() - j;
                if (p2.getX() >= 0 && p2.getX() < LARGEUR && y >= 0 && y < HAUTEUR)
                    grille[y][p2.getX()] = '|';
            }
        }

        // Si la ligne est horizontale
        else if (dy == 0) {
            for (int j = 0; j <= abs(dx); ++j) {
                int x = (p1.getX() < p2.getX()) ? p1.getX() + j : p1.getX() - j;
                if (p2.getY() >= 0 && p2.getY() < HAUTEUR && x >= 0 && x < LARGEUR)
                    grille[p2.getY()][x] = '-';
            }
        }

        // Si la ligne est diagonale
        else {
            pente = (double) dy / dx;
                for (int i = 0; i <= abs(dy); ++i) {
                    double t = (double)i / abs(dy);
                    // On fait une interpolation lineaire
                    int x = round(p1.getX() + t * (p2.getX() - p1.getX()));
                    int y = round(p1.getY() + t * (p2.getY() - p1.getY()));

                    int debut = 0, fin = 0;
                    if (abs(pente) < 0.4) {
                        debut = x-1;
                        fin = x+1;
                    } else if (abs(pente) < 0.8) {
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
        }
        
    // Ajouter les points
    for (const Point& p : points) {
        int x = p.getX();
        int y = p.getY();
        string textures = strategie.getString(p);
        if (x >= 0 && x < LARGEUR && y >= 0 && y < HAUTEUR) {
            for (int i = 0; i < textures.length() && x < LARGEUR; i++) {
                char texture = textures[i];
                grille[y][x++] = texture;
            }

        }
    }
}

void Gestionnaire::imprimerGrille(const vector<Point>& points, const AffichageStrategie& strategie) {
    // On crée une grille.
    vector<vector<char>> grille(HAUTEUR, vector<char>(LARGEUR, ' '));

    // On trace une ligne entre le point 0 et 1.
    // TODO : Remplacer par un tracé selon la commande de l'utilisateur (c1 ou c2)
    tracerLigne(grille, strategie);


    // On imprime la grille.
    for (int y = HAUTEUR - 1; y >= 0; --y) {
        for (int x = 0; x < LARGEUR; ++x)
            cout << grille[y][x];
        cout << '\n';   
    }
}


void Gestionnaire::creerPoints(const string& ligne) {
    //vector<Point> points;
    // On crée un flux de lecture (istringstream) à partir de la chaîne ligne.
    istringstream iss(ligne);
    string token;
    // On lit chaque point de la ligne (séparé par des espaces).
    while (iss >> token) {
        // On vérifie que le point est entre parenthèses
        if (token.size() >= 3 && token.front() == '(' && token.back() == ')') {
            // On enlève les parenthèses au début et à la fin.
            token = token.substr(1, token.size() - 2);
            // On remplace la virgule par un espace.
            replace(token.begin(), token.end(), ',', ' ');
            // On crée un flux de lecture pour chaque point
            istringstream pair(token);
            int x, y;
            // On ajoute un point {x, y} au vecteur de points.
            if (pair >> x >> y) {
                points.push_back(Point(x, y));
            }
        }
    }

}

void Gestionnaire::afficherPoints() {
    cout << "\nListe:\n";
    for (const auto& p : points) {
        cout << p.getId() + ": ("
            + to_string(p.getX()) + ","
            + to_string(p.getY()) + ")   textures: '"
            + p.getTexture() + "'\n";
    }
}

void Gestionnaire::supprimerPoint() {
    string idSupprimer;

    cout << "ID du point a supprimer: ";
    cin >> idSupprimer;

    auto it = remove_if(points.begin(), points.end(),
        [&](const Point& p) { return p.getId() == idSupprimer; });

    if (it == points.end()) {
        cout << "Erreur : ID invalide";
    }
    else {
        points.erase(it, points.end());
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Gestionnaire::deplacerPoint() {
    string idDeplacer;
    int nouveauX, nouveauY;

    cout << "ID du point a deplacer: ";
    cin >> idDeplacer;

    auto it = find_if(points.begin(), points.end(),
        [&](const Point& p) { return p.getId() == idDeplacer; });


    if (it == points.end()) {
        cout << "Erreur : ID invalide";
    }
    else {
        cout << "Nouvelle position (x y): ";
        if (!(cin >> nouveauX >> nouveauY)) {
            cout << "Erreur : Mauvaise coordonnees\n";
        }
        else {
            it->deplacerPoint(nouveauX, nouveauY);
        }
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Gestionnaire::fusionnerPoints() {
    static bool premiereFusion = true; // alterne entre "o" et "#"

    cout << "Entrez les IDs des points a fusionner (ex: 0 2 4) : ";
    string ligne;
    getline(cin >> ws, ligne);
    istringstream iss(ligne);
    string id;
    vector<string> ids;
    while (iss >> id) {
        ids.push_back(id);
    }

    for (const auto& fusionId : ids) {
        auto it = find_if(points.begin(), points.end(),
            [&](const Point& p) { return p.getId() == fusionId; });
        if (it != points.end()) {
            if (premiereFusion)
                it->setTexture(it->getTexture() + "o");
            else
                it->setTexture(it->getTexture() + "#");
        }
        else {
            cout << "ID invalide: " << fusionId << "\n";
        }
    }
    premiereFusion = !premiereFusion;
}

vector<Point> Gestionnaire::getPoints() {
    return points;
}


string AffichageTexture::getString(const Point& p) const {
    if (p.getTexture() == "") {
        return ".";
    }
    return p.getTexture();
}

string AffichageID::getString(const Point& p) const {
    std::string id = p.getId();
    return id;
}