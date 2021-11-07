#include <SPI_periferia/spi_periferia.h>

static SPIDRV_HandleData_t sl_spidrv_exp_handle_data;
static SPIDRV_Handle_t sl_spidrv_exp_handle = &sl_spidrv_exp_handle_data;

uint8_t mcp3202_read(uint16_t *data)
{
  uint8_t rx_buff_ch0[SPI_BUFF_SIZE] = {0};
  uint8_t tx_buff_ch0[SPI_BUFF_SIZE] = {0b00000001, CH0_SINGLE, 0x00};
  uint8_t rx_buff_ch1[SPI_BUFF_SIZE] = {0};
  uint8_t tx_buff_ch1[SPI_BUFF_SIZE] = {0b00000001, CH1_SINGLE, 0x00};
  Ecode_t err_code;

  for (uint8_t i = 0; i < ITERATION_NUM; i++)
  {
    //GPIO_PinOutClear(SL_SPIDRV_EXP_CS_PORT, SL_SPIDRV_EXP_CS_PIN);
    err_code = SPIDRV_MTransferB(sl_spidrv_exp_handle, tx_buff_ch0, rx_buff_ch0, SPI_BUFF_SIZE);
    //for (uint8_t j = 0; j < SPI_BUFF_SIZE; j++)
      //rx_buff_ch0[j] = spi_writeByte(SL_SPIDRV_EXP_PERIPHERAL, tx_buff_ch0[j]);
    //GPIO_PinOutSet(SL_SPIDRV_EXP_CS_PORT, SL_SPIDRV_EXP_CS_PIN);
    if (err_code != ECODE_OK) return 1;
    //GPIO_PinOutClear(SL_SPIDRV_EXP_CS_PORT, SL_SPIDRV_EXP_CS_PIN);
    //for (uint8_t j = 0; j < SPI_BUFF_SIZE; j++)
      //rx_buff_ch1[j] = spi_writeByte(SL_SPIDRV_EXP_PERIPHERAL, tx_buff_ch1[j]);
    err_code = SPIDRV_MTransferB(sl_spidrv_exp_handle, tx_buff_ch1, rx_buff_ch1, SPI_BUFF_SIZE);
    //GPIO_PinOutSet(SL_SPIDRV_EXP_CS_PORT, SL_SPIDRV_EXP_CS_PIN);
    if (err_code != ECODE_OK) return 1;
    data[1] += ((rx_buff_ch0[1] & 0x0F) << 8) | rx_buff_ch0[2];
    data[2] += ((rx_buff_ch1[1] & 0x0F) << 8) | rx_buff_ch1[2];
    sl_sleeptimer_delay_millisecond(ITERATION_DELAY);
  }

  data[1] /= ITERATION_NUM;
  data[2] /= ITERATION_NUM;

  data[0] = ((data[1] - data[2]) * 10000) / (V_REF - data[1]);
  data[0] = Convert_Res2Temp(data[0]);

  return 0;
}

void SPI_init(void)
{
  SPIDRV_Init_t sl_spidrv_init_exp = {
    .port = SL_SPIDRV_EXP_PERIPHERAL,
  #if defined(_USART_ROUTELOC0_MASK)
    .portLocationTx = SL_SPIDRV_EXP_TX_LOC,
    .portLocationRx = SL_SPIDRV_EXP_RX_LOC,
    .portLocationClk = SL_SPIDRV_EXP_CLK_LOC,
  #if defined(SL_SPIDRV_EXP_CS_LOC)
    .portLocationCs = SL_SPIDRV_EXP_CS_LOC,
  #endif
  #elif defined(_GPIO_USART_ROUTEEN_MASK)
    .portTx = SL_SPIDRV_EXP_TX_PORT,
    .portRx = SL_SPIDRV_EXP_RX_PORT,
    .portClk = SL_SPIDRV_EXP_CLK_PORT,
  #if defined(SL_SPIDRV_EXP_CS_PORT)
    .portCs = SL_SPIDRV_EXP_CS_PORT,
  #endif
    .pinTx = SL_SPIDRV_EXP_TX_PIN,
    .pinRx = SL_SPIDRV_EXP_RX_PIN,
    .pinClk = SL_SPIDRV_EXP_CLK_PIN,
  #if defined(SL_SPIDRV_EXP_CS_PIN)
    .pinCs = SL_SPIDRV_EXP_CS_PIN,
  #endif
  #else
    .portLocation = SL_SPIDRV_EXP_ROUTE_LOC,
  #endif
    .bitRate = SL_SPIDRV_EXP_BITRATE,
    .frameLength = SL_SPIDRV_EXP_FRAME_LENGTH,
    .dummyTxValue = 0,
    .type = SL_SPIDRV_EXP_TYPE,
    .bitOrder = SL_SPIDRV_EXP_BIT_ORDER,
    .clockMode = SL_SPIDRV_EXP_CLOCK_MODE,
    .csControl = SL_SPIDRV_EXP_CS_CONTROL,
    .slaveStartMode = SL_SPIDRV_EXP_SLAVE_START_MODE,
  };

  SPIDRV_Init(sl_spidrv_exp_handle, &sl_spidrv_init_exp);
}

int16_t Convert_Res2Temp(uint16_t data)
{
  static float temp_coeff[11][2] = {{0.0F, -1.0F},
                                    {-0.000991572F, 32.3847298F},
                                    {-0.002008032F, 45.08032129F},
                                    {-0.002570694F, 50.70694087F},
                                    {-0.003664346F, 59.51630634F},
                                    {-0.005800464F, 70.89327146F},
                                    {-0.008976661F, 82.33393178F},
                                    {-0.013568521F, 93.75848033F},
                                    {-0.02020202F, 105.3737374F},
                                    {-0.029411765F, 116.9411765F},
                                    {0.0F, 100.0F}};
  int16_t temp = 0;
  uint8_t i = 0;

  if (data >= 32660) i = 0;
  else if (data >= 12490) i = 1;
  else if (data >= 10000) i = 2;
  else if (data >= 8055) i = 3;
  else if (data >= 5326) i = 4;
  else if (data >= 3602) i = 5;
  else if (data >= 2488) i = 6;
  else if (data >= 1751) i = 7;
  else if (data >= 1256) i = 8;
  else if (data >= 916) i = 9;
  else if (data < 916) i = 10;

  temp = (int16_t)((temp_coeff[i][0] * ((float)data) + temp_coeff[i][1]) * 10.0F);

  return temp;
}
/*DEPRECATED
uint8_t spi_writeByte(USART_TypeDef *spi, uint8_t data)
{
  while (!(spi->STATUS & USART_STATUS_TXBL));
  spi->TXDATA = (uint32_t)data;
  while (!(spi->STATUS & USART_STATUS_TXC));
  return (uint8_t)spi->RXDATA;
}

uint8_t spi_readByte(USART_TypeDef *spi)
{
  while (!(spi->STATUS & USART_STATUS_TXBL));
  spi->TXDATA = (uint32_t)0xFF;
  while (!(spi->STATUS & USART_STATUS_TXC));
  return (uint8_t)spi->RXDATA;
}
*/
/*
void eeprom_send_cmd(uint8_t cmd, uint32_t address)
{
  spi_writeByte(EEPROM_SPI, cmd);
  USART_Tx(EEPROM_SPI, (address >> 16) & 0xFF);
  USART_Tx(EEPROM_SPI, (address >> 8) & 0xFF);
  USART_Tx(EEPROM_SPI, address & 0xFF);
  USART_Rx(EEPROM_SPI);
  USART_Rx(EEPROM_SPI);
  USART_Rx(EEPROM_SPI);
}

uint8_t eeprom_read(uint32_t address, uint8_t *data, uint8_t len)
{

  if (!eeprom_verifyAddressRange(address, len)) return 1;

  while(eeprom_Busy());

  GPIO_PinOutClear(SL_SPIDRV_EXP_CS_2_PORT, SL_SPIDRV_EXP_CS_2_PIN);
  eeprom_send_cmd(CMD_READ_DATA, address);
  for (uint8_t i = 0; i < len; i++)
    data[i] = spi_readByte(EEPROM_SPI);
  //while (len--) *data++ = spi_readByte(EEPROM_SPI);
  GPIO_PinOutSet(SL_SPIDRV_EXP_CS_2_PORT, SL_SPIDRV_EXP_CS_2_PIN);

  return 0;
}

uint8_t eeprom_write_page(uint32_t address, uint8_t *data, uint8_t len)
{
  if (!eeprom_verifyAddressRange(address, len)) return 1;
  //eeprom_erase_sector(address);
  //while(eeprom_Busy());

  GPIO_PinOutClear(SL_SPIDRV_EXP_CS_2_PORT, SL_SPIDRV_EXP_CS_2_PIN);
  spi_writeByte(EEPROM_SPI, CMD_WRITE_ENABLE);
  GPIO_PinOutSet(SL_SPIDRV_EXP_CS_2_PORT, SL_SPIDRV_EXP_CS_2_PIN);

  GPIO_PinOutClear(SL_SPIDRV_EXP_CS_2_PORT, SL_SPIDRV_EXP_CS_2_PIN);
  eeprom_send_cmd(CMD_PAGE_PROG, address);
  //while (len--) spi_writeByte(EEPROM_SPI, *data++);
  for (uint8_t i = 0; i < len; i++)
    spi_writeByte(EEPROM_SPI, data[i]);
  GPIO_PinOutSet(SL_SPIDRV_EXP_CS_2_PORT, SL_SPIDRV_EXP_CS_2_PIN);

  return 0;
}

uint8_t eeprom_erase_sector(uint32_t address)
{
  if (address & 0xFFF) return 1;

  while(eeprom_Busy());

  GPIO_PinOutClear(SL_SPIDRV_EXP_CS_2_PORT, SL_SPIDRV_EXP_CS_2_PIN);
  spi_writeByte(EEPROM_SPI, CMD_WRITE_ENABLE);
  GPIO_PinOutSet(SL_SPIDRV_EXP_CS_2_PORT, SL_SPIDRV_EXP_CS_2_PIN);

  GPIO_PinOutClear(SL_SPIDRV_EXP_CS_2_PORT, SL_SPIDRV_EXP_CS_2_PIN);
  eeprom_send_cmd(CMD_ERASE_SECTOR, address);
  GPIO_PinOutSet(SL_SPIDRV_EXP_CS_2_PORT, SL_SPIDRV_EXP_CS_2_PIN);

  return 0;
}

void eeprom_init()
{
  sl_sleeptimer_delay_millisecond(20);
  GPIO_PinOutClear(SL_SPIDRV_EXP_CS_2_PORT, SL_SPIDRV_EXP_CS_2_PIN);
  spi_writeByte(EEPROM_SPI, CMD_POWER_UP);
  GPIO_PinOutSet(SL_SPIDRV_EXP_CS_2_PORT, SL_SPIDRV_EXP_CS_2_PIN);
  sl_sleeptimer_delay_millisecond(50);
}

uint8_t eeprom_Busy()
{
  uint8_t status = 1;

  GPIO_PinOutClear(SL_SPIDRV_EXP_CS_2_PORT, SL_SPIDRV_EXP_CS_2_PIN);
  spi_writeByte(EEPROM_SPI, CMD_READ_STATUS);
  status = spi_readByte(EEPROM_SPI);
  GPIO_PinOutSet(SL_SPIDRV_EXP_CS_2_PORT, SL_SPIDRV_EXP_CS_2_PIN);

  return (status & STATUS_BUSY_MASK);
}

uint8_t eeprom_verifyAddressRange(uint32_t address, uint32_t len)
{
  if ((len > SPI_DEVICE_SIZE_8M) || (address > SPI_DEVICE_SIZE_8M)) return false;
  if ((address + len) <= SPI_DEVICE_SIZE_8M) return true;
  return false;
}
*/
