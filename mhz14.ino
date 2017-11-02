#include <SoftwareSerial.h>

SoftwareSerial mySerial(D3, D4, false, 256);

void setup_co2() {
  mySerial.begin(9600);  
}

byte cmd[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79}; 
char response[9];

int get_co2() {
  static bool first = true;

  if (first) {
    first = false;
    setup_co2();
    Serial.println("Setup co2");
  }

  
  mySerial.write(cmd,9);
  mySerial.readBytes(response, 9);
  int responseHigh = (int) response[2];
  int responseLow = (int) response[3];
  int ppm = (256*responseHigh)+responseLow;
  Serial.println("CO2="+ String(ppm));
  return(ppm);
}
