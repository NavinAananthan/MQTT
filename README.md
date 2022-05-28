# MQTT
This project is based on mqtt development we get Temperature and Humidity sensor data through ESP32. ESP32 is a series of low-cost, low-power system on a chip microcontrollers with integrated Wi-Fi and dual-mode Bluetooth.
We actually in this project establish a connection with online mqtt broker test.mosquitto.org which is free of cost and can send messages over the internet the meesages can be of different types chat messages, IOT datas etc.
In this project we establish a connection with online mqtt broker and publish our data on two topics named "/humidity" amd "/temperature" where it gets published at time interval of 8 seconds and i have written a application on python which subscribes the data of the published data.
so through this we can get a idea on how mqtt works and how to connect to a wifi using ESP32 module and send data over the internet and get data across any mobile over the internet in this day today world with ease
