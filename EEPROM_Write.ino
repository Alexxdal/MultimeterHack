#include <Wire.h>
const int I2C_ADDR = 0x50;


 
void setup() {
  Serial.begin(9600);
  Wire.setClock(100000);
  Wire.begin();

  
  //writeByte(I2C_ADDR, 0xF9, (byte) 0xC3); //C3  Address F9 impostazioni alimentazione ecc.. 
  //writeByte(I2C_ADDR, 0xFA, (byte) 0xCE); //enable RS232
  //writeByte(I2C_ADDR, 0xFC, (byte) 0x0f); //Backlight time 30s //Backlight time 30s
  
  //writeByte(I2C_ADDR, 0x3c, (byte) 0x00); //Environment temperature (25 C)
  //writeByte(I2C_ADDR, 0x0C, (byte) 0x01); //Environment temperature (25 C)

  //writeByte(I2C_ADDR, 0x0D, (byte) 0xEC);
  
  //DC 1000V range calibration ratio
  /*
  writeByte(I2C_ADDR, 0xF0, (byte) 0x00);
  writeByte(I2C_ADDR, 0xF1, (byte) 0x00);
  //DC 600V range calibration ratio
  writeByte(I2C_ADDR, 0xEE, (byte) 0x00);
  writeByte(I2C_ADDR, 0xEF, (byte) 0x00);
  //DC 60V range calibration adjustment ratio
  writeByte(I2C_ADDR, 0xEC, (byte) 0x00);
  writeByte(I2C_ADDR, 0xED, (byte) 0x00);
  //DC 6V range calibration adjustment ratio
  writeByte(I2C_ADDR, 0xEA, (byte) 0x00);
  writeByte(I2C_ADDR, 0xEB, (byte) 0x00);
  */
  //DC 600mV range calibration adjustment ratio
  //writeByte(I2C_ADDR, 0xE8, (byte) 0x00);
  //writeByte(I2C_ADDR, 0xE9, (byte) 0x80);
  
  //80
  /*
  writeByte(I2C_ADDR, 0x80, (byte) 0x00);
  writeByte(I2C_ADDR, 0x81, (byte) 0x00);
  writeByte(I2C_ADDR, 0x82, (byte) 0x00);
  writeByte(I2C_ADDR, 0x83, (byte) 0x00);
  writeByte(I2C_ADDR, 0x84, (byte) 0x00);
  writeByte(I2C_ADDR, 0x85, (byte) 0x00);
  writeByte(I2C_ADDR, 0x86, (byte) 0x13);
  writeByte(I2C_ADDR, 0x87, (byte) 0x12);
  writeByte(I2C_ADDR, 0x88, (byte) 0x10);
  writeByte(I2C_ADDR, 0x89, (byte) 0x03);
  writeByte(I2C_ADDR, 0x8a, (byte) 0x0e);
  writeByte(I2C_ADDR, 0x8b, (byte) 0x09);
  writeByte(I2C_ADDR, 0x8c, (byte) 0x01);
  writeByte(I2C_ADDR, 0x8d, (byte) 0x0c);
  writeByte(I2C_ADDR, 0x8e, (byte) 0x04);
  writeByte(I2C_ADDR, 0x8f, (byte) 0x07);
  */
  //writeByte(I2C_ADDR, 0xf0, (byte) 0xff);
  //writeByte(I2C_ADDR, 0xf1, (byte) 0xff);
  
  
  //writeByte(I2C_ADDR, 0xFC, (byte) 0x00); //Backlight time 30s

  
}


int incomingByte = 0;
void loop() {
    // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    String command = Serial.readString();
    if(command.indexOf("dump") > -1)
    {
      dumpEEPROM();
    }
  }
  
  
}
 
void dumpEEPROM()
{
  for (int i = 0; i < 256; i++) {
    byte b = readByte(I2C_ADDR, i);
    //Serial.print(b, HEX); 
    char buffer[3];
    sprintf (buffer, "%02X", b);
    Serial.print(buffer);
    Serial.print(" ");
    if ((i + 1) % 16 == 0) Serial.println();
  }
  Serial.println();
}
 
void writeByte(int i2cAddr, unsigned int addr, byte data) {
  Wire.beginTransmission(i2cAddr);
  Wire.write(addr);
  Wire.write(data);
  Wire.endTransmission();
}
 
byte readByte(int i2cAddr, unsigned int addr) {
  byte data = 0x00;
  Wire.beginTransmission(i2cAddr);
  Wire.write(addr);
  Wire.endTransmission();
  Wire.requestFrom(i2cAddr, 1);
  while (!Wire.available()) ;
 
  data = Wire.read();
  return data;
}
