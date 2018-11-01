#include <DHT.h>   //載入溫度套件
#include <MQ2.h>    //載入氣體套件
#include <PMS.h>   //載入G3套件
#include <SoftwareSerial.h>
#include <Bridge.h>   //MCU TO MPU
#include <Wire.h>     
#include <SeeedOLED.h>  //載入OLED套件
#define DHTPIN A1       //定義DHT腳位
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial pmsSerial(9, 10);   //定義G3腳位
PMS pms(pmsSerial);
PMS::DATA pmsData;

int pin = A0;       //定義MQ2腳位
int lpg, co, smoke;
int PM1()   //G3 PM1
{
  pms.read(pmsData);
  return pmsData.PM_AE_UG_1_0;
}

int PM2()   //G3 PM2.5
{
  pms.read(pmsData);
  return pmsData.PM_AE_UG_2_5;
}

int PM10()   //G3 PM10
{
  pms.read(pmsData);
  return pmsData.PM_AE_UG_10_0;
}

MQ2 mq2(pin);

void setup() {  //相關設定
  // put your setup code here, to run once:
  Serial.begin(9600);  // 鮑率9600
  dht.begin();
  mq2.begin();
  pmsSerial.begin(9600);
  Wire.begin();
  SeeedOled.init(); 
  Bridge.begin();
  SeeedOled.clearDisplay();              //清除OLED
  SeeedOled.setNormalDisplay();         //設定OLED正常顯示
  SeeedOled.setPageMode();             //設定為頁模式
}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();    //DHT22計算
  float t = dht.readTemperature();
  float* values= mq2.read(true);   //MQ2
  
  lpg = mq2.readLPG();  //MQ2計算
  co = mq2.readCO();
  smoke = mq2.readSmoke();
  Serial.print("DHT-Humidity: ");  //印出濕度
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("DHT-Temperature: ");  //印出溫度
  Serial.print(t);
  Serial.println(" *C\t");
  Serial.println(PM1());    //印出PM1.0
  Serial.println(PM2());    //印出PM2.5
  Serial.println(PM10());   //印出PM10

  SeeedOled.clearDisplay();      //清除OLED   
  SeeedOled.setTextXY(0,0);     //OLED游標移至0.0
  SeeedOled.putString("Temp: ");   //顯示字元TEMP
  SeeedOled.putNumber(t); //顯示運算後的t值
  SeeedOled.putString("*C");    //顯示字元*C
    
  SeeedOled.setTextXY(1,0);     //OLED游標移至1.0
  SeeedOled.putString("Humi: ");   //顯示字元Humi:
  SeeedOled.putNumber(h); //顯示運算後h的值
  SeeedOled.putString("%");    //顯示字元%
  
  SeeedOled.setTextXY(2,0);     //OLED游標移至2.0
  SeeedOled.putString("PM1.0: ");   //顯示字元PM1.0:
  SeeedOled.putNumber(PM1()); //顯示運算後PM1.0的值
  SeeedOled.putString("ug/m3");    //顯示字元ug/m3

  SeeedOled.setTextXY(3,0);    
  SeeedOled.putString("PM2.5: ");   
  SeeedOled.putNumber(PM2()); 
  SeeedOled.putString("ug/m3");   

  SeeedOled.setTextXY(4,0);    
  SeeedOled.putString("PM10: ");
  SeeedOled.putNumber(PM10());
  SeeedOled.putString("ug/m3");

  SeeedOled.setTextXY(5,0);
  SeeedOled.putString("LPG: ");
  SeeedOled.putNumber(lpg);
  SeeedOled.putString("ppm");

  SeeedOled.setTextXY(6,0);
  SeeedOled.putString("CO: ");
  SeeedOled.putNumber(co);
  SeeedOled.putString("ppm");

  SeeedOled.setTextXY(7,0);
  SeeedOled.putString("SMOKE: ");
  SeeedOled.putNumber(smoke);
  SeeedOled.putString("ppm");
  // Bridge to MPU
  Bridge.put("h", String(h));
  Bridge.put("t", String(t));
  Bridge.put("lpg", String(lpg));
  Bridge.put("co", String(co));
  Bridge.put("smoke", String(smoke));
  Bridge.put("PM1", String(PM1()));
  Bridge.put("PM2", String(PM2()));
  Bridge.put("PM10", String(PM10()));
  delay(5000); //每5秒回傳一次資料
}
