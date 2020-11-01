#include <Servo.h>
#include <ezButton.h>

// pins
const int buzzerPin = 9;
const int emergencyButtonPin = 8;
const int servoPin = 3;
const int lightSwitchPin = 4;

// variables
int onAngle;
int offAngle;
Servo servo; // create servo object to control a servo
ezButton lightButton(lightSwitchPin);
bool lightState;
bool previousLightState = LOW;

// calibration
const int offsetAngle = 25;
const int parkAngle = 90;

void setup()
{
    onAngle = parkAngle + offsetAngle;
    offAngle = parkAngle - offsetAngle;

    lightButton.setDebounceTime(50); // set debounce time to 50 milliseconds

    servo.attach(servoPin);
    servo.write(parkAngle);
}

void loop()
{
    lightButton.loop(); // MUST call the loop() function first

    if (lightButton.isPressed())
    {
        lightState = !lightState;
    }

    if (!goalReached())
    {
        handle();
    }

    previousLightState = lightState;
}

void handle() {
    if (lightState)
    {
        turnOffLights();
    }
    else {
        turnOnLights();
    }

    delay(250);
    servo.write(parkAngle);
}

bool goalReached() {
    return previousLightState == lightState;
}

bool lightsToggled()
{
    return digitalRead(lightSwitchPin) != previousLightState;
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
