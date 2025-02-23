/*Definitionen aus dem TM16xx Beispielprojekt, um das LED&KEY-Shield einzubinden
// Legt die notwendigen PINs zur Kommunikation fest data pin 8, clock pin 9 and strobe pin 7
// Definiert ein Objekte für Display (LEDs, Matrix) und eines für die Buttons
*/
#include <TM1638.h>
#include <TM16xxDisplay.h>
#include <TM16xxButtons.h>
TM1638 module(8, 9, 7);   // DIO=8, CLK=9, STB=7
TM16xxButtons buttons(&module);       // TM16xx button 
TM16xxDisplay display(&module, 8);    // TM16xx object, 8 digits

/* Definitionen aus dem TM16xx Beispielprojekt, um das LED&KEY-Shield einzubinden
// Legt die notwendigen PINs zur Kommunikation fest und die Anzahl der LEDs
*/
#include <Adafruit_NeoPixel.h>
#define PIN        6 // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS 16 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//Farbdefinitionen, um Schreibarbeit zu sparen
#define WHITE 255,255,255
#define YELLOW 255,255,0
#define MAGENTA 255,0,255
#define CYAN 0,255,255
#define RED 255,0,0
#define GREEN 0,255,0
#define BLUE 0,0,255
#define BLACK 0,0,0

// Funktion um die eingebaute LED im Arduino anzusteuern
void Blink(int nDelay=500, int nTimes=1)
{
  for(int i=0; i<nTimes; i++)
  {
  digitalWrite(LED_BUILTIN, HIGH);    // switch on (or active low LED off for ESP)
  delay(nDelay);
  digitalWrite(LED_BUILTIN, LOW);    // switch off (or active low LED on for ESP)
  delay(nDelay);
  }
}


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
      status = true;
    }

    void off(){
      pixels.setPixelColor(pinLED1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(pinLED2, pixels.Color(0, 0, 0));
      pixels.show();   // Send the updated pixel colors to the hardware.
      status = false;
    }

    void toggle(){
      if(status == true){
        off();
        status = false;
      }
      else
      {
        on();
        status = true;
      }
    }
};


class Blinker {
  bool status = false;
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
      status = true;
    }

    void off(){
      blinkerRun = false;
      pixels.setPixelColor(pinLED1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(pinLED2, pixels.Color(0, 0, 0));
      pixels.show();   // Send the updated pixel colors to the hardware.
      status = false;
    }

    void toggle(){
      if(status == true){
        off();
        status = false;
      }
      else
      {
        on();
        status = true;
      }
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
  bool status = false;
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
      status = true;
    }

    void off(){
      blinkerRun = false;
      status = false;
      pixels.setPixelColor(pinLED1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(pinLED2, pixels.Color(0, 0, 0));
      pixels.show();   // Send the updated pixel colors to the hardware.
    }

    void toggle(){
      if(status == true){
        off();
        status = false;
      }
      else
      {
        on();
        status = true;
      }
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

/* Fahrzeugdefinition
  Welche LEDs werden für welches Licht verwendet?
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

//Pin-Nummern den Zwecken zuweisen
*/
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

/* Hier werden Objekte für die einzelnen Lichter erzeugt*/
Light frontLight(15, 3, WHITE);
Light farLight(0, 2, WHITE);
Light breakLight(7, 11, RED);
Light reverseLight(10, 8, WHITE);
Blinker blinkerR(4, 6);
Blinker blinkerL(14, 12);
Warner warner(13, 5);




void setup()
{
  Serial.begin(9600);
  Serial.println(F("TM16xxButtons example"));
  Serial.println(F("TM1638: DIO=8, CLK=9, STB=7"));
  //Serial.println(F("TM1637: DIO=5, CLK=4"));
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  Serial.println();

  Serial.println(F("clear"));
  digitalWrite(LED_BUILTIN, LOW);     // switch (active) low LED off
  module.clearDisplay();              // clear display
  module.setupDisplay(true, 7);       // set intensity 0-7, 7=highest
  delay(50);

  // Show some text.
  // Note: the TM16xxDisplay provides the println() function which is used in the callback functions below.
  Serial.println(F("txt"));
  module.setDisplayToString("CAR");
  delay(800);
  module.setDisplayToString("CARCARAS ");
  delay(800);
  module.clearDisplay();

  // Attach the button callback functions that are defined below
  buttons.attachRelease(fnRelease);
  buttons.attachClick(fnClick);
  buttons.attachDoubleClick(fnDoubleclick);
  buttons.attachLongPressStart(fnLongPressStart);
  buttons.attachLongPressStop(fnLongPressStop);
  buttons.attachDuringLongPress(fnLongPress);

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear();
  pixels.show();


  Serial.println(F("Setup done"));
}

void loop()
{
  blinkerR.runner();
  blinkerL.runner();
  warner.runner();

  static unsigned long ulTime=millis();
  uint32_t dwButtons=buttons.tick();

  if(dwButtons){
    //display.setDisplayToHexNumber(dwButtons, 0, true);
    //display.setDisplayToString(dwButtons);
    Serial.println(dwButtons, 16);

    }
  else
  {
    // For best doubleclick detection, the loop() needs to be as fast as possible. 
    // So instead of calling delay(100), we check if 100ms has passed.
    if(millis()-ulTime>100)
    {
      char text[17];
      //sprintf(text, "%lu", millis());
      ltoa(millis(), text, 10);   // DECIMAL = base 10
      //module.setDisplayToString(text);
      ulTime=millis();
    }
  }

  //delay(100); // to keep the loop fast don't use delay(100) 
}


/*  Das ist wieder ein Block der aus dem TM16xx Beispiel übernommen wurde
      Bisher wurden nur Änderungen im fnClick Callback-Aufruf vorgenommen
/*/
// The Release function will be called when a button was released.
// It can be used for fast actions when no click or double click needs to be detected.
void fnRelease(byte nButton)
{
  // using isPressed or is LongPressed a shift-key can be implemented
  if(buttons.isLongPressed(0))
    Serial.print(F("Button 0 still longpressed. "));
  else if(buttons.isPressed(0))
    Serial.print(F("Button 0 still pressed. "));

  Serial.print(F("Button "));
  Serial.print(nButton);
  Serial.println(F(" release."));
  display.println(F("rels  "));
  Blink(10,1);
} // release

// This function will be called when a button was pressed 1 time (without a second press).
void fnClick(byte nButton)
{
  Serial.print(F("Button "));
  Serial.print(nButton);
  Serial.println(F(" click."));
  display.println(F("sclk  "));
  Blink(100,1);

    switch(nButton){
      case 16:
        frontLight.toggle();
        breakLight.toggle();
        break;

      case 18:
        blinkerR.toggle();
        break;

      case 20:
        blinkerL.toggle();
        break;

      case 22:
        warner.toggle();
        break;

      case 17:
        farLight.toggle();
        break;

      case 19:
        reverseLight.toggle();
        break;

      case 21:
        frontLight.on();
        farLight.on();
        breakLight.on();
        blinkerR.on();
        blinkerL.on();
        warner.on();
        reverseLight.on();
        break;

      case 23:
        frontLight.off();
        farLight.off();
        breakLight.off();
        blinkerR.off();
        blinkerL.off();
        warner.off();
        reverseLight.off();
        break;
    }
} // click


// This function will be called when a button was pressed 2 times in a short timeframe.
void fnDoubleclick(byte nButton)
{
  Serial.print(F("Button "));
  Serial.print(nButton);
  Serial.println(F(" doubleclick."));
  display.println(F("dclk  "));
  Blink(200,2);
} // doubleclick


// This function will be called once, when a button is pressed for a long time.
void fnLongPressStart(byte nButton)
{
  Serial.print(F("Button "));
  Serial.print(nButton);
  Serial.println(F(" longPress start"));
  display.println(F("strt  "));
  Blink(50,1);
} // longPressStart


// This function will be called often, while a button is pressed for a long time.
void fnLongPress(byte nButton)
{
  Serial.print(F("Button "));
  Serial.print(nButton);
  Serial.println(F(" longPress..."));
} // longPress


// This function will be called once, when a button is released after beeing pressed for a long time.
void fnLongPressStop(byte nButton)
{
  Serial.print(F("Button "));
  Serial.print(nButton);
  Serial.println(F(" longPress stop"));
  display.println(F("stop  "));
  Blink(500,1);
} // longPressStop
