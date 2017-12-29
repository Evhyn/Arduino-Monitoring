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

char server[] = "192.168.123.101"; // IMPORTANT: If you are using XAMPP you will have to find out the IP address of your computer and put it here (it is explained in previous article). If you have a web page, enter its address (ie. "www.yourwebpage.com")
EthernetClient client;

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
  
  // Connect to the server (your computer or web page)  
  if (client.connect(server, 80)) {
    client.print("GET /Insert_data.php?"); // This
    client.print("value1="); // This
    client.print(temp); // And this is what we did in the testing section above. We are making a GET request just like we would from our browser but now with live data from the sensor
    client.print("&value2=");
    client.print(hum);// This
    client.println(" HTTP/1.1"); // Part of the GET request
    client.println("Host: 192.168.123.100"); // IMPORTANT: If you are using XAMPP you will have to find out the IP address of your computer and put it here (it is explained in previous article). If you have a web page, enter its address (ie.Host: "www.yourwebpage.com")
    client.println("Connection: close"); // Part of the GET request telling the server that we are over transmitting the message
    client.println(); // Empty line
    client.println(); // Empty line
    client.stop();    // Closing connection to server

  }

  else {
    // If Arduino can't connect to the server (your computer or web page)
    Serial.println("--> connection failed\n");
  }
 
  // Give the server some time to recieve the data and store it. I used 10 seconds here. Be advised when delaying. If u use a short delay, the server might not capture data because of Arduino transmitting new data too soon.
  delay(5000);
}
