#include "oversample.h"

Oversample::Oversample(byte pin, byte resolution)
{
  _pin = pin;

  pinMode(_pin, INPUT);
  setPrescaler(4);
  setResolution(resolution);
}

double Oversample::read()
{
  int scaled = readScaled();
  double averaged = (scaled * 1.0) / (B00000001 << _additionalBits);
  return averaged;
}

long Oversample::readScaled()
{
  /* Do all the measurements as quickly as possible. */
  for(int i = 0; i < _sampleCount; i++) {
    _samples[i] = analogRead(_pin);
  }

  /* Sum all measurements. */
  long total = 0;

  for(int i = 0; i < _sampleCount; i++) {
    total += _samples[i];
  }

  /* Scale by right shifting. */
  long scaled = total >> _additionalBits;
  return scaled;
}

void Oversample::setResolution(byte resolution)
{
  _resolution = sanitizeResolution(resolution);
  _additionalBits = _resolution - 10;
  _sampleCount = B00000001 << (_additionalBits * 2);

  if(_samples != 0) {
    delete [] _samples;
  }

  _samples = new int [_sampleCount];
}

byte Oversample::getResolution()
{
  return _resolution;
}

void Oversample::setPrescaler(byte prescaler)
{
  byte mask = B11111000;
  ADCSRA &= mask;
  ADCSRA |= prescaler;
}

byte Oversample::getPrescaler()
{
  return _prescaler;
}

byte Oversample::sanitizeResolution(byte resolution)
{
  if(resolution > 16) {
    resolution = 16;
  }

  else if(resolution < 10) {
    resolution = 10;
  }

  return resolution;
}
