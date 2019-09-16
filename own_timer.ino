/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/
const int buttonPin = 2; 
const int ledPin =  13;    
int buttonState = 0; 
int gameState = 0; 
unsigned long delayStart = 0; // the time the delay started
bool delayRunning = false;
int winTime = 0;

// the setup routine runs once when you press reset:
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  delayStart = millis();   // start delay
  delayRunning = true; // not finished yet
}

// the loop routine runs over and over again forever:
void loop() {
  if (gameState == 1 && delayRunning && ((millis() - delayStart) >= 5000)) {
    delayRunning = false; // // prevent this code being run more then once
    Serial.println("Game Over");
    gameState = 0;
  }
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    gameState = 1;
    Serial.println("Start Game");
    delayStart = millis();
    delayRunning = true;
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }

  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  if (gameState == 1 && sensorValue < 101 && sensorValue > 99) 
  {
    Serial.println(sensorValue);
    Serial.println("Yaay! You won in:");
    winTime = (millis() - delayStart)/1000; 
    Serial.println(winTime);
    Serial.println("seconds");
    gameState = 0;
  }
  else if (gameState == 1)
  {
  // print out the value you read:
  Serial.println(sensorValue);
  delay(100);        // delay in between reads for stability
  }
}
