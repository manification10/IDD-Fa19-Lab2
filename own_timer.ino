/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/
#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
int lostMelody[] = {
    NOTE_G3, 0, NOTE_G3, NOTE_G3,  NOTE_A3, NOTE_C4,NOTE_C3, NOTE_C2
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};


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
void winTune() {
    for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}
void loserTune() {
    for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, lostMelody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

// the loop routine runs over and over again forever:
void loop() {
  if (gameState == 1 && delayRunning && ((millis() - delayStart) >= 5000)) {
    delayRunning = false; // // prevent this code being run more then once
    Serial.println("Game Over, you lost. :(");
    gameState = 0;
    loserTune();
  }
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    gameState = 1;
    Serial.println("Start Game, get to 100 in 5 seconds");
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
  if (gameState == 1 && sensorValue == 100) 
  {
    Serial.println(sensorValue);
    Serial.println("Yaay! You won in:");
    winTime = (millis() - delayStart)/1000; 
    Serial.println(winTime);
    Serial.println("seconds");
    gameState = 0;
    winTune();
  }
  else if (gameState == 1)
  {
  // print out the value you read:
  Serial.println(sensorValue);
  delay(100);        // delay in between reads for stability
  }
}
