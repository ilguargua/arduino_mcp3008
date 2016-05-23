
#include <SPI.h>

#include "mcp3008.h"


mcp3008::mcp3008(uint8_t ss)
{
  _ss = ss;
  pinMode(ss, OUTPUT);
  digitalWrite(ss, LOW);
  digitalWrite(ss, HIGH);
}

/*
 * channel = mode single (1) 0-7 : pseudo-diff (0) 0-3
 * samples = n. of samples; default 4
 * mode = 1 single - 0 pseudo-diff
 * polarity = in diff. mode first channel IN+ 0 ; IN- 1
 */
uint16_t mcp3008::readADC(uint8_t channel, uint8_t samples, uint8_t mode, uint8_t polarity)
{
  uint16_t ret = 0;
  uint8_t adc_set = mode << 7;
  uint8_t first = 0;
  uint8_t second = 0;
  if(mode == 1) adc_set |= channel << 4;
  else
  {
    adc_set |= channel << 5;
    adc_set |= polarity << 4;
  }
  SPI.beginTransaction(SPISettings (2000000, MSBFIRST, SPI_MODE0));
  for(uint8_t i = 0; i < samples; i++)
  {
    digitalWrite(_ss,LOW);
    SPI.transfer(1);
    first = SPI.transfer(adc_set);
    second = SPI.transfer(0);
    digitalWrite(_ss, HIGH);
    ret += second + ((first & 3) << 8);
  }
  SPI.endTransaction();
  return ret / samples;
}