#define BLYNK_PRINT Serial
#include <MQ2.h>
#include <BlynkSimpleYun.h>
#include <DHT.h>

char auth[] = "8320b6af67fd49f4b6f5a6b727f5d573";
#define DHTPIN A1
#define DHTTYPE DHT22 
WidgetLCD lcd(V0);
int lpg, co, smoke, pin = A0; 
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
  Serial.print(h);
  Serial.print(t);
  if (t < 38){
    lcd.print(4, 0, "正常  ");
  }
   if (t > 38){
    Blynk.notify(F("溫度超過38C！"));
    lcd.print(4, 0, "有點熱");
  }
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
  }

MQ2 mq2(pin);

void setup(){
  Serial.begin(9600);
  Blynk.begin(auth);
  dht.begin();
  timer.setInterval(1000L, sendSensor);
  mq2.begin();
  lcd.clear();
}

void loop(){
  
  float* values= mq2.read(true); //set it false if you don't want to print the values in the Serial
  
  lpg = mq2.readLPG();
  co = mq2.readCO();
  smoke = mq2.readSmoke();
   Blynk.virtualWrite(V7, lpg);
   Blynk.virtualWrite(V8, co);
   Blynk.virtualWrite(V9, smoke);
   delay(2000);
   Blynk.run();
   timer.run();
}
//0725
//mq2&dht to blynk 

