#define BLYNK_PRINT Serial
#include <MQ2.h>
#include <Bridge.h>
#include <BlynkSimpleYun.h>
#include <DHT.h>
#include <Wire.h>
#include <SeeedOLED.h>
//載入相關套件

char auth[] = "8320b6af67fd49f4b6f5a6b727f5d573";//Blynk通行證
#define DHTPIN A1 //dht腳位

#define DHTTYPE DHT22 

int pin = A0; //mq2腳位
int lpg, co, smoke; //定義擷取數據
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor()  //溫度傳送
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // 讀取dht
  
  Serial.print("DHT-Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("DHT-Temperature: "); 
  Serial.print(t);
  Serial.println(" *C\t");
  if (isnan(h) || isnan(t)) { //沒收到數據
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  else if (t > 38) {
    Blynk.notify("警告-溫度超過38C！");
  }
  else if (h < 40) {
    Blynk.notify("警告-濕度小於40%！");
  }  
  Blynk.virtualWrite(V5, h); //定義接收腳位
  Blynk.virtualWrite(V6, t);
  Bridge.put("Humidity", String(h));
  Bridge.put("Temperature", String(t));
  }

MQ2 mq2(pin);

void setup(){
  Serial.begin(9600);
  Blynk.begin(auth);
  dht.begin();
  timer.setInterval(1000L, sendSensor); //多久傳送數據
  Bridge.begin();
  mq2.begin();
  Wire.begin();
  SeeedOled.init();                         // 初始化OLED               
  SeeedOled.setNormalDisplay();           //設定OLED 正常顯示
  SeeedOled.setPageMode();     
}

void loop(){ //OLED&MQ2
  
  float h = dht.readHumidity(); 
  float t = dht.readTemperature();
  float* values= mq2.read(true); //set it false if you don't want to print the values in the Serial
  
  lpg = values[0];
  lpg = mq2.readLPG();
  co = values[1];
  co = mq2.readCO();
  smoke = values[2];
  smoke = mq2.readSmoke();
  Blynk.virtualWrite(V7, lpg); //定義腳位
  Blynk.virtualWrite(V8, co);
  Blynk.virtualWrite(V9, smoke);
  SeeedOled.clearDisplay();          //清除OLED   
  SeeedOled.setTextXY(0,0);         //設定OLED 從0,0開始顯示
  SeeedOled.putString("Humidity: ");  // 顯示字元 Humidity: 
  SeeedOled.putFloat(h);             //顯示讀取的濕度值
  SeeedOled.putString("%");          //顯示字元 % 
  SeeedOled.setTextXY(2,0);         //設定OLED 從2,0開始顯示
  SeeedOled.putString("Temp: ");     //顯示字元 Temp
  SeeedOled.putFloat(t);            //顯示讀取的攝氏溫度值
  SeeedOled.putString("*C");         
  delay(200);
  Blynk.run();
  timer.run();
}




//8月中
//程式能跑，但是7688記憶體不足無法上傳執行。
