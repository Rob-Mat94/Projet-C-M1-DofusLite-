	######################## DofusLite ########################

	Il s'agit d'un jeu de rôle de type joueur contre joueur (JcJ).

	Chaque joueur gère une équipe de guerriers, déployés sur une carte où ils peuvent se déplacer et s'affronter.
	Chaque guerrier peut au maximum faire 4 mouvements durant son tour.
	Quand un guerrier attaque un ennemi, le tour est passé automatiquement.

	Sur la carte il y a des obstacles que les guerriers ne peuvent pas traverser, et des objets ramassables (en les traversant) dont :
		* des potions (Potion) qui donnent des points de vie au guerrier 
		* des bouclier (Armor) qui boost les capacités de défense du guerrier 
		* des armes (Sword) qui boost les capacités d'attaque du guerrier 


	Contrôles (au clavier seulement) :
		Le joueur peut déplacer le guerrier actuel avec Z S Q D, lorsque vous êtes à proximité d'un guerrier ennemi vous pouvez appuyer sur Y pour l'attaquer
		Dans l’interface graphique, il est possible de choisir la carte dans le menu et d’appuyer sur entrée pour commencer
			* En jeu la touche R sert à recommencer la partie, la touche Esc à revenir dans le menu principal


	Comment faire fonctionner le jeu :
		Le jeu est conçu sur Linux donc je vous recommande de le faire tourner sur une machine Linux, mais il peut très bien fonctionner sur windows (Visual Studio 2019)

		Sur Linux : (ubuntu, debian, Kali)
			* Installer GCC pour pouvoir compiler du C++
			* Installer SFML avec la commande suivante : sudo apt install libsfml-dev
			* Créer les dossiers obj et bin s'ils ne sont pas déjà créés
			* Executer la commande make (en cas d'echec "commande introuvable" => sudo apt install build-essential make)
			* Executer la commande suivante : « export DISPLAY=:0.0 »
			* Executer l'executable généré dans le dossier bin avec la commande «./bin/game »

		Sur Windows (Visual Studio 2019):
			* Créer un nouveau projet vide puis copier les dossiers src, include, res ainsi que le fichier main.cpp dans le répertoire du projet
			* Dans l'explorateur de solutions de visual studio cliquer sur afficher tous les fichiers et pour chacun des dossiers includes et src ainsi que le fichier main.cpp faire un clic droit et sélectionner inclure dans le projet
			* Télécharger SFML sur le site suivant : https://www.sfml-dev.org/download.php
			* Suivre le tuto configuration SFML suivant : https://www.sfml-dev.org/tutorials/2.5/start-vc.php
				Dans le menu projet -> propriétés du projet :

				Pour toutes les configurations:
					Dans C/C++ -> général -> autres répértoires include: ajouter l'emplacement de SFML\include exemple: c:\SFML\include
					Dans C/C++ -> préprocesseur -> définitions de préprocesseur : ajouter SFML_STATIC;
					Dans éditeur de liens -> général -> répértoires de bibliothèques supplémentaires : ajouter l'emplacement de SFML\lib exemple : c:\SFML\lib

				Dans editeur de liens -> entrée -> dépendances supplémentaires :
					Pour la configuration release: ajouter sfml-graphics-s.lib;sfml-window-s.lib;sfml-system-s.lib;sfml-audio-s.lib;openal32.lib;flac.lib;vorbisenc.lib;vorbisfile.lib;vorbis.lib;ogg.lib;winmm.lib;opengl32.lib;freetype.lib;gdi32.lib;
					Pour la configuration debug: ajouter sfml-graphics-s-d.lib;sfml-window-s-d.lib;sfml-system-s-d.lib;sfml-audio-s-d.lib;openal32.lib;flac.lib;vorbisenc.lib;vorbisfile.lib;vorbis.lib;ogg.lib;winmm.lib;opengl32.lib;freetype.lib;gdi32.lib;

		Fichiers du jeu:
			Le fichier .config contenu dans le dossier res sert à configurer le menu du jeu:
				* Chaque ligne contient le nom qui apparait dans le menu et le nom du fichier qui contient la carte avec la syntaxe suivante : nom:carte
				* Chaque fichier contenant une carte doit être situé dans le dossier res

		Affichage sans interface graphique (dans le terminal):
			Le jeu peut être affiché dans le terminal Linux ou Windows pour cela il suffit de remplacer le code du main par le code qui est mis en commentaire
			et dans Game.cpp mettre en commentaire la 5e ou 6e ligne en fonction de votre OS