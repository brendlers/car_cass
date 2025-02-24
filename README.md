# car_cass

  CarCass - Fahrzeug-Beleuchtung-Grundaufbau - Abstecken des Vorhabens
  
## Komponenten
- NeoPixel-LEDs für Lichter --> NeoPixel-Ring 16 Pixel (WS2812)
- Taster für Eingabe        --> LED&KEY-Shield (TM1638)
- Arduino für Steuerung     --> Arduino Uno R3 (ATmega328P)

## Teile der Beleuchtung und zugehoerige Abkuerzungen
Hier werden die einzelnen Lichter benannt, festgelegt wieviele nötig sind, und dann englische Namen vergeben, einfach so.

--> Bisher weniger als 16 (zwingend notwendig), also möglich mit einem NeoPixel-Ring, aber in der Zukunft soll beliebige Länge und beliebige PIN-Zuordnungen möglich sein

| Abkürz. | Name        | Anzahl | Intensität | LEDs  | Position           | Farbe    |
| ------- | ----------- | ------ | ---------- | ----- | ------------------ | -------- |
| LF      | Light       | 2      | 60         | 15,3  | Front, Links/Rechs | weiß     |
| F       | FarLight    | 2      | 100        | 0,2   | Front, Links/Rechs | weiß     |
| B       | BlinkL      | 2      | 50         | 13,14 | Heck/Front, Links  | orange   |
| B       | BlinkR      | 2      | 50         | 4,6   | Heck/Front, Rechts | orange   |
| S       | Stop        | 2      | 50         | 11,7  | Heck, Links/Rechs  | rot      |
| R       | Reverse     | 2      | 50         | 10,8  | Heck, Links/Rechs  | weiß     |
| N       | Nebula      | 1      | 100        | 9     | Heck, Rechts       | rot      |
| P       | PoliceLight | 2      | 70         | 13,5  | Dach, Links/Rechs  | rot/blau |
| A       | AlarmLight  | 1      | 30         | 1     | Tür, Links         | rot      |
## Wie sind die Lichter auf dem Ring angeordnet?
Zur besseren Planung der Anordnung ist hier eine kleine "Skizze" des NeoPixel-Rings und der Anordnung der LEDs.

```
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
```

XD GitHub mag meine Formatierung nicht!? :-( --> Deshalb "Code-Block"

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
