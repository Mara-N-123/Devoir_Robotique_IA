#include <Servo.h>

Servo base, epaule, coude;
int posBase = 90, posEpaule = 90, posCoude = 90;

// Déplace les 3 servos pas à pas vers les angles demandés
void deplacer(int cibleBase, int cibleEpaule, int cibleCoude) {
  while (posBase != cibleBase || posEpaule != cibleEpaule || posCoude != cibleCoude) {
    if (posBase < cibleBase) posBase++;
    else if (posBase > cibleBase) posBase--;

    if (posEpaule < cibleEpaule) posEpaule++;
    else if (posEpaule > cibleEpaule) posEpaule--;

    if (posCoude < cibleCoude) posCoude++;
    else if (posCoude > cibleCoude) posCoude--;

    base.write(posBase);
    epaule.write(posEpaule);
    coude.write(posCoude);
    delay(15);
  }
}

void setup() {
  base.attach(9);
  epaule.attach(10);
  coude.attach(11);
  base.write(posBase);
  epaule.write(posEpaule);
  coude.write(posCoude);
  delay(1000);
}

void loop() {
  deplacer(0, 90, 45);    // Position 1
  delay(1000);
  deplacer(90, 45, 120);  // Position 2
  delay(1000);
  deplacer(180, 90, 90);  // Position 3
  delay(1000);
  deplacer(90, 90, 90);   // Retour à la position de départ
  delay(1500);
}
