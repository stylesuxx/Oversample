#include "Oversample.h"

Oversample::Oversample(byte pin, byte resolution)
{
  _pin = pin;
  _resolution = 10;
  _baseResolution = 10;
  _maxResolution = 16;
  _additionalBits = 0;
  _sampleCount = 0;

  pinMode(_pin, INPUT);
  setResolution(resolution);
  setPrescaler(4);
}

double Oversample::read()
{
  unsigned long scaled = readDecimated();
  double proportional = (scaled * 1.0) / (B00000001 << _additionalBits);
  return proportional;
}

unsigned long Oversample::readDecimated()
{
  /* Sum all measurements. */
  unsigned long total = 0UL;
  for(int i = 0; i < _sampleCount; i++) {
    total += analogRead(_pin);
  }

  /* Decimate by right shifting. */
  return total >> _additionalBits;
}

void Oversample::setResolution(byte resolution)
{
  _resolution = sanitizeResolution(resolution);
  _additionalBits = _resolution - _baseResolution;
  _sampleCount = B00000001 << (_additionalBits * 2);
}

byte Oversample::getResolution()
{
  return _resolution;
}

void Oversample::setPrescaler(byte prescaler)
{
  prescaler &= B00000111;
  ADCSRA &= B11111000;
  ADCSRA |= prescaler;
}

byte Oversample::getPrescaler()
{
  return (ADCSRA & B00000111);
}

byte Oversample::sanitizeResolution(byte resolution)
{
  if(resolution > _maxResolution) {
    resolution = _maxResolution;
  }

  else if(resolution < _baseResolution) {
    resolution = _baseResolution;
  }

  return resolution;
}
