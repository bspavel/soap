/*
  Measure.cpp - Library for measure distance, status of buttery and status of water sensor.
  Created by bspavel, March 18, 2018.
  Released into the public domain.
*/

#include "WProgram.h"
#include "Measure.h"

Measure::Measure(
	int debug,
	int trigPin, int echoPin,
	byte butteryPin,
	byte waterPin
)
{
	_debug = debug;
	
	pinMode(trigPin, OUTPUT);
	digitalWrite(trigPin, 0);
	pinMode(echoPin, INPUT);
	_trigPin = trigPin;
	_echoPin = echoPin;

	pinMode(butteryPin, INPUT);
	_butteryPin=butteryPin;

	pinMode(waterPin, INPUT);
	_waterPin=waterPin;
}


	byte distance()
	{
		digitalWrite(_trigPin, 0);
		delayMicroseconds(5);
		digitalWrite(_trigPin, 1);
		delayMicroseconds(15);
		digitalWrite(_trigPin, 0);
		duration = pulseIn(_echoPin, HIGH);
		return (duration / 2) / 29.1;
	}

	int buttery()
	{
		int voltage = analogRead(_butteryPin);
		float vout = (voltage * 5.0) / 1024.0;
		int status;
		
		if( (procent >= 3.3) && (procent <= 5) ) {
			status = 3; // full
		}else if( (procent > 2.3) && (procent < 3.2) )   {
			status = 2; // 2/3
		}else {
			status = 1; // >= 1/3
		}
		
		return status;
	}

	int water()
	{
	//	http://www.learningaboutelectronics.com/Articles/Arduino-liquid-level-indicator-circuit.php
		int waterLevel=analogRead(_waterPin);
		int status;
		
		if(_debug)Serial.print("water level: ");
		if(_debug)Serial.println(waterLevel);
		
		if ( (waterLevel >= 200) && (waterLevel <= 256) )
		{
			status=3 // full
		}else if ( (waterLevel >= 50) && (waterLevel <= 150) ){
			status=2 // 2/3
		}else {
			status=1 // >= 1/3
		}
		
		return status;
	}