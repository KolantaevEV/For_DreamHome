#include "ssd.h"

static const uint8_t digit_code[] = { // XGFEDCBA
                                        0b11111100,    // 0
                                        0b01100000,    // 1
                                        0b11011010,    // 2
                                        0b11110010,    // 3
                                        0b01100110,    // 4
                                        0b10110110,    // 5
                                        0b10111110,    // 6
                                        0b11100000,    // 7
                                        0b11111110,    // 8
                                        0b11110110,    // 9
                                        0b11101110,    // A
                                        0b00111110,    // b
                                        0b10011100,    // C
                                        0b01111010,    // d
                                        0b10011110,    // E
                                        0b10001110,    // F
                                        0b00000001,    // : (16)
                                        0b00000010     // - (17)
                                        };

static const uint8_t bright_code[] = {0b00000001,    // 0
                                      0b10010001,    // 1
                                      0b01010001,    // 2
                                      0b11010001,    // 3
                                      0b00110001,    // 4
                                      0b10110001,    // 5
                                      0b01110001,    // 6
                                      0b11110001};   // 7



void lcd_print_to_display(uint16_t num, num_type type, uint8_t start_pos, uint8_t brightness, uint8_t colon)
{
  uint32_t div[LCD_MAX_DIGITS] = {0};
    for (uint8_t i = 0; i < LCD_MAX_DIGITS; i++)
    {
      div[i] = 1;
      for (uint8_t j = 0; j < i; j++, div[i] *= 10);
    }
  uint8_t i2c_msg[LCD_MAX_DIGITS + 3];
    i2c_msg[0] = (uint8_t)TM1637_I2C_CMD1;
    i2c_msg[1] = (uint8_t)TM1637_I2C_CMD2;
    i2c_msg[sizeof(i2c_msg) - 1] = bright_code[brightness];
  uint8_t flag = 0;

  if (type == LCD_HEX)
  {
    for (int8_t i = (LCD_MAX_DIGITS - 1); i >= 0; i--)
    {
      i2c_msg[LCD_MAX_DIGITS - i + 1] = (num >> (i * 4)) & 0x0F;
      if (i2c_msg[LCD_MAX_DIGITS - i + 1] == 0 && !flag && i)
      {
        i2c_msg[LCD_MAX_DIGITS - i + 1] = 0xFF;
      }
      else flag = 1;
      i2c_msg[LCD_MAX_DIGITS - i + 1] = lcd_get_digit_code(i2c_msg[LCD_MAX_DIGITS - i + 1]);
    }
  }
  else if (type == LCD_DEC)
  {
    for (int8_t i = (LCD_MAX_DIGITS - 1); i >= 0; i--)
    {
      i2c_msg[LCD_MAX_DIGITS - i + 1] = (uint8_t)(num / div[i]);
      num -= i2c_msg[LCD_MAX_DIGITS - i + 1] * div[i];
      if (i2c_msg[LCD_MAX_DIGITS - i + 1] == 0 && !flag && i && !colon)
      {
        i2c_msg[LCD_MAX_DIGITS - i + 1] = 0xFF;
      }
      else flag = 1;
      i2c_msg[LCD_MAX_DIGITS - i + 1] = lcd_get_digit_code(i2c_msg[LCD_MAX_DIGITS - i + 1]) | ((colon) ? lcd_get_digit_code(16) : 0);
    }
  }

  if (start_pos)
  {
    memmove(&i2c_msg[2], &i2c_msg[2 + start_pos], LCD_MAX_DIGITS - start_pos);
    memset(&i2c_msg[2 + LCD_MAX_DIGITS - start_pos], 0x00, start_pos);
  }

  send_bytes(&i2c_msg[0], 1);
  send_bytes(&i2c_msg[1], LCD_MAX_DIGITS + 1);
  send_bytes(&i2c_msg[sizeof(i2c_msg)-1], 1);
}

uint8_t lcd_get_digit_code(uint8_t num)
{
  return (num < sizeof(digit_code)) ? digit_code[num] : (uint8_t)LCD_SEG_NONE;
}

void send_bytes(uint8_t *buff, uint8_t cnt)
{
  for (uint8_t i = 0; i < cnt; i++)
  {
    while(!(I2C0->STATUS & I2C_STATUS_TXBL));
    I2C0->TXDATA = buff[i];
    I2C0->CMD = I2C_CMD_START;
  }

  while(!(I2C0->STATUS & I2C_STATUS_TXC));
  I2C0->CMD = I2C_CMD_STOP;
}

void reset_i2c(void)
{
  I2C0->CMD = I2C_CMD_STOP;
  I2C0->CMD = I2C_CMD_ABORT;
  I2C0->CMD = I2C_CMD_START;
  I2C0->CMD = I2C_CMD_STOP;
}

void i2c_init(void)
{
  I2CSPM_Init_TypeDef i2c_struct = {0};

  i2c_struct.port = I2C0;
  i2c_struct.sclPort = gpioPortC;
  i2c_struct.sclPin = 11;
  i2c_struct.portLocationScl = 15;
  i2c_struct.sdaPort = gpioPortC;
  i2c_struct.sdaPin = 10;
  i2c_struct.portLocationSda = 15;
  i2c_struct.i2cRefFreq = 0;
  i2c_struct.i2cMaxFreq = 57600;
  i2c_struct.i2cClhr = i2cClockHLRStandard;
  CMU_ClockEnable(cmuClock_GPIO, true);
  I2CSPM_Init(&i2c_struct);
  reset_i2c();
}
