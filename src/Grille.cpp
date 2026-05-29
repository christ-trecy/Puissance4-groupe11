#include "Grille.h"

#include <iomanip>

Grille::Grille()
    : derniereLigne(-1), derniereColonne(-1) {
    initialiserGrille();
}

void Grille::initialiserGrille() {
    for (auto& ligne : cases) {
        ligne.fill(caseVide);
    }

    derniereLigne = -1;
    derniereColonne = -1;
}

void Grille::afficherGrille(std::ostream& sortie) const {
    sortie << "\n";
    for (int colonne = 1; colonne <= nbColonnes; ++colonne) {
        sortie << "   " << colonne;
    }
    sortie << "\n";

    sortie << " +";
    for (int colonne = 0; colonne < nbColonnes; ++colonne) {
        sortie << "---+";
    }
    sortie << "\n";

    for (int ligne = 0; ligne < nbLignes; ++ligne) {
        sortie << " |";
        for (int colonne = 0; colonne < nbColonnes; ++colonne) {
            sortie << " " << cases[ligne][colonne] << " |";
        }
        sortie << "\n +";

        for (int colonne = 0; colonne < nbColonnes; ++colonne) {
            sortie << "---+";
        }
        sortie << "\n";
    }

    sortie << "\n";
}

bool Grille::placerJeton(int colonne, char symbole) {
    int indiceColonne = colonne - 1;

    if (indiceColonne < 0 || indiceColonne >= nbColonnes) {
        return false;
    }

    for (int ligne = nbLignes - 1; ligne >= 0; --ligne) {
        if (cases[ligne][indiceColonne] == caseVide) {
            cases[ligne][indiceColonne] = symbole;
            derniereLigne = ligne;
            derniereColonne = indiceColonne;
            return true;
        }
    }

    return false;
}

bool Grille::estPleine() const {
    for (int colonne = 0; colonne < nbColonnes; ++colonne) {
        if (cases[0][colonne] == caseVide) {
            return false;
        }
    }

    return true;
}

char Grille::getCase(int ligne, int colonne) const {
    if (!positionValide(ligne, colonne)) {
        return caseVide;
    }

    return cases[ligne][colonne];
}

int Grille::getDerniereLigne() const {
    return derniereLigne;
}

int Grille::getDerniereColonne() const {
    return derniereColonne;
}

int Grille::getNbLignes() {
    return nbLignes;
}

int Grille::getNbColonnes() {
    return nbColonnes;
}

char Grille::getCaseVide() {
    return caseVide;
}

bool Grille::positionValide(int ligne, int colonne) const {
    return ligne >= 0 && ligne < nbLignes && colonne >= 0 && colonne < nbColonnes;
}
