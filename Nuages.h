#ifndef NUAGE_H
#define NUAGE_H

#include "Composante.h"
#include <vector>
#include <string>
#include <memory>
#include "Point.h"
#include "StrategieConsutruction.h"

using namespace std;

class Nuage : public Composante, public enable_shared_from_this<Nuage> {
public:
    Nuage();
    static void retirerNuageCompteur();
    
    int getNombreComposants() const override;
    void deplacer(int dx, int dy) override;
    void setTexture(const string& texture) override;
    string getId() const override { return id; }
    string getTexture() const override { return symbole; }
    
    void ajouter(shared_ptr<Composante> composante) override;
    void retirer(shared_ptr<Composante> composante) override;
    void vider() override;
    const vector<shared_ptr<Composante>>& getEnfants() const override { return enfants; }
    
    vector<shared_ptr<Composante>> obtenirPoints() const override;
    void reorganiserEnfants(const vector<shared_ptr<Composante>>& nouveauxEnfants) override;
    
    string getSymbole() const;
    
private:
    string id;
    string symbole;
    vector<shared_ptr<Composante>> enfants;
    static int compteurNuages;
    int indexNuage;
    static const string symboles[3];
};

#endif