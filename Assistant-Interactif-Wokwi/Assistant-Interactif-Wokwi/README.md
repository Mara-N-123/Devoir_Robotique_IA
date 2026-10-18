# Assistant interactif sur Wokwi

## Objectif
Réaliser, sur le simulateur Wokwi, un assistant interactif qui exécute
des commandes tapées dans le moniteur série. La carte Arduino analyse la
commande, active le composant concerné et affiche une confirmation sur un
écran LCD. C'est la première étape d'un projet plus large : la
reconnaissance vocale et l'IA seront ajoutées plus tard.

## Composants et outils utilisés
- Simulateur : Wokwi
- Arduino Mega
- Écran LCD 1602 I2C
- 3 LED (rouge, verte, jaune) avec 3 résistances de 220 Ω
- 1 servomoteur
- 1 buzzer
- 1 bouton poussoir
- Bibliothèques : Wire.h, LiquidCrystal_I2C.h, Servo.h

## Fonctionnement

### Principe
1. Réception : l'utilisateur tape une commande dans le moniteur série.
2. Lecture : la carte lit le texte jusqu'au retour à la ligne.
3. Analyse : le programme compare le texte aux commandes connues
   (insensible à la casse).
4. Action et confirmation : le composant est activé, puis un message
   s'affiche sur le LCD et dans le moniteur série.

Le bouton est surveillé en permanence : un appui éteint les trois LED et
arrête le buzzer.

### Commandes
| Commande | Effet |
|---|---|
| ROUGE ON / OFF | Allume / éteint la LED rouge |
| VERTE ON / OFF | Allume / éteint la LED verte |
| JAUNE ON / OFF | Allume / éteint la LED jaune |
| SERVO 0 / 90 / 180 | Positionne le servomoteur à l'angle demandé |
| BUZZER ON / OFF | Fait sonner / arrête le buzzer |
| Bouton physique | Éteint les LED et arrête le buzzer |

Toute autre commande affiche « Commande inconnue ».

### Câblage
| Composant | Broche du composant | Relié à |
|---|---|---|
| LED rouge | Anode (via 220 Ω) / Cathode | D2 / GND |
| LED verte | Anode (via 220 Ω) / Cathode | D3 / GND |
| LED jaune | Anode (via 220 Ω) / Cathode | D4 / GND |
| Buzzer | + / − | D5 / GND |
| Servomoteur | PWM / V+ / GND | D9 / 5V / GND |
| Bouton | gauche / droite | D7 / GND |
| LCD I2C | SDA / SCL / VCC / GND | 20 / 21 / 5V / GND |

Le bouton utilise la résistance interne (INPUT_PULLUP). Le moniteur série
fonctionne à 9600 bauds. L'adresse du LCD est 0x27 (essayer 0x3F si
l'écran reste vide).

### Code
Le programme est dans le fichier `assistant_interactif.ino`.

## Résultats obtenus
- Au démarrage, le LCD affiche « Assistant pret / Tapez une commande » et
  le moniteur série affiche la liste des commandes.
- La commande `VERTE ON` allume la LED verte ; le LCD affiche
  « LED verte / ALLUMEE » et le moniteur série confirme.


## Lien du projet Wokwi
https://wokwi.com/projects/477447164871324673

## Rapport complet
Voir le fichier PDF :
Francoise_NOEL_Devoir_Assistant_Interactif_Robotique_IA.pdf
