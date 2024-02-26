  //#include <Servo.h>

#define TRIGGER_PIN D1
#define ECHO_PIN D2
//#define SERVO_PIN D3

//Servo myservo;

void setup() {
  Serial.begin(115200);
  //myservo.attach(SERVO_PIN);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  long duration, distance;
  
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
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
 
if(distance > 6)
  Serial.print("Slot: Empty");

else
  Serial.print("Slot: Full");

  Serial.println(" ");
  // Wait for a moment before the next reading
  delay(500);
}
