#ifndef _MCP3008_H
#define _MCP3008_H

#if ARDUINO >= 100
 #include "Arduino.h"

#else
 #include "WProgram.h"
#endif



//SPISettings mcp3008_set(2000000, MSBFIRST, SPI_MODE0);

class mcp3008 
{
public:
  mcp3008(uint8_t ss = SS);
  //void init(void);
  uint16_t readADC(uint8_t channel, uint8_t samples = 4, uint8_t mode = 1, uint8_t polarity = 0);
private:
  uint8_t _ss;  
 
};






#endif