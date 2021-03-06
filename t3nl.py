from urllib2 import Request, urlopen
import time    #載入套件
import sys
import httplib, urllib

sys.path.insert(0, '/usr/lib/python2.7/bridge/') 
from bridgeclient import BridgeClient as bridgeclient
thinkSpeakApiKey = "FCPQKIEO15PEY042"  #Thinkspeak通行證

BLYNK_AUTH = '8320b6af67fd49f4b6f5a6b727f5d573' #BLYNK通行證
input_pin = "V0"    #定義腳位
input_pin1 = "V1"
input_pin2 = "V2"
input_pin3 = "V3"
input_pin4 = "V4"
input_pin5 = "V5"
input_pin6 = "V6"
input_pin7 = "V7"

def post_to_thingspeak(payload):    #傳到thingspeak
    headers = {"Content-type": "application/x-www-form-urlencoded","Accept": "text/plain"}
    not_connected = 1
    while (not_connected):   #如果傳不上
        try:
            conn = httplib.HTTPConnection("api.thingspeak.com:80")
            conn.connect()
            not_connected = 0
        except (httplib.HTTPException, socket.error) as ex:
            print "Error: %s" % ex
            time.sleep(10)  # sleep 10 seconds

    conn.request("POST", "/update", payload, headers)
    response = conn.getresponse()
    print( response.status, response.reason, payload, time.strftime("%c"))
    data = response.read()
    conn.close()

while True:   
    value = bridgeclient()  #BRIDGE連接
    t0 = value.get("t")  #取得MPU數據
    h0 = value.get("h")
    l0 = value.get("lpg")
    c0 = value.get("co")
    s0 = value.get("smoke")
    p1 = value.get("PM1")
    p2 = value.get("PM2")
    p10 = value.get("PM10")
    print "Temp: " + t0    #MPU數據印出
    print "Humi: " + h0
    print "lpg: " + l0
    print "co: " + c0
    print "smoke: " + s0
    print "pm1: " + p1
    print "pm2: " + p2
    print "pm10: " + p10


    requestString = "http://blynk-cloud.com/" + BLYNK_AUTH + "/update/" + input_pin + "?value=" + t0
    print "requestString: " + requestString
    requestString1 = "http://blynk-cloud.com/" + BLYNK_AUTH + "/update/" + input_pin1 + "?value=" + h0
    print "requestString1: " + requestString1
    requestString2 = "http://blynk-cloud.com/" + BLYNK_AUTH + "/update/" + input_pin2 + "?value=" + l0
    print "requestString2: " + requestString2
    requestString3 = "http://blynk-cloud.com/" + BLYNK_AUTH + "/update/" + input_pin3 + "?value=" + c0
    print "requestString3: " + requestString3
    requestString4 = "http://blynk-cloud.com/" + BLYNK_AUTH + "/update/" + input_pin4 + "?value=" + s0
    print "requestString4: " + requestString4
    requestString5 = "http://blynk-cloud.com/" + BLYNK_AUTH + "/update/" + input_pin5 + "?value=" + p1
    print "requestString5: " + requestString5
    requestString6 = "http://blynk-cloud.com/" + BLYNK_AUTH + "/update/" + input_pin6 + "?value=" + p2
    print "requestString6: " + requestString6
    requestString7 = "http://blynk-cloud.com/" + BLYNK_AUTH + "/update/" + input_pin7 + "?value=" + p10
    print "requestString7: " + requestString7
    #上傳Blynk

    request = Request(requestString)
    response_body = urlopen(request).read()
    print response_body
    
    request = Request(requestString1)
    response_body = urlopen(request).read()
    print response_body
    
    request = Request(requestString2)
    response_body = urlopen(request).read()
    print response_body
    
    request = Request(requestString3)
    response_body = urlopen(request).read()
    print response_body
    
    request = Request(requestString4)
    response_body = urlopen(request).read()
    print response_body

    request = Request(requestString5)
    response_body = urlopen(request).read()
    print response_body
    
    request = Request(requestString6)
    response_body = urlopen(request).read()
    print response_body
    
    request = Request(requestString7)
    response_body = urlopen(request).read()
    print response_body
    
    
    params = urllib.urlencode({'field1': t0, 'field2': h0, 'field3': l0, 'field4': c0, 'field5': s0, 'field6': p1, 'field7': p2, 'field8': p10, 'key': thinkSpeakApiKey})
    post_to_thingspeak(params)   #上傳thingspeak
    
    time.sleep(5)  #5秒傳一次