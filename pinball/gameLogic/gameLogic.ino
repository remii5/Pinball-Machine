#include <Arduino.h>
#include <LiquidCrystal.h>

// LCD Setup
LiquidCrystal lcd(12, 10, 11, 5, 4, 3, 2);

// Pins
const int startButtonPin = 16;      // New start button
const int scoreUpSwitch = 6;        // +50 pts
const int scoreDownSwitch = 7;      // -50 pts

const int sensorPins[4] = {8, 9, 13, 14};  // R-A-C-E sensors

// Game State
int score = 0;
String targetWord = "RACE";
String currentProgress = "";
bool gameRunning = false;

void resetGame() {
  gameRunning = false;
  score = 0;
  currentProgress = "";
  lcd.clear();
  lcd.print("Score: 0");
  Serial.println("Game Reset!");
}

void flashLCD(String text, int times = 3, int delayTime = 300) {
  for (int i = 0; i < times; i++) {
    lcd.clear();
    lcd.print(text);
    delay(delayTime);
    lcd.clear();
    delay(delayTime);
  }
}

void updateDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Score: " + String(score));
  lcd.setCursor(0, 1);
  lcd.print("Progress: " + currentProgress);
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Ready to Start");

  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(scoreUpSwitch, INPUT_PULLUP);
  pinMode(scoreDownSwitch, INPUT_PULLUP);
  for (int i = 0; i < 4; i++) {
    pinMode(sensorPins[i], INPUT_PULLUP);
  }

  resetGame();
}

void loop() {
  // Wait for Start
  if (!gameRunning && digitalRead(startButtonPin) == LOW) {
    gameRunning = true;
    currentProgress = "";
    score = 0;
    updateDisplay();
    Serial.println("Game Started!");
    delay(300); // Debounce
  }

  if (!gameRunning) return;


  // Score control
  if (digitalRead(scoreUpSwitch) == LOW) {
    score += 50;
    updateDisplay();
    delay(300);
  }
  if (digitalRead(scoreDownSwitch) == LOW) {
    score -= 50;
    updateDisplay();
    delay(300);
  }

  for (int i = 0; i < 4; i++) {
    if (digitalRead(sensorPins[i]) == LOW) {
      char expected = targetWord.charAt(currentProgress.length());
      char hit = targetWord.charAt(i);

      if (hit == expected) {
        currentProgress += hit;
        Serial.print("Progress: ");
        Serial.println(currentProgress);
        updateDisplay();
        delay(300);
      } else {
        Serial.println("Wrong order! Resetting progress.");
        currentProgress = "";
        updateDisplay();
        delay(300);
      }

      // Jackpot check
      if (currentProgress == targetWord) {
        score += 500;
        flashLCD("VROOM!", 4);
        currentProgress = "";
        updateDisplay();
        delay(300);
      }
    }
  }
}
