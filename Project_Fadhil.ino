#include <WiFi.h>
#include <WiFiClient.h>
#include <DHT.h>
#include <ThingSpeak.h>
#define DHTTYPE DHT11
#define DHTPIN 32
const char *ssid = "xxx";
const char *pass = "akatsuki";
WiFiClient client;
DHT dht(DHTPIN, DHTTYPE);
long myChannelNumber = 2193919;
const char myWriteAPIKey[] = "ELZ8KLCWWZT7640C";
void setup() {
Serial.begin(9600);
WiFi.begin(ssid, pass);
while(WiFi.status() != WL_CONNECTED)
{
delay(200);
Serial.print("..");
}
Serial.println();
Serial.println("NodeMCU is connected!");
Serial.println(WiFi.localIP());
dht.begin();
ThingSpeak.begin(client);
}
void loop() {
float t = dht.readTemperature();
Serial.println("Temperature: " + (String) t);
ThingSpeak.writeField(myChannelNumber, 1, t, myWriteAPIKey);
delay(2000);
}