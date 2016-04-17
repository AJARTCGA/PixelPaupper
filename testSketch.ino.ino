//Sine out w/ 40kHz sampling rate
//by Amanda Ghassaei
//http://www.instructables.com/id/Arduino-Audio-Output/
//Sept 2012

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
*/

#include <stdlib.h>
#include "midi.h"

Song * mySong;
Song * bulletSound;

void setupSong()
{
  float myDurations[] = {1,   1,  1,  1,  1,  1,  1,  1};
  byte myMidis[] =      {60,  62, 64, 65, 67, 69, 71, 72};
  
  float bulletDurations[] = {.0125,   .0125,  .0125,  .0125,  .0125,  .0125,  .0125,  .0125,  .0125,  .0125,  .0125,  .0125,  .0125,  .0125,  .0125,  .0125,  .0125,  .0125,  .0125,  .0125,  .0125,  .0125,  .0125,  .0125,  .0125};
  byte bulletMidis[] =      {84,  83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60};

  mySong = makeSong(myDurations, myMidis, 8);
  bulletSound = makeSong(bulletDurations, bulletMidis, sizeof(bulletMidis) / sizeof(byte));
}

void setup(){
  //set digital pins 0-7 as outputs
  DDRA |= 11111111;

  Serial.begin(9600);

  setupMidi();
  setupSong();
  
  cli();//disable interrupts
  //set timer0 interrupt at 40kHz
  TCCR0A = 0;// set entire TCCR0A register to 0
  TCCR0B = 0;// same for TCCR0B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 40khz increments
  OCR0A = 90;// = (16*10^6) / (22050*8) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS11 bit for 8 prescaler
  TCCR0B |= (1 << CS11); 
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);
  sei();
  
}


ISR(TIMER0_COMPA_vect){ //22.05kHz interrupt routine
  PORTA = updateSong(bulletSound);
  
}

void loop(){
  //Serial.println(updateSong(mySong));
  //Serial.println(mySong->curDuration);
  
//  Serial.print("curTime: ");
//  Serial.println(mySong->curTime);
//  Serial.print("curNoteTime: ");
//  Serial.println(mySong->curNoteTime);
//  Serial.print("Duration: ");
//  Serial.println(mySong->curDuration);
//  Serial.print("Midi: ");
//  Serial.println(mySong->curMidi);
}


