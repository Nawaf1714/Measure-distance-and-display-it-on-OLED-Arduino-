# Measure-distance-and-display-it-on-OLED-Arduino-
This code is written in Arduino/C++ and uses an Ultrasonic Sensor to measure the distance, and displays the result on an OLED display using the `Adafruit_SSD1306` library. Let's explain the code step by step:

### Libraries used:
```cpp
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
```
- `Wire.h`: A library to control the I2C protocol to communicate with devices such as OLED displays.
- `Adafruit_GFX.h`: A library that provides graphical functions such as drawing shapes and texts.
- `Adafruit_SSD1306.h`: A library for OLED displays that work with SSD1306 controller.

### Definition of variables and constants:
```cpp
#define TRIG_PIN 26
#define ECHO_PIN 35

#define SCREEN_WIDTH 128
#define SCREEN_HIGHT 64
#define OLED_RESET -1
#define OLED_I2C_ADDRESS 0x3C
```
- `TRIG_PIN` and `ECHO_PIN`: Define the pins connected to the ultrasonic sensor.
- `SCREEN_WIDTH` and `SCREEN_HIGHT`: Define the width and height of the OLED screen.
- `OLED_RESET`: Define the reset ID of the screen, here it is set to -1 because it is not used.
- `OLED_I2C_ADDRESS`: I2C address of the OLED screen.

### Setting up an OLED display:
```cpp
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HIGHT, &Wire, OLED_RESET);
```
- Defines a `display` object representing the OLED display using the library with the width and height specified.

### Setting up functions:
#### `setup()`:
```cpp
void setup() {
Serial.begin(115200);

if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
Serial.println(F("SSD1306 allocation failed"));
for(;;);
}

display.clearDisplay();
display.setTextSize(1);
display.setTextColor(SSD1306_WHITE);
display.setCursor(0,0);
display.println("Initializing");
display.display();

pinMode(TRIG_PIN, OUTPUT);
pinMode(ECHO_PIN, INPUT);
}
```
- `Serial.begin(115200)`: Starts the serial communication at 115200 baud rate.
- `display.begin(...)`: Initializes the OLED display.
- If initialization fails, an error message is displayed on the serial display and the program is terminated.
- `display.clearDisplay()`: Clears the display.
- `display.setTextSize(1)`: Set the text size.
- `display.setTextColor(SSD1306_WHITE)`: Set the text color.
- `display.setCursor(0,0)`: Positions the cursor in the upper left corner.
- `display.println("Initializing")`: Print "Initializing" to the screen.
- `display.display()`: Refresh the screen to display the contents.
- `pinMode(TRIG_PIN, OUTPUT)` and `pinMode(ECHO_PIN, INPUT)`: Set the pin `TRIG_PIN` as output and `ECHO_PIN` as input for the ultrasonic sensor.

#### `loop()`:
```cpp
void loop() {
long duration;
int distance;

digitalWrite(TRIG_PIN, LOW);
delayMicroseconds(2);

digitalWrite(TRIG_PIN, HIGH);
delayMicroseconds(10);
digitalWrite(TRIG_PIN, LOW);

duration = pulseIn(ECHO_PIN, HIGH);
distance = duration * 0.034 / 2;

Serial.print("Distance: ");
Serial.print(distance);
Serial.println("cm");

display.clearDisplay();
display.setCursor(0, 0);
display.print("Distance: ");
display.print(distance);
display.println("cm");
display.display();
delay(1000);
}
```
- At the beginning of the loop, a short pulse is sent to the sensor to start measuring the distance.
- `digitalWrite(TRIG_PIN, LOW)` and `delayMicroseconds(2)`: Make sure the `TRIG_PIN` pin is low before sending a pulse.
- `digitalWrite(TRIG_PIN, HIGH)` and `delayMicroseconds(10)`: Send a high pulse for 10 microseconds.
- `duration = pulseIn(ECHO_PIN, HIGH)`: Measures the duration of the pulse that the sensor takes to send the sound back to the sensor.
- `distance = duration * 0.034 / 2`: Calculates the distance based on the pulse duration using the sound speed equation (343 m/s).

- Prints the calculated distance in the serial monitor.
- Displays the distance on the OLED using the functions `display.clearDisplay()`, `display.setCursor(0,0)`, and `display.display()` to refresh the display.

- `delay(1000)`: Waits for 1 second before starting the next measurement.

### Basic Idea:
The code measures the distance using the ultrasonic sensor, and then displays the calculated distance on the OLED as well as the serial monitor every second.
