import requests 
import json
import paho.mqtt.client as mqtt


res = requests.get('https://api.thingspeak.com/channels/506100/feeds/last.json?key=BF7HJHRF5JYA8QXF')

data = str(res.json())

print(data)


MQTT_HOST = "localhost"
MQTT_PORT = 1883
MQTT_KEEPALIVE_INTERVAL = 45
MQTT_TOPIC = "helloTopic"
MQTT_MSG = data



def on_publish(client, userdata, mid):
	print ("Message Published...")


mqttc = mqtt.Client()


mqttc.on_publish = on_publish


mqttc.connect(MQTT_HOST, MQTT_PORT, MQTT_KEEPALIVE_INTERVAL)		

	
mqttc.publish(MQTT_TOPIC,MQTT_MSG)


mqttc.disconnect()

