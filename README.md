# VOILIER

> :warning: **IMPORTANT** : Avant d'effectuer un `git pull` il faut impérativement FERMER KEIL (sinon le fichier projet sera corrompu)

> :warning: **IMPORTANT** : Lors de l'ajout d'un fichier au projet, vérifier que le chemin est RELATIF (`.\Include` ou `.\Tests` dans les balises `FilePath` par exemple) dans le fichier projet `driver.uvprojx`

## Git Modules

Pour utiliser la librairie externe, il faut cloner le projet avec la commande suivante :
```sh
git clone --recurse-submodules https://github.com/rmonier/VOILIER
```

Pour récuperer un nouveau module ajouté, exécuter :
```sh
git submodule update --init --recursive
```
