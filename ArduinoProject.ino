/*
    Max Bugay
    Computer Architecture

    Red light, Green Light
    Purpose: Uses Windows Phone Arduino Remote to translate voice commands "Red" or "Green" to Red or Green LED Lights, respectively, on Arduino Board via Bluetooth connection. 
*/

#include <ArduinoJson.h>

#include <VirtualShield.h>
#include <Text.h>
#include <Speech.h>
#include <Recognition.h>

VirtualShield shield;	          // identify the shield
Text screen = Text(shield);	  // connect the screen
Speech speech = Speech(shield);	  // connect text to speech
Recognition recognition = Recognition(shield);	  // connect speech to text

int RED_PIN = 8;
int GREEN_PIN = 9;

void recognitionEvent(ShieldEvent* event)
{
  if (event->resultId > 0) {
	digitalWrite(RED_PIN, recognition.recognizedIndex == 1 ? HIGH : LOW);
        screen.printAt(5, "Heard " + String(recognition.recognizedIndex == 1 ? "Stop" : "Go"));
  digitalWrite(GREEN_PIN, recognition.recognizedIndex == 1 ? LOW : HIGH);
        screen.printAt(5, "Heard " + String(recognition.recognizedIndex == 1 ? "Stop" : "Go"));
	recognition.listenFor("Stop,Go", false);	    // reset up the recognition after each event
  }
}

// when Bluetooth connects, or the 'Refresh' button is pressed
void refresh(ShieldEvent* event)
{
        String message = "Welcome to Redlight, Greenlight. Say 'Go' or 'Stop' to affect the LEDs.";

	screen.clear();
	screen.print(message);
        speech.speak(message);

	recognition.listenFor("Stop,Go", false);	// NON-blocking instruction to recognize speech
}

void setup()
{
	pinMode(RED_PIN, OUTPUT);
	pinMode(RED_PIN, LOW);

  pinMode(GREEN_PIN, OUTPUT);
  pinMode(GREEN_PIN, LOW);

	recognition.setOnEvent(recognitionEvent);	// set up a function to handle recognition events (turns auto-blocking off)
        shield.setOnRefresh(refresh);

        // begin() communication - you may specify a baud rate here, default is 115200
	shield.begin();
}

void loop()
{
	shield.checkSensors();		    // handles Virtual Shield events.
}
