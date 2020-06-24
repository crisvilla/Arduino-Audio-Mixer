  /*-----------------+
   *  Encoder sketch |
   *  ---------------+
   */

  void setSettings(int var, int value);
  void encoder(){
    static int newPosition = 0;       // static value
    newPosition = enc.read();         // read encoder
    newPosition = newPosition / 4;
    //Serial.println(newPosition);      // uncomment for debugging purpose
    if(newPosition != oldPosition){
      if(newPosition > oldPosition) para = 1;
      else para = -1;
      oldPosition = newPosition;

      switch(main_menu){
        case 0:               // main volume adjust
           setvalue[0] = constrain(setvalue[0] + para, minvalue[0], maxvalue[0]);
           setSettings(0, setvalue[0]);
           break;
        case 1:               // fader adjust
           setvalue[1] = constrain(setvalue[1] + para, minvalue[1], maxvalue[1]);
           setSettings(1, setvalue[1]);
           break;

        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
           setvalue[selecteditem] = constrain(setvalue[selecteditem] + para,minvalue[selecteditem],maxvalue[selecteditem]);
           setSettings(selecteditem, setvalue[selecteditem]);
           break;
           
        case 10:                                  // menu selection item
           selecteditem = selecteditem + para;
           cursor = cursor + para;
           if(cursor > 1) cursor = 1;
           else if(cursor < 0) cursor = 0;
           if(selecteditem > 7){
             selecteditem = 0;
             cursor = 0;
           }
           else if(selecteditem < 0){
             selecteditem = 7;
             cursor = 1;
           }
           break;
      }
      adjustment = true;
      display_init = false;
      lcd_timer = 0;
      lcd.clear();
    }
    para = 0;
  }
