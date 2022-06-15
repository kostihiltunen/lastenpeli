// elementaalio.ino

/*
parts:
1 Arduino Uno WIFI rev2 controller, 1 Crowtail - Base Shield for Arduino v2.0, 4 Crowtail - Hall Sensor v2.0 modules, 4 Crowtail - RGB-LED v2.0 modules, 1 MP3 Player v2.0 module
description:
When a sensor is activated a specific RGB-LED module lights up. When all sensors
are activated MP3 player plays a sound file
*/

#include <Adafruit_NeoPixel.h>

#define LED_PIN 9

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, LED_PIN, NEO_GRB + NEO_KHZ800);

int wait = 10;

// variables for Hall sensor pins
int hall1 = 2;
int hall2 = 3;
int hall3 = 4;
int hall4 = 5;

// variables for sensor states
int hall1State = 1;
int hall2State = 1;
int hall3State = 1;
int hall4State = 1;

void setup() {
    // set pins active
    pinMode(hall1, INPUT);
    pinMode(hall2, INPUT);
    pinMode(hall3, INPUT);
    pinMode(hall4, INPUT);
    // set led strips active
    strip.begin();
    strip.show();
}

void loop() {
    Serial.begin(9600);
    // reading sensor values to variables
    hall1State = digitalRead(hall1);
    hall2State = digitalRead(hall2);                                                             
    hall3State = digitalRead(hall3);
    hall4State = digitalRead(hall4);
    // printing variables to console                                                     
    Serial.println(hall1State);
    Serial.println(hall2State);
    Serial.println(hall3State);
    Serial.println(hall4State);
    
    if(hall1State == 0) {
        onLedModule1();
    } else {
        offLedModule1();
    }
    if(hall2State == 0) {
        onLedModule2();
    } else {
        offLedModule2();
    }
    if(hall3State == 0) {
        onLedModule3();
    } else {
        offLedModule3();
    } 
    if(hall4State == 0) {
        onLedModule4();
    } else {
        offLedModule4();
    }
    if(hall1State == 0 && hall2State == 0 && hall3State == 0 && hall4State == 0){
        solve();
    } 

}

void onLedModule1() {
    for(int i = 0; i < 4; i++) {
        strip.setPixelColor(i, strip.Color(255, 0, 0));
    }
    strip.show();
    delay(wait);
}

void offLedModule1() {
    for(int i = 0; i < 4; i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
    delay(wait);
}

void onLedModule2() {
    for(int i = 4; i < 8; i++) {
        strip.setPixelColor(i, strip.Color(255, 0, 0));
    }
    strip.show();
    delay(wait);
}

void offLedModule2() {
    for(int i = 4; i < 8; i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
    delay(wait);

}void onLedModule3() {
    for(int i = 8; i < 12; i++) {
        strip.setPixelColor(i, strip.Color(255, 0, 0));
    }
    strip.show();
    delay(wait);
}

void offLedModule3() {
    for(int i = 8; i < 12; i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
    delay(wait);

}void onLedModule4() {
    for(int i = 12; i < 16; i++) {
        strip.setPixelColor(i, strip.Color(255, 0, 0));
    }
    strip.show();
    delay(wait);
}

void offLedModule4() {
    for(int i = 12; i < 16; i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
    delay(wait);
}

void solve() {
    for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(255, 255, 255));
    // delay(wait);
    strip.show();
    allLedsOff();
    } 
}

void allLedsOff() {
    for(uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
    delay(wait);
}