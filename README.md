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
3. Adjustable game speed (the speed that the blue led goes at between the two players green LED's).
4. Point counter.
5. Adjustable max score.
6. Buzzing noises indicating a win and points gained.
7. LED light show on start-up and when someone wins.
8. Creating a nice portable case for the came.

### Deliverables

1. Code for Project
2. Marketing Video

### Link to original project


### Links to hardware used


## Examples of changes to code

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