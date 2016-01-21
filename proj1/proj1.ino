#include <Wire.h>  
#include <dht.h>
#include <LiquidCrystal.h>
#include <TaskScheduler.h>

//温度湿度传感器
#define DHT11_PIN 11
//声音传感器
#define ANALOG_SOUND_PIN A2
#define SOUND_THRESHOLD 1000
//光照传感器
#define GY_30_ADDR  0x23
#define LIGHT_THRESHOLD 3
#define LIGHT_PIN 13
//红外传感器
#define HC_SR501_PIN 12
//蜂鸣器
#define TONE_PIN 10
//LCD另外一个亮度,避免了5V供电晚上太亮
#define LCD_LIGHT 9

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
dht DHT;

void setup()  {
  Serial.begin(9600);
  Wire.begin();
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(HC_SR501_PIN, INPUT);

  lcd.begin(16, 2);

  GY_30_INIT(GY_30_ADDR);

  Sch.init();
  Sch.addTask(dht11Read,0,1000,1);
  Sch.addTask(lightProcess,0,10,1);
  Sch.start();
}

void dht11Read(){
  int chk = DHT.read11(DHT11_PIN);
  switch (chk){
    case 0:  
      lcd.setCursor(0, 0);
      lcd.print("H:");
      lcd.print(DHT.humidity);
      lcd.print("  ");
      lcd.print("T:");
      lcd.println(DHT.temperature);
      break;
    case -1: Serial.print("Checksum error,\t"); break;
    case -2: Serial.print("Time out error,\t"); break;
    default: Serial.print("Unknown error,\t"); break;
  }
}

int lightPid = -1;
int dayTime = 0;
void lightProcess(){
  int rayIn = digitalRead(HC_SR501_PIN); 
  int soundvalue = analogRead(ANALOG_SOUND_PIN);
  uint16_t lightVal = GY_30_READ(GY_30_ADDR);

  if(lightVal<LIGHT_THRESHOLD){
      if(soundvalue<SOUND_THRESHOLD || rayIn == 1){
        lightOn();
      }
      dayTime = 0;
  }else{
      if(dayTime == 0){
        dayTime = 1;
        Sch.deleteTask(lightPid);
        lightOff();

        digitalWrite(LCD_LIGHT,HIGH);
        lcd.setCursor(0, 1);
        lcd.print("Day Time!!");

        tone(TONE_PIN,1484);
        delay(10); 
        noTone(TONE_PIN);
      }
  }
}
void lightOn(){
  digitalWrite(LCD_LIGHT,HIGH);
  lcd.setCursor(0, 1);
  lcd.print("Light On! ");

  digitalWrite(LIGHT_PIN,HIGH);
  Sch.deleteTask(lightPid);
  lightPid = Sch.addTask(lightOff,1000*10,0,1);
}
void lightOff(){
  digitalWrite(LIGHT_PIN,LOW);

  digitalWrite(LCD_LIGHT,LOW);
  lcd.setCursor(0, 1);
  lcd.print("Light Off!");
}
 
void loop() {
  Sch.dispatchTasks();
}
int GY_30_READ(int address) {
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
