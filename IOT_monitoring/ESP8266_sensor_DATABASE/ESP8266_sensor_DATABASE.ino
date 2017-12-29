
/***************************************************************************************
*    Title: Insert_data_php
*    Author: Evi Andrianto
*    Date: 27-Jan-17
*    Code version: v1.0
*
***************************************************************************************/




#include <ESP8266WiFi.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

char server[] = "192.168.123.100";

const char* ssid     = "Carrot"; // Your ssid
const char* password = "jussayur"; // Your Password


void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  //Serial.println();
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  dht.begin();
}
void loop() {

  delay(2000);

  float hum = dht.readHumidity();
  float temp = dht.readTemperature();

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(' ');
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.println();
  
  if (isnan(hum) || isnan(temp) || hum<37){
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

// Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;

  if (client.connect(server, httpPort)){

    String data1 = "value1=" + (String)temp;
    String data2 = "&value2=" + (String)hum;
    String url = "GET /Insert_data.php?" + data1 + data2 + " HTTP/1.1";
    client.println(url);
    client.println("Host: 192.168.123.100");
    client.println("Connection: close");
    client.println();
    client.println();
    client.stop();
  }
  else{
    Serial.println("--> connection failed\n");
  }
  
  //ESP.deepSleep(60U*60*1000000); //U for unsigned
  delay(1000); //for above sleep
}
