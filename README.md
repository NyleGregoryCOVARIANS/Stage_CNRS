Tutoriel : Structurer et gérer un dépôt Git avec plusieurs projets
Ce tutoriel explique comment organiser un dépôt Git avec plusieurs projets, déposer un projet sur GitHub, gérer les versions avec les commits, et revenir à une version précédente. Nous utiliserons comme exemple un projet nommé "Alimentation canon à électrons" avec deux sous-dossiers : "Kimball" et "SPECS".

1. Initialiser et structurer un dépôt Git
Étape 1 : Créer un dépôt local

Ouvrir un terminal dans le répertoire où vous souhaitez créer votre projet.

Initialiser un dépôt Git :
git init

Cela crée un dossier caché .git qui contient toutes les informations de versionnement.

Créer une arborescence de dossiers :Organisez vos projets dans une structure claire. Par exemple :
mkdir -p "Alimentation canon à électrons/Kimball" "Alimentation canon à électrons/SPECS"

Cette commande crée un dossier principal "Alimentation canon à électrons" avec deux sous-dossiers : "Kimball" et "SPECS".

Ajouter des fichiers :Placez le code source de vos projets dans les sous-dossiers. Par exemple :

Alimentation canon à électrons/Kimball/main.py
Alimentation canon à électrons/SPECS/config.json

Exemple de création d’un fichier fictif :
echo "# Code pour Kimball" > "Alimentation canon à électrons/Kimball/main.py"
echo "{\"setting\": \"example\"}" > "Alimentation canon à électrons/SPECS/config.json"


Ajouter les fichiers au suivi Git :
git add .

La commande git add . ajoute tous les fichiers et dossiers à l’index Git.

Créer un premier commit :
git commit -m "Initialisation du projet avec structure de dossiers"




2. Déposer le projet sur GitHub
Étape 1 : Créer un dépôt sur GitHub

Connectez-vous à GitHub.
Cliquez sur New pour créer un nouveau dépôt.
Donnez un nom au dépôt, par exemple Alimentation-Canon-Electrons.
Laissez les options par défaut (pas besoin d’initialiser avec un README pour l’instant).
Cliquez sur Create repository.

Étape 2 : Lier le dépôt local à GitHub

Copiez l’URL du dépôt GitHub (par exemple, https://github.com/votre-utilisateur/Alimentation-Canon-Electrons.git).

Dans votre terminal, associez le dépôt local au dépôt distant :
git remote add origin https://github.com/votre-utilisateur/Alimentation-Canon-Electrons.git


Pousser les modifications vers GitHub :
git push -u origin main

Si vous utilisez une branche autre que main (par exemple master), remplacez main par le nom de votre branche.



3. Gérer les versions avec Git
Étape 1 : Faire des commits réguliers
Chaque modification importante doit être sauvegardée dans un commit. Par exemple :

Modifiez un fichier, par exemple main.py dans le dossier Kimball :
echo "print('Hello from Kimball')" >> "Alimentation canon à électrons/Kimball/main.py"


Ajoutez les modifications :
git add "Alimentation canon à électrons/Kimball/main.py"


Créez un commit avec un message descriptif :
git commit -m "Ajout de la fonction d'impression dans main.py"



Étape 2 : Consulter l’historique des versions
Pour voir l’historique des commits :
git log

Cela affiche tous les commits avec leur identifiant (hash), auteur, date et message.
Pour une version plus concise :
git log --oneline

Étape 3 : Sauvegarder les versions
Chaque commit est une sauvegarde de l’état du projet à un moment donné. Pour organiser vos commits :

Utilisez des messages clairs et descriptifs.
Faites des commits fréquents pour des modifications spécifiques.
Exemple :git commit -m "Ajout de la configuration initiale dans SPECS"
she




4. Revenir à une version précédente
Si vous souhaitez revenir à une version antérieure de votre projet, suivez ces étapes :
Étape 1 : Identifier le commit cible

Consultez l’historique pour trouver l’identifiant (hash) du commit auquel vous voulez revenir :git log --oneline

Notez le hash du commit (par exemple, a1b2c3d).

Étape 2 : Revenir à une version précédente
Pour revenir temporairement à une version sans perdre les commits ultérieurs :
git checkout a1b2c3d

Cela met votre répertoire de travail dans l’état du commit spécifié.
Pour revenir définitivement à une version (en supprimant les commits ultérieurs) :
git reset --hard a1b2c3d

Attention : Cette commande supprime tous les commits après a1b2c3d. Assurez-vous de sauvegarder votre travail avant.
Étape 3 : Pousser les modifications (si nécessaire)
Si vous avez utilisé git reset --hard et souhaitez mettre à jour le dépôt distant :
git push --force

Note : L’option --force est dangereuse, car elle écrase l’historique sur le dépôt distant. Utilisez-la avec prudence.

5. Bonnes pratiques pour la gestion de Git

Structure claire : Organisez vos projets dans des dossiers logiques (comme Kimball et SPECS) pour une meilleure lisibilité.
Commits fréquents : Sauvegardez souvent avec des messages clairs.
Branches : Utilisez des branches pour travailler sur des fonctionnalités spécifiques :git branch nouvelle-fonction
git checkout nouvelle-fonction

Fusionnez ensuite avec :git checkout main
git merge nouvelle-fonction


.gitignore : Créez un fichier .gitignore pour exclure les fichiers inutiles (par exemple, __pycache__, *.log) :echo "__pycache__" > .gitignore
git add .gitignore
git commit -m "Ajout du fichier .gitignore"




Conclusion
Vous savez maintenant comment :

Structurer un dépôt Git avec plusieurs projets.
Déposer un projet sur GitHub.
Gérer les versions avec des commits.
Revenir à une version précédente.

Pour aller plus loin, explorez les fonctionnalités avancées comme les pull requests, les tags pour marquer des versions, et la résolution de conflits de fusion.
