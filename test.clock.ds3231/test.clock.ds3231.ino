/*
SCL→A5
　　SDA→A4
　　VCC→5V
　　GND→GND
*/

#include <DS3231.h>
#include <Wire.h>

DS3231 Clock;
bool Century=false;
bool h12;
bool PM;
byte ADay, AHour, AMinute, ASecond, ABits;
bool ADy, A12h, Apm;

byte year, month, date, DoW, hour, minute, second;

void setup() {
	// Start the I2C interface
  Clock.setSecond(50);//Set the second 
  Clock.setMinute(59);//Set the minute 
  Clock.setHour(11);  //Set the hour 
  Clock.setDoW(5);    //Set the day of the week
  Clock.setDate(31);  //Set the date of the month
  Clock.setMonth(5);  //Set the month of the year
  Clock.setYear(13);  //Set the year (Last two digits of the year)
	// Start the serial interface
	Serial.begin(9600);
}
void ReadDS3231()
{
  int second,minute,hour,date,month,year,temperature; 
  second=Clock.getSecond();
  minute=Clock.getMinute();
  hour=Clock.getHour(h12, PM);
  date=Clock.getDate();
  month=Clock.getMonth(Century);
  year=Clock.getYear();
  
  temperature=Clock.getTemperature();
  
  Serial.print("20");
  Serial.print(year,DEC);
  Serial.print('-');
  Serial.print(month,DEC);
  Serial.print('-');
  Serial.print(date,DEC);
  Serial.print(' ');
  Serial.print(hour,DEC);
  Serial.print(':');
  Serial.print(minute,DEC);
  Serial.print(':');
  Serial.print(second,DEC);
  Serial.print('\n');
  Serial.print("Temperature=");
  Serial.print(temperature); 
  Serial.print('\n');
}
void loop() {
  ReadDS3231();delay(1000);
}

