#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int LED_VERTE = 2, LED_JAUNE = 3, LED_ROUGE = 4;
const int BUZZER = 5, BOUTON = 6;

bool hold = false;
bool dernierEtat = HIGH;
float tension = 0;

void setup() {
  pinMode(LED_VERTE, OUTPUT);
  pinMode(LED_JAUNE, OUTPUT);
  pinMode(LED_ROUGE, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BOUTON, INPUT_PULLUP);   // bouton relie a GND
  lcd.init();
  lcd.backlight();
}

void loop() {
  // Gestion du bouton HOLD (appui = bascule figer / reprendre)
  bool etat = digitalRead(BOUTON);
  if (dernierEtat == HIGH && etat == LOW) {
    hold = !hold;
    delay(50);                     // anti-rebond
  }
  dernierEtat = etat;

  // Mesure uniquement si on n'est pas en HOLD
  if (!hold) {
    tension = analogRead(A0) * 5.0 / 1023.0;
  }

  // Affichage
  lcd.setCursor(0, 0);
  lcd.print(hold ? "HOLD " : "LIVE ");
  lcd.print(tension, 2);
  lcd.print(" V ");

  lcd.setCursor(0, 1);
  if (tension < 2.0)      lcd.print("Niveau : NORMAL ");
  else if (tension < 4.0) lcd.print("Niveau : MOYEN  ");
  else                    lcd.print("Niveau : DANGER ");

  // LED et buzzer selon la tension
  digitalWrite(LED_VERTE, tension < 2.0);
  digitalWrite(LED_JAUNE, tension >= 2.0 && tension < 4.0);
  digitalWrite(LED_ROUGE, tension >= 4.0);

  if (tension >= 4.0) tone(BUZZER, 1000);
  else noTone(BUZZER);

  delay(100);
}
