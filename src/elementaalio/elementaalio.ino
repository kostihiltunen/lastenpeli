// elementaalio.ino

// included libraries
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#include <MP3Player_KT403A.h>

#define LED_PIN 9

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, LED_PIN, NEO_GRB + NEO_KHZ800);

// Note: You must define a SoftwareSerial class object that the name must be mp3, 
//       but you can change the pin number according to the actual situation.
// Note2: Use pins that are not already in use!!1
SoftwareSerial mp3(7, 8);

// Integer variable for delays
int wait = 10;

// Variable for solving whole puzzle (1 = solved, 0 = not solved)
int solved = 0;

// Variables for playback
int activeHall1 = 0;
int activeHall2 = 0;

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
    mp3.begin(9600);
    Serial.begin(9600);
    delay(100);

    SelectPlayerDevice(0x02);
    SetVolume(0x0E);

    // set led pins active
    pinMode(hall1, INPUT);
    pinMode(hall2, INPUT);
    pinMode(hall3, INPUT);
    pinMode(hall4, INPUT);
    // set led strips active
    strip.begin();
    strip.show();
    SpecifyMusicPlay(6);
}

void loop() {
    if(solved == 0) {
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
    }

    if(hall1State == 0 && hall2State == 0 && hall3State == 0 && hall4State == 0){
        solve();
    }
}

/* Functions for operating leds */

void onLedModule1() {
    for(int i = 0; i < 4; i++) {
        strip.setPixelColor(i, strip.Color(255, 0, 0));
    }
    strip.show();
    delay(wait);
    if(activeHall1 != 2) {
        playHall1();
    }
}

void offLedModule1() {
    for(int i = 0; i < 4; i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
    delay(wait);
    PlayPause();
    activeHall1 = 0;
}

void onLedModule2() {
    for(int i = 4; i < 8; i++) {
        strip.setPixelColor(i, strip.Color(255, 0, 0));
    }
    strip.show();
    delay(wait);
    // if(activeHall2 != 2) {
    //     playHall2();
    // }
}

void offLedModule2() {
    for(int i = 4; i < 8; i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
    delay(wait);
    // PlayPause();
    // activeHall2 = 0;
}

void onLedModule3() {
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

}

void onLedModule4() {
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
    solved = 1;
    
    for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(255, 255, 255));
    // delay(wait);
    strip.show();
    allLedsOff();
    }
    
    hall1State = digitalRead(hall1);
    hall2State = digitalRead(hall2);
    hall3State = digitalRead(hall3);
    hall4State = digitalRead(hall4);
    
    if(hall1State == 1 || hall2State == 1 || hall3State == 1 || hall4State == 1) {
        solved = 0;
    }
}

void allLedsOff() {
    for(uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
    delay(wait);
}

/* Functions for audio playback */



void playHall1() {
    SpecifyMusicPlay(1);
//    Serial.println("playHall1() executed");
    delay(1000);
    activeHall1 = 2;
}

// void playHall2() {
//     SpecifyMusicPlay(2);
//     delay(1000);
//     activeHall2 = 2;
// }