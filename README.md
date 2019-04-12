# Ring_Pong

## Playful Interaction Group Project

Our playful interaction Project is Ring Pong. 
We are aiming to make a more interactive version of this game.

### Contributors

| Name            | Matriculation # |
| --------------- | --------------- |
| Rodger Zak      | 40415721        |
| Maksimova Alina | 40333354        |
| Curran Ruaraidh | 40209895        |

## How to play

Ring Pong involves two players and a ring of LED's.
There is a green light for each player on opposite sides of the LED Ring.
There is a single blue light that bounces around the led ring, between the players corresponding green lights.
The aim of the game is for each player to press their own button when the blue light comes within 2 leds of their green light.
This will fire the Blue led back along the led ring towards the other player where they will try do the same.
A point is gained when the opposite player fails to press their button when the blue led is within 2 spaces of their corresponding green LED.

## Changes we are making

1. Larger led ring.
2. IR sensors instead of buttons.
3. Point counter.
4. Adjustable max score.
5. Buzzing noises indicating a win and points gained.
6. LED light show on start-up and when someone wins.
7. Creating a nice portable case for the came.

### Deliverables

1. Code for Project
2. Marketing Video

### Link to original project

https://www.youtube.com/watch?v=_JxduTo8mgg

### Links to hardware used

#### Original Project Hardware:
**Neopixel Ring 60**<br/>
Cost: £15.00 https://www.ebay.co.uk/itm/8-12-16-24-60-Bit-LED-RGB-5050-WS2812B-WS2812-Ring-Arduino-Raspberry-Pi-NeoPixel/173069314025?hash=item284bbc27e9:m:mNKMAt0PkpxN9KKlkxOpeww:rk:1:pf:0<br/>
**Arduino UNO R3**<br/>
Cost: £5.59 https://www.ebay.co.uk/itm/Arduino-UNO-R3-Rev3-ATMEGA328P-16U2-Compatible-Development-Board-Free-USB-Cable/302754099732?epid=28020006064&hash=item467d8cf214:g:VHMAAOSwTQtaTdvQ:rk:14:pf:0<br/>
**Capacitor 100nF**<br/>
Cost: £0.44 https://uk.farnell.com/kemet/c320c104k5r5ta/cap-0-1-f-50v-10-x7r/dp/1457655?CMP=GRHB-OCTOPART<br/>
**Capacitor 1000μF**<br/>
Cost: £0.67 https://uk.farnell.com/panasonic-electronic-components/eca1em102/cap-1000-f-25v-20/dp/1848503?CMP=GRHB-OCTOPART<br/>
**Jumper Cables**<br/>
Cost: £2.20 https://www.ebay.co.uk/itm/40pcs-Dupont-Cables-MALE-TO-FEMALE-Jumper-GPIO-Breadboard-Wire-Ribbon-Pi-Arduino/262202347968?epid=15008856895&hash=item3d0c7a51c0:g:fD4AAOSwAJFZ4fAe:rk:3:pf:1&frcectupt=true<br/>
Sub Total: £23.90<br/>
#### Additional Hardware:
**Push Button Switch**<br/>
Cost: £2.73 https://www.ebay.co.uk/itm/Tactile-Push-Button-Switch-Momentary-Tact-Cap-12x12x7-3mm-Kit-Arduino-U1Q5<br/>
**Bluetooth Modules**<br/>
Cost: 2 x £3.79 (£7.58) https://www.ebay.co.uk/itm/HC-05-Wireless-Bluetooth-Serial-6-Pin-Master-Slave-Module-Arduino-ARM-Pi-PIC-NN/273379842405?epid=15009566424&hash=item3fa6b55965:g:pvcAAOSwfk9bXtZe:rk:3:pf:1&frcectupt=true<br/>
**Display Modules**<br/>
Cost: 2 x £1.33 (£2.66) https://www.ebay.co.uk/itm/MAX7219-8x8-LED-Dot-Matrix-Modules-Dot-Matrix-Modules-for-Arduino-Raspberry-Pi/291991910235?hash=item43fc12f75b:m:m6BlJWhnS4uLC2tghbOmEqw:rk:40:pf:0<br/>
**5mm LED**<br/>
Cost: £0.99 https://www.ebay.co.uk/itm/Ultra-Bright-Water-Clear-5mm-LED-Bulb-3V-All-Colours-Light-Emitting-Diode/251559482881?hash=item3a921d1601:g:D9gAAOxyhXRTPCQQ:rk:10:pf:0&var=550462657933<br/>
**Potentiometer**<br/>
Cost: £0.99 https://www.ebay.co.uk/itm/1K-1M-ohm-Lin-Linear-Log-Logarithmic-Mono-Stereo-Pot-Potentiometer-Or-Knobs/170703080727?hash=item27beb24d17:m:m8lVZ4hvJCHBNbD1RCYU0PQ:rk:2:pf:1&frcectupt=true<br/>
**Rocker Switch**<br/>
Cost: £0.99 https://www.ebay.co.uk/itm/On-Off-Round-Rectangle-Rocker-Switch-Waterproof-Cover-Car-Dash-Boat-SPST-12V/261349269695?hash=item3cd9a160bf:m:mSGWmJYq-haVfJ31ZszXcsw:rk:2:pf:1&frcectupt=true<br/>
**Sub Total**: £15.94<br/><br/>
**Grand Total**: £39.84

## Examples of adapted or changed to code

### Buzzer melody's code

    #include "pitches.h" //Note Library
    ////////////////////////////////////////////////////////
    // Noise once each player hits the light back
    int passNote[]={
    NOTE_F4
    };
    int passNoteDurations[]={
    6
    };
    // Function
    void pass_note(){
    pinMode(12, OUTPUT);
    for (int x = 0; x < 1; x++){
        int Duration = 1000 / passNoteDurations [x];
        tone(12, passNote[x], Duration);

        int quite = Duration * 1.30;
        delay (quite);

        noTone(12);
    }
    }

    ////////////////////////////////////////////////////////
    // Melody that plays when game starts
    int startTune[]={
    NOTE_C4, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_C4,
    NOTE_C5, NOTE_F5, NOTE_G5, 
    };
    int startTuneDurations[]={
    // 6, 4, 4, 10, 10, 10, 10, 10, 10, 5
    9, 7, 7, 13, 13, 13, 13, 13, 13, 8
    };
    // Function
    void start_tune(){
    pinMode(12, OUTPUT);
    for (int x = 0; x < 10; x++){
        int Duration = 1000 / startTuneDurations [x];
        tone(12, startTune[x], Duration);

        int quite = Duration * 1.30;
        delay (quite);

        noTone(12);
    }
    }
    ////////////////////////////////////////////////////////
    // Melody that plays when someone wins the game
    int winTune[]={
    NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, NOTE_C4, NOTE_B3,
    NOTE_C4};
    int winTuneDurations[]={
    4, 8, 8, 4, 4, 4, 4, 4
    };
    // Function
    void win_tune(){
    pinMode(12, OUTPUT);
    for (int x = 0; x < 8; x++){
        int Duration = 1000 / winTuneDurations [x];
        tone(12, winTune[x], Duration);

        int quite = Duration * 1.30;
        delay(quite);

        noTone(12);
    }
    }
    ////////////////////////////////////////////////////////
    // Melody that plays when a player scores a point
    int pointTune[]={
    NOTE_G5, NOTE_G6
    };
    int pointTuneDurations[]={
    4, 8
    };
    // Function
    void point_tune(){
    pinMode(12, OUTPUT);
    for (int x = 0; x < 2; x++){
        int Duration = 1000 / pointTuneDurations [x];
        tone(12, pointTune[x], Duration);

        int quite = Duration * 1.30;
        delay(quite);
    } 
    noTone(12);
    }

#### Pitches.h

    #define NOTE_B2  123
    #define NOTE_C3  131
    #define NOTE_D3  147
    #define NOTE_E3  165
    #define NOTE_F3  175
    #define NOTE_G3  196
    #define NOTE_A3  220
    #define NOTE_B3  247
    #define NOTE_C4  262
    #define NOTE_D4  294
    #define NOTE_E4  330
    #define NOTE_F4  349
    #define NOTE_G4  392
    #define NOTE_A4  440
    #define NOTE_B4  494
    #define NOTE_C5  523
    #define NOTE_D5  587
    #define NOTE_E5  659
    #define NOTE_F5  698
    #define NOTE_G5  784
    #define NOTE_A5  880
    #define NOTE_B5  988
    #define NOTE_G6  1568

### Light Show code

```
void startLightShow() {

  for (int i = 0; i < num_LED; i++) {
    ring.setPixelColor(i, random(255), random(255), random(255));
    delay(200);
    ring.show();
  }
  ring.clear();

  for (int i = 0; i < num_LED1; i++) {
    ring1.setPixelColor(i, random(255), random(255), random(255));
    delay(200);
    ring1.show();
  }
  ring1.clear();

  for (int i = 0; i < 8; i++) {
    for (int k = 0; k < 5; k++) {
      for (int i = 0; i < num_LED; i += 2) {
        ring.setPixelColor(i, random(255), random(255), random(255));
      }
      ring.show();
      //delay(10);
      ring.clear();

      for (int i = 0; i < num_LED1; i += 2) {
        ring1.setPixelColor(i, random(255), random(255), random(255));
      }
      ring1.show();
      //delay(10);
      ring1.clear();

      for (int i = 1; i < num_LED; i += 2) {
        ring.setPixelColor(i, random(255), random(255), random(255));
      }
      ring.show();
      //delay(10);
      ring.clear();

      //neopixel1
      for (int i = 1; i < num_LED1; i += 2) {
        ring1.setPixelColor(i, random(255), random(255), random(255));
      }
      ring1.show();
      //delay(10);
      ring1.clear();
    }
  }
  show_none();
  show_n();
}
```

### Ultra-sonic sensors code

```
int player0_sensor() {

  //Pulse for player 0 sensor
  digitalWrite(player0_trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(player0_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(player0_trigPin, LOW);


  pinMode(player0_echoPin, INPUT);
  duration = pulseIn(player0_echoPin, HIGH);

  // Convert the time into a distance
  cm = (duration / 2) / 29.1;

  return cm;
}


int player1_sensor() {
  
  //Pulse for player 1 sensor
  digitalWrite(player1_trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(player1_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(player1_trigPin, LOW);


  pinMode(player1_echoPin, INPUT);
  duration = pulseIn(player1_echoPin, HIGH);

  // Convert the time into a distance
  cm = (duration / 2) / 29.1;

  return cm;
}

```