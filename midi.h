#ifndef _MIDI_H_
#define _MIDI_H_

#define MIDI_MAX 84
#define MIDI_MIN 48
#define SAMPLE_RATE 22050 // samples per second
#define NOISE (86 - 48)

#include <stdint.h>
#include <stdlib.h>

typedef struct Note {
  uint32_t duration; //samples
  byte midi; // midi number, between 48 and 84. 85 = silence, 86 = noise
} Note;

typedef struct Song {
  Note * notes;
  uint32_t numNotes;
  uint32_t curNote;
  uint32_t curTime;
  uint32_t curDuration;
  byte curMidi;
  byte curNoteTime;
  byte flags; // Unused currently
} Song;

void setupMidi();

//durations in seconds, 
Note makeNote(float duration, byte midi);

Song * makeSong(float * durations, byte * midis, uint32_t num);

byte updateSong(Song * song); //To be called every sample?

#endif //_MIDI_H_
