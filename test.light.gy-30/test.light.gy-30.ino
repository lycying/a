#include <Wire.h> //IIC
#include <math.h> 
#define BH1750_ADDR  0x23

void setup()
{

  Wire.begin();
  Serial.begin(9600);
}
void loop()
{
  uint16_t u =  GY_30_READ(BH1750_ADDR);
  Serial.println(u);
  delay(100);

}

int GY_30_READ(int address) {
  GY_30_INIT(address);
  delay(100);
  int i=0;
  byte buff[2];
  uint16_t val=0;
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 2);
  while(Wire.available()) {
    buff[i] = Wire.read();  // receive one byte
    i++;
  }
  Wire.endTransmission();  
  if(2==i){
   val=((buff[0]<<8)|buff[1])/1.2;
   return val;
  }
}
void GY_30_INIT(int address) {
  Wire.beginTransmission(address);
  Wire.write(0x10);//1lx reolution 120ms
  Wire.endTransmission();
}

