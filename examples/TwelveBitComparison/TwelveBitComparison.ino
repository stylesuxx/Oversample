#include <Oversample.h>
#include <SPI.h>

byte analogPin = A0;
byte resolution = 12;

// MCP3201 via SPI
byte cs = 4;

byte interval = 1;

Oversample * sampler;

void setup() {
  SPI.begin();
  Serial.begin(115200);

  sampler = new Oversample(analogPin, resolution);

  pinMode(cs, OUTPUT);
  digitalWrite(cs, HIGH);
}

void loop() {
  int internal = sampler->readDecimated();
  int external = readADC();

  Serial.print(internal);
  Serial.print(", ");
  Serial.println(external);

  delay(interval * 1000);
}

int readADC() {
  byte hi, lo;
  uint16_t reading;

  SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));
  digitalWrite(cs, LOW);

  hi = SPI.transfer(0x00);
  lo = SPI.transfer(0x00);

  digitalWrite(cs, HIGH);
  SPI.endTransaction();

  reading = hi;
  reading <<= 8;
  reading |= lo;
  reading >>= 1;
  reading &= 0b001111111111111;

  return reading;
}
