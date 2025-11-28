#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Gestionnaire.h"

// Commande
class Commande {
public:
    Commande() = default;
    virtual ~Commande() = default;
    virtual void executer() = 0;
    virtual void annuler() = 0;
    virtual shared_ptr<Commande> clone() const = 0;
    virtual bool possibiliteRetour() const { return true; }
};

// Commande a
class CommandeAfficher : public Commande {
public:
    CommandeAfficher(Gestionnaire& g);
    virtual ~CommandeAfficher() = default;
    virtual void executer() override;
    virtual void annuler() override;
    virtual shared_ptr<Commande> clone() const override;
    virtual bool possibiliteRetour() const override { return false; }
private:
    Gestionnaire& gestionnaire;
};

// Commande s
class CommandeSupprimer : public Commande {
public:
    CommandeSupprimer(Gestionnaire& g, string id);
    virtual ~CommandeSupprimer() = default;
    virtual void executer() override;
    virtual void annuler() override;
    virtual shared_ptr<Commande> clone() const override;
private:
    string idSupprimer;
    Gestionnaire& gestionnaire;
    vector<shared_ptr<Point>> points;
    vector<shared_ptr<Nuage>> nuages;
    vector<vector<shared_ptr<Composante>>> contenuNuages;
};

// Commande d
class CommandeDeplacer : public Commande {
public:
    CommandeDeplacer(Gestionnaire& g, string id, int x, int y);
    virtual ~CommandeDeplacer() = default;
    virtual void executer() override;
    virtual void annuler() override;
    virtual shared_ptr<Commande> clone() const override;
private:
    Gestionnaire& gestionnaire;
    vector<shared_ptr<Point>> points;
    string idDeplacer;
    int positionX;
    int positionY;
    int ancienX;
    int ancienY;
};

// Commande f
class CommandeFusionner : public Commande {
public:
    CommandeFusionner(Gestionnaire& g, string ligne);
    virtual ~CommandeFusionner() = default;
    virtual void executer() override;
    virtual void annuler() override;
    virtual shared_ptr<Commande> clone() const override;
private:
    Gestionnaire& gestionnaire;
    vector<shared_ptr<Nuage>> nuages;
    vector<shared_ptr<Point>> points;
    vector<string> texturesPoints; 
    string ids;
};

// Commande c1
class CommandeConstructionCroissante : public Commande {
public:
    CommandeConstructionCroissante(Gestionnaire& g);
    virtual ~CommandeConstructionCroissante() = default;
    virtual void executer() override;
    virtual void annuler() override;
    virtual shared_ptr<Commande> clone() const override;
private:
    Gestionnaire& gestionnaire;
    shared_ptr<StrategieConstruction> strategie;
};

// Commande c2
class CommandeConstructionMinimale : public Commande {
public:
    CommandeConstructionMinimale(Gestionnaire& g);
    virtual ~CommandeConstructionMinimale() = default;
    virtual void executer() override;
    virtual void annuler() override;
    virtual shared_ptr<Commande> clone() const override;
private:
    Gestionnaire& gestionnaire;
    shared_ptr<StrategieConstruction> strategie;
};

// Commande o1
class CommandeGrilleTexture : public Commande {
public:
    CommandeGrilleTexture(Gestionnaire& g);
    virtual ~CommandeGrilleTexture() = default;
    virtual void executer() override;
    virtual void annuler() override;
    virtual shared_ptr<Commande> clone() const override;
    virtual bool possibiliteRetour() const override { return false; }
private:
    Gestionnaire& gestionnaire;
};

// Commande o2
class CommandeGrilleId : public Commande {
public:
    CommandeGrilleId(Gestionnaire& g);
    virtual ~CommandeGrilleId() = default;
    virtual void executer() override;
    virtual void annuler() override;
    virtual shared_ptr<Commande> clone() const override;
    virtual bool possibiliteRetour() const override { return false; }
private:
    Gestionnaire& gestionnaire;
};