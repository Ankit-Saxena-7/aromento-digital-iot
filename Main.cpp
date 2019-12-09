// Initializations
#include <neopixel.h>
#include <Adafruit_MPR121.h>
#include <Particle.h>

// Button States
int buttonState1;
int buttonState2;
int buttonState3;
int buttonState4;
int buttonState5;
int buttonState6;

// Inputs (Buttons)
const int buttonPin1 = A0;
const int buttonPin2 = A1;
const int buttonPin3 = A2;
const int buttonPin4 = A3;
const int buttonPin5 = A4;
const int buttonPin6 = A5;

// Outputs (Atomizers)
int atomPin1 = D0;
int atomPin2 = D1;
int atomPin3 = D2;
int atomPin4 = D3;
int atomPin5 = D4;
int atomPin6 = D5;

// Outputs (Fog machine)
int fogPin1 = D7;

// Code for LED strip (Start)

// Initializations
#include "application.h"
#include "neopixel/neopixel.h"

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_COUNT 87
#define PIXEL_PIN D8
#define PIXEL_TYPE WS2812B

#define PEACH 200,50,5
#define CYAN 10,150,70
#define PURPLE 180,3,180
#define BLUE 5,5,190
#define WHITE 150,150,150
#define GREEN 10,150,10
#define LIME 164,255,202
#define RED 255,117,183
#define OFF 0,0,0

// Outputs (LED)
int lightsPin1 = D8;

Adafruit_NeoPixel magicalLEDStrip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

int waitTimeLED = 15;
int counterLED;
void spin(int R, int G, int B);

// Code for LED strip (End)

// Timer-related functions

int atomizerFlag = 0;
int foggerFlag = 0;

int atomizerActive = 0;

#define atomizerDelay 50

void atomizerTurnOff()
{
    atomizerFlag = 2;
}

void foggerTurnOff()
{
    foggerFlag = 2;
}

Timer atomizerTurnOn(5000, atomizerTurnOff);

Timer foggerTurnOn(3000, foggerTurnOff);

// SETUP
void setup() {

    // Set up the frame rate
    Serial.begin(9600);

    // Scent input buttons
    pinMode(buttonPin1, INPUT);
    pinMode(buttonPin2, INPUT);
    pinMode(buttonPin3, INPUT);
    pinMode(buttonPin4, INPUT);
    pinMode(buttonPin5, INPUT);
    pinMode(buttonPin6, INPUT);

    // Atomizer outputs
    pinMode(atomPin1, OUTPUT);
    pinMode(atomPin2, OUTPUT);
    pinMode(atomPin3, OUTPUT);
    pinMode(atomPin4, OUTPUT);
    pinMode(atomPin5, OUTPUT);
    pinMode(atomPin6, OUTPUT);

    // LED lights output
    pinMode(lightsPin1, OUTPUT);

    // Fog machine output
    pinMode(fogPin1, OUTPUT);

    // Code for LED strip
    magicalLEDStrip.begin();
    magicalLEDStrip.show();

    digitalWrite(atomPin1, LOW);
    digitalWrite(atomPin2, LOW);
    digitalWrite(atomPin3, LOW);
    digitalWrite(atomPin4, LOW);
    digitalWrite(atomPin5, LOW);
    digitalWrite(atomPin6, LOW);
    digitalWrite(lightsPin1, LOW);
    digitalWrite(fogPin1, HIGH); // Default high for fogger. Low to turn it on.
    
    // Array of atomizer pins
    int atomizerList[6] = {atomPin1, atomPin2, atomPin3, atomPin4, atomPin5, atomPin6};
    
    // Simulate a button press for the atomizers because they are 'on' at default state
    for (int pinCounter = 0; pinCounter <= 5; pinCounter++) {
        
        digitalWrite(atomizerList[pinCounter], HIGH);
        delay(200);
        digitalWrite(atomizerList[pinCounter], LOW);
        delay(200);
        digitalWrite(atomizerList[pinCounter], HIGH);
    }
}

// LOOP
void loop() {
    
    // Handling atomizers
    if(atomizerFlag == 1){
        // Simulate a button press to start atomizers
        digitalWrite(atomizerActive, HIGH);
        delay(200);
        digitalWrite(atomizerActive, LOW);
        delay(200);
        digitalWrite(atomizerActive, HIGH);  

        atomizerTurnOn.start();
    }
    else if(atomizerFlag == 2){
        atomizerTurnOn.stop();

        // Simulate a button press to stop atomizers
        digitalWrite(atomizerActive, LOW);
        delay(atomizerDelay);
        digitalWrite(atomizerActive, HIGH);
        delay(atomizerDelay);
        digitalWrite(atomizerActive, LOW);
        atomizerFlag = 0;
    }

    // Handling fogger
    if(foggerFlag == 1){
        // Turn on fogger
        digitalWrite(fogPin1, LOW);
        foggerTurnOn.start();
    }
    else if(foggerFlag == 2){
        // Turn off fogger
        foggerTurnOn.stop();
        digitalWrite(fogPin1, HIGH);
        foggerFlag = 0;
    }
    
    // Read button states
    int buttonStateReading1 = digitalRead(buttonPin1);
    int buttonStateReading2 = digitalRead(buttonPin2);
    int buttonStateReading3 = digitalRead(buttonPin3);
    int buttonStateReading4 = digitalRead(buttonPin4);
    int buttonStateReading5 = digitalRead(buttonPin5);
    int buttonStateReading6 = digitalRead(buttonPin6);
    
    
    // only toggle the LED if the new button state is HIGH
    if (buttonStateReading1 == HIGH) {
        Particle.publish("Button nerds.", "A0", PUBLIC);

        // Launch atomizer
        atomizerFlag = 1;
        atomizerActive = atomPin1;

        // LED Lights
        letThereBeLight(PEACH);
        letThereBeLight(RED);
        letThereBeLight(CYAN);

        // Say cheese! Click the photo
        Serial.println(7777);
    }
        
    // only toggle the LED if the new button state is HIGH
    if (buttonStateReading2 == HIGH) {
        Particle.publish("Button nerds.", "A1", PUBLIC);

        // Launch atomizer
        atomizerFlag = 1;
        atomizerActive = atomPin2;

        // LED Lights
        letThereBeLight(CYAN);
        letThereBeLight(PURPLE);
        letThereBeLight(WHITE);

        // Say cheese! Click the photo
        Serial.println(7777);
    }
            
    // only toggle the LED if the new button state is HIGH
    if (buttonStateReading3 == HIGH) {
        Particle.publish("Button nerds.", "A2", PUBLIC);

        // Launch atomizer
        atomizerFlag = 1;
        atomizerActive = atomPin3;

        // LED Lights
        letThereBeLight(PURPLE);
        letThereBeLight(BLUE);
        letThereBeLight(LIME);

        // Say cheese! Click the photo
        Serial.println(7777);
    } 
        
    // only toggle the LED if the new button state is HIGH
    if (buttonStateReading4 == HIGH) {
        Particle.publish("Button nerds.", "A3", PUBLIC);

        // Launch atomizer
        atomizerFlag = 1;
        atomizerActive = atomPin4;

        // LED Lights
        letThereBeLight(BLUE);
        letThereBeLight(LIME);
        letThereBeLight(CYAN);

        // Say cheese! Click the photo
        Serial.println(7777);
    }  
        
    // only toggle the LED if the new button state is HIGH
    if (buttonStateReading5 == HIGH) {
        Particle.publish("Button nerds.", "A4", PUBLIC);

        // Launch atomizer
        atomizerFlag = 1;
        atomizerActive = atomPin5;

        // LED Lights
        letThereBeLight(GREEN);
        letThereBeLight(RED);
        letThereBeLight(BLUE);

        // Say cheese! Click the photo
        Serial.println(7777);
    } 
            
    // only toggle the LED if the new button state is HIGH
    if (buttonStateReading6 == HIGH) {
        Particle.publish("Button nerds.", "A5", PUBLIC);

        // Launch atomizer
        atomizerFlag = 1;
        atomizerActive = atomPin6;

        // LED Lights
        letThereBeLight(RED);
        letThereBeLight(GREEN);
        letThereBeLight(PEACH);

        // Say cheese! Click the photo
        Serial.println(7777);
    }
}

// Code for LED strip (Start)
void letThereBeLight(int R, int G, int B) {
    // Turn on colorful lights
    for(counterLED=0; counterLED < PIXEL_COUNT; counterLED++) {
        magicalLEDStrip.setPixelColor(counterLED, R,G,B);
        magicalLEDStrip.show();
        delay(waitTimeLED);
    }
    // Turn on white lights
    for(counterLED=0; counterLED < PIXEL_COUNT; counterLED++) {
        magicalLEDStrip.setPixelColor(counterLED, 0,0,0);
        magicalLEDStrip.show();
        delay(waitTimeLED);
    }
}
// Code for LED strip (End)
