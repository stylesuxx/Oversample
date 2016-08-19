#include "Arduino.h"
#include "oversample.h"

Oversample::Oversample(int pin, int resolution)
{
  _pin = pin;

  pinMode(_pin, INPUT);
  setPrescaler(4);
  setResolution(resolution);
}

float Oversample::read()
{
   //...
   return 0;
}

void Oversample::setResolution(int resolution)
{
  _resolution = resolution;
  if(_resolution > 16) {
   _resolution = 16;
  }

  if(_resolution < 10) {
   _resolution = 10;
  }

  int additionalBits = _resolution - 10;

  _samplesCount = 1;
  if(additionalBits > 0) {
   _samplesCount += pow(4, additionalBits);
  }

  delete [] _samples;
  _samples = new int[_samplesCount];
}

int Oversample::getResolution()
{
  return _resolution;
}

void Oversample::setPrescaler(int prescaler)
{
  int mask = B11111000;
  ADCSRA &= mask;
  ADCSRA |= prescaler;
}

int Oversample::getPrescaler()
{
  return _prescaler;
}
