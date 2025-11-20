#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

// BNO055-Objekt anlegen
Adafruit_BNO055 bno = Adafruit_BNO055(55);

void setup() {
    Serial.begin(9600);
    pinMode(2, INPUT);

    if (!bno.begin()) {
        Serial.println("BNO055 nicht gefunden! Bitte Verkabelung prüfen.");
        while (1);
    }

    delay(1000);  // Sensor initialisieren lassen
    bno.setExtCrystalUse(true);
}

int value;
bool pressedA;

void loop() {
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

    double pitch = -euler.z();
    if (pitch < -40) {
        pitch = -40;
    } else if (pitch > 40) {
        pitch = 40;
    }

    int newValue = (pitch + 40) * 20;
    if (newValue != value) {
        value = newValue;
        Serial.print("X ");
        Serial.println(value);
    }

    if (!pressedA && digitalRead(2)) {
        pressedA = true;
        Serial.println("A");
    }
    if (pressedA && !digitalRead(2)) {
        pressedA = false;
        Serial.println("a");
    }

    delay(100);
}

