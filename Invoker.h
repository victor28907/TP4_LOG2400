#pragma once
#include <string>
#include <memory>
#include <list>
#include "Commandes.h"


using CommandePtr = shared_ptr<Commande>;
using Commandes = list<CommandePtr>;

class Invoker {
public:
    Invoker() = default;
    virtual ~Invoker() = default;
    void executer(const CommandePtr& commande);
    void undo();
    void redo();
private:
    Commandes commandesEffectuees;
    Commandes commandesAnnulees;
};