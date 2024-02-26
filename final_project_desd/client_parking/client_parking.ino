#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>
#include<SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


  int slots = 2;
  String slot1;
  String slot1_status;
  String slot2;
  String slot2_status;
  int slot_1 = 0;
  int slot_2 = 0;
LiquidCrystal_I2C lcd(0x27,16,2);

// SCL - D1
// SDA - D2


#define TX D5
#define RX D6

SoftwareSerial uart(RX,TX);


const char* ssid = "MotoG62";
const char* password = "12345678";

//Your Domain name with URL path or IP address with path
const char* serverName = "http://192.168.223.203:5000/slot";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 1000;

String sensorReadings;
String sensorReadingsArr[20];

void setup() {
  Serial.begin(115200);
  uart.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    lcd.setCursor(11,0);
    lcd.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  lcd.clear();
  lcd.setCursor(0,0)
  lcd.print("Connect to Wifi");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");

lcd.init();  
lcd.backlight();
  
}

void loop() {
  // Send an HTTP POST request depending on timerDelay
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
              
      sensorReadings = httpGETRequest(serverName);
      Serial.println(sensorReadings);
      JSONVar myObject = JSON.parse(sensorReadings);
  
      // JSON.typeof(jsonVar) can be used to get the type of the var
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }
    
      Serial.print("JSON object = ");
      Serial.println(myObject);
    
      // myObject.keys() can be used to get an array of all the keys in the object
      JSONVar keys = myObject.keys();
    
      for (int i = 0; i < keys.length(); i++) {
        JSONVar value = myObject[keys[i]];
        sensorReadingsArr[i] = String(value);
      }
      Serial.print("slot_no = ");
      Serial.println(sensorReadingsArr[0]);
      Serial.print("slot_status = ");
      Serial.println(sensorReadingsArr[1]);

      slot1 = sensorReadingsArr[0];
      slot1_status = sensorReadingsArr[1];

      Serial.print("slot_no = ");
      Serial.println(sensorReadingsArr[2]);
      Serial.print("slot_status = ");
      Serial.println(sensorReadingsArr[3]);

      slot2 = sensorReadingsArr[2];
      slot2_status = sensorReadingsArr[3];

      if(slot1_status == "Empty" && slot2_status == "Empty" )
      {
        slots = 2;
      }
      else if(slot1_status == "Full" && slot2_status == "Empty")
      {
        slots = 1;
      }
      else if(slot1_status == "Empty" && slot2_status == "Full")
      {
        slots = 1;
      }
      else 
      {
        slots = 0;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Sorry no slots:(");
        delay(2000);
      }


      if(slot1 == "1" &&  slot1_status == "Full" )
      {
        slot_1 = 1;
        
      }
      else
      {
        slot_1 = 0;
        //slots = slots + 1;
      }
      if(slot2 == "2" &&  slot2_status == "Full" )
      {
        slot_2 = 1; 
      }
      else 
      {
        slot_2 = 0;
      }
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("  Welcome to");
      lcd.setCursor(0,1);
      lcd.print("   Sunbeam :)");
      delay(2000);
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("   Smart ");
      lcd.setCursor(0,1);
      lcd.print(" Parking System");
      delay(2000);


      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print(" Avail slots:");
      lcd.print(slots);
      lcd.setCursor(0,1);
      lcd.print(" S1 = ");
      lcd.print(slot_1); 
      lcd.setCursor(8,1);
      lcd.print(" S2 = ");
      lcd.print(slot_2); 
      delay(2000);
      
      //uart.write((char*)&s1, sizeof(s1));
    
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(client, serverName);
  
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
