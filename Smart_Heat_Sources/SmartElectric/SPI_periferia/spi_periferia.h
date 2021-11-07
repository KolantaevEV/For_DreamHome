#ifndef SPI_periferia
#define SPI_periferia

#include "spidrv.h"
#include "sl_sleeptimer.h"
#include "em_usart.h"

#define ITERATION_NUM 5
#define ITERATION_DELAY 10
#define SPI_BUFF_SIZE 3
#define V_REF 4096

// Protocol commands
#define CMD_WRITE_ENABLE                    (0x06)
#define CMD_WRITE_DISABLE                   (0x04)
#define CMD_READ_STATUS                     (0x05)
#define CMD_WRITE_STATUS                    (0x01)
#define CMD_READ_DATA                       (0x03)
#define CMD_PAGE_PROG                       (0x02)
#define CMD_ERASE_SECTOR                    (0x20)
#define CMD_ERASE_BLOCK                     (0xD8)
#define CMD_ERASE_CHIP                      (0xC7)
#define CMD_POWER_DOWN                      (0xB9)
#define CMD_POWER_UP                        (0xAB)
#define CMD_JEDEC_ID                        (0x9F)
#define CMD_UNIQUE_ID                       (0x4B)

// Bitmasks for status register fields
#define STATUS_BUSY_MASK                    (0x01)
#define STATUS_WEL_MASK                     (0x02)

#define SPI_DEVICE_SIZE_8M                  (1048576L)
#define EEPROM_WEEK_SETPOINTS_ADDR          (0x001000)
#define EEPROM_WEEK_SETPOINTS_FLAG_ADDR     (0x002000)

// <h> SPIDRV settings

// <o SL_SPIDRV_EXP_BITRATE> SPI bitrate
// <i> Default: 1000000
#define SL_SPIDRV_EXP_BITRATE           100000

// <o SL_SPIDRV_EXP_FRAME_LENGTH> SPI frame length <4-16>
// <i> Default: 8
#define SL_SPIDRV_EXP_FRAME_LENGTH      8

// <o SL_SPIDRV_EXP_TYPE> SPI mode
// <spidrvMaster=> Master
// <spidrvSlave=> Slave
#define SL_SPIDRV_EXP_TYPE              spidrvMaster

// <o SL_SPIDRV_EXP_BIT_ORDER> Bit order on the SPI bus
// <spidrvBitOrderLsbFirst=> LSB transmitted first
// <spidrvBitOrderMsbFirst=> MSB transmitted first
#define SL_SPIDRV_EXP_BIT_ORDER         spidrvBitOrderMsbFirst

// <o SL_SPIDRV_EXP_CLOCK_MODE> SPI clock mode
// <spidrvClockMode0=> SPI mode 0: CLKPOL=0, CLKPHA=0
// <spidrvClockMode1=> SPI mode 1: CLKPOL=0, CLKPHA=1
// <spidrvClockMode2=> SPI mode 2: CLKPOL=1, CLKPHA=0
// <spidrvClockMode3=> SPI mode 3: CLKPOL=1, CLKPHA=1
#define SL_SPIDRV_EXP_CLOCK_MODE        spidrvClockMode0

// <o SL_SPIDRV_EXP_CS_CONTROL> SPI master chip select (CS) control scheme.
// <spidrvCsControlAuto=> CS controlled by the SPI driver
// <spidrvCsControlApplication=> CS controlled by the application
#define SL_SPIDRV_EXP_CS_CONTROL        spidrvCsControlAuto//spidrvCsControlApplication

// <o SL_SPIDRV_EXP_SLAVE_START_MODE> SPI slave transfer start scheme
// <spidrvSlaveStartImmediate=> Transfer starts immediately
// <spidrvSlaveStartDelayed=> Transfer starts when the bus is idle (CS deasserted)
// <i> Only applies if instance type is spidrvSlave
#define SL_SPIDRV_EXP_SLAVE_START_MODE  spidrvSlaveStartImmediate
// </h>
// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>
// <usart signal=TX,RX,CLK,(CS)> SL_SPIDRV_EXP
// $[USART_SL_SPIDRV_EXP]
#define EEPROM_SPI                               USART2
#define SL_SPIDRV_EXP_PERIPHERAL                 USART2
#define SL_SPIDRV_EXP_PERIPHERAL_NO              2

// USART2 TX on PK0
#define SL_SPIDRV_EXP_TX_PORT                    gpioPortK
#define SL_SPIDRV_EXP_TX_PIN                     0
#define SL_SPIDRV_EXP_TX_LOC                     29

// USART2 RX on PK2
#define SL_SPIDRV_EXP_RX_PORT                    gpioPortK
#define SL_SPIDRV_EXP_RX_PIN                     2
#define SL_SPIDRV_EXP_RX_LOC                     30

// USART2 CLK on PF7
#define SL_SPIDRV_EXP_CLK_PORT                   gpioPortF
#define SL_SPIDRV_EXP_CLK_PIN                    7
#define SL_SPIDRV_EXP_CLK_LOC                    18

// USART2 CS on PA5
#define SL_SPIDRV_EXP_CS_PORT                    gpioPortA
#define SL_SPIDRV_EXP_CS_PIN                     5
#define SL_SPIDRV_EXP_CS_LOC                     29
// [USART_SL_SPIDRV_EXP]$
// <<< sl:end pin_tool >>>

typedef enum
{
  //Single
  CH0_SINGLE = 0b10100000,
  CH1_SINGLE = 0b11100000,

  //Diff
  CH0_CH1_DIFF = 0b00100000,
  CH1_CH0_DIFF = 0b01100000
} mcp3202_src_t;

typedef struct {
  //SPI_TypeDef *perif;
  //uint8_t CH_num;
  //uint16_t data;
} mcp3202_t;

uint8_t mcp3202_read(uint16_t *data);
void SPI_init(void);
int16_t Convert_Res2Temp(uint16_t data);
uint8_t spi_writeByte(USART_TypeDef *spi, uint8_t data);
uint8_t spi_readByte(USART_TypeDef *spi);
void eeprom_send_cmd(uint8_t cmd, uint32_t address);
uint8_t eeprom_read(uint32_t address, uint8_t *data, uint8_t len);
uint8_t eeprom_write_page(uint32_t address, uint8_t *data, uint8_t len);
uint8_t eeprom_erase_sector(uint32_t address);
void eeprom_init();
uint8_t eeprom_Busy();
uint8_t eeprom_verifyAddressRange(uint32_t address, uint32_t len);

#endif /* SPI_periferia */
