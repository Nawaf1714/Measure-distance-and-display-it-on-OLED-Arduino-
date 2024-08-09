#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define TRIG_PIN 26
#define ECHO_PIN 35

#define SCREEN_WIDTH 128
#define SCREEN_HIGHT 64
#define OLED_RESET -1
#define OLED_I2C_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HIGHT, &Wire, OLED_RESET );


void setup() {
Serial.begin(115200);

if(!display.begin(SSD1306_SWITCHCAPVCC,OLED_I2C_ADDRESS )){

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

void loop() {
long duration;
int distance;
digitalWrite(TRIG_PIN, LOW);
delayMicroseconds(2);

digitalWrite(TRIG_PIN, HIGH);
delayMicroseconds(10);
digitalWrite(TRIG_PIN, LOW);

duration = pulseIn(ECHO_PIN, HIGH);
distance = duration *0.034/2;

Serial.print("Distance:");
Serial.print(distance);
Serial.print("cm");

display.clearDisplay();
display.setCursor(0,0);
display.print("Distance:");
display.print(distance);
display.print("cm");
display.display();
delay(1000);
}
