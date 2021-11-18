# VOILIER

## Utilisation

Veuillez cloner le projet avec la commande suivante :
```sh
git clone --recurse-submodules https://github.com/rmonier/VOILIER
```
Ouvrez ensuite le fichier `driver.uvprojx` avec Keil.

Vous pouvez ensuite compiler, télécharger et exécuter le code sur la carte.

## Structure du projet

Le code est découpé en 3 parties principales qui délivrent une couche d'abstraction supplémentaire à chaque fois. Il y a la partie Driver, qui s'occupe de la gestion très bas niveau des registres, la partie Service, qui utilise Driver pour exécuter une action plus générale, et enfin la partie Principale (main) qui utilise Service pour créer une boucle d'exécution du programme. Ces fichiers sont répartis dans les dossiers `Source` et `Include`.

Dans le dossier `Tests` se trouvent des tests spécifiques pour quelques fichiers que l'ont peut inclure dans le main à l'aide du Header Only `tests.h`. Certains sont ici obsolètes ou désactivés, ils servaient essentiellement durant la phase de développement bas niveau.

## Consignes pour le développement

> :warning: **IMPORTANT** : Avant d'effectuer un `git pull` ou un `git commit` il faut impérativement FERMER KEIL (sinon le fichier projet sera corrompu)

> :warning: **IMPORTANT** : Lors de l'ajout d'un fichier au projet, vérifier que le chemin est RELATIF (`.\Include` ou `.\Tests` dans les balises `FilePath` par exemple) dans le fichier projet `driver.uvprojx`

### Git Modules

Pour utiliser la librairie externe, il faut cloner le projet avec la commande suivante :
```sh
git clone --recurse-submodules https://github.com/rmonier/VOILIER
```

Pour récuperer un nouveau module ajouté, exécuter :
```sh
git submodule update --init --recursive
```
