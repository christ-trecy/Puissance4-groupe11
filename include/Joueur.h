#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>

class Joueur {
private:
    std::string nom;
    char symbole;

public:
    Joueur(const std::string& nom, char symbole);

    std::string getNom() const;
    char getSymbole() const;
};

#endif
