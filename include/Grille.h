#ifndef GRILLE_H
#define GRILLE_H

#include <array>
#include <iostream>

class Grille {
private:
    static constexpr int nbLignes = 8;
    static constexpr int nbColonnes = 8;
    static constexpr char caseVide = ' ';

    std::array<std::array<char, nbColonnes>, nbLignes> cases;
    int derniereLigne;
    int derniereColonne;

    bool positionValide(int ligne, int colonne) const;

public:
    Grille();

    void initialiserGrille();
    void afficherGrille(std::ostream& sortie = std::cout) const;
    bool placerJeton(int colonne, char symbole);
    bool estPleine() const;

    char getCase(int ligne, int colonne) const;
    int getDerniereLigne() const;
    int getDerniereColonne() const;

    static int getNbLignes();
    static int getNbColonnes();
    static char getCaseVide();
};

#endif
