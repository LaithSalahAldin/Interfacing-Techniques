// C++ code
int old_ultrasonic_sensor_reading = 0;
int ultrasonic_sensor_reading = 0;
int old_potentiometer_reading = 0;
int potentiometer_reading = 0;

int threshold = 0;


long readUltrasonicDistance(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

void setup() {
  Serial.begin(9600);
  pinMode(A4, INPUT);	// Potentiometer pin
  pinMode(2, OUTPUT);	// Green LED pin
  pinMode(4, OUTPUT);	// Yellow LED pin
  pinMode(7, OUTPUT);	// Red LED pin
  pinMode(11, OUTPUT); // Trigger pin
  pinMode(10, INPUT);  // Echo pin
}

void loop() {
  // Reset threshold at the beginning of each loop
  threshold = 20;

  // Read ultrasonic distance
  // Constant 0.01723 is used to convert microseconds to centimeters
  ultrasonic_sensor_reading = 0.01723 * readUltrasonicDistance(11, 10);
  if(ultrasonic_sensor_reading != old_ultrasonic_sensor_reading)
  	Serial.println("Ultrasonic Reading: " + String(ultrasonic_sensor_reading));
  old_ultrasonic_sensor_reading = ultrasonic_sensor_reading;
  
  // Read potentiometer value
  potentiometer_reading = analogRead(A4);
  threshold = (potentiometer_reading/1023.0) * 200 + 20;
  if(potentiometer_reading != old_potentiometer_reading)
  	Serial.println("Potentiometer Reading: " + String(potentiometer_reading));
  old_potentiometer_reading = potentiometer_reading;
  
  // Turn off the LEDs
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(7, LOW);

  // LED control based on distance
  if (ultrasonic_sensor_reading > threshold)
      digitalWrite(2, HIGH);
  else if(ultrasonic_sensor_reading >= threshold / 2)
  	  digitalWrite(4, HIGH);
  else
      digitalWrite(7, HIGH);
  
  delay(200); // Delay a little bit to improve simulation performance
}
