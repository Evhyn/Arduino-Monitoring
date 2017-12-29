#include <SPI.h>
#include <Ethernet.h>
#include <DHT.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
 
// Enter the IP address for Arduino, as mentioned we will use 192.168.0.16
// Be careful to use , insetead of . when you enter the address here
IPAddress ip(192,168,123,100);


#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Initialize the Ethernet server library
EthernetServer server(80);

long previousMillis = 0;
unsigned long currentMillis = 0;
long interval = 250; // READING INTERVAL
int temperature = 0;
int humidity = 0;

int temp = 0;  // TEMPERATURE VAR
int hum = 0;  // HUMIDITY VAR

void setup() {
 
 // Serial.begin starts the serial connection between computer and Arduino
  Serial.begin(9600);
 
 // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("Arduino server IP address: ");
  Serial.println(Ethernet.localIP());
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
  
  EthernetClient client = server.available();  // Listen for incoming clients
 
  if (client) {
    
   // When a client sends a request to a webserver, that request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        
       // This line is used to send communication information between Arduino and your browser over Serial Monitor
        Serial.write(c);
        
       // When the request has ended send the client a reply
        if (c == '\n' && currentLineIsBlank) {
          
         // We send the HTTP response code to the client so it knows that we will send him HTML data
         // and to refresh the webpage every 5 seconds
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println("Refresh: 5");
          client.println();
         // Here we write HTML data (for the page itself) which will be sent to the client.
         // The HTML includes Javascript which fills the data
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<title>Arduino sensor data</title>");
          client.println("<h1>Temperature:</h1> ");
          client.println("<h1>");
          client.print(temp);
          client.println("</h1> ");
          client.println("<h1>Humidity:</h1> ");
          client.println("<h1>");
          client.print(hum);
          client.println("</h1> ");
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // Check if a new line is started
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // If a new line was not strated
          currentLineIsBlank = false;
        }
      }
    }
    // Give the client some time to recieve the data (1ms)
    delay(2000);
    // In the end close the connection
    client.stop();
  }
}
