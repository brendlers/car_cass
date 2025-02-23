/*  CarCass - Fahrzeug-Beleuchtung-Grundaufbau

# Komponenten
- NeoPixel-LEDs für Lichter   --> Vorhanden NeoPixel-Ring 16 Pixel
- LED&KEY-Shield für Eingabe
- Arduino für Steuerung       --> Arduino Uno R3

# Teile der Beleuchtung und zugehoerige Abkuerzungen
LF Light    2                     60   15,3     Front
F Far-Light 2                    100   0,2      Front, neben Light

B BlinkL    2                     50   13,14    Front, Seite, Hinten
B BlinkR    2                     50   4,6      Front, Seite, Hinten

S Stop      2                     60   11,7     Hinten
    |_____ aber wenn Break, dann 100

R Reverse   2                     50   10,8     Hinten, neben Stop
N Nebula    1   extra bright --> 100   9        Hinten, unten, links

Weil noch was übrig war:
P PoliceLight 2                     70   13,5   Oben
A Alarm-Light 1                     30   1      Tür

--> Weniger als 16 (zwingend notwendig), also möglich mit einem NeoPixel-Ring

Wie sind die Lichter auf dem Ring angeordnet?

    15  0  1  2  3
     L  F  A  F  L
14  B             B 4

13  P  NEOPIXEL   P 5

12  B             B 6
     S  R  N  R  S
    11 10  9  8  7 
*/



// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
// How many NeoPixels are attached to the Arduino?
// Which pin on the Arduino is connected to the NeoPixels?
#include <Adafruit_NeoPixel.h>
#define PIN        6 // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS 16 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//Color definitions
#define WHITE 255,255,255
#define YELLOW 255,255,0
#define MAGENTA 255,0,255
#define CYAN 0,255,255
#define RED 255,0,0
#define GREEN 0,255,0
#define BLUE 0,0,255
#define BLACK 0,0,0



class Light {
  bool status = false;

  int pinLED1;
  int pinLED2;
  
  int redComponent;
  int greenComponent;
  int blueComponent;

  public:
    Light(int lLpin, int lRpin, int red, int green, int blue) {
      pinLED1 = lLpin;
      pinLED2 = lRpin;

      redComponent = red;
      greenComponent = green;
      blueComponent = blue;
      
      pinMode(pinLED1, OUTPUT);
      pinMode(pinLED2, OUTPUT);
    }

    void on(){
      pixels.setPixelColor(pinLED1, pixels.Color(redComponent, greenComponent, blueComponent));
      pixels.setPixelColor(pinLED2, pixels.Color(redComponent, greenComponent, blueComponent));
      pixels.show();   // Send the updated pixel colors to the hardware.
    }

    void off(){
      pixels.setPixelColor(pinLED1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(pinLED2, pixels.Color(0, 0, 0));
      pixels.show();   // Send the updated pixel colors to the hardware.
    }

    void toggle(){
      if(status){
        status = false;
        on();
      }
      else
      {
        off();
        status = true;
      }


    }
};

class Blinker {
  int pinLED1;
  int pinLED2;
  bool state;
  int blinkDuration = 200;
  bool blinkerRun = false;
  unsigned long currentMillis = 0;
  unsigned long previousMillis = 0;

  public:
    Blinker (int lLpin, int lRpin) {
      pinLED1 = lLpin;
      pinLED2 = lRpin;
      state = true;      
      pinMode(pinLED1, OUTPUT);
      pinMode(pinLED2, OUTPUT);
    }

    void on(){
      blinkerRun = true;
    }

    void off(){
      blinkerRun = false;
      pixels.setPixelColor(pinLED1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(pinLED2, pixels.Color(0, 0, 0));
      pixels.show();   // Send the updated pixel colors to the hardware.

    }

    void runner(){
      currentMillis = millis();

      if (currentMillis - previousMillis >= 200 && blinkerRun == true){
        previousMillis = currentMillis;

        if (state == true)
        {
          pixels.setPixelColor(pinLED1, pixels.Color(200, 150, 0));
          pixels.setPixelColor(pinLED2, pixels.Color(200, 150, 0));
          pixels.show();   // Send the updated pixel colors to the hardware.
          state = false;
        }
        else
        {
          pixels.setPixelColor(pinLED1, pixels.Color(0, 0, 0));
          pixels.setPixelColor(pinLED2, pixels.Color(0, 0, 0));
          pixels.show();   // Send the updated pixel colors to the hardware.
          state = true;
        }
      }
    }
};

class Warner {
  int pinLED1;
  int pinLED2;
  bool state;
  int blinkDuration = 200;
  bool blinkerRun = false;
  unsigned long currentMillis = 0;
  unsigned long previousMillis = 0;

  public:
    Warner (int lLpin, int lRpin) {
      pinLED1 = lLpin;
      pinLED2 = lRpin;
      state = true;      
      pinMode(pinLED1, OUTPUT);
      pinMode(pinLED2, OUTPUT);
    }

    void on(){
      blinkerRun = true;
    }

    void off(){
      blinkerRun = false;
      pixels.setPixelColor(pinLED1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(pinLED2, pixels.Color(0, 0, 0));
      pixels.show();   // Send the updated pixel colors to the hardware.

    }

    void runner(){
      currentMillis = millis();

      if (currentMillis - previousMillis >= 100 && blinkerRun == true){
        previousMillis = currentMillis;

        if (state == true)
        {
          pixels.setPixelColor(pinLED1, pixels.Color(200, 0, 0));
          pixels.setPixelColor(pinLED2, pixels.Color(0, 0, 200));
          pixels.show();   // Send the updated pixel colors to the hardware.
          state = false;
        }
        else
        {
          pixels.setPixelColor(pinLED1, pixels.Color(0, 0, 200));
          pixels.setPixelColor(pinLED2, pixels.Color(200, 0, 0));
          pixels.show();   // Send the updated pixel colors to the hardware.
          state = true;
        }
      }
    }
};

//Pin-Nummern den Zwecken zuweisen
int lightL = 15;
int lightR = 3;

int farLightL = 0;
int farLightR = 2;

int blinkLF = 14;
int blinkLR = 12;

int blinkRF = 4;
int blinkRR = 6;

int breakL = 11;
int breakR = 7;

int reverseL = 10;
int reverseR = 8;

int nebula = 9;

int policeL = 13;
int policeR = 5;

int alarm = 1;

unsigned long currentRunTime;
unsigned long previousRunTime = 0;
bool state = true;
int variation = 0;

bool buttonState;
int buttonPin = 2;
bool lastState = LOW;

Light frontLight(15, 3, WHITE);
Light farLight(0, 2, WHITE);
Light breakLight(7, 11, RED);
Light reverseLight(10, 8, WHITE);
Blinker blinkerR(4, 6);
Blinker blinkerL(14, 12);
Warner warner(13, 5);


void setup() {
  // put your setup code here, to run once:
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pinMode(buttonPin, INPUT_PULLUP);

}

void loop() {
  blinkerR.runner();
  blinkerL.runner();
  warner.runner();

  buttonState = digitalRead(buttonPin);

  if(buttonState == LOW && buttonState != lastState){
    variation = (variation + 1) % 8;
    lastState = buttonState;
    delay(50);
  } else {
    lastState = buttonState;
  }

  currentRunTime = millis();
  // put your main code here, to run repeatedly:
    switch(variation){
      case 0:
        frontLight.toggle();
        break;
      case 1:
        frontLight.off();
        breakLight.on();
        break;
      case 2:
        breakLight.toggle();
        break;
      case 3:
        blinkerR.off();
        blinkerL.on();
        break;
      case 4:
        blinkerL.off();
        warner.on();
        break;
      case 5:
        warner.off();
        break;
      case 6:
        frontLight.on();
        farLight.on();
        breakLight.on();
        blinkerR.on();
        blinkerL.on();
        warner.on();
        reverseLight.on();
        break;
      case 7:
        frontLight.off();
        farLight.off();
        breakLight.off();
        blinkerR.off();
        blinkerL.off();
        warner.off();
        reverseLight.off();
        break;
    } 
}





