#include "sm32f030_spi.h"


void SPI_DeInit(void)
{
  SYSCON_AHBPeriphResetCmd(SYSCON_AHBRESET_SPI, ENABLE);
  SYSCON_AHBPeriphResetCmd(SYSCON_AHBRESET_SPI, DISABLE);
}


void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct)
{
  SPI_InitStruct->SPI_Mode = SPI_Mode_Master;
  SPI_InitStruct->SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStruct->SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStruct->SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStruct->SPI_NssIdleLevel = SPI_NSS_Idle_High;
  SPI_InitStruct->SPI_ClockPrescaler = 12;
}

void SPI_Init(SPI_InitTypeDef* SPI_InitStruct)
{
  uint32_t tmpreg;
  /* Check the parameters */
  assert_param(CNF_SPI_MODE(SPI_InitStruct->SPI_Mode));
  assert_param(CNF_SPI_DATA_SIZE(SPI_InitStruct->SPI_DataSize));
  assert_param(CNF_SPI_CPOL(SPI_InitStruct->SPI_CPOL));
  assert_param(CNF_SPI_CPHA(SPI_InitStruct->SPI_CPHA));
  assert_param(CNF_SPI_NSS_IDLE(SPI_InitStruct->SPI_NssIdleLevel));
  
  tmpreg = SPI->CR0;
  /* Clear DSS, CPOL and CPHA bits */
  tmpreg &= 0x0030;
  tmpreg |= (SPI_InitStruct->SPI_DataSize |
          SPI_InitStruct->SPI_CPOL | SPI_InitStruct->SPI_CPHA);
  SPI->CR0 = tmpreg;
  
  tmpreg = SPI->CR1;
  /* Clear MS and CSFL bits */
  tmpreg &= 0x006B;
  tmpreg |= (SPI_InitStruct->SPI_Mode | SPI_InitStruct->SPI_NssIdleLevel);
  SPI->CR1 = tmpreg;
  
  SPI->CPSR = SPI_InitStruct->SPI_ClockPrescaler;
}

void SPI_Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(CNF_FUNCTIONAL_STATE(NewState));
  
  if(NewState != DISABLE)
  {
    /* Enable the SPI peripheral */
    SPI->CR1 |= SPI_CR1_SSE;
  }
  else
  {
    /* Disable the SPI peripheral */
    SPI->CR1 &= (~SPI_CR1_SSE);
  }
}

// 向SPI的发送FIFO写入nWrite个数据
void SPI_WriteFIFO(uint16_t* pBuffer, uint8_t nWrite)
{
  while((SPI->SR & SPI_SR_TNF) && (nWrite))
  {
    /* Write data to FIFO */
    SPI->DR = *pBuffer;
    ++pBuffer;
  }
}

// 读取SPI的接收FIFO
// 返回实际读取的数据个数
uint8_t SPI_ReadFIFO(uint16_t* pBuffer, uint8_t nBuffer)
{
  uint8_t cnt = 0;
  while((SPI->SR & SPI_SR_RNE) && (nBuffer))
  {
    /* Read data from FIFO */
    pBuffer[cnt] = SPI->DR;
    ++cnt;   --nBuffer;
  }
  return cnt;
}

// 向SPI的FIFO写入一个数据
// 返回1 表示写入成功
// 返回0 表示FIFO已满
uint8_t SPI_WriteOneData(uint16_t data)
{
  if(SPI->SR & SPI_SR_TNF)
  {
    SPI->DR = data;
    return 1;       //Success
  }
  return 0;   //Failed
}

// 从SPI的接收FIFO读取一个数据
// 若FIFO中没有数据  返回0
uint16_t SPI_ReadOneData(void)
{
  if(SPI->SR & SPI_SR_RNE)
  {
    return SPI->DR;
  }
  return 0;
}

// 进行一次SPI的数据传输
uint16_t SPI_ReadWriteData(uint16_t data)
{
	/* Wait until the transmit buffer is empty */
  while(!(SPI->SR & SPI_SR_TFE));
  /* Clear RX FIFO */
  SPI->CR1 |= SPI_CR1_RSFR;
  SPI->CR1 &= (~SPI_CR1_RSFR);
  /* Write data to FIFO */
  SPI->DR = data;
  /* Wait until the transmit buffer is empty */
  while(!(SPI->SR & SPI_SR_RNE));
  /* Read data from FIFO */
  return SPI->DR;
}



