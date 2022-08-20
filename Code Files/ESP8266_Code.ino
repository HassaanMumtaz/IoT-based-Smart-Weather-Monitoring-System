#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <dht.h>
#include <ESP8266HTTPClient.h>

/* Global Variables */
#ifndef STASSID
#define STASSID "EVO-Charji-2C4E"
#define STAPSK  "G55BHv2G"
#endif

const char* serverName = "http://weathermonitoringstationee.000webhostapp.com//post-data.php";
String apiKeyValue = "12345";

#define seaLevelPressure 101325.0   /* Standard Atmospheric Pressure */
#define sensorDHT11 2               /* NodeMCU D4 */
#define _analog A0
#define _S0 D3
#define _S1 D7
#define _S2 D8
  
WiFiClient client;
Adafruit_BMP085 bmp;
dht DHT;



const char* ssid     = STASSID;
const char* password = STAPSK;
long channel_ID = 1583586;
const char* write_API_Key = "P2I91BUMUB83EO7H";
long channel2_ID = 1616771;
const char* write_API2_Key = "VV7S17VFGB31GH3G";
int analogValue;


/* Setup */ 
void setup() {
  Serial.begin(9600);

  /* Wifi */
  Serial.print("Connecting to: ");
  Serial.println(ssid);

  /* Client Mode */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("REBOOT");

  /* BMP180 */
  if (!bmp.begin()) 
  {
    Serial.println("Error....Something wrong with BMP!");
  }

  /* Multiplexer */
  pinMode(_S0, OUTPUT);
  pinMode(_S1, OUTPUT);
  pinMode(_S2, OUTPUT);

  digitalWrite(_S0, LOW);
  digitalWrite(_S1, LOW);
  digitalWrite(_S2, LOW);
  
  /* ThingSpeak */
  ThingSpeak.begin(client);
}  


/* Loop */   
void loop() {

    double Temperature, Altitude, RealAltitude;
    int Pressure, CalcPressure;
    float temperature11, humidity;
    int intensityRain, intensityLight, airQuality; 
    
    /* BMP180 */  
    Temperature = bmp.readTemperature();
    Pressure = bmp.readPressure();
    Altitude = bmp.readAltitude();
    CalcPressure = bmp.readSealevelPressure();
    RealAltitude = bmp.readAltitude(seaLevelPressure);
    /* <END> */


    /* DHT11 */
    DHT.read11(sensorDHT11);
    temperature11 = DHT.temperature;
    humidity = DHT.humidity;
    /* <END> */

    
    /* Rain Intensity */
    digitalWrite(_S0, LOW);
    digitalWrite(_S1, LOW);
    digitalWrite(_S2, LOW);
    delay(100);
    intensityRain = analogRead(_analog);
    /* <<END> */

    /* Light Intensity */
    digitalWrite(_S0, HIGH);
    digitalWrite(_S1, LOW);
    digitalWrite(_S2, LOW);
    delay(100);
    intensityLight = analogRead(_analog);
    /* <<END> */

    /* Air Quality */
    digitalWrite(_S0, LOW);
    digitalWrite(_S1, HIGH);
    digitalWrite(_S2, LOW);
    delay(100);
    airQuality = analogRead(_analog);
    /* <<END> */

    /* Serial Print */
    Serial.println("Temperature = " + (String) Temperature + " *C");
    Serial.println("Pressure = " + (String) Pressure + " Pa");                /*Absolute or Actual Ambient Temperature. It will vary with both altitude and weather */
    Serial.println("Altitude = " + (String) Altitude + " meters");
    Serial.println("Pressure (sealevel) = " + (String) CalcPressure + " Pa"); /* Adjusted Pressure */
    Serial.println("Real altitude = " + (String) RealAltitude + " meters");
    Serial.println("Temperature11 (*C): " + (String) temperature11);
    Serial.println("Humidity: " + (String) humidity + " %");
    Serial.println("Rain:" + (String)intensityRain);
    Serial.println("Light Intensity:" + (String) intensityLight);
    Serial.println("Air Quality:" + (String) airQuality); 
    Serial.println();
    /* <<END> */

    /* ThingSpeak */
    ThingSpeak.setField(1, (float) Temperature);
    ThingSpeak.setField(2, (float) Pressure);
    ThingSpeak.setField(3, (float) Altitude);
    ThingSpeak.setField(4, (float) CalcPressure);
    ThingSpeak.setField(5, humidity);
    ThingSpeak.setField(6, (float) intensityRain);
    ThingSpeak.setField(7, (float) intensityLight);
    ThingSpeak.setField(8, (float) airQuality);

    ThingSpeak.writeFields(channel_ID, write_API_Key);
    /* <<END> */
    delay(1100);
    float maxT = ThingSpeak.readFloatField(channel2_ID, 1, write_API2_Key);
    delay(1100);
    float minT = ThingSpeak.readFloatField(channel2_ID, 2, write_API2_Key);
        delay(1100);
    float RealFeel = ThingSpeak.readFloatField(channel2_ID, 5, write_API2_Key);
    delay(1100);
    float dewPoint = ThingSpeak.readFloatField(channel2_ID, 4, write_API2_Key);  

    Serial.println("maxT:" + (String) maxT);
    Serial.println("MinT:" + (String) minT);
    Serial.println("RealFeel:" + (String) RealFeel);
    Serial.println("DewPoint" + (String) dewPoint);
    Serial.println();

    if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
   
    http.begin(client,serverName);
    
   
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    // Prepare your HTTP POST request data
    String httpRequestData = "api_key=" + apiKeyValue + "&Temprature=" + (float) Temperature
                          + "&Humidity=" + humidity + "&Pressure=" + (float) Pressure
                          + "&Altitude=" +float(Altitude) + "&Light=" + intensityLight +"&Rain=" +intensityRain + "&AirQuality=" + (float) airQuality + "&RealFeel=" + RealFeel + "&DewPoint=" + dewPoint;
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
   
 
    int httpResponseCode = http.POST(httpRequestData);
     
 
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
 
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
 
    delay(12000);
}
