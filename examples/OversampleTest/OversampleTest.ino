#include <Oversample.h>

byte analogPin = A0;
byte resolution = 16;
byte interval = 1;

Oversample * sampler;

void setup() {
  Serial.begin(115200);
  sampler = new Oversample(analogPin, resolution);

  byte resolution = sampler->getResolution();
  //sampler->setResolution(16);
  Serial.print("Resolution: ");
  Serial.println(resolution);

  byte prescaler = sampler->getPrescaler();
  //sampler->setPrescaler(7);
  Serial.print("Prescaler: ");
  Serial.println(resolution);
}

void loop() {
  int single = analogRead(analogPin);
  double oversampled = sampler->read();
  long scaled = sampler->readDecimated();

  Serial.print(single);
  Serial.print(", ");
  Serial.print(oversampled, 7);
  Serial.print(", ");
  Serial.println(scaled);

  delay(interval * 1000);
}
