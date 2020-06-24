/*
+-------------+
| TDA7319.cpp |
+-------------+

Arduino library for TDA7319

Use at your own risk. You can modify at anytime according to your needs.

This is a free software. Please don't blame me if it goes wrong.

Cris Villa

*/

#include "TDA7319.h"

// initialize TDA7319
int TDA7319::init(void)   
{   
    delay(400); // in case this is first time - I2C bus not ready for this long on power on with 10uF cref
    unsigned char masterVolumeValue = 0x5E;    //master volume = -15db - temporary at 0
	unsigned char masterVolumeValue1 = 0x5D;   //master volume = -15db - temporary at 0
    unsigned char bassValue   = 0x10;       //Bass   = -0dB   
    unsigned char middleValue = 0x10;       //Middle = -0dB   
    unsigned char trebleValue = 0x10;       //Treble = -0dB   
        

    // set the second volume control to zero
    Wire.beginTransmission(TDA7319_ADDR); // transmit to device 0x86, TDA7319 (43 after moving one char to right)
    Wire.write(95);   
    Wire.endTransmission();       // stop transmitting


    // and finish with the tone controls
    write(COMMAND_VOL_CTRL, masterVolumeValue);
	write(COMMAND_VOL_CTRL, masterVolumeValue1);
    write(COMMAND_BASS_CONTROL, bassValue);   
    write(COMMAND_MIDDLE_CONTROL, middleValue);   
    write(COMMAND_TREBLE_CONTROL, trebleValue);   
}


// TDA7319 has two volume which in this library was made to look like one
// RANGE 0-94 units
void TDA7319::setVolume(byte vol) {

  vol = constrain(vol, 0, 0x5E);
  byte bytvol = 94 - vol;

  write(COMMAND_VOL_CTRL, bytvol);
}


// RANGE -15 to +15 units
void TDA7319::setBass(int Bass) {
  
  int intBass;
  
  if (Bass < 0) intBass = 15 - Bass;
  else intBass = Bass;
    
  write(COMMAND_BASS_CONTROL, intBass);
}

// RANGE -15 to +15 units
void TDA7319::setMiddle(int Mid) {
  
  int intMid;

  if (Mid < 0) intMid = 15 - Mid;
  else intMid = Mid;
    
  write(COMMAND_MIDDLE_CONTROL, intMid);
}

// RANGE -15 to +15 units
void TDA7319::setTreble(int Treble) {
  
  int intTreble;

  if (Treble < 0) intTreble = 15 - Treble;
  else intTreble = Treble;

  write(COMMAND_TREBLE_CONTROL, intTreble);
}



// mute on
void TDA7319::muteOn(void)   
{   
    write(COMMAND_MUTMUX_CONTROL,2); //mute input
}   

// mute off
void TDA7319::muteOff(void)   
{      
    write(COMMAND_MUTMUX_CONTROL,15);  // input active
}


void TDA7319::write(byte command, byte val) {
  
  Wire.beginTransmission(TDA7319_ADDR);
  Wire.write(command | val);
  Wire.endTransmission();
  
  delay(10);
}