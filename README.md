La bibliothèque mrpiz doit être au même niveau que le dossier racine du projet (..\lib_mrpiz par rapport à votre répertoire racine)

Pour lancer la compilation, placer vous dans le répertoire src du projet et lancer, depuis un terminal, la commande suivante : make
La compilation utilise gcc avec les options nécessaires au simulateur.

Pour générer de la documentation doxygen, faite la commande : make doc

Pour effacer les fichiers générés par la compilation (.o, .d, binaire et aussi doc doxygen), faite la commande : make clean

Avant de lancer votre programme, assurez-vous que le simulateur soit lancé.
Pensez à appuyer sur le bouton démarrer du simulateur si vous voulez le voir s'animer.
Depuis le répertoire src, vous lancez le programme avec la commande ../bin/go

Petite modif
