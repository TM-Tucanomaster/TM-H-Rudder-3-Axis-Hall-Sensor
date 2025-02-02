#include <Joystick.h>

// Joystick object definition
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
                   JOYSTICK_TYPE_MULTI_AXIS, 3, 2,  // 3 axes (X, Y, Z)
                   true, true, true, false, false, false,
                   true, false, false, false, false); // 'true' for Z rotation

const int button1Pin = 4;    // Pin for button 1 (e.g., digital pin 4)
const int button2Pin = 5;    // Pin for button 2 (e.g., digital pin 5)
const int hallSensor1Pin = A1;  // Pin for Hall sensor 1 (analog pin A1)
const int hallSensor2Pin = A2;  // Pin for Hall sensor 2 (analog pin A2)
const int hallSensor3Pin = A0;  // Pin for Hall sensor 3 (analog pin A0) - Z axis

void setup() {
  pinMode(button1Pin, INPUT_PULLUP);  // Configure the pin for button 1
  pinMode(button2Pin, INPUT_PULLUP);  // Configure the pin for button 2
  
  Joystick.begin();          // Initialize the Joystick library
}

void loop() {
  // Read values from the Hall sensors
  int hallValue1 = analogRead(hallSensor1Pin);  // Hall sensor 1 (A1)
  int hallValue2 = analogRead(hallSensor2Pin);  // Hall sensor 2 (A2)
  int hallValue3 = analogRead(hallSensor3Pin);  // Hall sensor 3 (A0) - Z axis

  // Map Hall sensor values to joystick range
  int mappedHallValueX = map(hallValue1, 810, 536, 0, 1023);  // For X-axis
  int mappedHallValueY = map(hallValue2, 643, 540, 0, 1023);  // For Y-axis
  int mappedHallValueZ = map(hallValue3, 209, 828, 0, 1023);  // For Z-axis

  // Set the mapped Hall values
  Joystick.setXAxis(mappedHallValueX); // X-axis
  Joystick.setYAxis(mappedHallValueY); // Y-axis
  Joystick.setZAxis(mappedHallValueZ); // Z-axis

  // Read the state of the buttons and update them on the joystick
  int buttonState1 = !digitalRead(button1Pin);  // Invert the value due to pull-up
  int buttonState2 = !digitalRead(button2Pin);  // Invert the value due to pull-up
  
  Joystick.setButton(0, buttonState1);  // Set the state of button 1
  Joystick.setButton(1, buttonState2);  // Set the state of button 2
  
  delay(10);  // Small delay to avoid excessive readings
}

