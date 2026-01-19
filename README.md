# Position-Based-Fluids-

Projet réalisé dans le cadre du cours électif Introduction au C++.

--------
CONTEXTE
--------

Le sujet initialement proposé est l'implémentation d'une simulation de type "Position based dynamics" introduite par Müller et al [1] en 2006. Après avoir suivi les étapes définies dans le sujet, j'ai choisi de l'étendre à la simulation de fluides. Pour cela je me suis appuyé sur le papier de Macklin et Müller [2] intitulé "Position Based Fluids". Dans leur article, ils décrivent comment étendre la méthode "Position based dynamics" à la simulation fluide par la formulation et la résolution d'un ensemble de contraintes de positions afin d'imposer une densité constante et donc de simuler l'incompressibilité d'un fluide tel que l'eau. Mon projet s'inscrit dans la continuité du sujet initialement proposé et en reprend donc les principaux éléments. Je précise également que pour la réalisation de la partie fluide de ce projet j'ai eu recours à l'IA générative GEMINI.

--------------------------
DESCRIPTION DE L'INTERFACE
--------------------------

L'exécution du programme fait apparaître l'interface de simulation. Dans la partie supérieure on trouve des boutons, une spinBbox ainsi que des sliders. Pour lancer la simulation, l'utilisateur sélectionne dans la spinBox le nombre de particules à générer à l'écran selon une distribution uniforme puis clique sur le bouton generate. Les particules vont alors apparaître à l'écran. Le bouton start permet alors de lancer la simulation. 

---------------------
EXEMPLE DE SIMULATION
---------------------

Générer 2000 particules puis lancer la simulation. Mettre la gravité au maximum (1000) puis augmenter progressivement le curseur de l'amplitude. Les murs de gauche et de droite vont alors se déplacer en phase selon un mouvement périodique. Le fluide va alors se mettre en mouvement. Regarder l'effet des différents curseurs sur la simulation. 

-------------------
DESCRIPTION DU CODE
-------------------

Le cœur de la simulation repose sur la résolution d'un système de contrainte non linéaires afin de satisfaire la condition d'incompressibilité du fluide comme indiqué dans [2]. A chaque pas de temps, on prédit la future position des particules en fonction de la gravité puis on applique des corrections afin de maintenir une densité constante. Ainsi chaque particule cherche à maintenir sa densité le plus proche possible d'une densité de repos stockée dans la variable rho_0. La résolution des contraintes de densité est implémentée dans les méthodes computeLambdas() et computeDeltaPositions() de la classe Context. Un hachage spatiale est implémenté afin d'éviter de comparer chaque particule à toutes les autres. La zone de simulation est divisée en mailles dont le pas est désigné par le paramètre constant cellSize. On ne considère donc que les plus proches voisins selon un rayon donné. Les noyaux de lissage recommandés dans [2] sont utilisés afin de calculer la densité et les forces d'interaction en fonction de la distance entre les particules.

J'ai également implémenté des fonctionnalités supplémentaires. Une pression artificielle notée scorr (équation (13) dans [2]) qui traduit une force de répulsion à courte portée afin d'éviter que les particules ne s'agglutinent et permet donc de simuler une tension de surface. Ce terme fait intervenir trois paramètres :
- dq_dist_scorr : distance de référence à laquelle les particules veulent se positionner les unes par rapport aux autres. D'après [2] il est généralement fixé entre 0.1h et 0.3h où h désigne le pas de maillage pour la grille de hachage. 
- k_scorr : facteur multiplicatif. Plus il est grand, plus la force de répulsion sera importante. Il est fixé à 0.1 dans [2]. 
- n_scorr : exposant entier qui intervient dans le calcul de la pression artificielle. Il est fixé à 4 comme recommandé dans [2].
Ajout d'une force de vorticité (équations (15) et (16) dans [2]) pour réinjecter de l'énergie dissipée par le solveur. Elle est pilotée par le coefficient c_vorti. Ajout d'un terme de viscosité (équation (17) dans [2]) pour le lissage des vitesses et assurer un mouvement plus cohérent. Il est piloté par le coefficient c_visco dont la valeur choisie par les auteurs est de 0.01.

----------------------------
CE QUE LE PROJET M'A APPORTE 
----------------------------

Ce projet m'a permis d'appliquer des notions vues en cours ainsi que de mieux les comprendre. Parmi ces concepts je peux citer :

- la gestion de la mémoire : utilisation des pointeurs, distinction entre la stack et le tas, les allocations dynamiques, le principe RAII.
- interface graphique de Qt : gestion d'évènement utilisateur, hiérarchie d'instance de QWidget et notamment QLabel, QSpinBox, QSlider, QLayout, les signaux et slots ainsi que la gestion du temps.  
- les classes : constructeur, destructeur, définitions de méthodes et d'opérateurs. 
- l'héritage et le polymorphisme à travers les colliders.
- l'utilisation de la librairie standard : std::vector<>, std::unique_ptr<>, std::unordered_map<>.  
- l'utilisation des fichiers .h et des fichiers .cpp et comment ils interagissent.

L'IA générative m'a permis de cerner et de comprendre la démarche développée dans [2]. Elle m'a également aidé pour le débogage de mon code et m'a suggéré des idées d'améliorations. Elle m'a par exemple aidé à appliquer les metaballs, une méthode de rendu qui transforme les points en une surface liquide continue grâce à une carte de densité et un seuillage progressif. 

Je souhaite préciser que j'ai ajouté cette fonctionnalité en fin de projet afin d'avoir un rendu plus réaliste mais que je n'ai pas eu le temps de comprendre clairement l'algorithme proposé par l'IA générative. Pour revenir au rendu "classique" avec les sphères il suffit de mettre entre commentaire l'implémentation de la deuxième méthode void DrawArea::paintEvent(QPaintEvent *event) dans drawarea.cpp et de retirer les commentaires pour la première version de la méthode bien plus courte.

-------------
BIBLIOGRAPHIE
-------------

[1] MÜLLER M., HEIDELBERGER B., HENNIX M., RATCLIFF J.: Position based dynamics. Journal of Visual Communication and Image Representation 18, 2 (2007), 109–118. 5, 11, 28

[2] MACKLIN M., MÜLLER M.: Position based fluids. ACM Trans. Graph. 32, 4 (July 2013), 104:1–104:12. 19
