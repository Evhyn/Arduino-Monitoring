#include <ESP8266WiFi.h>
#include <DHT.h>

const char* ssid     = "VictoriaAlsut-WDS-Wifi"; // Your ssid
const char* password = "webdata7"; // Your Password



WiFiServer server(80);
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

long previousMillis = 0;
unsigned long currentMillis = 0;
long interval = 250; // READING INTERVAL
int temperature = 0;
int humidity = 0;

int temp = 0;  // TEMPERATURE VAR
int hum = 0;  // HUMIDITY VAR


void setup() {
Serial.begin(115200);
delay(10);
Serial.println();

// Connect to WiFi network
WiFi.mode(WIFI_STA);
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);

WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");

// Start the server
server.begin();
Serial.println("Server started");

// Print the IP address
Serial.println(WiFi.localIP());

  dht.begin();
  delay(1000);
  hum = (int) dht.readHumidity(); 
  temp = (int) dht.readTemperature(); 


}

void loop() {

  currentMillis = millis();
  if(currentMillis - previousMillis > interval) { // READ ONLY ONCE PER INTERVAL
    previousMillis = currentMillis;
    hum = (int) dht.readHumidity();
    temp = (int) dht.readTemperature();
  }
  

WiFiClient client = server.available();
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("Connection: close");  // the connection will be closed after completion of the response
client.println("Refresh: 5");  // refresh the page automatically every 5 sec
client.println();
client.println("<!DOCTYPE html>");
client.println("<html>");
client.println("<title>ESP8266 Temperature & Humidity DHT11 Sensor</title>");
client.println("<h1>Temperature:</h1> ");
client.println("<h1>");
client.print(temp);
client.println("</h1> ");
client.println("<h1>Humidity:</h1> ");
client.println("<h1>");
client.print(hum);
client.println("</h1> ");
client.println("</html>");
delay(5000); //delay for reread
}
