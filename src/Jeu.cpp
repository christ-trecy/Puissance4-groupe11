#include "Jeu.h"

#include <cctype>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

Jeu::Jeu(const Joueur& joueur1, const Joueur& joueur2)
    : joueur1(joueur1), joueur2(joueur2), joueurActuel(&this->joueur1) {
}

void Jeu::tourSuivant() {
    joueurActuel = (joueurActuel == &joueur1) ? &joueur2 : &joueur1;
}

bool Jeu::verifierVictoire() const {
    int ligne = grille.getDerniereLigne();
    int colonne = grille.getDerniereColonne();

    if (ligne < 0 || colonne < 0) {
        return false;
    }

    char symbole = joueurActuel->getSymbole();
    const int directions[4][2] = {
        {0, 1},
        {1, 0},
        {1, 1},
        {1, -1}
    };

    for (const auto& direction : directions) {
        int total = 1;
        total += compterJetons(ligne, colonne, direction[0], direction[1], symbole);
        total += compterJetons(ligne, colonne, -direction[0], -direction[1], symbole);

        if (total >= 4) {
            return true;
        }
    }

    return false;
}

void Jeu::lancerPartie() {
    std::cout << "\n===== PUISSANCE 4 =====\n";
    std::cout << "Alignez 4 jetons horizontalement, verticalement ou en diagonale.\n";

    while (true) {
        grille.afficherGrille();

        std::cout << joueurActuel->getNom()
                  << " (" << joueurActuel->getSymbole() << "), a vous de jouer.\n";

        int colonne = 0;
        try {
            colonne = demanderColonne();
        } catch (const std::runtime_error& erreur) {
            std::cout << "\n" << erreur.what() << "\n";
            break;
        }

        if (!grille.placerJeton(colonne, joueurActuel->getSymbole())) {
            std::cout << "Coup impossible: la colonne est pleine ou invalide.\n";
            continue;
        }

        enregistrerDernierCoup();

        if (verifierVictoire()) {
            grille.afficherGrille();
            std::cout << "Bravo " << joueurActuel->getNom() << ", vous avez gagne !\n";
            afficherRecapitulatif();
            break;
        }

        if (grille.estPleine()) {
            grille.afficherGrille();
            std::cout << "Match nul: la grille est pleine.\n";
            afficherRecapitulatif();
            break;
        }

        tourSuivant();
    }
}

void Jeu::afficherRecapitulatif(std::ostream& sortie) const {
    if (historiqueCoups.empty()) {
        sortie << "\nAucun coup n'a ete joue.\n";
        return;
    }

    sortie << "\nTableau recapitulatif des coups\n";
    sortie << "+------+----------------------+---------+--------+---------+---------------+\n";
    sortie << "| Coup | Joueur               | Symbole | Ligne  | Colonne | Couple (L,C)  |\n";
    sortie << "+------+----------------------+---------+--------+---------+---------------+\n";

    for (const Coup& coup : historiqueCoups) {
        std::string couple = "(" + std::to_string(coup.ligne) + ", " + std::to_string(coup.colonne) + ")";

        sortie << "| " << std::setw(4) << coup.numero
               << " | " << std::left << std::setw(20) << coup.joueur
               << " | " << std::right << std::setw(7) << coup.symbole
               << " | " << std::setw(6) << coup.ligne
               << " | " << std::setw(7) << coup.colonne
               << " | " << std::left << std::setw(13) << couple << std::right
               << " |\n";
    }

    sortie << "+------+----------------------+---------+--------+---------+---------------+\n";
}

int Jeu::demanderColonne() const {
    while (true) {
        try {
            std::cout << "Choisissez une colonne entre 1 et "
                      << Grille::getNbColonnes() << " : ";

            std::string saisie;
            if (!std::getline(std::cin, saisie)) {
                throw std::runtime_error("Partie interrompue: aucune nouvelle saisie disponible.");
            }

            size_t position = 0;
            int colonne = std::stoi(saisie, &position);

            while (position < saisie.size() && std::isspace(static_cast<unsigned char>(saisie[position]))) {
                ++position;
            }

            if (position != saisie.size()) {
                throw std::invalid_argument("La saisie contient des caracteres non numeriques.");
            }

            if (colonne < 1 || colonne > Grille::getNbColonnes()) {
                throw std::out_of_range("La colonne est hors limites.");
            }

            return colonne;
        } catch (const std::invalid_argument&) {
            std::cout << "Saisie invalide. Entrez uniquement un nombre de 1 a "
                      << Grille::getNbColonnes() << ".\n";
        } catch (const std::out_of_range&) {
            std::cout << "Saisie invalide. Entrez uniquement un nombre de 1 a "
                      << Grille::getNbColonnes() << ".\n";
        }
    }
}

int Jeu::compterJetons(int ligne, int colonne, int directionLigne, int directionColonne, char symbole) const {
    int total = 0;
    int ligneCourante = ligne + directionLigne;
    int colonneCourante = colonne + directionColonne;

    while (ligneCourante >= 0 && ligneCourante < Grille::getNbLignes()
           && colonneCourante >= 0 && colonneCourante < Grille::getNbColonnes()
           && grille.getCase(ligneCourante, colonneCourante) == symbole) {
        ++total;
        ligneCourante += directionLigne;
        colonneCourante += directionColonne;
    }

    return total;
}

void Jeu::enregistrerDernierCoup() {
    Coup coup;
    coup.numero = static_cast<int>(historiqueCoups.size()) + 1;
    coup.joueur = joueurActuel->getNom();
    coup.symbole = joueurActuel->getSymbole();
    coup.ligne = grille.getDerniereLigne() + 1;
    coup.colonne = grille.getDerniereColonne() + 1;

    historiqueCoups.push_back(coup);
}
