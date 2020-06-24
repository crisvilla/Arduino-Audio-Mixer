
  /*--------------------------------|
   * This code will demonstrate how |
   * how to control I2C audio chips |
   * TDA7319 and PT
   *                                |
   *   TX  1         - RAW          |
   *   RX  0         - GND          |
   *   GND -         - RST          |
   *   GND -         - VCC          |
   *   N/A 2        A3 N/A          |
   *   RST 3        A2 N/A          |
   *   CE  4        A1 N/A          |
   *   DC  5        A0 AUDIO INPUT  |
   *   DIN 6        13 N/A          |
   *   CLK 7        12 N/A          |
   *   N/A 8        11 N/A          |
   *   N/A 9        10 N/A          |
   *       A4 A5 A6 A7              |
   *                                |
   * -------------------------------|
   */
  // this is a free software and can be used at ur own risk, Cris Villa
  //***************Libraries*****************
  #include <LiquidCrystal.h>
  #include <Encoder.h>
  #include <PT2258.h>
  #include <TDA7319.h>
  #include <DS3231.h>
  #include <Wire.h>

  // lcd device devlaration
  //lcd(rs, en, d4, d5, d6, d7)
  // RS = 8
  // EN = 9
  // D4 = 4
  // D5 = 5
  // D6 = 6
  // D7 = 7
  LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

  // Rotary encoder is wired with the common to ground and the two
  // outputs to pins 2 and 6.
  Encoder enc(3, 2);

  // TONE variables
  TDA7319 audio;
  PT2258 mixer;

  long oldPosition  = -4, newPosition = 0;
  //define some values for lcd menu
  #define btnRIGHT  0
  #define btnUP     1
  #define btnDOWN   2
  #define btnLEFT   3
  #define btnSELECT 4
  #define btnNONE   5
  #define baklytpin 10

  #define sample 50
  

  // ***************some variables********************
  char tmp[16];
  byte char1[8] = {0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18};  // ||
  byte char2[8] = {0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B,0x1B};  // || ||
  byte char3[8] = {0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03};  //    ||
  char *menu[] = {"Master Volume","Fader","Bass","Midrange","Treble","Back light","BL timer","Style"};
  // fader, master volume, bass, mid, treble, brightness, vu style
  int setvalue[] = {0,0,10,0,10,0,5,2};
  int maxvalue[] = {32,15,15,15,15,255,30,2};
  int minvalue[] = {0,-15,-15,-15,-15,0,5,0};
  int vol[] = {0,60,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93};
  int fader[] = {0,0,0,1,1,1,1,1,2,2,2,2,3,3,3,4,5,6,7,8,9,10,15,20,25,30,35,40,50,60,79};
  int para = 0;
  int audioLevel[2];
  DS3231 Clock;

  byte year, month, date, DoW, hour, minute, last_sec, second, temperature;
  long millisec = 0; 

  byte lcd_menu = 0, lcd_timer = 0;
  int main_menu = 0, selecteditem = 0, cursor = 0;
  bool buttonWasReleased=false,adjustment=false,display_init=false;
  
  
  // *********Read buttons*********
  int read_buttons(){
    int adc_key_in = analogRead(A0);  // read analog value from lcd shield button
    if(adc_key_in > 1000) return btnNONE;
    
    // for version V1.1 use these threshold    --------> use ur button analog value here
    if(adc_key_in < 50) return btnDOWN;       // 50
    if (adc_key_in < 400) return btnSELECT;   // 250
    if (adc_key_in < 450) return btnUP;       // 450
    if (adc_key_in < 650) return btnLEFT;     // 650
    if (adc_key_in < 850) return btnRIGHT;    // 850

    // For V1.0 comment the other threshold and use the one below:
    /*
     if (adc_key_in < 50) return btnRIGHT;
     if (adc_key_in < 195) return btnUP;
     if (adc_key_in < 380) return btnDOWN;
     if (adc_key_in < 555) return btnLEFT;
     if (adc_key_in < 790) return btnSELECT;
    */
     return btnNONE; // when all others fail, return this.
  }

  void print_txt();
  void loopDS3231();
  void setupDisplay();
  void loopDisplay();
  void loopButton();
  void encoder();
  

  void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    Wire.begin();
    setupDisplay();

    pinMode(baklytpin,OUTPUT);
    pinMode(A0,INPUT);
    mixer.init();
    delay(10);
    audio.init();
    delay(10);
    //initialized audio chips condition
    mixer.setMasterVolume(0);     // set PT2258 master volume to max
    mixer.setChannelVolume(3,0);  // fader center position
    mixer.setChannelVolume(3,1);
    mixer.setChannelVolume(3,2);
    mixer.setChannelVolume(3,3);
    audio.setBass(setvalue[2]);
    audio.setMiddle(setvalue[3]);
    audio.setTreble(setvalue[4]);
  }

  void loop() {
    // put your main code here, to run repeatedly:
    encoder();
    loopDS3231();
    loopButton();
    loopDisplay();
    if(last_sec != second){
      last_sec = second;
    }
  }
