# UMRT RC Object Avoiding Car

## Overview
This project is a Bluetooth-controlled RC car equipped with obstacle avoidance functionality. Built using the ESP32 microcontroller, the car is designed to navigate autonomously and avoid obstacles using an ultrasonic sensor. It can be controlled remotely through a smartphone via Bluetooth.

## Features
- **Bluetooth Control**: Operate the car remotely using a smartphone.
- **Obstacle Avoidance**: Automatically stops when an obstacle is detected within 20 cm.
- **Direction Control**: Move forward, backward, left, and right via Bluetooth commands.
- **Ultrasonic Sensor**: Measures the distance to obstacles and ensures collision avoidance.

## Hardware Components
- ESP32 microcontroller
- DC Motors (2x)
- Ultrasonic Sensor (HC-SR04)
- Motor Driver
- Chassis with wheels
- Bluetooth Module (integrated in ESP32)

## Software
The control software is written in C++ using the Arduino IDE. It integrates:
- **BluetoothSerial Library**: For Bluetooth communication.
- **NewPing Library**: To manage the ultrasonic sensor for obstacle detection.

## How It Works
1. **Bluetooth Pairing**: The car connects to a smartphone via Bluetooth.
2. **Obstacle Detection**: The ultrasonic sensor continuously monitors the distance to objects.
3. **Motor Control**: Based on Bluetooth commands or obstacle detection, the car's motors change direction or stop.

### Main Controls:
- `U`: Move Forward
- `D`: Move Backward
- `L`: Turn Left
- `R`: Turn Right
- `S`: Stop

If an obstacle is detected within 25 cm, the car will stop automatically to avoid collisions.

## Setup Instructions
1. Assemble the car and connect all components to the ESP32.
2. Upload the code to the ESP32 using Arduino IDE.
3. Pair your smartphone with the ESP32 via Bluetooth (PIN: 1234).
4. Use a Bluetooth controller app to send commands (`U`, `D`, `L`, `R`, `S`) to control the car.

## Code Example
```cpp
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
}
```

## Team
- **MD Habibulla Misba**
- **Nazmul Hasan Athin**
- **Naeem Abdullah Sadik**
- **Abdullah Khan**

## License
This project is open-source and available under the MIT License.
