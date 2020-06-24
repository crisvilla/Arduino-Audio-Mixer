  /*----------------+
   *  Detect Audio  |
   *  --------------+
   */

  void getAudioLevel(){
    unsigned level[2][sample];
    unsigned minLevel[2], maxLevel[2];

    // get audio level sample
    for(int i=0;i<sample;i++){
      level[0][i] = analogRead(A1);
      level[1][i] = analogRead(A2);
    }

    // get the maximum and minimum value from samples
    // initiate values
    minLevel[0] = minLevel[1] = 2000;
    maxLevel[0] = maxLevel[1] = 0;
    for(int i=0;i<2;i++){
      for(int n=0;n<sample;n++){
        if(level[i][n]<minLevel[i]) minLevel[i] = level[i][n];
        if(level[i][n]>maxLevel[i]) maxLevel[i] = level[i][n];
      }
    }
    for(int v=0;v<2;v++){
      audioLevel[v] = map((maxLevel[v] - minLevel[v]),0,1023,0,32);
    }
  }
