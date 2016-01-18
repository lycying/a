#define PIN A2
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  int soundvalue = analogRead(PIN);
  if(soundvalue<1000){
      Serial.println(soundvalue);
    }
  delay(100);
}
