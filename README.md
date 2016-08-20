# Arduino ADC Oversampling
This library implements "ENhancing ADC rewsolutino by oversampling" as per [Note AVR121](http://www.atmel.com/images/doc8003.pdf).

For detail information please refer to the paper mentioned above.

## Theory of operation
Oversampling means, sampling a signal over its Nyquist Frequency. The Nyquist freuqency is twice the highest frequency of interest in the input signal.
Sampling above **fnyquist > 2 * fsignal** is called oversampling.
For each additional Bit of resolution *n*, the signal must be oversampled four times.
So the oversampling frequency is **foversampling = 4^n * fnyquist**.

Some criteria must be fullfilled in order for oversampling to work properly:

* The signal-component of interest should not vary significantly during a conversion.
* There should be **some noise present** in the signal.
* The amplitude of the noise should be at least 1LSB.

Usually enough noise will be available for this method to work properly, though it might be introduced artificially.

## Implementation
Atmega allows a prescaler to be set for the ADC. By default it is set to 128.
So with a clock of 16MHz, the ADC operates with **16,000,000Hz / 128 = 125,000Hz = 125kHz**.
As per datasheet is is safe to set the prescaler as low as *16*, allowing us to clock the ADC with **16,000,000Hz / 16 = 1,000,000Hz = 1MHz**. This is one of the first thin done, when you create a new Oversampler object. This will now apply to **all your analog measurements**.

The ADC provides us with 10Bit resolution. So to get 11Bit resolution we need to oversample by 4^n, n= 11 - 10 = 1 => 4 samples.

So in total we will collect 4 samples to achieve 11Bit of resolution.

Lets assume our collected samples look like this:

    00000001
    00000010
    00000010
    00000001

All samples are added up to one integer.

    00000110

The result is now scaled by shifting it to the right by n(1):

    00000011

The value is now divided by **2^n** and stored as float:

     3/2^1 = 1.5

This is the value you obtain through a call to read().

## Usage
Simply clone this repository to your library folder. This repository also contains an example which should show up in your Arduino IDE.

    // Oversample * sampler = new Oversample(analogPin, resolution);
    Oversample * sampler = new Oversample(A0, 16);
    double oversampled = sampler->read();

The library provides getters and setters for resolution and prescaler. Please see the example on how to use them.

## Does it work?
The first time I heard about it, it sounded a bit like magic, so I thought the only way for sure is to try it and compare. I would like to compare it to a **real** 12 and 16 Bit ADC, unfortunately I do not have any on hand at the moment and will aquire them with my next electronics order to provide proper comparison.

In the mean time I cam up with the following test setup to at least see how it compares to regular analog reads.
