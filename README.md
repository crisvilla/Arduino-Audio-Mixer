# Arduino-Audio-Mixer
This project was an attempt to redesign my old audio mixer posted on Youtube having all the libraries required to run it. This is a free software and u can modify as long as u want
DS3231 link: https://github.com/rodan/ds3231
  /*--------------------------------|
   * This code will demonstrate how |
   * how to control I2C audio chips |
   * TDA7319 and PT
   *                                |
   *   TX  1         - RAW          |     5V
   *   RX  0         - GND          |     |
   *   GND -         - RST          |     \
   *   GND -         - VCC          |     /
   *   enc 2        A3 N/A          |     \   4.7k
   *   enc 3        A2 N/A          |     /
   *   D4  4        A1 N/A          |     |     1uf/50v
   *   D5  5        A0 <------------------0-----||-----< audio input
   *   D6  6        13 N/A          |     |
   *   D7  7        12 N/A          |     /
   *   RS  8        11 N/A          |     \   4.7k
   *   EN  9        10 N/A          |     /
   *       A4 A5 A6 A7              |     \
   *                                |     |
   * -------------------------------|    Gnd
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
