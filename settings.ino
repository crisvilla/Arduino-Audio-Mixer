  /*---------------------+
   *      SETTINGS       |
   *--------------------*/


  void setSettings(int var, int value){
    switch(var){
      case 0:                // volume
         audio.setVolume(vol[value]);
         audio.setVolume(vol[value] + 1);
         break;
      case 1:                // fader
         mixer.setChannelVolume(fader[15 + value],0);
         mixer.setChannelVolume(fader[15 + value],1);
         mixer.setChannelVolume(fader[15 - value],2);
         mixer.setChannelVolume(fader[15 - value],3);
         break;
      case 2:                // bass
         audio.setBass(value);
         break;
      case 3:                // midrange
         audio.setMiddle(value);
         break;
      case 4:                // treble
         audio.setTreble(value);
         break;
      case 5:                // backlight
         analogWrite(baklytpin,value);
         break;
    }
  }
