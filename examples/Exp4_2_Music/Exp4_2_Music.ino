/***********************************************************************
 * Exp04_2_Music -- RedBot Experiment 4.2 (Making Music)
 *
 * Rather than just making beeps and boops, what about playing an actual 
 * song? This example includes a "header" file called notes.h that has all
 * the notes on any standard piano #defined to make composing sounds easier.
 *
 * Hardware setup:
 * Plug the included RedBot Buzzer board into the Servo header labeled 9.
 *
 * This sketch was written by SparkFun Electronics,with lots of help from 
 * the Arduino community. This code is completely free for any use.
 * 
 * 23 Sept 2013 N. Seidle/M. Hord
 * 29 Oct 2014 B. Huang
 *
 * Music from: 
 * http://musicwithmstomomi.global2.vic.edu.au/2013/02/18/recorder-its-small-world-after-all/
 ***********************************************************************/

#include "notes.h"  // Individual "notes" have been #defined in the notes.h tab to make
                    // playing sounds easier. noteC4, for example, is defined as 262, the
                    // frequency for middle C. See the tab above? 

#include <RedBot.h> 
RedBotMotors motors;

// Create a couple of constants for our pins.
const int buzzerPin = 9;
const int buttonPin = 12;

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP); // configures the button as an INPUT
  // INPUT_PULLUP defaults it to HIGH.
  pinMode(buzzerPin, OUTPUT);  // configures the buzzerPin as an OUTPUT
}

void loop()
{
  if(digitalRead(buttonPin) == LOW)
  {
    playTwinkleTwinkle();
  }
}

void playTwinkleTwinkle()
{
  playNote(noteC4, QN);
  playNote(noteC4, QN);
  
  playNote(noteG4, QN);    
  playNote(noteG4, QN);  

  playNote(noteA4, QN);    
  playNote(noteA4, QN);  

  playNote(noteG4, HN);
 
  playNote(noteF4, QN);    
  playNote(noteF4, QN);  

}

void playSmallWorld()
{ 
  // we use a custom function below called playNote([note],[duration]) 
  // to play a note and delay a certain # of milliseconds. 
  //
  // Both notes and durations are #defined in notes.h -- WN = whole note, 
  // HN = half note, QN = quarter note, EN = eighth note, SN = sixteenth note.
  //
  playNote(noteG5, HN+QN);
  playNote(noteG5, QN);
  playNote(noteB5, HN);
  playNote(noteG5, HN);
  playNote(noteA5, HN+QN);
  playNote(noteA5, QN);
  playNote(noteA5, HN+QN);
  playNote(Rest, QN);
  playNote(noteA5, HN+QN);
  playNote(noteA5, QN);
  playNote(noteC6, HN);
  playNote(noteA5, HN);
  playNote(noteB5, HN+QN);
  playNote(noteB5, QN);
  playNote(noteB5, HN+QN);
  playNote(Rest, QN);
  playNote(noteB5, HN+QN);
  playNote(noteB5, QN);
  playNote(noteD6, HN);
  playNote(noteB5, HN);
  playNote(noteC6, HN+QN);
  playNote(noteC6, QN);
  playNote(noteC6, HN);
  playNote(noteB5, QN);
  playNote(noteA5, QN);
  playNote(noteD5, WN);
  playNote(noteFs5, WN);
  playNote(noteG5, WN);
}

void playNote(int note, int duration)
// This custom function takes two parameters, note and duration to make playing songs easier.
// Each of the notes have been #defined in the notes.h file. The notes are broken down by 
// octave and sharp (s) / flat (b).
{
  tone(buzzerPin, note, duration);
  delay(duration);
}

/***********************************************************************
 * Troubleshooting for experiment 4.1
 * My code won't upload!
 * - Make sure that your USB cable is plugged into the robot and the
 * computer you're using to write code.
 * - Make sure that the "Power" switch is switched to "ON".
 * - Double check that you have the right serial port selected under the
 * "Tools" menu. The easiest way to check is to see which item
 * disappears from the menu when you unplug the USB cable, and select
 * that one when you plug the board back in.
 * - Make sure the Serial Select switch at the top edge of the board is 
 * switched to "XBEE SW SERIAL", even if you have an Xbee attached.
 * - Check that you have the right board selected under the "Tools" menu.
 * The RedBot is Uno-compatible, so select "Arduino Uno" from the list.
 * My motors aren't turning!
 * - This code demonstrates only the tone() commands; there's no code to
 * make the motors turn.
 ***********************************************************************/




