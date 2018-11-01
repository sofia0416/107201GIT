#define BLYNK_PRINT Serial
#include <Bridge.h>
#include <BlynkSimpleYun.h>
#include <MQ2.h>

char auth[] = "19f92e80b5e34502b59a61e83d7bf589";


int pin = A0;
int lpg, co, smoke;

BlynkTimer timer;

MQ2 mq2(pin);

void sendSensor()
{
  float* values= mq2.read(true); //set it false if you don't want to print the values in the Serial
  
  //lpg = values[0];
  lpg = mq2.readLPG();
  //co = values[1];
  co = mq2.readCO();
  //smoke = values[2];
  smoke = mq2.readSmoke();
  Blynk.virtualWrite(V5, lpg);
  Blynk.virtualWrite(V6, co);
  Blynk.virtualWrite(V7, smoke);
  }


void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth);
  mq2.begin();
  timer.setInterval(1000L, sendSensor);
  Bridge.begin();
}

void loop()
{
  delay(1000);
  Blynk.run();
  timer.run();
}

//0722
//mq2 to blynk 成功

