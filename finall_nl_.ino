#define BLYNK_PRINT Serial
#include <Bridge.h>
#include <BlynkSimpleYun.h>
#include <DHT.h>

char auth[] = "8320b6af67fd49f4b6f5a6b727f5d573";

#define DHTPIN A1          // What digital pin we're connected to


// Uncomment whatever type you're using!

#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;


void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  
  Serial.print("DHT-Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("DHT-Temperature: "); 
  Serial.print(t);
  Serial.println(" *C\t");
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
   if (t > 38){
    digitalWrite(5, HIGH);
  }
   else if (h < 40){
    digitalWrite(5, HIGH);
   }
   else{
    digitalWrite(5, LOW);
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
  Bridge.put("Humidity", String(h));
  Bridge.put("Temperature", String(t));
  }


void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth);
  dht.begin();
  timer.setInterval(1000L, sendSensor);
  Bridge.begin();
}

void loop()
{
  delay(1000);
  Blynk.run();
  timer.run();
}
//六月初
//測試DHT22 AND 使用ARDUINO
