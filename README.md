# ClavierGenetique
TD Métaheuristiques </br>
Compilation : g++ -std=c++11 main.cpp clavier.cpp tribu.cpp -o main </br>
Lancement : ./main *options* </br>
<ul> Options de lancement:
<li> --nbIterations : nombre total de génération (default = 1000) </li>
<li>--percentageConsanguinite : pourcentage de consanguinité acceptable au sein de la population (default = 5) </li>
<li>--percentageCroisement : pourcentage des meilleurs individus de la population à croiser à chaque génération (default = 30) </li>
<li>--percentageMutation : pourcentage de la population qui développera une ou plusieurs mutation entre 2 générations (default = 50) </li>
<li>--nbMaxMutations : nombre maximum de mutations que peut subir un individu lorsqu'il est choisi pour muter (pas de croisement, mutation pure) (default = 4) </li>
<li>--nbIndividus : nombre d'individus dans la population(default = 50) </li>
<li>--tailleLigne : Nombre de claviers affichable en largeur dans un terminal, si la valeur est trop grande l'affichage se fera mal. (default pour un écran 1080p : 7) </li>
<li>--sort : tri? Oui (default: 1); À enlever comme c'est pas utilisé </li>
</ul>
<br>
Exemple: ./main --nbIterations 1 --percentageConsanguinite 2 --percentageCroisement 3 --percentageMutation 4 --nbMaxMutations 5 --nbIndividus 6 --tailleLigne 7 --sort 8
