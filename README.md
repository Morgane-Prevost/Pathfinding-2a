# SFML ImGUI Template

Ce projet implémente plusieurs algorithmes de pathfinding permettant de trouver un chemin optimal entre deux points dans un environnement en grille.
Il inclut une visualisation en temps réel du fonctionnement des algorithmes et permet de comparer leurs performances.

**ALGORITHME IMPLEMENTE**

   - BFS - pathfinding de base 
   - A* (A-star) – optimal et performant
   - Dijkstra – exhaustive, sans heuristique
   - Greedy – très rapide mais pas toujours optimal

Chaque algorithme peut être activé et reset depuis l’interface ImGui.

-----------------------------------------------------------------------

**FONCTIONNEMENT**

Le programme utilise une grille composée de cellules pouvant être :
   - libres, obstacles, départ, arrivée
Il est possible de choisir les points d'arrivée et de départ, ainsi que de placer des murs et des péages.

Des couleurs permettent de comprendre les étapes du pathfinding :
   - Vert (S) & Rouge (Left Ckick) : Points de départ et d'arrivée
   - Noir (W) : Mur
   - Blanc (T) : Péage
   - Bleu foncé : recherche de l'&rrivé en vistant les voisins
   - Jaune : chemin final

On peut connaître le nombre de neouds visités, la distance parcourut, et le coût de 'litinéraire pris en fonction du type de route et donc péage.

-------------------------------------------------------------------------

**REPARTITION DU TRAVAIL**

   - Morgane : Maping & Input Maping - A* & BFS - AlgoManager - ImGuiManager - Affichage - Graphe & Node
   - Julia : Djikstra & Greedy

