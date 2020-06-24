  
  void setSettings(int var, int value);
  void loopButton(){
    lcd_menu = read_buttons();
    switch(lcd_menu){
      case btnUP:
          if(buttonWasReleased){
            buttonWasReleased=false;
            Serial.println("display");
            switch(main_menu){
              case 0:                       // increase master volume
                 if(setvalue[0]<maxvalue[0]){
                  setvalue[0]++;
                  adjustment = true;
                 }
                 else{
                  setvalue[0] = maxvalue[0];
                 }
                 setSettings(0, setvalue[0]);
                 break;
              case 1:
              case 2:
              case 3:
              case 4:
              case 5:
              case 6:
              case 7:
                 if(setvalue[selecteditem]<maxvalue[selecteditem]){  // fade to channel 2
                  setvalue[selecteditem]++;
                 }
                 else{
                  setvalue[selecteditem] = maxvalue[selecteditem];
                 }
                 setSettings(selecteditem, setvalue[selecteditem]);
                 break;
              case 10:                       // menu adjust
                 selecteditem++;
                 cursor++;
                 if(cursor > 1) cursor = 1;
                 if(selecteditem > 7){
                  selecteditem = 0;
                  cursor = 0;
                 }
                 break;

            }  // switch main_menu ends here
          }  // buttonWasReleased ends here
          break;

      case btnDOWN:
          if(buttonWasReleased){
            buttonWasReleased=false;
            switch(main_menu){
              case 0:                       // decrease master volume
                 if(setvalue[0]>minvalue[0]){
                  setvalue[0]--;
                  adjustment = true;
                 }
                 else{
                  setvalue[0] = minvalue[0];
                 }
                 setSettings(0, setvalue[0]);
                 break;
              case 1:
              case 2:
              case 3:
              case 4:
              case 5:
              case 6:
              case 7:
                 if(setvalue[selecteditem]>minvalue[selecteditem]){
                  setvalue[selecteditem]--;
                 }
                 else{
                  setvalue[selecteditem] = minvalue[selecteditem];
                 }
                 setSettings(selecteditem, setvalue[selecteditem]);
                 break;
              case 10:                       // menu decrease
                 selecteditem--;
                 cursor--;
                 if(cursor < 0) cursor = 0;
                 if(selecteditem < 0){
                  selecteditem = 7;
                  cursor = 1;
                 }
                 break;

            }  // switch main_menu ends here
          }  // buttonWasReleased ends here
          break;

      case btnSELECT:
          if(buttonWasReleased){
            buttonWasReleased=false;
            switch(main_menu){
              case 0:
                  main_menu=1;
                  break;
              case 1:
                  main_menu=10;
                  selecteditem = 0;
                  cursor = 0;
                  break;
              case 2:
              case 3:
              case 4:
              case 5:
              case 6:
              case 7:
                  main_menu = 10;
                  break;
              case 10:
                  main_menu = selecteditem;
                  break;
            }
          }
          break;
      case btnNONE:
          if(!buttonWasReleased){
            buttonWasReleased = true;
            display_init = false;
            lcd_timer = 0;
            lcd.clear();
          }
          break;
    }
  }
