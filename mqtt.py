import requests 
import json
import time
import paho.mqtt.client as mqtt
import pymongo

idx=0
while True:

	# 抓thingspeak資料
	res = requests.get('https://api.thingspeak.com/channels/506100/feeds/last.json?key=BF7HJHRF5JYA8QXF')
	data = str(res.json())
	print(data)

	# Mqtt資訊
	MQTT_HOST = "localhost"
	MQTT_PORT = 1883
	MQTT_KEEPALIVE_INTERVAL = 45
	MQTT_TOPIC = "Airlysis"
	MQTT_MSG = data
	
	# 發布方法
	def on_publish(client, userdata, mid):
		print ("Message Published...")

	mqttc = mqtt.Client()
	mqttc.on_publish = on_publish
	mqttc.connect(MQTT_HOST, MQTT_PORT, MQTT_KEEPALIVE_INTERVAL)		
	mqttc.publish(MQTT_TOPIC,MQTT_MSG)

	#存MongoDB
	myclient = pymongo.MongoClient('mongodb://localhost:27017/')
	mydb = myclient['mqttdatabase']
	mycol = mydb["feed"]
	mydict = res.json()

	x = mycol.insert_one(mydict)
	print(x.inserted_id)

	# 15秒迴圈
	idx +=1
	time.sleep(15)



