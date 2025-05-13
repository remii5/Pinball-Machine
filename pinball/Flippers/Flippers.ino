const int leftButton = 8;
const int leftMosfet = 10;

const int rightButton = 9;
const int rightMosfet = 11;


void setup() {
  pinMode(leftButton, INPUT_PULLUP); 
  pinMode(leftMosfet, OUTPUT);  
  digitalWrite(leftMosfet, LOW);     
  Serial.begin(9600);
}

void loop() {
  int leftButtonState = digitalRead(leftButton);
  Serial.println(leftButtonState);
  if (leftButtonState == LOW) {
    digitalWrite(leftMosfet, HIGH); // Activate solenoid
    Serial.println("Button pressed - Solenoid ON");
  } else {
    digitalWrite(leftMosfet, LOW);  // Deactivate solenoid
    Serial.println("Button released - Solenoid OFF");
  }

  delay(100); // Small debounce delay
}

