#include "Arduino.h"

#ifndef Oversample_h
#define Oversample_h

class Oversample
{
  public:
    /* Total Resolution, including oversampled Bit
     * This may range from 10(no oversampling) to 16(max oversampling)
     * The more resolution you want, the longer the measurement will take.
     */
    Oversample(byte pin, byte resolution);

    /* Returns a measurement with the requested resolution. */
    double read();

    /* Returns the scaled sum of the measurements. */
    long readScaled();

    void setResolution(byte resolution);
    byte getResolution();

    /* Prescaler
     * 7: 128 (Arduino default)
     * 6: 64
     * 5: 32
     * 4: 16 (recommended maximum - our default)
     * 3: 8
     * 2: 4
     * 1: 2
     * 0: 2
     */
    void setPrescaler(byte prescaler);
    byte getPrescaler();

  private:
    byte _pin;
    byte _prescaler = 4;
    byte _resolution = 10;
    byte _baseResolution = 10;
    byte _additionalBits;
    int _sampleCount;
    int * _samples = 0;

    byte sanitizeResolution(byte resolution);
};

#endif
