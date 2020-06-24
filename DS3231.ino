  void loopDS3231(){

    Clock.getTime(year, month, date, DoW, hour, minute, second);
    /*second=Clock.getSecond();
    minute=Clock.getMinute();
    hour=Clock.getHour(h12, PM);
    date=Clock.getDate();
    month=Clock.getMonth(Century);
    year=Clock.getYear();*/
  
    temperature=Clock.getTemperature();
    /*if(last_sec != second){
      Serial.print("20");
      Serial.print(year,DEC);
      Serial.print('-');
      Serial.print(month,DEC);
      Serial.print('-');
      Serial.print(date,DEC);
      Serial.print(' ');
      Serial.print(hour,DEC);
      Serial.print(':');
      Serial.print(minute,DEC);
      Serial.print(':');
      Serial.print(second,DEC);
      Serial.print('\n');
      Serial.print("Temperature=");
      Serial.print(temperature); 
      Serial.print('\n');
    }*/
  }
