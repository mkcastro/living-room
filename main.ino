#include <Servo.h>

// pins
const int buzzerPin = 9;
const int emergencyButtonPin = 8;
const int servoPin = 2;

// variables
int onAngle;
int offAngle;
Servo servo; // create servo object to control a servo
bool lightState;
bool previousLightState;

// calibration
const int offsetAngle = 25;
const int parkAngle = 90;

void setup()
{
    onAngle = parkAngle + offsetAngle;
    offAngle = parkAngle - offsetAngle;

    servo.attach(servoPin);
    servo.write(parkAngle);
}

void loop()
{
    if (lightsToggled())
    {
        toggleLights();
    }

    if (emergency())
    {
        performEmergencyMeasures();
    }

    delay(300);
}

bool lightsToggled()
{
    return lightState != previousLightState;
}

void toggleLights()
{
    lightState = !lightState;

    if (lightState)
    {
        turnOnLights();
    }
    else
    {
        turnOffLights();
    }

    servo.write(parkAngle);
    previousLightState = lightState;
}

bool emergency()
{
    return digitalRead(emergencyButtonPin);
}

void performEmergencyMeasures()
{
    blareAlarm();
}

void blareAlarm()
{
    tone(buzzerPin, 1000); // Send 1KHz sound signal...
    delay(1000);           // ...for 1 sec
    noTone(buzzerPin);     // Stop sound...
    delay(1000);           // ...for 1sec
}

void turnOnLights()
{
    Serial.println("ON");
    servo.write(onAngle);
}

void turnOffLights()
{
    Serial.println("OFF");
    servo.write(offAngle);
}
