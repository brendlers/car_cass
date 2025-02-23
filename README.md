# car_cass

  CarCass - Fahrzeug-Beleuchtung-Grundaufbau - Abstecken des Vorhabens
  
## Komponenten
- NeoPixel-LEDs für Lichter --> NeoPixel-Ring 16 Pixel (WS2812)
- Taster für Eingabe        --> LED&KEY-Shield (TM1638)
- Arduino für Steuerung     --> Arduino Uno R3 (ATmega328P)

## Teile der Beleuchtung und zugehoerige Abkuerzungen
Hier werden die einzelnen Lichter benannt, festgelegt wieviele nötig sind, und dann englische Namen vergeben, einfach so.
LF Light    2                     60   15,3     Front                    weiß
F Far-Light 2                    100   0,2      Front, neben Light       weiß

B BlinkL    2                     50   13,14    Front, Seite, Hinten     orange
B BlinkR    2                     50   4,6      Front, Seite, Hinten     orange

S Stop      2                     60   11,7     Hinten                   rot
    |_____ aber wenn Break, dann 100

R Reverse   2                     50   10,8     Hinten, neben Stop       weiß
N Nebula    1   extra bright --> 100   9        Hinten, unten, links     rot

Weil noch was übrig war:
P PoliceLight 2                     70   13,5   Oben                     rot/blau
A Alarm-Light 1                     30   1      Tür                      rot

--> Weniger als 16 (zwingend notwendig), also möglich mit einem NeoPixel-Ring

## Wie sind die Lichter auf dem Ring angeordnet?
Zur besseren Planung der Anordnung ist hier eine kleine "Skizze" des NeoPixel-Rings und der Anordnung der LEDs.

   15  0  1  2  3
    L  F  A  F  L
       -------
     /         \
14 B|           |B 4
    | NEOPIXEL- | 
13 P|  "Ring"   |P 5
    |   (lol)   |
12 B|           |B 6
     \         /
       -------
    S  R  N  R  S
   11 10  9  8  7

XD GitHub mag meine Formatierung nicht!? :-(

## Inhalt der Lerneinheit:
Jedes Projekt stellt ja in einem gewissen Sinne eine "Lerneinheit" dar. Die behandelten Themen sind:
- Einbinden von Fremdhardware und Bibliotheken (NeoPixel (WS2812) und Led&Key-Shield (TM1638))
- Mikrocontroller
- SPI
- RGB-Farben
- Konstanten
- Varablen
- Arduino
- und so..
- Verzögerung ohne Delay()
