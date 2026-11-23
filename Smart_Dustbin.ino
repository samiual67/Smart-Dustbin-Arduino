#include <Servo.h>

Servo lidServo; // Create Servo object to control the dustbin lid

// =========================================================================
// PIN CONFIGURATION (Verified Hardware Mapping)
// =========================================================================
const int servoPin  = 5;  // PWM Pin D5  -> SG90 Servo Motor Signal (Orange)
const int trigPin1  = 6;  // Pin D6      -> Outer HC-SR04 Trig (Hand Detection)
const int echoPin1  = 7;  // Pin D7      -> Outer HC-SR04 Echo (Hand Detection)

const int trigPin2  = 9;  // Pin D9      -> Inner HC-SR04 Trig (Bin Fill Level)
const int echoPin2  = 10; // Pin D10     -> Inner HC-SR04 Echo (Bin Fill Level)
const int ledPin    = 11; // Pin D11     -> Red LED Anode (via 330 Ohm Resistor)
const int buzzerPin = 12; // Pin D12     -> Active Buzzer Positive (Yellow)

// =========================================================================
// CALIBRATION THRESHOLDS (in centimeters)
// =========================================================================
const int handDistanceLimit = 20; // Open lid if hand is within 20 cm
const int binFullLimit      = 8;  // Trigger Full Alert if waste is within 8 cm of lid

void setup() {
  // Configure Ultrasonic Sensor I/O pins
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  // Configure Visual & Acoustic Indicator pins
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Attach Servo Motor and initialize to Closed position (0 degrees)
  lidServo.attach(servoPin);
  lidServo.write(0);
}

// Helper function to measure distance in cm using Time-of-Flight (ToF)
long getDistance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);   // Send 10us ultrasonic trigger pulse
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // Measure echo return duration with a 30ms timeout
  long duration = pulseIn(echo, HIGH, 30000);
  if (duration == 0) return 999; // Return 999 cm if out of range
  return duration * 0.034 / 2;   // Convert duration to centimeters
}

void loop() {
  long binLevel = getDistance(trigPin2, echoPin2); // Measure internal waste level
  long handDist = getDistance(trigPin1, echoPin1); // Measure external hand proximity

  // 1. BIN FULL MONITORING: Turn ON Red LED & Buzzer when waste <= 8 cm
  if (binLevel <= binFullLimit && binLevel > 0) {
    digitalWrite(ledPin, HIGH); // Illuminate Red LED warning light
    tone(buzzerPin, 1000);      // Emit 1000 Hz audio alert
  } else {
    digitalWrite(ledPin, LOW);  // Turn OFF Red LED
    noTone(buzzerPin);          // Mute Buzzer
  }

  // 2. TOUCHLESS LID ACTUATION: Open lid when hand <= 20 cm (even when full)
  if (handDist <= handDistanceLimit && handDist > 0) {
    lidServo.write(90);         // Rotate servo to 90 degrees (Lid Open)
    delay(3000);                // Keep lid open for 3 seconds
  } else {
    lidServo.write(0);          // Return servo to 0 degrees (Lid Closed)
  }

  delay(100); // Short stability delay before next cycle
}
