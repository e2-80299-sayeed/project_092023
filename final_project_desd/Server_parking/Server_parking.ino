#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266HTTPClient.h>

#define TRIGGER_PIN D1
#define ECHO_PIN D2

const char *ssid = "MotoG62";
const char *password = "12345678";

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
Serial.flush();
Serial.println("Serial Setup is completed");

WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);

Serial.print("connecting to WiFi");
while(WiFi.status() != WL_CONNECTED){
    delay(50);
    Serial.print(".");     
 }

 Serial.println("WiFi is connected");
 Serial.print("IP Address : ");
 Serial.println(WiFi.localIP());

pinMode(TRIGGER_PIN, OUTPUT);
pinMode(ECHO_PIN, INPUT);
pinMode(D6,OUTPUT);
pinMode(D7,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 long duration, distance;
 String body;
 int value,slot_no=2;
  
  // Trigger ultrasonic sensor
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Measure the duration of the echo
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in centimeters
  distance = duration * 0.034 / 2;

  // Print the distance to the Serial Monitor
  Serial.print("\nDistance: ");
  Serial.print(distance);
  Serial.println(" cm");
  

if(distance > 10)
  {
    Serial.print("Slot: Empty");
    value = 0;
    digitalWrite(D6, LOW);//RED
    delay(50);
    digitalWrite(D7, HIGH);//GREEN
    delay(50);
    body = "{ \"slot_no\":" + String(slot_no) + " ,\"slot_status\": \"Empty\"  }";
    Serial.print("\nvalue :");
    Serial.print(value);
    
  }
else  
  {
    Serial.print("Slot: Full");
    value = 1;
    digitalWrite(D6, HIGH);//RED
    delay(50);
    digitalWrite(D7, LOW);//GREEN
    delay(50);
    Serial.print("\nvalue :");
    Serial.print(value);
    body = "{ \"slot_no\":" + String(slot_no) + " ,\"slot_status\": \"Full\"  }";
    //body = "{ \"slot_status\":" + String(value) + " }";
  }


HTTPClient httpclient;
WiFiClient wificlient;
httpclient.begin(wificlient, "http://192.168.223.105:5000/slot");
httpclient.addHeader("content-type", "application/json");
int statuscode = httpclient.PUT(body);
Serial.printf("\nStatus code : %d\n", statuscode);

delay(2000);

}
