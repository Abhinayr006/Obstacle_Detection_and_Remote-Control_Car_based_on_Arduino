🚗 Arduino Robot Car with Bluetooth Control + Obstacle Avoidance

This project is a 4-wheel robot car built using an Arduino, Adafruit Motor Shield, ultrasonic sensor, and a servo for scanning. The robot can operate in multiple modes using Bluetooth commands sent from a mobile app.

📱 Bluetooth Control via Mobile App

I used the “Arduino Bluetooth Controller” app (v1.7) from the Google Play Store to control the car.
The app sends customized characters through Bluetooth such as:

A – Normal Bluetooth control

O – Emergency Stop mode

T – Bluetooth + Obstacle Avoidance

X – Stop

F, B, L, R, S – Direction commands

These commands are received by the Arduino through the HC-05/HC-06 Bluetooth module and are used to control the robot's movement.

✨ Main Features
1. Manual Bluetooth Control

The robot responds to commands:

F → Forward

B → Backward

L → Turn Left

R → Turn Right

S → Stop

2. Ultrasonic Obstacle Detection

A servo-mounted ultrasonic sensor rotates to check left and right distances.
This enables the robot to navigate around obstacles automatically.

3. Obstacle Avoidance Mode

When enabled, the robot:

Stops when an obstacle is within a set distance

Moves backward slightly

Scans left and right

Turns toward the side with more free space

Continues driving forward

4. Emergency Stop Mode

Even during manual control, the robot automatically stops and backs away if an obstacle is dangerously close.

5. Combined Mode

Allows normal Bluetooth control while still preventing collisions.

🔧 How It Works

Four DC motors are driven by the Adafruit Motor Shield.

The ultrasonic sensor measures distance using trigger/echo pulses.

A servo rotates the sensor to scan at 20°, 103°, and 180°.

The main loop checks which mode is activated and runs the corresponding function.
