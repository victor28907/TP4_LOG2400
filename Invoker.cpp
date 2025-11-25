#include "Invoker.h"

void Invoker::executer(const CommandePtr & commande) {
    auto commandeClone = commande->clone();
    commandeClone->executer();
    if (commandeClone->possibiliteRetour()) commandesEffectuees.push_back(commandeClone);
}

void Invoker::undo() {
    if(!commandesEffectuees.empty()) {
        CommandePtr commande = commandesEffectuees.back();
        commande->annuler();
        commandesEffectuees.pop_back();
        commandesAnnulees.push_back(commande);
    }
}

void Invoker::redo() {
    if (!commandesAnnulees.empty()) {
        CommandePtr commande = commandesAnnulees.back();
        commande->executer();
        commandesAnnulees.pop_back();
        commandesEffectuees.push_back(commande);
    }
}