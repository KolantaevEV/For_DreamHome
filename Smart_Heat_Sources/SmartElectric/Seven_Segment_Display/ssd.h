#ifndef SEVEN_SEGMENT_DISPLAY_SSD
#define SEVEN_SEGMENT_DISPLAY_SSD

#include "stdint.h"
#include "string.h"
#include "i2cspm.h"
#include "em_cmu.h"

#define TM1637_I2C_CMD1    0x02
#define TM1637_I2C_CMD2    0x03
//#define TM1637_I2C_CMD3    0x01
//#define TM1637_I2C_CMD4    0x42

#define LCD_MAX_DIGITS 4
#define LCD_SEG_NONE 0x00

typedef enum
{
  LCD_HEX = 0x10,
  LCD_DEC = 10
} num_type;

void lcd_print_to_display(uint16_t num, num_type type, uint8_t start_pos, uint8_t brightness, uint8_t colon);
uint8_t lcd_get_digit_code(uint8_t num);
void send_bytes(uint8_t *buff, uint8_t cnt);
void i2c_init(void);
void reset_i2c(void);

#endif /* SEVEN_SEGMENT_DISPLAY_SSD */
