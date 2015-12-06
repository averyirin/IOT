
// Import required libraries
#include "ESP8266WiFi.h"

// WiFi parameters
const char* ssid = "dd-wrt";
const char* password = "";

int fullPin = 0;
int halfPin = 2;

const char* host = "192.168.1.125";

void setup() {

  // Start Serial
  Serial.begin(115200);
  pinMode(fullPin, INPUT);
  pinMode(halfPin, INPUT);
}

void loop() {
  // We start by connecting to a WiFi network
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
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    delay(16000);
    return;
  }

  int FULL = digitalRead(fullPin);
  delay(100);
  int HALF = digitalRead(halfPin);
  delay(100);


  String STATUS;
  Serial.println(String(FULL) + " FULL  " + String(HALF) + " HALF");
  if (FULL == 1 && HALF == 1) {
    STATUS = "FULL";
  } else if (FULL == 0 && HALF == 1) {
    STATUS = "HALF";
  } else if (FULL == 0 && HALF == 0) {
    STATUS = "EMPTY";
  }
  Serial.println(STATUS);
  client.print(String("GET /vanguard/index.php?status=") + STATUS + " HTTP/1.1\r\n" +
               "Host: " + "127.0.0.1" + "\r\n" +
               "Connection: close\r\n\r\n");

  Serial.print(String("GET /vanguard/index.php?status=") + STATUS + " HTTP/1.1\r\n" +
               "Host: " + "127.0.0.1" + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(10);
  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();
  Serial.println("closing connection");

  // ESP.deepSleep(5000000, WAKE_RF_DEFAULT);
  delay(15000);
}

