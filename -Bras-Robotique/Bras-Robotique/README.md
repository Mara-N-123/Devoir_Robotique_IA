# Bras robotique à plusieurs degrés de liberté

## Objectif
Construire un petit bras robotique avec trois servomoteurs commandés par
une carte Arduino Uno, puis le programmer pour qu'il passe d'une position
précise à une autre.

## Composants et outils utilisés
- Plateforme : Tinkercad Circuits
- Carte Arduino Uno
- 3 servomoteurs (base, épaule, coude)
- Breadboard et fils de connexion
- Bibliothèque Arduino : Servo.h

## Fonctionnement

### Montage
Les trois servomoteurs sont alimentés par le 5 V de l'Arduino, distribué
grâce aux rails de la breadboard.

| Servomoteur | Signal | Alimentation | Terre |
|---|---|---|---|
| Servo 1 : base | Broche 9 | 5 V | GND |
| Servo 2 : épaule | Broche 10 | 5 V | GND |
| Servo 3 : coude | Broche 11 | 5 V | GND |


### Degrés de liberté
Le bras possède 3 degrés de liberté : chaque servomoteur commande un seul
axe de rotation.
- Base : fait tourner tout le bras horizontalement.
- Épaule : lève ou abaisse l'ensemble du bras.
- Coude : plie ou déplie l'avant-bras.

### Programme
Le code est dans le fichier `bras_robotique.ino`. La fonction `deplacer()`
avance les trois servos d'un degré à la fois avec une petite pause
(15 ms), ce qui rend le mouvement progressif. La boucle enchaîne quatre
positions :

| Position | Base | Épaule | Coude |
|---|---|---|---|
| Position 1 | 0° | 90° | 45° |
| Position 2 | 90° | 45° | 120° |
| Position 3 | 180° | 90° | 90° |
| Retour au départ | 90° | 90° | 90° |

## Résultats obtenus
Le bras effectue en simulation le cycle complet des quatre positions de
façon fluide et progressive.

## Ce que j'ai appris
- Un servomoteur se commande avec un angle de 0° à 180° via `write()`.
- Le nombre de degrés de liberté correspond au nombre d'axes motorisés.
- Avancer par petits pas donne un mouvement plus fluide qu'un saut direct.
- Plusieurs servos peuvent partager l'alimentation et la masse, mais
  chacun a besoin de sa propre broche de commande.

## Difficultés rencontrées
Brancher correctement les trois fils de chaque servo (signal,
alimentation, Terre).

## Lien du projet Tinkercad
https://www.tinkercad.com/things/8Vu6sjWdhYJ-brilliant-habbi

## Rapport complet
Voir le fichier PDF : NOEL_Francoise_Devoir_Bras_robotique_.pdf
