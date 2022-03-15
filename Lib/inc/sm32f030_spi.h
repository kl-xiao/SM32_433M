#ifndef __SM32F030_SPI_H
#define __SM32F030_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "sm32f030.h"


/** 
  * @brief  SPI Init structure definition  
  */

typedef struct
{
  uint16_t SPI_Mode;                /*!< Specifies the SPI mode (Master/Slave).
                                         This parameter can be a value of @ref SPI_mode */
  
  uint16_t SPI_DataSize;            /*!< Specifies the SPI data size.
                                         This parameter can be a value of @ref SPI_data_size */

  uint16_t SPI_CPOL;                /*!< Specifies the serial clock steady state.
                                         This parameter can be a value of @ref SPI_Clock_Polarity */

  uint16_t SPI_CPHA;                /*!< Specifies the clock active edge for the bit capture.
                                         This parameter can be a value of @ref SPI_Clock_Phase */

  uint16_t SPI_NssIdleLevel;
 
  uint16_t SPI_ClockPrescaler;
}SPI_InitTypeDef;


/** @defgroup SPI_mode 
  * @{
  */

#define SPI_Mode_Master                 ((uint16_t)0x0000)
#define SPI_Mode_Slave                  ((uint16_t)0x0004)
#define CNF_SPI_MODE(MODE) (((MODE) == SPI_Mode_Master) || \
                            ((MODE) == SPI_Mode_Slave))
/**
  * @}
  */

/** @defgroup SPI_data_size
  * @{
  */

#define SPI_DataSize_4b                 SPI_CR0_DSS_4Bit
#define SPI_DataSize_5b                 SPI_CR0_DSS_5Bit
#define SPI_DataSize_6b                 SPI_CR0_DSS_6Bit
#define SPI_DataSize_7b                 SPI_CR0_DSS_7Bit
#define SPI_DataSize_8b                 SPI_CR0_DSS_8Bit
#define SPI_DataSize_9b                 SPI_CR0_DSS_9Bit
#define SPI_DataSize_10b                SPI_CR0_DSS_10Bit
#define SPI_DataSize_11b                SPI_CR0_DSS_11Bit
#define SPI_DataSize_12b                SPI_CR0_DSS_12Bit
#define SPI_DataSize_13b                SPI_CR0_DSS_13Bit
#define SPI_DataSize_14b                SPI_CR0_DSS_14Bit
#define SPI_DataSize_15b                SPI_CR0_DSS_15Bit
#define SPI_DataSize_16b                SPI_CR0_DSS_16Bit
#define CNF_SPI_DATA_SIZE(SIZE) (((SIZE) == SPI_DataSize_4b) || \
                                 ((SIZE) == SPI_DataSize_5b) || \
                                 ((SIZE) == SPI_DataSize_6b) || \
                                 ((SIZE) == SPI_DataSize_7b) || \
                                 ((SIZE) == SPI_DataSize_8b) || \
                                 ((SIZE) == SPI_DataSize_9b) || \
                                 ((SIZE) == SPI_DataSize_10b) || \
                                 ((SIZE) == SPI_DataSize_11b) || \
                                 ((SIZE) == SPI_DataSize_12b) || \
                                 ((SIZE) == SPI_DataSize_13b) || \
                                 ((SIZE) == SPI_DataSize_14b) || \
                                 ((SIZE) == SPI_DataSize_15b) || \
                                 ((SIZE) == SPI_DataSize_16b))
/**
  * @}
  */

/** @defgroup SPI_Clock_Polarity 
  * @{
  */

#define SPI_CPOL_Low                    ((uint16_t)0x0000)
#define SPI_CPOL_High                   SPI_CR0_CPOL
#define CNF_SPI_CPOL(CPOL) (((CPOL) == SPI_CPOL_Low) || \
                            ((CPOL) == SPI_CPOL_High))
/**
  * @}
  */

/** @defgroup SPI_Clock_Phase 
  * @{
  */

#define SPI_CPHA_1Edge                  ((uint16_t)0x0000)
#define SPI_CPHA_2Edge                  SPI_CR0_CPHA
#define CNF_SPI_CPHA(CPHA) (((CPHA) == SPI_CPHA_1Edge) || \
                            ((CPHA) == SPI_CPHA_2Edge))
/**
  * @}
  */

/** @defgroup SPI_NSS_Idle_Level
  * @{
  */

#define SPI_NSS_Idle_Low                  SPI_CR1_CSFL
#define SPI_NSS_Idle_High                 ((uint16_t)0x0000)
#define CNF_SPI_NSS_IDLE(IDLE) (((IDLE) == SPI_NSS_Idle_Low) || \
                                ((IDLE) == SPI_NSS_Idle_High))
/**
  * @}
  */
  

void SPI_DeInit(void);
void SPI_Init(SPI_InitTypeDef* SPI_InitStruct);
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);
void SPI_Cmd(FunctionalState NewState);
void SPI_WriteFIFO(uint16_t* pBuffer, uint8_t nWrite);
uint8_t SPI_ReadFIFO(uint16_t* pBuffer, uint8_t nBuffer);
uint8_t SPI_WriteOneData(uint16_t data);
uint16_t SPI_ReadOneData(void);
uint16_t SPI_ReadWriteData(uint16_t data);


#ifdef __cplusplus
}
#endif

#endif /* __SM32F030_SPI_H */

