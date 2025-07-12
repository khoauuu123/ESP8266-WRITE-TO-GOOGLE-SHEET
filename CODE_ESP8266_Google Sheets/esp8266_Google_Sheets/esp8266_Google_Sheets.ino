#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* host = "script.google.com";
const int httpsPort = 443;

String GAS_ID = "";

const char* ssid = "";
const char* password = "";


WiFiClientSecure client;

void setup() {
  Serial.begin(115200);
  delay(500);

  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  client.setInsecure();
}

void loop() {
  int nd = random(20,40);
  int dm = random(70,95);
  Serial.println(nd);
  Serial.println(dm);

  sendata(nd, dm);
  delay(4000);
}

void sendata(int c, int h){
  Serial.print("connecting to ");
  Serial.println(host);

  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  String url = "/macros/s/" + GAS_ID + "/exec?nhietdo=" + String(c) + "&doam=" + String(h);
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");
 Serial.println("OK");
}
