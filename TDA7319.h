/*
+-----------+
| TDA7319.h |
+-----------+

Required the Wire.h library to be included in your Arduino Sketch.

Use at your own risk. You are being warned.

*/

#ifndef TDA7319_h
#define TDA7319_h

#include "Arduino.h"
#include "Wire.h"


// +----------+
// | #Defines |
// +----------+
// TDA7319 I2C Single Input Stereo Audio Processor
// Used for switching volume, bass, and treble
#define TDA7319_ADDR            0x43


#define COMMAND_VOL_CTRL       0x00 // Master Volume (0..94)
#define COMMAND_BASS_CONTROL   0xC0 // Bass          (-15...15)
#define COMMAND_MIDDLE_CONTROL 0xA0 // Mid           (-15...15)
#define COMMAND_TREBLE_CONTROL 0x80 // Treble        (-15...15)
#define COMMAND_MUTMUX_CONTROL 0xE0 // Input         (enable=15, disable=2)

class TDA7319 {
  
public:
  int init(void); 
  void  setVolume (byte vol);         // 0..94 (0 minimum or no sound)
  void  setBass   (int intBass);      // -15..15
  void  setMiddle (int intMid);       // -15..15
  void  setTreble (int intTreble);    // -15..15
  void  muteOn();
  void  muteOff();

private:
  void  write   (byte command, byte val);
};

#endif