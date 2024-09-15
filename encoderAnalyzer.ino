#include "Keyboard.h"

// Rotary Encoder Inputs
#define CLK 2
#define DT 3
#define SW 4

int counter = 0;

int inhale = 0;
int exhale = 0;
int prevIn = 0;
int prevEx = 0;
int prevBreathLength = 0;
int curBreathLength = 0;

int currentStateCLK;
int lastStateCLK;
String currentDir ="";
unsigned long lastButtonPress = 0;

void setup() {
        
	// Set encoder pins as inputs
	pinMode(CLK,INPUT);
	pinMode(DT,INPUT);
	pinMode(SW, INPUT_PULLUP);

	// Setup Serial Monitor
	Serial.begin(9600);

	// Read the initial state of CLK
	lastStateCLK = digitalRead(CLK);
}

void loop() {
        
	// Read the current state of CLK
	currentStateCLK = digitalRead(CLK);

	// If last and current state of CLK are different, then pulse occurred
	// React to only 1 state change to avoid double count
	if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){

		// If the DT state is different than the CLK state then
		// the encoder is rotating CCW so decrement
		if (digitalRead(DT) != currentStateCLK) {
      inhale = 1;
      exhale = 0;

      curBreathLength++;
			counter ++;
			currentDir ="CCW";
      // Keyboard.press(48 + 1);
      // delay(50);
      // Keyboard.release(48 + 1);
		} else {
			// Encoder is rotating CW so increment
      inhale = 0;
      exhale = 1;

      curBreathLength++;
			counter --;
			currentDir ="CW";
      // Keyboard.press(48 + 2);
      // delay(50);
      // Keyboard.release(48 + 2);
		}

    if (prevIn != inhale)
    {
      prevIn = inhale;
      prevBreathLength = curBreathLength;
      curBreathLength = 0;


    }
    


		// Serial.print("Direction: ");
		// Serial.print(currentDir);
		// Serial.print(" | Counter: ");

		Serial.print(counter);
    Serial.print(" ");

    Serial.print(abs(curBreathLength - prevBreathLength));
    Serial.print(" ");

    // toggle inhale
    Serial.print(inhale);
    Serial.print(" ");

    // toggle exhale
    Serial.print(exhale);
    Serial.print(" ");

    Serial.println();


	}

	// Remember last CLK state
	lastStateCLK = currentStateCLK;

	// Read the button 1111state
	int btnState = digitalRead(SW);

	//If we detect LOW signal, button is pressed
	if (btnState == LOW) {
		//if 50ms have passed since last LOW pulse, it means that the
		//button has been pressed, released and pressed again
		if (millis() - lastButtonPress > 50) {
			Serial.println("Button pressed!");
		}

		// Remember last button press event
		lastButtonPress = millis();
	}

	// Put in a slight delay to help debounce the reading
	delay(1);
}