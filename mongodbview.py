import pymongo

myclient = pymongo.MongoClient("mongodb://localhost:27017/")
mydb = myclient["mqttdatabase"]
mycol = mydb["feed"]

for x in mycol.find():
  print(x)
