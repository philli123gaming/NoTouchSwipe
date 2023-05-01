/*!
 * @file GestureRecognize_HighRate.ino
 * @brief Present the 9 built-in gestures data the sensor supports. 
 * @n Wave your hand above the sensor (within 0~20cm), it can recognize 9 kinds of gestures: move up, down, left, right, forward,
 * @n backward, clockwise, anti-clockwise, wave.
 * @n For more usages of the sensor, refer to the description about setGestureHighRate in function setup.
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      [Alexander](ouki.wang@dfrobot.com)
 * @maintainer  [fary](feng.yang@dfrobot.com)
 * @version  V1.0
 * @date  2019-07-16
 * @url https://github.com/DFRobot/DFRobot_PAJ7620U2
 */

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#include <DFRobot_PAJ7620U2.h>
#endif
// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 6  // On Trinket or Gemma, suggest changing this to 1
int ResetPin = 12;

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 24  // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

DFRobot_PAJ7620U2 paj;
DFRobot_PAJ7620U2::eGesture_t gesture = paj.getGesture();


void setup() {
  digitalWrite(ResetPin, HIGH);  // Set digital pin to 5V
  pinMode(ResetPin, OUTPUT);     // Set the digital pin to an OUTPUT pin
  Serial.begin(115200);
  delay(300);
  Serial.println("Gesture recognition system base on PAJ7620U2");

  while (paj.begin() != 0) {
    Serial.println("initial PAJ7620U2 failure! Please check if all the connections are fine,
                    #  or if the wire sequence is correct?");
    delay(500);
  }
  Serial.println("PAJ7620U2 init completed, start to test the gesture recognition function");

  paj.setGestureHighRate(true);

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin();                        // INITIALIZE NeoPixel strip object (REQUIRED)
  for (int i = 0; i < NUMPIXELS; i++) {  // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));

    pixels.show();  // Send the updated pixel colors to the hardware.

    delay(10);  // Pause before next pass through loop
  }
}

void startgame() {
  pixels.clear();
  Serial.println("Starting Game");
  for (int i = 0; i < 3; i++) {
    for (int i = 0; i < 24; i++) {  // loops pixels red to show starting
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
      pixels.show();  // Send the updated pixel colors to the hardware.
      delay(30);      // Pause before next pass through loop
    }
    pixels.clear();
    delay(70);
  }

  for (int i = 0; i < NUMPIXELS; i++) {
    if (i < 3 or i > 20) {
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
      pixels.show();  // Send the updated pixel colors to the hardware.
      delay(30);
    } else if (i < 9 and i >= 3) {
      pixels.setPixelColor(i, pixels.Color(255, 255, 0));
      pixels.show();  // Send the updated pixel colors to the hardware.
      delay(30);      // Pause before next pass through loop
    } else if (i < 15 and i >= 9) {
      pixels.setPixelColor(i, pixels.Color(255, 0, 255));
      pixels.show();  // Send the updated pixel colors to the hardware.
      delay(30);      // Pause before next pass through loop
    } else if (i < 21 and i >= 15) {
      pixels.setPixelColor(i, pixels.Color(0, 255, 255));
      pixels.show();  // Send the updated pixel colors to the hardware.
      delay(30);      // Pause before next pass through loop
    }
  }

  int Max_lives = 3;
  int current_lives = Max_lives;
  int points = 0;

  while (current_lives > 0) {
    if (current_lives <= 0) { break; }
    int got_point = false;
    pixels.clear();
    float modifier = 1 - (points / 25);
    Serial.println("modifier is " + String(modifier));
    float timer = 500 * modifier;
    Serial.println("timer is " + String(timer));
    //int rand = random(0, 4);  //random number from 0-3 then checks what that number
    int rand = random(1, 4);
    Serial.println("rand is " + String(rand));

    if (rand == 1) {  //is and depending on the position shows light then coded
      for (int i = 0; i < 3; i++) {
        pixels.setPixelColor(i, pixels.Color(255, 255, 0));
        pixels.show();  // Send the updated pixel colors to the hardware.
        delay(10);      // Pause before next pass through loop
      }
      for (int i = 21; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(255, 255, 0));
        pixels.show();  // Send the updated pixel colors to the hardware.
        delay(10);      // Pause before next pass through loop
      }
    }
    if (rand == 2) {
      for (int i = 3; i < 9; i++) {
        pixels.setPixelColor(i, pixels.Color(255, 0, 0));
        pixels.show();  // Send the updated pixel colors to the hardware.
        delay(10);      // Pause before next pass through loop
      }
    }
    if (rand == 3) {
      for (int i = 9; i < 15; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 255, 0));
        pixels.show();  // Send the updated pixel colors to the hardware.
        delay(10);      // Pause before next pass through loop
      }
    }
    if (rand == 4) {
      for (int i = 15; i < 21; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 255, 255));
        pixels.show();  // Send the updated pixel colors to the hardware.
        delay(10);      // Pause before next pass through loop
      }
    }

    for (float i = timer; i > 0; i--) {
      DFRobot_PAJ7620U2::eGesture_t gesture = paj.getGesture();
      if (gesture != paj.eGestureNone) {
        String description = paj.gestureDescription(gesture);  
        //Convert gesture number into string description
        Serial.println("gesture code        = " + String(gesture));
        Serial.println("gesture description  = "+ String(description));
      }

      if ((gesture == 1 and rand == 2) or (gesture == 2 && rand == 4) 
       or (gesture == 4 && rand == 1) or (gesture == 8 && rand == 3)) {
        got_point = 1;
        Serial.println("gesture was " + String(gesture) + " and rand was " + String(rand) + " so now broken");
        break;
      }
      delay(25);
    }


    if (got_point == 0) {
      Serial.println(got_point);
      current_lives = current_lives - 1;
      Serial.println("no point? Lost a life. lives left " + String(current_lives));
      delay(5000);
    } else {
      points = points + 1;
      Serial.println(got_point);
      Serial.println("you got one! points equal " + String(points));
    }
    if (current_lives <= 0) {
      Serial.println("Game lost. || play file this guy stinks.mp3");
      digitalWrite(ResetPin, LOW);  // This command grouunds the reset pin and reboots the Arduino
      break;
      //Serial.println("If it worked, the Arduino will never output this line!");
    }
    delay(30);
  }
}

void loop() {
  DFRobot_PAJ7620U2::eGesture_t gesture = paj.getGesture();
  if (gesture != paj.eGestureNone) {
    String description = paj.gestureDescription(gesture);  //Convert gesture number into string description
    Serial.println("--------------Gesture Recognition System---------------------------");
    Serial.print("gesture code        = ");
    Serial.println(gesture);
    Serial.print("gesture description  = ");
    Serial.println(description);
    Serial.println();
  }

  //MOTION DIRECTION DETECTION LOOPS
  if (gesture == 64) {
    pixels.clear();
    Serial.println("Clockwise");
    for (int i = 0; i < NUMPIXELS; i++) {
      int red = random(0, 255);
      int blue = random(0, 255);
      int green = random(0, 255);
      int randomcolors[] = { red, blue, green };
      pixels.setPixelColor(i, pixels.Color(randomcolors[0], randomcolors[1], randomcolors[2]));
      pixels.show();  // Send the updated pixel colors to the hardware.
      delay(10);      // Pause before next pass through loop
    }
    pixels.clear();
  }
  if (gesture == 128) {
    startgame();
  }
  if (gesture == 1) {
    pixels.clear();
    Serial.println("RIGHT");
    for (int i = 0; i < 12; i++) {
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
      pixels.show();  // Send the updated pixel colors to the hardware.
      delay(10);      // Pause before next pass through loop
    }
    pixels.clear();
  }
  if (gesture == 8) {
    pixels.clear();
    Serial.println("Down");
    for (int i = 6; i < 18; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 255, 0));
      pixels.show();  // Send the updated pixel colors to the hardware.
      delay(10);      // Pause before next pass through loop
    }
  }
  if (gesture == 2) {
    pixels.clear();
    Serial.println("left");
    for (int i = 12; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 255));
      pixels.show();  // Send the updated pixel colors to the hardware.
      delay(10);      // Pause before next pass through loop
    }
  }
  if (gesture == 4) {
    pixels.clear();
    Serial.println("Up");
    for (int i = 0; i < 6; i++) {
      pixels.setPixelColor(i, pixels.Color(255, 255, 0));
      pixels.show();  // Send the updated pixel colors to the hardware.
      delay(10);      // Pause before next pass through loop
    }
    for (int i = 18; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(255, 255, 0));
      pixels.show();  // Send the updated pixel colors to the hardware.
      delay(10);      // Pause before next pass through loop
    }
  }
}
