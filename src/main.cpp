#include "Jeu.h"
#include "Joueur.h"

#include <iostream>
#include <string>

std::string demanderNom(const std::string& libelle, const std::string& nomParDefaut) {
    std::cout << libelle << " : ";

    std::string nom;
    std::getline(std::cin, nom);

    if (nom.empty()) {
        return nomParDefaut;
    }

    return nom;
}

int main() {
    std::cout << "Creation d'une partie de Puissance 4\n";
    std::string nomJoueur1 = demanderNom("Nom du joueur 1", "Joueur 1");
    std::string nomJoueur2 = demanderNom("Nom du joueur 2", "Joueur 2");

    Joueur joueur1(nomJoueur1, 'X');
    Joueur joueur2(nomJoueur2, 'O');

    Jeu jeu(joueur1, joueur2);
    jeu.lancerPartie();

    return 0;
}
