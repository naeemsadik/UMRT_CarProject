#include "BluetoothSerial.h"
#include <NewPing.h>

#define ENA 25
#define IN1 2
#define IN2 4
#define ENB 26
#define IN3 15
#define IN4 13
#define LED_RED 16
#define LED_GREEN 17

#define TRIGGER_PIN 5
#define ECHO_PIN 18
#define MAX_DISTANCE 200

const char *pin = "1234";

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

String device_name = "TODOS";

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(9600);
  SerialBT.begin(device_name);  //Bluetooth device name
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
//Serial.printf("The device with name \"%s\" and MAC address %s is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str(), SerialBT.getMacString()); // Use this after the MAC method is implemented
#ifdef USE_PIN
  SerialBT.setPin(pin);
  Serial.println("Using PIN");
#endif

  // Motor control pins as outputs
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  // Set motor A and B to stop initially
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(LED_GREEN, HIGH);
}
void forward() {
  unsigned int distance = sonar.ping_cm();

  if (distance <= 25) {
    stop();
    return;
  }

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 255);  // Adjust the speed as needed
  analogWrite(ENB, 255);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 255);  // Adjust the speed as needed
  analogWrite(ENB, 255);
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 255);  // Adjust the speed as needed
  analogWrite(ENB, 255);
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 255);  // Adjust the speed as needed
  analogWrite(ENB, 255);
}

void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void loop() {
  if (SerialBT.available() > 0) {

    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, HIGH);

    char command = SerialBT.read();  // Read the incoming character

    // Control the car based on the received command
    switch (command) {
      case 'U':
        forward();
        Serial.println("Forward");
        delay(100);
        break;
      case 'D':
        backward();
        Serial.println("Backward");
        delay(100);
        break;
      case 'L':
        left();
        Serial.println("Left");
        delay(100);
        break;
      case 'R':
        right();
        Serial.println("Right");
        delay(100);
        break;
      case 'S':
        stop();
        Serial.println("Stop");
        break;
      default:
        stop();
        break;
    }
  }
}
