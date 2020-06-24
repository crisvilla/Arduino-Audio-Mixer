  /*---------------------+
   *      DISPLAY        |
   *--------------------*/

  
  void setupDisplay(){
    lcd.begin(16,2);             // initialize LCD
    lcd.createChar(1,char1);     // our custom characters
    lcd.createChar(2,char2);
    lcd.createChar(3,char3);
    analogWrite(baklytpin,setvalue[8]);
    lcd.setCursor(0, 0);
    lcd.print("AUDIO CONTROLLER");
    lcd.setCursor(0, 1);
    lcd.print("by: Cris Villa");
    delay(1000);
    lcd.clear();
  }
  
  void loopDisplay(){
    static int peakVal[2] = {0, 0};
    static int peakStep[2] = {0, 0};
    switch(main_menu){
      case 0:
         if(adjustment){
           if(!display_init){                       // display volume adjustment
             display_init = true;
             print_txt("Volume",0,0);
             print_txt(dtostrf(setvalue[0],2,0,tmp),14,0);
             barDisplay(setvalue[0], minvalue[0], maxvalue[0], 1);
           }
          }
          else{
           if(!display_init){
           display_init = true;
           }
           else{
            switch(setvalue[7]){
              case 0:                         // display vu meter-one channel only and clock
                 if(last_sec != second){
                   lcd.clear();
                   snprintf(tmp,9,"%02d:%02d:%02d",hour,minute,second);
                   print_txt(tmp,0,0);
                   print_txt(dtostrf(temperature,2,0,tmp),13,0);
                   lcd.println("C");
                   //Serial.println(tmp);
                 }
                 getAudioLevel();
                 barDisplay(audioLevel[1], 0, 32, 1);
                 break;

              case 1:
                 getAudioLevel();           // display 2 channel vu meter
                 for(int i=0;i<2;i++){
                   barDisplay(audioLevel[i], 0, 32, i);
                 }
                 break;

              case 2:                       // display 2 channel vumeter with peak level effects
                 getAudioLevel();
                 for(int i=0;i<2;i++){
                   barDisplay(audioLevel[i], 0, 32, i);
                   if(audioLevel[i]>=peakVal[i]){
                    peakVal[i] = audioLevel[i];
                    peakStep[i] = 0;
                   }
                   if(peakVal[i]>2){
                    int block = map(peakVal[i],0,32,0,16);
                    int bar = peakVal[i] - (block*2);
                    lcd.setCursor(block,i);
                    if(bar == 1) lcd.write(byte (3));
                    else lcd.write(byte (1));
                   }
                   if(peakVal[i] > 2){
                    peakStep[i]++;
                    if(peakStep[i]>=15){
                      peakVal[i]--;
                      peakStep[i] = 0;
                    }
                   }
                 }
                 break;
                 
            }
            
           }
          }
          break;
        case 1:                                  // display fader
          if(!display_init){
           display_init = true;
           print_txt("Ch#1        Ch#2",0,0);
           midBar(setvalue[1]);
          }
          break;

        case 2:                                  // display setup menu
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
          if(!display_init){
           display_init = true;
           print_txt(menu[selecteditem],0,0);
           if(setvalue[selecteditem]<9) print_txt(dtostrf(setvalue[selecteditem],2,0,tmp),13,0);
           else if(setvalue[selecteditem]>99) print_txt(dtostrf(setvalue[selecteditem],2,0,tmp),13,0);
           else print_txt(dtostrf(setvalue[selecteditem],2,0,tmp),14,0);
           if(selecteditem == 2 || selecteditem == 3 || selecteditem == 4){
            midBar(setvalue[selecteditem]);
           }
           else barDisplay(setvalue[selecteditem], minvalue[selecteditem], maxvalue[selecteditem], 1);
          }
          break;

       case 10:                                  // display menu
         if(!display_init){
          display_init = true;
          for(int i=0;i<2;i++){
            print_txt(menu[selecteditem-cursor+i],1,i);
          }
          print_txt(">",0,cursor);
         }
         break;
    }

    if(adjustment || main_menu != 0 || selecteditem != 0){        // routine check for main display
      if(lcd_timer < setvalue[6]){
        if(last_sec != second) lcd_timer++;
      }
      else{
        adjustment = false;
        main_menu = 0;
        selecteditem = 0;
        lcd_timer = 0;
      }
    }
  }

  void print_txt(char temp[16], int x, int y){             // char to display, x,y location
    lcd.setCursor(x,y);
    lcd.print(temp);
  }



  void barDisplay(int data, int min, int max, int x){
    lcd.setCursor(0,x);         // lcd.setCursor(0,x);
    int block = map(data,min,max,0,16);
    int bar = data - (block*2);
    for(int i=0;i<block;i++){
      lcd.write(byte (2));
    }
    if(bar != 0){
      lcd.write(byte (1));
    }
    else lcd.write(1022);
    if(block<16){
      for(int i=16;i>block;i--){
        lcd.setCursor(i,x);
        lcd.write(1022);
      }
    }

    /*Serial.print("block = ");
    Serial.println(block);
    Serial.print("bar = ");
    Serial.println(bar);
    Serial.print("data = ");
    Serial.println(data);
    Serial.println("============");*/
  }

  void midBar(int data){
    //lcd.setCursor(0,1);     // lcd.setCursor(0,1);
    int block = map(data,0,16,0,8);
    int bar = data - (block*2);
    if(data == 0){
      lcd.setCursor(7,1);
      lcd.write(byte (3));
      lcd.write(byte (1));
    }
    else if(data > 0){
      lcd.setCursor(8,1);
      for(int i=0;i<block;i++){
        lcd.write(byte (2));
      }
      if(bar != 0){
        lcd.write(byte (1));
      }
      else lcd.write(1022);
    }
    else if(data < 0){
      lcd.setCursor(7+block,1);
      if(bar != 0){
        lcd.write(byte (3));
      }
      else lcd.write(1022);
      for(int i=0;i<abs(block);i++){
        lcd.write(byte (2));
      }
    }
    /*Serial.print("block = ");
    Serial.println(block);
    Serial.print("bar = ");
    Serial.println(bar);
    Serial.print("data = ");
    Serial.println(data);
    Serial.println("============");*/
  }
