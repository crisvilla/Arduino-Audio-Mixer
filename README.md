# Arduino-Audio-Mixer
This project was an attempt to redesign my old audio mixer posted on Youtube having all the libraries required to run it. This is a free software and u can modify as long as u want
DS3231 link: https://github.com/tfg13/DS3231
  /*--------------------------------|
   * This code will demonstrate how |
   * how to control I2C audio chips |
   * TDA7319 and PT
   *                                |     5V
   *   TX  1         - RAW          |     |                    do the same resistor netowrk for right channel and send to A2 of arduino, audio source from TDA7319 pin13.
   *   RX  0         - GND          |     \
   *   GND -         - RST          |     /
   *   GND -         - VCC          |     \   4.7k
   *   enc 2        A3 N/A          |     /
   *   enc 3        A2 <---         |     |     1uf/50v
   *   D4  4        A1 <------------------0-----||-----< L from TDA7319 pin8
   *   D5  5        A0              |     |
   *   D6  6        13 N/A          |     /
   *   D7  7        12 N/A          |     \   4.7k
   *   RS  8        11 N/A          |     /
   *   EN  9        10 N/A          |     \
   *       A4 A5 A6 A7              |     |
   *                                |    Gnd
   * -------------------------------|
   */
   SDA = A4             --------/\/\/\-----
   SCl = A5             |        10k      |
         1uf      10k   |     |\          |
  in1R>--||-----/\/\/\--0-----|-\         |
                        |     |  \        |   1uf/50v
         1uf      10k   |     |   --------0---||------> R output to TDA7319 pin 2
  in2R>--||-----/\/\/\---     |  /
                           ---|+/
                           |  |/
                          Gnd
                          
                        --------/\/\/\-----
                        |        10k      |
         1uf      10k   |     |\          |
  in1L>--||-----/\/\/\--0-----|-\         |
                        |     |  \        |   1uf/50v
         1uf      10k   |     |   --------0---||------> L output to TDA7319 pin 19
  in2L>--||-----/\/\/\---     |  /
                           ---|+/
                           |  |/
                          Gnd
                          
   This is a typical opamp mixer, use 4 channel from PT2258, two channel per audio source
                         PT2258(pins)
                        --------
   audio 1 R in>--||---1|  R   |20---||---> to opamp in1R
                  1uf   |------|     1uf
   audio 1 L in>--||---2|  L   |19---||---> to opamp in1L
                        --------
                        
                        --------
   audio 2 R in>--||---3|  R   |18---||---> to opamp in2R
                  1uf   |------|     1uf
   audio 2 L in>--||---8|  L   |13---||---> to opamp in2L
                        --------
                        
   Non-polar or polarized will do. the rest of the components, just follow the schematic provided in datasheet.
   
   PT2258 datasheet link: https://www.electrokit.com/uploads/productfile/41011/PT2258.pdf
   TDA7319 datasheet link: https://datasheet.octopart.com/TDA7319-STMicroelectronics-datasheet-14143094.pdf
