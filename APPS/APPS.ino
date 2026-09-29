unsigned long poprzedniCzas = 0;
unsigned long poczatekBledu = 0;
bool pomiar = false;
int licznik = 0;

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
}

void loop() {
  if (millis() - poprzedniCzas >= 10) {
    poprzedniCzas = millis();
    //poprzedniCzas odczytuje wartość millis co kolejne 10ms

    int sensorValue = analogRead(A0);
    float gazProcent = (sensorValue / 1023.0) * 100.0;

    int sensorHelp = analogRead(A1);
    float gazPomoc = (sensorHelp / 1023.0) * 100.0;
    //Odczyty potencjometrów na procenty

    licznik++;

    if (licznik >= 25) {
      Serial.print("Gaz: ");
      Serial.print(gazProcent);
      Serial.println("%");
      Serial.print("Pomoc: ");
      Serial.print(gazPomoc);
      Serial.println("%");
      Serial.println();

      licznik = 0;
      //Funkcja licznika odpowaida za telegrafie z częstotliwością 4 Hz
    }

    float roznica = abs(gazProcent - gazPomoc);

    if (roznica > 10.0) {
      if (!pomiar) {
        poczatekBledu = millis();
        pomiar = true;
      }

      if (millis() - poczatekBledu >= 100) {
        digitalWrite(2, LOW);
        digitalWrite(3, HIGH);
      }

    }

    else {
        pomiar = false;
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
      }

  }

}
