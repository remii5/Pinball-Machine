// Pin assignments
const int pinR = 1;
const int pinA = 2;
const int pinC = 3;
const int pinE = 4;
const int pinPlus50 = 5;
const int pinMinus50 = 6;

int points = 0;
int raceProgress = 0; // 0:R, 1:A, 2:C, 3:E (jackpot)

// Sequence letters in order
const int racePins[4] = { pinR, pinA, pinC, pinE };
const char* raceLetters[4] = { "R", "A", "C", "E" };

void setup() {
  Serial.begin(9600);

  // Set pin modes
  for (int i = 1; i <= 6; i++) {
    pinMode(i, INPUT);
  }

  Serial.println("Pinball Machine Initialized.");
  Serial.println("Current Progress: <none>");
}
void loop() {
  /*
  // Check each letter in the RACE sequence
  for (int i = 0; i < 4; i++) {
    if (digitalRead(racePins[i]) == HIGH) {
      if (i == raceProgress) {
        Serial.print("Hit: ");
        Serial.println(raceLetters[i]);
        raceProgress++;

        // Show current progress
        Serial.print("Current Progress: ");
        for (int j = 0; j < raceProgress; j++) {
          Serial.print(raceLetters[j]);
          Serial.print(" ");
        }
        Serial.println();

        if (raceProgress == 4) {
          Serial.println("JACKPOT! +1000 points!");
          points += 1000;
          raceProgress = 0;
          Serial.println("Current Progress: <none>");
        }
      } else {
        Serial.print("Out of order hit: ");
        Serial.println(raceLetters[i]);
        raceProgress = 0;
        Serial.println("Progress reset. Start over.");
        Serial.println("Current Progress: <none>");
      }
      delay(300); // Debounce
    }
  }*/
  
  // Check +50 point bumper
  if (digitalRead(pinPlus50) == HIGH) {
    points += 50;
    Serial.println("+50 Points!");
    delay(300); // Debounce
  }
  /*
  // Check -50 point bumper
  if (digitalRead(pinMinus50) == HIGH) {
    points -= 50;
    Serial.println("-50 Points!");
    delay(300); // Debounce
  }
  */
  Serial.print("Total Points: ");
  Serial.println(points);
}
