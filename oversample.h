#ifndef Oversample_h
#define Oversample_h

class Oversample
{
  public:
    /* Total Resolution, including oversampled Bit
     * This may range from 10(no oversampling) to 16(max oversampling)
     * The more resolution you want, the longer the measurement will take.
     */
    Oversample(int pin, int resolution);

    /* Returns a measurement with the requested resolution.
     */
    float read();

    void setResolution(int resolution);
    int getResolution();

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
    void setPrescaler(int prescaler);
    int getPrescaler();

  private:
    int _pin;
    int _prescaler;
    int _resolution;
    int _samplesCount;
    int * _samples;
};

#endif
