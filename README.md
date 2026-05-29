# Jeu Puissance 4 en C++

Projet console realise en programmation orientee objet, d'apres l'enonce fourni.

## Compilation

```bash
make
```

## Execution

```bash
make run
```

ou directement:

```bash
./bin/puissance4
```

## Regles implementees

- Grille verticale configuree dans `include/Grille.h` avec les constantes `nbLignes` et `nbColonnes`.
- Deux joueurs jouent tour a tour avec les symboles `X` et `O`.
- Un jeton tombe automatiquement dans la case libre la plus basse de la colonne choisie.
- Victoire detectee sur 4 jetons alignes horizontalement, verticalement ou diagonalement.
- Match nul si la grille est pleine sans victoire.
- Saisie utilisateur controlee avec gestion des erreurs.
- Tableau recapitulatif final des coups joues: joueur, symbole, ligne, colonne et couple `(ligne, colonne)`.

## Architecture

- `Joueur`: represente un participant avec un nom et un symbole.
- `Grille`: gere le plateau, l'affichage, le placement des jetons et l'etat plein.
- `Jeu`: orchestre la partie, alterne les tours et verifie la victoire.

Un diagramme UML texte est disponible dans `docs/diagramme_uml.md`.
