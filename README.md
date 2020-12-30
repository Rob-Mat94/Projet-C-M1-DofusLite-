	######################## DofusLite ########################

	Il s'agit d'un jeu de role de type joueur contre joueur (JcJ).

	Chaque joueur gère une equipe de guerriers, deployés sur une carte, ils peuvent s'y déplacer et s'affronter.
    Chaque guerrier peut faire au maximum 4 mouvement durant son tour soit il se déplace, ou il attaque.
    Quand un guerrier fait une attaque réussi sur un autre le tour est passé automatiquement à l'autre équipe.

	Sur la carte il y a des obstacles que les guerrier ne peuvent pas traverser, et des objets ramassables (en les traversant) dont:
		* des potions (Potion) qui donnent des points de vie au guerrier qui les ramasse
		* des bouclier (Armor) qui boost les capacité de défense du guerrier qui les ramasse
		* des armes (Sword) qui boost les capacité d'attaque du guerrier qui les ramasse


	Controles (au clavier seulement):
		Le joueur peut déplacer le guerrier actuel avec Z S Q D, lorsque vous etes a proximité d'un guerrier enemi vous pouver appuyer sur Y pour l'attaquer
		En interface graphique choisir la carte dans le menu et appuyer sur entree pour commencer
			* En jeu la touche R sert à recommencer la partie, la touche Esc sert a revenir dans le menu principale


	Comment faire fonctionner le jeu:
		Le jeu est conçu sur Linux donc je vous suggère de le faire tourner sur une machine Linux, mais il peux très bien fonctionner sur windows (Visual Studio 2019)

		Sur Linux: (ubuntu, debian, Kali)
			* Installer GCC pour pouvoir compiler du C++
			* Installer SFML avec la commande suivante: sudo apt install libsfml-dev
			* Créer les dossiers obj et bin s'ils ne sont pas déjà créés
			* Executer la commande make (en cas d'echec "commande introuvable" => sudo apt install build-essential make)
			* Executer l'executable généré dans le dossier bin avec la commande ./bin/game

		Sur Windows (Visual Studio 2019):
			* Télécharger SFML sur le site suivant: https://www.sfml-dev.org/download.php
			* Suivre le tuto configuration SFML suivant: https://www.sfml-dev.org/tutorials/2.5/start-vc.php

		Fichiers du jeu:
			Le fichier .config contenu dans le dossier res sert a configurer le menu du jeu: 
				* Chaque ligne contien le nom qui apparait dans le menu et le nom du fichier qui contient la carte avec la syntaxe suivante: "nom:carte"
				* Chaque carte doit etre situé dans le dossier res

		Affichage sans interface graphique (dans le terminal):
			Le jeu peut etre affiché dans le terminal Linux ou Windows pour cela il suffit de remplacer le code du main par le code qui est mis en commentaire
			et dans Game.cpp mettre en commentaire la 5e ou 6e ligne en fonction de votre OS
