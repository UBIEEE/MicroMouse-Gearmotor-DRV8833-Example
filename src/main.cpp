#include <Arduino.h>

#include <Button.hpp>
#include <Drive.hpp>

static const int kButtonPin = 10;
static Button button;

void setup() {
  Serial.begin(9600);

  driveSetup();
  button.setupDefaultLow(kButtonPin, true);
}

void loop() {
  // Use the button to control the drivetrain for demo
  if (button.isPressed()) {
    driveSetRawSpeeds(0.25, 0.25);
  } else {
    driveStop();
  }

  driveLoop();

  delay(10);

  static int count = 0;
  if ((++count * 10) % 250 == 0) { // Print every 250ms
    float leftEncoderDistance = driveGetLeftEncoderDistance();
    float rightEncoderDistance = driveGetRightEncoderDistance();
    float leftEncoderVelocity = driveGetLeftEncoderVelocity();
    float rightEncoderVelocity = driveGetRightEncoderVelocity();

    Serial.print("Left Distance: ");
    Serial.print(leftEncoderDistance);
    Serial.print(" Right Distance: ");
    Serial.print(rightEncoderDistance);
    Serial.print(" Left Velocity: ");
    Serial.print(leftEncoderVelocity);
    Serial.print(" Right Velocity: ");
    Serial.print(rightEncoderVelocity);
    Serial.println();
  }
}
