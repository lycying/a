// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>
#include <SoftwareSerial.h>

// Connect a stepper motor with 48 steps per revolution (7.5 degree)
// to motor port #2 (M3 and M4)
AF_Stepper motor1(100, 2);
AF_Stepper motor2(100, 1);

#define HC_05_RX A0
#define HC_05_TX A5

SoftwareSerial BT(HC_05_RX, HC_05_TX); 


void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Stepper test!");
  BT.begin(9600);

  motor1.setSpeed(100);  // 10 rpm   
  motor2.setSpeed(100);  // 10 rpm   
}

void loop() {
  
  if (BT.available()){//Resp the data
    
    String val = "";
    while (BT.available() > 0)  {
     val += char(BT.read());
     delay(2);
   }
   if(val.equals("l")){      
          motor1.step(200, FORWARD, DOUBLE); 
   }else if(val.equals("r")){
          motor1.step(200, BACKWARD, DOUBLE); 
   }else if(val.equals("u")){
          motor2.step(200, FORWARD, DOUBLE); 
   }else if(val.equals("d")){
          motor2.step(200, BACKWARD, DOUBLE); 
   }
   

  }
  

}
