#include <DHT.h>
#include <ESP8266WiFi.h>
#include "AdafruitIO_WiFi.h"

#define DHTPIN 2
#define DHTTYPE DHT11

#define WIFI_SSID     "SSID" // WIFI SSID TO CONNECT TO
#define WIFI_PASS     "PASSWORD" // PASSWORD OF WIFI
 
#define IO_USERNAME  "USERNAME" //AdafruitIO username
#define IO_KEY       "KEY" //AdafruitIO KEY
 
// Connect to Wi-Fi and Adafruit IO handel 
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
 
// Create a feed object that allows us to send data to
AdafruitIO_Feed *temperatureFeed = io.feed("temperature"); // This temperature is the feed name u have set in Adafruit site.
AdafruitIO_Feed *humidityFeed = io.feed("humidity"); //This temperature is the feed name u have set in Adafruit site.

DHT dht(DHTPIN, DHTTYPE);
 
void setup() 
{
  // Enable the serial port so we can see updates
  Serial.begin(115200);
 
  // Connect to Adafruit IO
  io.connect();
  Serial.print("connected..to IO");
  dht.begin();
  Serial.print("DHT enabled");
 
  // wait for a connection
  while(io.status() < AIO_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
}
 
void loop() 
{
  
  io.run();
 
  // Send 10 to our Workshop Temperature Feed
  temperatureFeed->save(dht.readTemperature()); // Read temperature and send to feed.
  humidityFeed->save(dht.readHumidity()); // Read Humidity and send to feed
 
  // This is so we can see  response on the computer
  Serial.print("Data sent");
 
  // Data will be sent after every 5Sec ( Please DO NOT send data very quickly as the Adafruit api is rate limited )
  delay(5000);
}
