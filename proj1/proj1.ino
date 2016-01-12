#include <SoftwareSerial.h>
#include <Wire.h>  
#include <dht.h>

//温度湿度传感器
#define DHT11_PIN 8
//蓝牙
#define HC_05_RX 10
#define HC_05_TX 11
//声音传感器
#define ANALOG_SOUND_PIN A0
#define SOUND_THRESHOLD 1000
//光照传感器
#define GY_30_ADDR  0x23
#define LIGHT_THRESHOLD 4
#define LIGHT_PIN 13

SoftwareSerial BT(HC_05_RX, HC_05_TX); 
dht DHT;

void setup()  {
  Wire.begin();
  Serial.begin(9600);
  BT.begin(9600);

  pinMode(LIGHT_PIN, OUTPUT);
}
 
void loop() {
  int soundvalue = analogRead(ANALOG_SOUND_PIN);
  if(soundvalue<SOUND_THRESHOLD){
    uint16_t lightVal = GY_30_READ(GY_30_ADDR);
    if(lightVal<LIGHT_THRESHOLD){
      Serial.println(lightVal);
      digitalWrite(LIGHT_PIN,HIGH);
      delay(1000*10);
      digitalWrite(13,LOW);
    }else{
      Serial.println("Day Time!Ignore!");
      Serial.println(lightVal);
    }
  }
//  
//  int chk = DHT.read11(DHT11_PIN);
//  switch (chk){
//    case 0:  
//      BT.print(DHT.humidity,1);
//      BT.print(",\t");
//      BT.println(DHT.temperature,1);
//      break;
//    case -1: Serial.print("Checksum error,\t"); break;
//    case -2: Serial.print("Time out error,\t"); break;
//    default: Serial.print("Unknown error,\t"); break;
//  }
//  delay(2000);
//  if (BT.available()){//Resp the data
//    String val = "";
//    while (BT.available() > 0)  {
//      val += char(BT.read());
//      delay(2);
//    }
//    if(val.equals("light on")){
//        BT.println("you had light on :)!");
//        digitalWrite(13,HIGH);
//    }else if(val.equals("light off")){
//        BT.println("you had light off :(");
//        digitalWrite(13,LOW);
//    }
//  }
//  if (Serial.available()){//Send the data
//    BT.write(Serial.read());
//  }
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
