# 2020-2021 : Capteur Graphite GAICH-STEPHEN 
2020-2021 : Projet réalisé dans le cadre de l'Unité de Formation "du capteur au banc de test" en 4ème année Génie Physique, à l'INSA de Toulouse. Au cours de ce projet, nous avons réalisé un capteur de déformation/ jauge de contrainte à base de graphite 2H. Afin de mesurer la résistance de ce type de crayon, nous avons crée un dispositif bas-coût et transportable qui fut proposé par nos enseignants. Nous avons réalisé et fabriqué un PCB shield, à l'aide du logiciel Kicad, contenant un amplificateur transimpédance (circuit analogique) , un module Bluetooth, un écran OLED et un encodeur rotatoire. Ce dernier est pluggé sur un microcontrôleur Arduino Uno programmé à l'aide du logiciel Arduino IDE et contrôlé par une application android APK bluetooth. 

*** 
  - [Livrables](#livrables)
  - [PCB Shield](#pcb-shield)
  - [Code Arduino Mesure](#code-arduino-mesure)
  - [Application android APK](#application-android-apk)
  - [Banc de test](#banc-de-test)
  - [Datasheet capteur graphite](#datasheet-capteur-graphite)
  - [Problèmes rencontrés et améliorations à réaliser](#problèmes-rencontrés-et-améliorations-à-réaliser) 

*** 
## Livrables  

- [x] PCB shield 
- [x] Code Arduino permettant la mesure de R et le contrôle des fonctionnalités BT, OLED... 
- [x] Application android APK réalisé avec MIT APP INVENTOR.
- [x] Protocole et le programme Arduino pour le banc de test
- [x] Datasheet du capteur de déformation/ jauge de contrainte à base de graphite 2H 


## PCB Shield
Utilisation des outils présents dans le logiciel Kicad pour créer le PCB: 
[KiCad EDA - Schematic Capture & PCB Design Software](https://kicad-pcb.org/), version: 5.1.8 

Le PCB Shield est pluggé sur un microcontrôleur Arduino Uno. Un amplificateur transimpédance, un module BT, un écran OLED et un encodeur rotatoire sont présents. 

Librairies de composants:
* Capacitor THT
* Resistor THT 
* Arduino Uno

#### Composants créés : symboles & empreintes 

- *Capteur Graphique*

![CG](Images/Capteur_Graphite.PNG)

- *Module Bluetooth*

![BT](Images/BT.PNG)

- *Encodeur rotatoire Keyes KY 040*

![Encodeur](Images/Encodeur_Rotatoire.PNG)

- *Ecran OLED*

![Ecran](Images/Ecran_OLED.PNG)

- *Amplificateur LT1050* (Empreinte déjà présente : DIP-8_W7.62mm_LongPads)

![LT1050](Images/LT1050.PNG)


#### Schématique 

Dans le Eeschema, crée à partir d'un modèle Arduino Uno, nous avons regroupé les éléments suivant trois groupes : l'amplificateur transimpédance (circuit analogique qui permet de traiter les données envoyées par le capteur (variation de résistance)), les modules permettant d'ajouter des fonctionnalités au micro-contrôleur (module Bluetooth, encodeur rotatoire, écran OLED) et les broches de la carte Arduino Uno.  

![Schematique](Images/Schématique_all.PNG)

#### Placement des composants 

![Placement](Images/Routage_1.PNG)

#### Routage 3D

![Routage](Images/Routage_3D_1.PNG) 

![Routage](Images/Routage_3D_modules.PNG)

#### Soudage du PCB

Grâce à Catherine Crouzet, travaillant au Génie Physique, INSA Toulouse, nous avons pu réaliser notre PCB. Après avoir réalisé le schéma électrique, le placement des composants et le routage de la carte PCB sur le logiciel KiCad, le typon du PCB est imprimé sur deux feuilles calques. Les deux transparents sont alors superposés et scotchés entre eux afin de diminuer le risque de microcoupure (encre trop pale). Le typon est disposé sur la glace de l’insoleuse ainsi que la plaque d’époxy dont la face cuivrée (60µm) photosensible est du côté du typon. Cette opération dure environ deux minutes et permet d’insoler la face photosensible. Le dessin du typon est alors visible sur la face cuivrée. La plaque est ensuite plongée dans un révélateur jusqu’à ce que le dessin apparaisse parfaitement (retire la résine non insolée). Après l’avoir rincé à l’eau, la plaque est alors prête pour la gravure. Le PCB est alors place dans un bain de perchlorure de fer rongeant tout le cuivre non protégé par la résine pendant sept minutes. Après l’avoir rincé à l’eau et vérifié le circuit, la résine est retirée avec de l’acétone. Le PCB sera ensuite percé et les composants seront soudés. 

![Calque](Images/Calque.jpeg)

Passons ensuite au perçage des trous de la plaquette à l'aide d'une perçeuse électrique (voir dossier image)
- 0.8mm pour ceux de l'AOP, les résistances et les capacités.
- 1mm pour ceux des connecteurs de l'Arduino et des headers des différents modules (pinces pour la feuille de graphite, bluetooth, encodeur rotatoire, écran OLED)

![Perçage](Images/PCB_Perçé.png)

Pour finir, nous avons soudé chaque composant à l'aide d'un fer à souder. 

Remarque: il aurait fallu faire le diamètre des pads des connecteurs arduino plus gros afin d'avoir des soudures parfaites => peu de cuivre qui est resté autour après le perçage, ce qui a compliqué la soudure. 

![Soudure](Images/PCB_soudé.png)


## Code Arduino Mesure 
Utilisation de l'environnement Arduino IDE téléchargeable [ici](https://www.arduino.cc/en/software); version 1.8.13.
Les librairies que nous avons utilisées sont disponibles [ici](PGM_Arduino_Mesure/Librairie).
Nous avons développé un programme permettant de mesurer la résistance de notre capteur. Vous pouvez le retrouver [ici](PGM_Arduino_Mesure/Programme_Capteur_Mesure/Programme_Capteur_Mesure.ino). 

BLABLA Calvin 

## Application android APK
Utilisation du site MIT App Inventor : [ici](https://appinventor.mit.edu/). 
Nous récupérons les données envoyées par le module bluetooth HC05 sur l'application et créons un fichier pour stocker ces dernières. 
Après de nombreux problèmes avec cet environnement et en s'inspirant du code crée par M.Grisolia, nous avons pu développer cette application. 

Face avant 

![APKFaceAvant](https://github.com/MOSH-Insa-Toulouse/2020-2021_GAICH_STEPHEN_Capteur_Graphite/blob/60f94ac44989122d760d00fc086380a5088cdf57/APK%20Bluetooth/Face_avant_application.jpg)



## Banc de test 
Nous avons réalisé deux bancs de test "low-tech". Nous avons détaillé sa construction dans la datasheet afin que toute personne possédant notre capteur puisse retrouver les résultats que nous avons obtenus [ici](METTRE LIEN) à la page 7-8. De plus, étant réalisé à base de déchets ménagers, aucun matériel de haute pointe n'est nécessaire. 
Nous vous présentons donc nos deux bancs de test : 

![Banc_test_dechets](github.com/MOSH-Insa-Toulouse/2020-2021_GAICH_STEPHEN_Capteur_Graphite/blob/1bbbf6c18c017310fe74cf414251e39823f5b98b/Banc%20de%20test&r%C3%A9sultats/Banc_test_dechets_divers.jpg)
Figure : Banc de test « low-tech » n°1_ récupération de déchets divers


![Banc_test_carton](github.com/MOSH-Insa-Toulouse/2020-2021_GAICH_STEPHEN_Capteur_Graphite/blob/a87d0e02e8e8ca06ef43198a11463cf3f4247200/Banc%20de%20test&r%C3%A9sultats/Banc_test_cartons_2.jpg)
Figure : Banc de test « low-tech » n°2 _ carton



Au début, afin de diminuer les faux contacts entre les deux pinces crocodiles, nous avions utilisé un rouleau de papier toilette que nous avions troué (voir la photo ci-dessous).
Nous n'avons pas gardé cette méthode pour les mesures en tension et compression car les cercles créés sur le banc n'était pas à la même hauteur (amélioration possible).
![Astucepince](github.com/MOSH-Insa-Toulouse/2020-2021_GAICH_STEPHEN_Capteur_Graphite/blob/f2989648eed4300f170cb525334238355c40d5ae/Images/Astuce%20pinces%20crocodiles.jpg)




#### Code Arduino 
Nous avons utilisé ce programme arduino afin de déterminer les valeurs obtenues sur notre banc de test : [ici](......)


#### Protocole de test du capteur & résultats obtenus 
Nous avons réalisé différentes expériences afin de déterminer les caractéristiques de notre capteur. 

Dans un premier temps, nous avons souhaité étudier l'influence des dimensions du capteur sur la résistance initiale. De ce fait, nous avons réalisé un plan d'expérience avec un modèle linéaire sans interactions de type TRI. Veuillez consulter ce document pour plus de détails : [ici](https://github.com/MOSH-Insa-Toulouse/2020-2021_GAICH_STEPHEN_Capteur_Graphite/blob/bd30b66165ddde75881d0ac7740d650ffe0249c1/Banc de test/Plan d'exp%C3%A9rience_meilleures_dimensions.xlsx)

Nous avons pu identifier la réalité expérimentale (variables aléatoires de mesure) et tenter d’expliquer puis de maitriser au mieux les paramètres ayant un impact sur la résistance de notre capteur. Nous n’assurons pas que tous les paramètres influents furent identifiés. Elles ont aussi permis de vérifier que la résistance de notre capteur suivait la loi de Pouillet et donc la loi d’Ohm. Etant donné que nous ne sommes pas capables de déterminer le nombre de feuillets de graphite déposé lors du coloriage de notre capteur, nous allons étudier la variation relative en résistance ∆R/R_o =  (R_mes-R_o)/R_o  afin d’homogénéiser nos mesures et pouvoir les comparer.  



Dans un deuxième temps, nous nous avons essayé de determiner la zone de non-destruction du capteur. Après chaque mesure sur un rayon de courbure, nous avons noté la valeur de la tension du capteur au repos (non déformé) puis avons déterminé la résistance de ce dernier. Nous l’avons ensuite comparé à celle mesurée au début de la série de mesure. 
Document excel  [ici](https://github.com/MOSH-Insa-Toulouse/2020-2021_GAICH_STEPHEN_Capteur_Graphite/blob/7707906fa2d3f6bd2b70b1e03c5d6f7bcc5a4388/Banc de test&r%C3%A9sultats/Determination_zone_non_destruction_capteur.xlsx)


GRAPHES 






Voici notre conclusion : 









## Datasheet capteur graphite
Vous pouvez retrouver la datasheet complète de notre capteur [ici](METTRE LIEN)


## Problèmes rencontrés et améliorations à réaliser

#### Problèmes sur le PCB

- Pads pour les connecteurs arduino trop fins.
- Mauvais placement de l'empreinte OLED : En testant l'écran OLED avec un programme fourni dans les libraires arduino, nous nous sommes rendus compte que, par inattention, nous avions mal placé l'empreinte (rotation 180°) car nous souhaitions que l'écran OLED soit positionné vers l'extérieur (cf PCB 3D). Afin d'avoir les bonnes pins, ce dernier doit être placé à l'intérieur. Or il y a l'encodeur rotatoire. Pour palier à ce problème, nous allons utiliser la platine d'expérimentation. 

  Améliorations : Nouveau PCB. 

  ![PCB_rectifié](Images/Routage_rectification_OLED.PNG)
  
#### Améliorations sur la caractérisation du capteur 
Veuillez vous référer à notre datasheet présente [ici](mettre lien) section Suggestions/Remarques. 

Nous avons détaillé différentes expérimentations que nous aurions aimées mener. Par manque de temps, nous n'avons pu les mener. 
De plus, afin de determiner concrètement les dimentions optimales du capteur, le plan d'expérience que nous avons mené devrait être complété par une étude plus approfondie (modèle de 2nd ordre) pour determiner l'optimum. Cependant, il faut pouvoir maitriser des paramètres qui ne sont pas contrôlables pour le moment (nombre de feuillets de graphite sur le capteur). 


## Note des auteurs 
Nous tenons à remercier Mme Crouzet, M.Grisolia et M.Biganzoli pour leur aide tout au long de ce projet ainsi que M.Constancias pour l'aide lors de l'analyse des résultats obtenus sur notre DOE. 

Pour nous contacter : 
- Eléonore Gaich : gaich@etud.insa-toulouse.fr
- Calvin Stephen : stephen@etud.insa-toulouse.fr
