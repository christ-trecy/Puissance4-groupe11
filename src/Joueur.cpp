#include "Joueur.h"

Joueur::Joueur(const std::string& nom, char symbole)
    : nom(nom), symbole(symbole) {
}

std::string Joueur::getNom() const {
    return nom;
}

char Joueur::getSymbole() const {
    return symbole;
}
