/***
 * Project with Microview and Ultrasonic Distance Meter HC-SR-04, simulating Theremin
 * @author: Pavel Suk
 * Project Info & HW: https://samepage.io/app/#!/8740458cffb7c86971911d5f12e1e2291de7f7b7/page-143255827397014585-microview-theremin
 * Source code published on 
 * Codebender: https://codebender.cc/sketch:52064
 * Github: https://github.com/pavelsuk/MicroViewTheremin
*/


#include <MicroView.h>


// Set your own pins with these defines !
#define TRIG_PIN   5    // Arduino pin for the Trigger
#define ECHO_PIN   3    // Arduino pin for the Echo
#define SPEAKER_PIN   2    // Arduino pin for buzzer

const int dist_min = 4;
const int dist_max = 60;  // 34 
const int pitch_min = 50; // 131
const int pitch_max = 500; // 247

void setup()
{
	// MicroView setup:

    uView.begin();
    uView.clear(PAGE);      // clear the page buffer
    
	pinMode(TRIG_PIN, OUTPUT);
	pinMode(SPEAKER_PIN, OUTPUT);
	pinMode(ECHO_PIN, INPUT);
	
}

void loop()
{
	float dist;
	uView.clear(PAGE);      // clear the page buffer

	uView.setCursor(8,18);
 	
	dist = getDist();
    uView.print(dist);
 	playNote(dist);
    uView.display();        // display current page buffer

  	delay( 200);
}

float getDist() 
{
	unsigned long duration; 
	
	digitalWrite(TRIG_PIN, LOW);
  	delayMicroseconds(2);
  	digitalWrite(TRIG_PIN, HIGH);
  	delayMicroseconds(10);
  	digitalWrite(TRIG_PIN, LOW);
  	duration = pulseIn(ECHO_PIN, HIGH);
  	return microsecondsToCentimeters(duration);
}

int microsecondsToCentimeters(unsigned long microseconds){
  return ((microseconds*0.034029)/2);
}

void playNote(float dist) {
	if ((dist<=dist_min) or (dist>=dist_max)) {
		noTone(SPEAKER_PIN);
	} else {
		// float pitch = (dist-dist_min)*(pitch_max-pitch_min)/(dist_max-dist_min) + pitch_min;
		int pitch = map(dist, dist_min, dist_max, pitch_min, pitch_max);
		tone(SPEAKER_PIN, pitch);	
		uView.setCursor(8,28);
		uView.print(pitch);
	}
	
}
