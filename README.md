# IoT-based-Smart-Weather-Monitoring-System

## What is "WEATHER MONITORING STATION"?
The internet of things is a system of interrelated computing devices, mechanical and digital machines, that provide unique identifiers with the ability to transfer data over a network without requiring human-to-human or human-to-computer interaction. All those improvements are developed to facilitate human work and make lifestyles simpler than earlier. An NodeMCU-based based weather monitoring system implementation is proposed to monitor temperature, humidity, pressure, rain intensity, air quality, and altitude, based in geographically distant areas. The weather monitoring system is based on sensory inputs, that periodically update data to the cloud.


## Circuit Information
The circuit consists of Arduino based code configured with our ESP8266 based NodeMCU V3 to recieve data from our DHT11(Humidity),BMP 180(Temprature,Pressure,Altitude),MQ2(Air Quality)
![image](https://user-images.githubusercontent.com/53343462/185744660-b28218a5-d60b-449d-8d6e-7c02a47b4a51.png)


## Cloud Connection Path
The ESP 8266 uses PHP server side scripting and back-end HTTP data configuration to send data to our ThingSpeak and MySQL cloud
![image](https://user-images.githubusercontent.com/53343462/185744669-c4cd4288-3221-43c3-8edb-cfe0f5e10940.png)


## SQL Data
JSON data is posted by the ESP8266, using PHP server-side scripting language. This is then inserted into the database using INSERT, after extracting the necessary values from it. This data is then pulled out from this database using the READ command into "SQL Data"(accessible on the home page)
![image](https://user-images.githubusercontent.com/53343462/185744701-473b5e2b-380b-4a5c-9dd4-e5d296266bb4.png)


## Graph Data
ThingSpeak acts as an open-source Internet of Things(IoT) application where data is sent from ESP8266, to analyze and visualize uploaded data using either MATLAB custom plots or ThingSpeak generated graphs. These are posted to our website using their specific URLs into "Graph Data"(accessible on the home page)
![image](https://user-images.githubusercontent.com/53343462/185744716-925bb5ff-b011-42ac-9614-44b9552d3064.png)
