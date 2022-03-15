#include "sm32f030_i2c.h"
#include "system_sm32f030.h"


typedef enum {
  I2C_MASTATUS_IDLE,
  I2C_MASTATUS_OK,
  I2C_MASTATUS_ERROR,
} I2C_MasterStatus_TypeDef;

static I2C_EventHandler_TypeDef slveEventHandler = 0;   /* Current active Slave event handler */

static I2C_MasterStatus_TypeDef masterStatus = I2C_MASTATUS_IDLE;

static uint8_t firstByte = 0;

static uint8_t *pTxBuf = 0;
static int txSz = 0;
static uint8_t *pRxBuf = 0;
static int rxSz = 0;

void I2C_DeInit(void)
{
  SYSCON_AHBPeriphResetCmd(SYSCON_AHBRESET_I2C, ENABLE);
  SYSCON_AHBPeriphResetCmd(SYSCON_AHBRESET_I2C, DISABLE);
}

// 设置I2C通信速率
void I2C_SetClockRate(uint32_t ClockRate)
{
  uint32_t tmpValue;

  tmpValue = my_div(SystemCoreClock , ClockRate) >> 1;
  I2C->SCLH = tmpValue;
  I2C->SCLL = tmpValue;
}

// 获取I2C通信速率
uint32_t I2C_GetClockRate(void)
{
  return my_div(SystemCoreClock , (I2C->SCLH + I2C->SCLL));
}

void I2C_MastarInit(void)
{
  /* Clear Flags */
  I2C->CONCLR = 0xFF;

  I2C->CONSET = I2C_CONSET_I2CEN | I2C_CONSET_MASL;

  NVIC_SetPriority(I2C_IRQn, 2);
  NVIC_EnableIRQ(I2C_IRQn);
}

void I2C_SlaveInit(uint8_t slaveAddr, uint8_t addrMask, 
        I2C_EventHandler_TypeDef eventHandler)
{
  slveEventHandler = eventHandler;
  I2C->ADR0 = slaveAddr;
  I2C->MASK[0] = addrMask;
  I2C->CONSET = I2C_CONSET_I2CEN;
  NVIC_SetPriority(I2C_IRQn, 2);
  NVIC_EnableIRQ(I2C_IRQn);
}

void I2C_MasterWriteOneByte(uint8_t slvAddr, uint8_t dat)
{
  uint8_t i = 0xFF;
  firstByte = slvAddr & (~0x01);
  pTxBuf=&dat;  txSz=1;
  pRxBuf=0;     rxSz=0;

  /* Reset STA, STO, SI */
  I2C->CONCLR = I2C_CONCLR_SIC | I2C_CONCLR_STAC | I2C_CONCLR_AAC;

  /* Enter to Master Transmitter mode. Set Start Signal */
  I2C->CONSET = I2C_CONSET_I2CEN | I2C_CONSET_MASL | I2C_CONSET_STA;
  masterStatus = I2C_MASTATUS_IDLE;
  while(masterStatus != I2C_MASTATUS_OK);   //Wait for finished

  while(I2C->CONSET & I2C_CONSET_STO);

  pTxBuf=0;   txSz=0;
  pRxBuf=0;   rxSz=0;

  while(i--);
}

uint8_t I2C_MasterReadOneByte(uint8_t slvAddr)
{
  uint8_t i = 0xFF;
  uint8_t rd = 0;

  firstByte = slvAddr | 0x01;
  pTxBuf=0;     txSz=0;
  pRxBuf=&rd;   rxSz=1;

  /* Reset STA, STO, SI */
  I2C->CONCLR = I2C_CONCLR_SIC | I2C_CONCLR_STAC | I2C_CONCLR_AAC;

  /* Enter to Master Transmitter mode. Set Start Signal */
  I2C->CONSET = I2C_CONSET_I2CEN | I2C_CONSET_MASL | I2C_CONSET_STA;
  masterStatus = I2C_MASTATUS_IDLE;
  while(masterStatus != I2C_MASTATUS_OK);   //Wait for finished

  while(I2C->CONSET & I2C_CONSET_STO);

  pTxBuf=0;   txSz=0;
  pRxBuf=0;   rxSz=0;

  while(i--);
  return rd;
}

void I2C_MasterWriteBytes(uint8_t slvAddr, uint8_t *pData, int len)
{
  uint16_t i = 0xffff;
  firstByte = slvAddr & (~0x01);
  pTxBuf=pData; txSz=len;
  pRxBuf=0;     rxSz=0;

  /* Reset STA, STO, SI */
  I2C->CONCLR = I2C_CONCLR_SIC | I2C_CONCLR_STAC | I2C_CONCLR_AAC;

  /* Enter to Master Transmitter mode. Set Start Signal */
  I2C->CONSET = I2C_CONSET_I2CEN | I2C_CONSET_MASL | I2C_CONSET_STA;
  masterStatus = I2C_MASTATUS_IDLE;
  while(masterStatus != I2C_MASTATUS_OK);   //Wait for finished

  while(I2C->CONSET & I2C_CONSET_STO);

  pTxBuf=0;   txSz=0;
  pRxBuf=0;   rxSz=0;

  while(i--);
}

void I2C_MasterReadBytes(uint8_t slvAddr, uint8_t *pBuffer, int rdlen)
{
  uint8_t i = 0xFF;

  firstByte = slvAddr | 0x01;
  pTxBuf=0;         txSz=0;
  pRxBuf=pBuffer;   rxSz=rdlen;

  /* Reset STA, STO, SI */
  I2C->CONCLR = I2C_CONCLR_SIC | I2C_CONCLR_STAC | I2C_CONCLR_AAC;

  /* Enter to Master Transmitter mode. Set Start Signal */
  I2C->CONSET = I2C_CONSET_I2CEN | I2C_CONSET_MASL | I2C_CONSET_STA;
  masterStatus = I2C_MASTATUS_IDLE;
  while(masterStatus != I2C_MASTATUS_OK);   //Wait for finished

  while(I2C->CONSET & I2C_CONSET_STO);

  pTxBuf=0;   txSz=0;
  pRxBuf=0;   rxSz=0;

  while(i--);
}

void I2C_IRQHandler(void)
{
  uint32_t stat, temp;
  stat = I2C->STAT;

  // 0x4B--SLA+W transmitted but no ACK 
  // 0x54--Data byte in DAT transmitted;no ACK received.
  if((stat==0x4B) || (stat==0x54))
  {
    I2C->CONSET = I2C_CONSET_STO;   // Set Stop flag
    I2C->CONCLR = I2C_CONCLR_SIC | I2C_CONCLR_STAC | I2C_CONCLR_TXRX;
    masterStatus = I2C_MASTATUS_OK;
    return;
  }

  if(I2C->CONSET & I2C_CONSET_MASL)
  {     // Master
    stat &= (~0x740);

    switch(stat & 0xFF)
    {
    case I2C_STAT_M_TX_RESTART:
    case I2C_STAT_M_TX_START:     /*!< (0x01) A start condition has been transmitted */
     
      if(firstByte & 0x01)
      {
        I2C->DAT = firstByte;
        I2C->CONCLR = I2C_CONCLR_SIC | I2C_CONCLR_STAC | I2C_CONCLR_TXRX;
      }
      else
      {
        I2C->CONSET = I2C_CONSET_TXRX;
        I2C->DAT = firstByte;
        I2C->CONCLR = I2C_CONCLR_SIC | I2C_CONCLR_STAC;
      }
      break;
    case I2C_STAT_M_TX_SLAW_ACK:  /*!< (0x0B) SLA+W has been transmitted, ACK has been received */
      if(I2C->CONSET & I2C_CONSET_TXRX)
      {     // Tx
        if(txSz > 0)
        {
          I2C->DAT = *pTxBuf++;
          txSz--;
        }
        else
        {
          I2C->CONSET = I2C_CONSET_STO;   // Set Stop flag
          masterStatus = I2C_MASTATUS_ERROR;
        }
        I2C->CONCLR = I2C_CONCLR_SIC/* | I2C_CONCLR_STAC*/;
      }
      else
      {     // Rx
        if(rxSz > 0)
        {
          I2C->CONSET = I2C_CONSET_AA;
        }
        else
        {
          I2C->CONCLR = I2C_CONCLR_AAC;
        }
        I2C->CONCLR = I2C_CONCLR_SIC | I2C_CONCLR_STAC;
      }
      break;
    case I2C_STAT_M_TX_DAT_ACK:  /*!< (0x14) Data has been transmitted, ACK has been received */
      if(txSz > 0)
      {
        I2C->DAT = *pTxBuf++;
        txSz--;
      }
      else
      {
        if(rxSz > 0)
        {
          I2C->CONCLR = I2C_CONCLR_SIC | I2C_CONCLR_TXRX;
        }
        else
        {
          I2C->CONSET = I2C_CONSET_STO;   // Set Stop flag
          masterStatus = I2C_MASTATUS_OK;
        }
      }
      I2C->CONCLR = I2C_CONCLR_SIC;
      break;
    case I2C_STAT_M_RX_DAT_ACK: /*!< (0x1D) Data has been received, ACK has been returned */
      temp = I2C->DAT;
      if(rxSz > 0)
      {
        *pRxBuf++ = temp;
        rxSz--;
        I2C->CONSET = I2C_CONSET_AA;
        I2C->CONCLR = I2C_CONCLR_SIC;
      }
      else
      {
        if(I2C->CONSET & I2C_CONSET_AA)
            I2C->CONCLR = I2C_CONCLR_AAC | I2C_CONCLR_SIC;
          else {
            I2C->CONSET = I2C_CONSET_STO;   // Set Stop flag
            masterStatus = I2C_MASTATUS_OK;
            I2C->CONCLR = I2C_CONCLR_SIC;
          }
      }
      break;
    default:
      masterStatus = I2C_MASTATUS_ERROR;
      I2C->CONCLR = I2C_CONCLR_SIC;
      break;
    }
  }
  else  /*-------- Slave state handler --------*/
  {
    if(stat & I2C_STAT_SLVADDMATCH)
    {
      temp = I2C->DAT;
      slveEventHandler(I2C_EVENT_SLAVE_MATCH, temp);
      
      if(temp & 0x01)
        I2C->CONSET |= I2C_CONSET_TXRX;
      else
        I2C->CONCLR = I2C_CONCLR_TXRX;
      
      I2C->CONCLR = I2C_CONCLR_SLVADDMATCH;   //Clear match flag
      I2C->CONSET = I2C_CONSET_AA;
    }
    else if(stat & I2C_STAT_SLVRXBUFFULL)
    {
      slveEventHandler(I2C_EVENT_SLAVE_RX, I2C->DAT);
      I2C->CONSET = I2C_CONSET_AA;
    }
    else if(stat & I2C_STAT_SLVTXBUFEMPTY)
    {
      slveEventHandler(I2C_EVENT_SLAVE_TX, 0);
      I2C->CONSET = I2C_CONSET_AA;
      
      I2C->CONSET |= I2C_CONSET_TXRX;
    }

    if((stat == 0x0000) && (I2C->CONSET & I2C_CONSET_TXRX))
      I2C->CONCLR = I2C_CONCLR_TXRX;
    
    I2C->CONCLR = I2C_CONCLR_SIC | I2C_CONCLR_STAC;
  }
}


