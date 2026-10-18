# Voltmètre numérique avec écran LCD

## Objectif
Concevoir, simuler et analyser un voltmètre numérique construit autour
d'une carte Arduino Uno, en deux étapes sur Wokwi :
- Simulation 1 : un voltmètre de base qui affiche la tension sur un LCD.
- Simulation 2 : une version améliorée avec trois LED, un buzzer d'alerte
  et un bouton HOLD qui fige la mesure.

Dans les deux cas, un potentiomètre représente la tension inconnue
(0 à 5 V).

## Composants et outils utilisés
- Simulateur : Wokwi
- Arduino Uno
- Potentiomètre
- Écran LCD 16x2 I2C (adresse 0x27)
- Simulation 2 : LED verte, jaune, rouge, 3 résistances de 220 Ω,
  buzzer, bouton poussoir
- Bibliothèques : Wire.h, LiquidCrystal_I2C.h

## Fonctionnement

### Principe de la mesure
Le convertisseur analogique-numérique de 10 bits de l'Arduino transforme
la tension en un nombre de 0 à 1023 avec `analogRead(A0)`.
La tension se calcule par : `V = valeur × 5,0 / 1023`.
Résolution : environ 4,89 mV. Plage de mesure : 0 à 5 V.

### Simulation 1 : voltmètre de base
| Composant | Broche | Relié à |
|---|---|---|
| Potentiomètre | VCC / SIG / GND | 5V / A0 / GND |
| LCD I2C | GND / VCC / SDA / SCL | GND / 5V / A4 / A5 |

Le programme est dans `voltmetre_simple.ino`. Toutes les 200 ms,
l'Arduino lit A0, convertit en volts et affiche la tension avec deux
décimales.


### Simulation 2 : version améliorée
| Composant | Branchement |
|---|---|
| LED verte | D2 → 220 Ω → LED → GND |
| LED jaune | D3 → 220 Ω → LED → GND |
| LED rouge | D4 → 220 Ω → LED → GND |
| Buzzer | + sur D5, − sur GND |
| Bouton HOLD | D6 et GND (INPUT_PULLUP) |

Le potentiomètre et le LCD sont câblés comme dans la simulation 1.
Le programme est dans `voltmetre_ameliore.ino`.

Logique des seuils :
| Tension | Niveau | LED | Buzzer |
|---|---|---|---|
| moins de 2 V | NORMAL | verte | éteint |
| de 2 V à moins de 4 V | MOYEN | jaune | éteint |
| 4 V et plus | DANGER | rouge | actif (1000 Hz) |

Le bouton HOLD fige la valeur affichée (affichage « HOLD » au lieu de
« LIVE ») ; un second appui reprend la mesure en direct. Un anti-rebond
de 50 ms évite les appuis multiples.

## Résultats obtenus
- Simulation 1 : la tension affichée suit la rotation du potentiomètre
  de 0,00 V à 5,00 V.
- Simulation 2 : la LED allumée, le message du LCD et le buzzer
  correspondent bien au niveau de tension, et le bouton HOLD fige la
  mesure même quand on tourne le potentiomètre.

## Limites
L'entrée analogique de l'Arduino Uno supporte au maximum 5 V. Pour
mesurer des tensions plus élevées, il faudrait un pont diviseur de
tension.

## Liens Wokwi
- Simulation 1 : https://wokwi.com/projects/477448790742037505
- Simulation 2 : https://wokwi.com/projects/477453117099021313

## Rapport complet
Voir le fichier PDF : Francoise_NOEL_Devoir_Voltmetre_Numerique.pdf
