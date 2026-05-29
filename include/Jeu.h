#ifndef JEU_H
#define JEU_H

#include "Grille.h"
#include "Joueur.h"

#include <iostream>
#include <string>
#include <vector>

class Jeu {
private:
    struct Coup {
        int numero;
        std::string joueur;
        char symbole;
        int ligne;
        int colonne;
    };

    Grille grille;
    Joueur joueur1;
    Joueur joueur2;
    Joueur* joueurActuel;
    std::vector<Coup> historiqueCoups;

    int demanderColonne() const;
    int compterJetons(int ligne, int colonne, int directionLigne, int directionColonne, char symbole) const;
    void enregistrerDernierCoup();

public:
    Jeu(const Joueur& joueur1, const Joueur& joueur2);

    void tourSuivant();
    bool verifierVictoire() const;
    void afficherRecapitulatif(std::ostream& sortie = std::cout) const;
    void lancerPartie();
};

#endif
