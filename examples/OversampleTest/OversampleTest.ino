#include <Oversample.h>

byte analogPin = A0;
byte resolution = 16;
byte interval = 1;

Oversample * sampler = new Oversample(analogPin, resolution);

void setup() {
  Serial.begin(115200);

  byte resolution = sampler->getResolution();
  //sampler->setResolution(16);
  Serial.print("Resolution: ");
  Serial.println(resolution);

  byte prescaler = sampler->getPrescaler();
  //sampler->setPrescaler(4);
  Serial.print("Prescaler: ");
  Serial.println(resolution);
}

void loop() {
  double oversampled = sampler->read();
  long scaled = sampler->readScaled();
  int single = analogRead(analogPin);

  Serial.print(single);
  Serial.print(", ");
  Serial.print(oversampled, 7);
  Serial.print(", ");
  Serial.println(scaled);
}
