
/****************************************************************************
   RING PONG V2.0

   MADE BY

   Ruaraidh Curran 40209895
   Alina Maksimova 40333354
   Zak Rodger      40415721

 ***************************************************************************/

#include <Adafruit_NeoPixel.h> //used to control the ring
#include "pitches.h"

#define RING_PIN 6      //control PIN of the neopixel ring

//ADD*** control of the neopixel ring1
#define RING1_PIN 9

#define button0_PIN 2   //control PIN for the first button
#define button1_PIN 3   //control PIN for the 2nd button
#define num_LED 60      //number of LED on the ring

//ADD*** number of LED on the ring1
#define num_LED1 24

Adafruit_NeoPixel ring = Adafruit_NeoPixel(num_LED, RING_PIN, NEO_GRB + NEO_KHZ800);

//ADD*** Define NeoPixel as ring1
Adafruit_NeoPixel ring1 = Adafruit_NeoPixel(num_LED1, RING1_PIN, NEO_GRB + NEO_KHZ800);

uint32_t color;

bool game_ON = 0;          //state if the game is ON or not
bool player = 0;           //select the current player
int point_player0 = 0;     //number of player 0 points
int point_player1 = 0;     //number of player 1 points
bool dir = 0;              //select the direction of the game
int k = 4;                 //position of the ball
int game_speed = 100;      //speed of the ball
int normal = 100;          //normal speed
unsigned long timer;       //timer used to accelerate the game

//ADD*** button States var
int buttonState = 0;
int buttonState1 = 0;

//ADD*** game count
int index = 0;

//ADD*** Measurements for sensors
long duration, cm, inches;

//ADD*** Player 1 sensor
int player0_trigPin = 11;    // Trigger
int player0_echoPin = 12;    // Echo

//ADD*** Player 2 sensor
int player1_trigPin = 7;
int player1_echoPin = 8;

//ADD*** Sensor detection distance in centimetres
int sensorDistance = 7;

//ADD*** Pin number for buzzer
int buzzerPin = 13;

//ADD*** Notes for buzzer sounds
int winTune[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, NOTE_C4, NOTE_B3,
  NOTE_C4
};

int winTuneDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};


int startTune[] = {
  NOTE_C4, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_C4,
  NOTE_C5, NOTE_F5, NOTE_G5
};

int startTuneDurations[] = {
  9, 7, 7, 13, 13, 13, 13, 13, 13, 8
};

int pointTune[] = {
  NOTE_G5, NOTE_G6
};

int pointTuneDurations[] = {
  4, 8
};

int passNote[] = {
  NOTE_F4
};

int passNoteDurations[] = {
  9
};

/**************************************************************************
   SETUP
*************************************************************************/

void setup() {
  //pinMode(button0_PIN, INPUT_PULLUP); //Using the pullup option
  //pinMode(button1_PIN, INPUT_PULLUP);

  //show_n();

  //Player 0 sensor
  pinMode(player0_trigPin, OUTPUT);
  pinMode(player0_echoPin, INPUT);

  //Player 1 sensor
  pinMode(player1_trigPin, OUTPUT);
  pinMode(player1_echoPin, INPUT);

  ring.begin(); //switch on the ring

  //ADD*** switch on the ring1
  ring1.begin();

  randomSeed(analogRead(A5));

  //UPDATE*** to have lightshow before 1st game starts
  if (!index == 0) {
    ring_blink(color, 500, 4);  //starting "animation"

  } else {

    start_tune(); // Added buzzer tune before game starts
    startLightShow(); // Added light show before game starts

  }

}

/**************************************************************************
   LOOP
 *************************************************************************/

void loop() {

  
  //Initializing game if player 0 is selected
  if (!game_ON && player == 0) {
    k = 4;
    //Light on the border (green), the ball (blueish) and the points (red)
    ring.setPixelColor(3, 0, 100, 0);
    ring.setPixelColor(ring.numPixels() - 4, 0, 100, 0);
    ring.setPixelColor(4, 0, 50, 75);

    //UPDATE*** display score on ring1 for player 0
    for (int i = 2; i < point_player0 + 2; i++) {
      ring1.setPixelColor(i, 100, 0, 0);
    }
    for (int i = ring1.numPixels() - 3; i > ring1.numPixels() - point_player1 - 3; i--) {
      ring1.setPixelColor(i, 100, 0, 0);
    }

    ring.show();

    //ADD*** show changes ring1
    ring1.show();

    //Actions if player 0 engage the game
    if (player0_sensor() < sensorDistance) {
      game_ON = 1;
      player = !player;
      normal = 100;
      game_speed = normal;
      delay(1000);
      timer = millis();
    }
  }
  //Initializing game if player 1 is selected
  else if (!game_ON && player == 1) {
    k = ring.numPixels() - 5;

    //Light on the border (green), the ball (blueish) and the points (red)
    ring.setPixelColor(3, 0, 100, 0);
    ring.setPixelColor(ring.numPixels() - 4, 0, 100, 0);
    ring.setPixelColor(ring.numPixels() - 5, 0, 50, 75);

    //UPDATE*** display score on ring1 for player 1
    for (int i = 2; i < point_player0 + 2; i++) {
      ring1.setPixelColor(i, 100, 0, 0);
    }
    for (int i = ring1.numPixels() - 3; i > ring1.numPixels() - point_player1 - 3; i--) {
      ring1.setPixelColor(i, 100, 0, 0);
    }

    ring.show();

    //ADD*** show changes ring1
    ring1.show();


    //Actions if player 1 engages the game -
    if (player1_sensor() < sensorDistance) {
      game_ON = 1;
      player = !player;
      normal = 100;
      game_speed = normal;
      delay(1000);
      timer = millis();
    }
  }

  // GAME IS ON
  else {

    //ADD*** changes game count to 1
    index = 1;

    //Update the display
    comete(k, 0, 50, 75);

    ring.setPixelColor(3, 0, 100, 0);
    ring.setPixelColor(ring.numPixels() - 4, 0, 100, 0);

    //IF PLAYER 1 is playing
    if (player == 1) {

      //When Player 1 engages the sensor
      if (player1_sensor() < sensorDistance) {

        //At the best moment
        if (k == ring.numPixels() - 5) {
          dir = !dir; //direction inversion
          game_speed = normal * 0.5; // super speed
          pass_note();
          player = !player; //player switch
        }

        //At the good moment
        else if (k > ring.numPixels() - 12 && k < ring.numPixels() - 5) {
          dir = !dir; //direction inversion
          game_speed = normal;  //normal speed
          pass_note();
          player = !player; //player switch
        }

        //If he pushes at a wrong moment
        else {
          game_ON = 0;               //Game OFF
          point_player0 ++;          // + 1pt for other player
          point_tune();
          player = !player;          // player switch
          game_speed = normal * 0.75; //engagement speed
          ring_blink(color, 150, 2); //ring blink
          show_none(); //screen off
        }
      }
    }

    //IF PLAYER 0 is playing
    if (player == 0) {

      //When Player 0 engages the sensor
      if (player0_sensor() < sensorDistance) {

        //At the best moment
        if (k == 4) {
          dir = !dir; //direction inversion
          game_speed = normal * 0.5; // super speed
          pass_note();
          player = !player; //player switch
        }

        //At the good moment
        else if (k < 12 && k > 4) {
          dir = !dir; //change direction
          game_speed = normal;// Normal speed
          pass_note();
          player = !player; //player switch
        }

        //If he pushes at a wrong moment
        else {
          game_ON = 0;              //Game OFF
          point_player1 ++;         // + 1pt for other player
          point_tune();
          player = !player;         // player switch
          game_speed = normal * 0.75; //engagement speed
          ring_blink(color, 150, 2); //ring blink
          show_none();              //screen off
        }
      }

    }

    //MOVING THE BALL
    if (!dir) {
      k++;
      delay(game_speed);

      //Game fails for player 0 if they let the ball go too far
      if (k > ring.numPixels() - 5) {
        game_ON = 0;
        point_player0 ++;
        point_tune();
        player = !player;
        k = 4;
        ring_blink(color, 150, 2);
        show_none();
      }
    }
    else {
      k--;
      delay(game_speed);

      //Game fail for player 1 if they let the ball go too far
      if (k < 4) {
        game_ON = 0;       // Finish game
        point_player1 ++;  // Give other player point;
        point_tune();
        player = !player;  // Change the player ;
        k = ring.numPixels() - 5;
        ring_blink(color, 150, 2);
        show_none();
      }
    }
  }

  // ENDING THE GAME IF A PLAYER HAS MORE THAN 3 POINTS
  if (point_player0 > 3 || point_player1 > 3) {
    win_tune();
    ring_blink(color, 150, 2);
    game_ON = 0;
    player = 0;
    point_player0 = 0;
    point_player1 = 0;
    game_speed = 100;
    k = 4;
    dir = 0;
  }

  //ACCELERATING THE GAME
  if (millis() - timer > 5000) {
    normal = normal * 0.8;
    timer = millis();
  }
}


/**************************************************************************
   FUNCTIONS
 *************************************************************************/
//ring
void show_all(uint32_t color) {
  for (int i = 0; i < ring.numPixels(); i++) {
    ring.setPixelColor(i, color);
  }
  ring.show();
}

void show_none() {
  for (int i = 0; i < ring.numPixels(); i++) {
    ring.setPixelColor(i, 0, 0, 0);
  }
  ring.show();
}

//ring1
//ADD*** functions for ring1
void show_a(uint32_t color) {
  for (int i = 0; i < ring1.numPixels(); i++) {
    ring1.setPixelColor(i, color);
  }
  ring1.show();
}

void show_n() {
  for (int i = 0; i < ring1.numPixels(); i++) {
    ring1.setPixelColor(i, 0, 0, 0);
  }
  ring1.show();
}

//UPDATE*** to display ring1 functions
void ring_blink(uint32_t color, int wait, int num_repet) {
  //Creation of a random color for the game
  color = ring.Color(255, 204, 153);
  for (int i = 0 ; i < num_repet ; i++) {
    show_all(color);
    show_a(color);
    delay(wait);
    show_none();
    show_n();
    delay(wait);
  }
}

void comete(int pos, byte r, byte g, byte b) {
  for (int i = 0; i < ring.numPixels(); i++) {
    ring.setPixelColor(i, int32bittoRGB(ring.getPixelColor(i), 'r') / 3, int32bittoRGB(ring.getPixelColor(i), 'g') / 3, int32bittoRGB(ring.getPixelColor(i), 'b') / 3);
    ring.setPixelColor(pos, r, g, b);
  }
  ring.show();
}

uint8_t int32bittoRGB ( uint32_t color, char value )
{
  switch ( value ) {
    case 'r': return (uint8_t)(color >> 16);
    case 'g': return (uint8_t)(color >>  8);
    case 'b': return (uint8_t)(color >>  0);
    default:  return 0;
  }
}



/****************************************************************************

   Added buzzer noise functions

***************************************************************************/

void start_tune() {
  pinMode(buzzerPin, OUTPUT);
  for (int x = 0; x < 10; x++) {
    int Duration = 1000 / startTuneDurations [x];
    tone(buzzerPin, startTune[x], Duration);

    int quite = Duration * 1.30;
    delay (quite);

    noTone(buzzerPin);
  }
}

void win_tune() {
  pinMode(buzzerPin, OUTPUT);
  for (int x = 0; x < 8; x++) {
    int Duration = 1000 / winTuneDurations [x];
    tone(buzzerPin, winTune[x], Duration);

    int quite = Duration * 1.30;
    delay(quite);

    noTone(buzzerPin);
  }
}

void point_tune() {
  pinMode(buzzerPin, OUTPUT);
  for (int x = 0; x < 2; x++) {
    int Duration = 1000 / pointTuneDurations [x];
    tone(buzzerPin, pointTune[x], Duration);

    int quite = Duration * 1.30;
    delay(quite);
  }
  noTone(buzzerPin);
}


void pass_note() {
  pinMode(buzzerPin, OUTPUT);
  for (int x = 0; x < 1; x++) {
    int Duration = 1000 / passNoteDurations [x];
    tone(buzzerPin, passNote[x], Duration);

    int quite = Duration * 1;
    delay (quite);

    noTone(buzzerPin);
  }
}



/****************************************************************************

   Added light show function for when game is started

***************************************************************************/

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


/***************************************************************************

   Added functions for ultrasonic sensors

***************************************************************************/

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
