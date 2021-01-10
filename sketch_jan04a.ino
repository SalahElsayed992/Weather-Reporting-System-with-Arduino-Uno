
#include <DHT.h>
#include <DHT_U.h>

#define dhtpin 4
#define dht_type DHT11
DHT dht(dhtpin, dht_type);
// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP8266_SOFTSERIAL_POINT
#include <SoftwareSerial.h>
#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL_RX 2
#define REMOTEXY_SERIAL_TX 3
#define REMOTEXY_SERIAL_SPEED 9600
#define REMOTEXY_WIFI_SSID "Salah Elsayed"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,0,0,33,0,76,0,10,16,0,
  67,4,35,17,23,6,2,26,11,129,
  0,39,9,13,6,8,72,101,97,116,
  0,129,0,35,26,26,6,8,72,117,
  109,105,100,105,116,121,0,67,4,34,
  35,26,7,2,26,11,129,0,33,44,
  30,6,8,82,97,105,110,32,76,101,
  118,101,108,0,67,4,34,52,29,6,
  2,26,11 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // output variables
  char text_1[11];  // string UTF8 end zero 
  char text_2[11];  // string UTF8 end zero 
  char text_3[11];  // string UTF8 end zero 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////
void setup() {
  RemoteXY_Init (); 
  Serial.begin(9600);
  dht.begin();
  Serial.println("Weather Reporting System");
}

void loop() {
   RemoteXY_Handler ();
  delay(2000);
  // humidity
  float h = dht.readHumidity();
  // Temperature 
  float t = dht.readTemperature();
  // Heat 
  float heat = dht.computeHeatIndex(t, h, false);
  int rain = analogRead(A0);
  if (isnan(h) || isnan(t) || isnan(rain) ){
      Serial.println("Can\'t read From DHT Sensor .....");
    }
  else{
    Serial.print("\nTemperature is : ");
    Serial.print(t);
    Serial.print("\nHumidity is : ");
    Serial.print(h);
    Serial.print("\nRain is : ");
    Serial.print(rain);
    Serial.println(" ");
    dtostrf(heat, 0, 2, RemoteXY.text_1); 
    dtostrf(h, 0, 2, RemoteXY.text_2); 
    dtostrf(rain, 0, 2, RemoteXY.text_3); 

}
}
