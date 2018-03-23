#define debug 0 //  0-on, 1-off
#define minH 5
#define maxH 10
#define cap_time 3

#define voiceVCCpin 4
#define trigPin 2
#define echoPin 9

#define MOSFETpin 7

#define waterVCCpin 10
#define waterPin A2

#define LEDpin 6

#define butteryPin A5

#include "LowPower.h"
#include <Measure.h>

long duration;
byte distance;
unsigned long openTimer;
boolean flag;

Measure mlib(
	debug,
	trigPin, echoPin,
	butteryPin,
	waterPin
);
 
void setup(){
	Serial.begin(9600);
	if (debug) Serial.println("running...");
	
	pinMode(MOSFETpin, OUTPUT);
	digitalWrite(MOSFETpin, 0);
	
	pinMode(voiceVCCpin, OUTPUT);
	digitalWrite(VoiceVCCpin, 0);
	
	pinMode(waterVCCpin, OUTPUT);
	digitalWrite(waterVCCpin, 0);
	
	pinMode(LEDpin, OUTPUT);
	digitalWrite(LEDpin, 0);
}
 
void loop()
{
	LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
	if( Measure.buttery()<2 ){
		blink();
	}else if( Measure.water()<2 ){
		digitalWrite(LEDpin, 1);
	}else{
		openCloseWater();
	}
}

void blink()
{
	digitalWrite(LEDpin, HIGH);
	delay(1000);
	digitalWrite(LEDpin, LOW);
	delay(1000);
}

void openCloseWater(){
	digitalWrite(voiceVCCpin, 1);Measure.distance();//power of sensor turn on
	distance=Measure.distance();
	digitalWrite(voiceVCCpin, 0);
	
	if(debug)
	{
		Serial.print("Distance: ");
		Serial.println(distance);
		delay(500);
	}
	
	if( (distance > minH) && (distance < maxH) )
	{
		openTimer=0;
		if(!flag) openWater();
	}else{
		if(flag)
		{
		  ++openTimer;
		  if(openTimer > cap_time) closeWater();
		}
	}
	
}

void openWater() {
  if (debug) Serial.println("open water");
  digitalWrite(MOSFETpin, 1);
  delay(500);
  flag=1;
}

void closeWater() {
  if (debug) Serial.println("close water");
  digitalWrite(MOSFETpin, 0);
  flag=0;
}