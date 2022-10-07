/*versi blynk 2.0*/
/*sensor dht11 dengan blynk*/
#define BLYNK_TEMPLATE_ID "TMPLnVxg5S-_"
#define BLYNK_DEVICE_NAME "dht11"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <DHT.h>

char auth[] = "gSBiH9BGdk8sOMw1996M3cNSaGWXEYyc";
char ssid[] = "WIFI UiN";  // type your wifi name
char pass[] = "123456789";  // type your wifi password

BlynkTimer timer;


#define DHTPIN D7 //Connect Out pin to D2 in NODE MCU
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  Serial.print("Temperature : ");
  Serial.print(t);
  Serial.print("    Humidity : ");
  Serial.println(h);

}
void setup()
{
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  dht.begin();
  timer.setInterval(100L, sendSensor);

}

void loop()
{
  Blynk.run();
  timer.run();
}
