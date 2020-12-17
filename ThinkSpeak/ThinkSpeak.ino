#include <DHT.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>     //https://github.com/tzapu/WiFiManager
#include <ThingSpeak.h>
#define ESP_AP_NAME "Wemos Lab"
WiFiServer server(80);
// ค่าต่างๆของ DHT11
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

WiFiClient client;
unsigned long Channel_ID = 1259389;
const char * API_Key = "N6SV7GKRUQLPFFOS";
uint8_t temp, humi;


void setup()
{
  Serial.begin(9600);
  dht.begin();
  Serial.println();
  Serial.println();
  WiFiManager wifiManager;
  wifiManager.autoConnect(ESP_AP_NAME);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  ThingSpeak.begin(client);
}

unsigned long timer = millis();
void loop() {
  WiFiClient client = server.available();
  temp = dht.readTemperature();
  humi = dht.readHumidity();
  if (millis() - timer >= 1000) {
    timer += 1000;
    ThingSpeak.writeField(Channel_ID, 1, temp, API_Key);
    ThingSpeak.writeField(Channel_ID, 2, humi, API_Key);
    Serial.print("  ");
    Serial.print("Humidity is :");
    Serial.print(temp);
    Serial.print("%");
    Serial.print("  ");
    Serial.print("Temperature is :");
    Serial.print(humi);
    Serial.println(" C");

  }

}
