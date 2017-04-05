/*****************************************************************************
single_sensor.ino
Written By:  Sara Damiano (sdamiano@stroudcenter.org)
Development Environment: PlatformIO 3.2.1
Hardware Platform: EnviroDIY Mayfly Arduino Datalogger
Software License: BSD-3.
  Copyright (c) 2017, Stroud Water Research Center (SWRC)
  and the EnviroDIY Development Team

This sketch is an example of getting data from a single sensor, in this case, a
MaxBotix Ultrasonic Range Finder

DISCLAIMER:
THIS CODE IS PROVIDED "AS IS" - NO WARRANTY IS GIVEN.
*****************************************************************************/

// ---------------------------------------------------------------------------
// Include the base required libraries
// ---------------------------------------------------------------------------
#include <Arduino.h>
#include <SensorBase.h>
#include <MaxBotixSonar.h>

// ---------------------------------------------------------------------------
// Set up the sensor object
// ---------------------------------------------------------------------------

// MaxBotix Sonar: pin settings
const int SonarPower = 22;   // excite (power) pin
const int SonarData = 10;     // data  pin
const int SonarTrigger = -1;   // Trigger pin

// Create a new instance of the sonar_range object;
MaxBotixSonar_Range sonar(SonarPower, SonarData, SonarTrigger);

// ---------------------------------------------------------------------------
// Board setup info
// ---------------------------------------------------------------------------
const int SERIAL_BAUD = 9600;  // Serial port BAUD rate
const int GREEN_LED = 8;  // Pin for the green LED
const int RED_LED = 9;  // Pin for the red LED

// Flashes to Mayfly's LED's
void greenred4flash()
{
  for (int i = 1; i <= 4; i++) {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    delay(50);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    delay(50);
  }
  digitalWrite(RED_LED, LOW);
}

// ---------------------------------------------------------------------------
// Main setup function
// ---------------------------------------------------------------------------
void setup()
{
    // Start the primary serial connection
    Serial.begin(SERIAL_BAUD);

    // Set up pins for the LED's
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    // Blink the LEDs to show the board is on and starting up
    greenred4flash();

    // Print a start-up note to the first serial port
    Serial.println(F("Single Sensor Example - Sonar Ranging"));

    // Set up the sensor
    sonar.setup();

}


// ---------------------------------------------------------------------------
// Main loop function
// ---------------------------------------------------------------------------
void loop()
{
    // Power the sensor
    digitalWrite(SonarPower, HIGH);

    // Turn on the LED to show we're taking a reading
    digitalWrite(GREEN_LED, HIGH);

    // Update the sensor value
    sonar.update();

    // Print the sonar result
    Serial.print("Dat recieved from sonar: ");
    Serial.println(sonar.getValueString());

    // Turn of sensor power
    digitalWrite(SonarPower, LOW);

    // Turn off the LED to show we're done with the reading
    digitalWrite(GREEN_LED, LOW);

    // Wait for the next reading
    delay(5000);
}