/*
  Measure.h - Library for measure distance, status of buttery and status of water sensor.
  Created by bspavel, March 18, 2018.
  Released into the public domain.
*/
#ifndef Measure_h
#define Measure_h
 
#include "WProgram.h"
 
class Measure
{
	public:
		Measure(
			int debug,
			int trigPin, int echoPin,
			byte butteryPin,
			byte waterPin
		);
		byte distance();
	public:
		int buttery();
	public:
		int water();
	private:
		int _debug;
		int _trigPin;
		int _echoPin;
		byte _butteryPin;
		byte _waterPin;
};
 
#endif
