#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

const int LED_ROUGE = 2, LED_VERTE = 3, LED_JAUNE = 4;
const int BUZZER = 5, SERVO_PIN = 9, BOUTON = 7;

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo;

void afficher(String l1, String l2 = "") {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print(l1);
  lcd.setCursor(0, 1); lcd.print(l2);
}

void setLed(int pin, bool etat, String nom) {
  digitalWrite(pin, etat ? HIGH : LOW);
  afficher(nom, etat ? "ALLUMEE" : "ETEINTE");
  Serial.println(nom + (etat ? " allumee" : " eteinte"));
}

void setBuzzer(bool on) {
  if (on) tone(BUZZER, 1000); else noTone(BUZZER);
  afficher("Buzzer", on ? "SONNE" : "ARRETE");
  Serial.println(on ? "Buzzer actif" : "Buzzer arrete");
}

void setServo(int angle) {
  servo.write(angle);
  afficher("Servo", "Angle: " + String(angle));
  Serial.println("Servo a " + String(angle) + " degres");
}

void toutEteindre() {
  digitalWrite(LED_ROUGE, LOW);
  digitalWrite(LED_VERTE, LOW);
  digitalWrite(LED_JAUNE, LOW);
  noTone(BUZZER);
  afficher("Bouton appuye", "Tout eteint");
  Serial.println("Bouton : LED eteintes et buzzer arrete");
}

void traiter(String cmd) {
  cmd.trim();
  cmd.toUpperCase();
  if (cmd == "ROUGE ON") setLed(LED_ROUGE, true, "LED rouge");
  else if (cmd == "ROUGE OFF") setLed(LED_ROUGE, false, "LED rouge");
  else if (cmd == "VERTE ON") setLed(LED_VERTE, true, "LED verte");
  else if (cmd == "VERTE OFF") setLed(LED_VERTE, false, "LED verte");
  else if (cmd == "JAUNE ON") setLed(LED_JAUNE, true, "LED jaune");
  else if (cmd == "JAUNE OFF") setLed(LED_JAUNE, false, "LED jaune");
  else if (cmd == "SERVO 0") setServo(0);
  else if (cmd == "SERVO 90") setServo(90);
  else if (cmd == "SERVO 180") setServo(180);
  else if (cmd == "BUZZER ON") setBuzzer(true);
  else if (cmd == "BUZZER OFF") setBuzzer(false);
  else if (cmd.length() > 0) {
    afficher("Commande", "inconnue");
    Serial.println("Commande inconnue : " + cmd);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_ROUGE, OUTPUT);
  pinMode(LED_VERTE, OUTPUT);
  pinMode(LED_JAUNE, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BOUTON, INPUT_PULLUP);
  servo.attach(SERVO_PIN);
  servo.write(90);
  lcd.init();
  lcd.backlight();
  afficher("Assistant pret", "Tapez une commande");
  Serial.println("Commandes : ROUGE/VERTE/JAUNE ON|OFF, SERVO 0|90|180, BUZZER ON|OFF");
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    traiter(cmd);
  }
  if (digitalRead(BOUTON) == LOW) {
    toutEteindre();
    delay(300); // anti-rebond
  }
}
