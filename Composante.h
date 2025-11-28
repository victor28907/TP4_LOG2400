#ifndef COMPOSANTE_H
#define COMPOSANTE_H

#include <vector>
#include <string>
#include <memory>

using namespace std;

class Composante {
public:
    virtual ~Composante() = default;
    virtual int getNombreComposants() const = 0;
    virtual void deplacer(int dx, int dy) = 0;
    virtual void setTexture(const string& texture) = 0;
    virtual string getId() const = 0;
    virtual string getTexture() const = 0;
    static void retirerElementCompteur();
    virtual void vider() {}
    virtual void ajouter(shared_ptr<Composante> composante) {}
    virtual void retirer(shared_ptr<Composante> composante) {}
    virtual const vector<shared_ptr<Composante>>& getEnfants() const;
    virtual vector<shared_ptr<Composante>> getPoints() const = 0;
    virtual void reorganiserEnfants(const vector<shared_ptr<Composante>>& nouveauxEnfants) {}

protected:
    static int compteurComposant;
    static string generationId();
};

#endif // COMPOSANTE_H