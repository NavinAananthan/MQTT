import paho.mqtt.client as mqtt


# The below functions are implemented for the Temperature 
def on_connect(temp, userdata, flags, rc):
  print("Connected with Temperature topic\n")
  temp.subscribe("/temperature")

def on_message(temp, userdata, msg):
  print("Temperature:",msg.payload.decode(),"°C")
  temp.disconnect()

temp = mqtt.Client()
temp.connect("test.mosquitto.org",1883,60)

temp.on_connect = on_connect
temp.on_message = on_message

temp.loop_forever()


print("\n***************************************************\n")


#This piece of code is running for a single topic Humidity
#The on_connect() callback is called each time the client connects/reconnects to the broker.
#We create the on_connect callback function. It takes 4 parameters: the client object, userdata, flags, rc.
#1.The client object.
#2.userdata is custom data declared in the client constructor. You will need this if you want to pass custom data into the callback.
#3.flags is a dictionary object that is used to check if you have set clean session to True or False for the client object.
#4.rc which is the result code, is used to check the connection status. The different result codes are
def on_connect(humidity, userdata, flags, rc):
  print("Connected with Humidity topic\n")
  humidity.subscribe("/humidity")




#The on_message() callback is used to process messages that are published to a subscribed topic.
#In our program, we need to do 3 things:
#1. Subscribe to the topic that we are publishing to.
#2. Process the published message using the callback. In our program, we will simply print the message.
#3. Assign the callback function to the on_message attribute of the client object.
#The actual message payload is a binary buffer. In order to decode this payload you need to know what type of data was sent
def on_message(humidity, userdata, msg):
  print("Humidity:",msg.payload.decode())
  print("\n")
  humidity.disconnect()
    


#creating mqtt client object named humidity
#connection established to test mosquitto online broker with port number 1883
#client(client_id="", clean_session=True, userdata=None, protocol=MQTTv311, transport="tcp")
humidity = mqtt.Client()
humidity.connect("test.mosquitto.org",1883,60)

humidity.on_connect = on_connect
humidity.on_message = on_message

humidity.loop_forever()