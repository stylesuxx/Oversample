#include "Arduino.h"

#ifndef Oversample_h
#define Oversample_h

class Oversample
{
  public:
    /**
     * Total Resolution, including oversampled Bits.
     *
     * This may range from 10(no oversampling) to 16(max oversampling)
     * The more resolution you want, the longer the measurement will take.
     *
     * @param pin Analog pin to use.
     * @param resolution Chosen resolution.
     */
    Oversample(byte pin, byte resolution);

    /**
     * Run a measurement with the set resolution.
     *
     * @return The oversampled, decimated measurement.
     */
    double read();

    /**
     * Run a measurement with the set resolution.
     *
     * @return The oversampled, non decimated measurement.
     */
    unsigned long readDecimated();

    /**
     * Set measurment resolution.
     *
     * @param resolution Resolution might be between _baseResolution and
     *                   _maxResolution.
     */
    void setResolution(byte resolution);
    byte getResolution();

    /**
     * Set the ADC's Prescaler.
     *
     * 7: 128 (Arduino default)
     * 6: 64
     * 5: 32
     * 4: 16 (recommended maximum - our default)
     * 3: 8
     * 2: 4
     * 1: 2
     * 0: 2
     *
     * @param prescaler The prescaler to set for the ADC.
     */
    void setPrescaler(byte prescaler);
    byte getPrescaler();

  private:
    byte _pin = 0;
    byte _prescaler = 4;
    byte _resolution = 10;
    byte _baseResolution = 10;
    byte _maxResolution = 16;
    byte _additionalBits = 0;
    int _sampleCount = 0;
    int * _samples = 0;

    byte sanitizeResolution(byte resolution);
};

#endif
