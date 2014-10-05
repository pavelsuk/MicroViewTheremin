/***
 * Project with Microview and Ultrasonic Distance Meter HC-SR-04, simulating Theremin
 * @author: Pavel Suk
 * Project Info & HW: https://samepage.io/app/#!/8740458cffb7c86971911d5f12e1e2291de7f7b7/page-143255827397014585-microview-theremin
 * Source code published on 
 * Codebender: https://codebender.cc/sketch:52186
 * Github: https://github.com/pavelsuk/MicroViewTheremin
 * Used libraries
 * 	NewPing https://code.google.com/p/arduino-new-ping/
 * 	NewTone https://code.google.com/p/arduino-new-tone/
*/

#include "NewPing.h"
#include "NewTone.h"
#include <MicroView.h>


// Set your own pins with these defines !
#define TRIG_PIN   5    // Arduino pin for the Trigger
#define ECHO_PIN   3    // Arduino pin for the Echo
#define SPEAKER_PIN   2    // Arduino pin for buzzer
#define MAX_DISTANCE 350 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.r

const int dist_min = 4;
const int dist_max = 60;  // 34 
const int pitch_min = 50; // 131
const int pitch_max = 500; // 247

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup()
{
	// MicroView setup:

    uView.begin();
    uView.clear(PAGE);      // clear the page buffer
    
}

void loop()
{
	unsigned int dist;
	uView.clear(PAGE);      // clear the page buffer

	uView.setCursor(8,18);
 	delay(50);
 	
	dist = getDist();
    uView.print(dist);
 	playNote(dist);
    uView.display();        // display current page buffer

  	delay( 200);
}

float getDist() 
{
	unsigned long duration = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  	return microsecondsToCentimeters(duration);
}

int microsecondsToCentimeters(unsigned long microseconds){
  return (microseconds/ US_ROUNDTRIP_CM);
}

void playNote(float dist) {
	if ((dist<=dist_min) or (dist>=dist_max)) {
		noNewTone(SPEAKER_PIN);
	} else {
		// float pitch = (dist-dist_min)*(pitch_max-pitch_min)/(dist_max-dist_min) + pitch_min;
		int pitch = map(dist, dist_min, dist_max, pitch_min, pitch_max);
		NewTone(SPEAKER_PIN, pitch);	
		uView.setCursor(8,28);
		uView.print(pitch);
	}
	
}


 