#include <Oversample.h>

byte analogPin = A0;
byte resolution = 16;
byte interval = 1;
unsigned long time;

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
  //long scaled = sampler->readDecimated();

  time = micros();
  double oversampled = sampler->read();
  time = micros() - time;

  int single = analogRead(analogPin);

  Serial.print(single);
  Serial.print(", ");
  Serial.print(oversampled, 7);
  Serial.print(", ");
  Serial.print(scaled);
  Serial.print(", ");
  Serial.println(time);

  delay(interval * 1000);
}
