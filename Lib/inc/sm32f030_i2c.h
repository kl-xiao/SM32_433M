#ifndef __SM32F030_I2C_H
#define __SM32F030_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "sm32f030.h"



/*
 * @brief I2C Master transmit mode
 */
#define I2C_STAT_M_TX_START                   (0x01)/*!< A start condition has been transmitted */
#define I2C_STAT_M_TX_RESTART                 (0x10)/*!< A repeat start condition has been transmitted */
#define I2C_STAT_M_TX_SLAW_ACK                (0x0B)/*!< SLA+W has been transmitted, ACK has been received */
#define I2C_STAT_M_TX_SLAW_NACK               (0x4B)/*!< SLA+W has been transmitted, NACK has been received */
#define I2C_STAT_M_TX_DAT_ACK                 (0x14)/*!< Data has been transmitted, ACK has been received */
#define I2C_STAT_M_TX_DAT_NACK                (0x54)/*!< Data has been transmitted, NACK has been received */


/*
 * @brief I2C Master receive mode
 */
#define I2C_STAT_M_RX_START                   (0x01)/*!< A start condition has been transmitted */
#define I2C_STAT_M_RX_RESTART                 (0x22)/*!< A repeat start condition has been transmitted */
#define I2C_STAT_M_RX_SLAR_ACK                (0x0B)/*!< SLA+R has been transmitted, ACK has been received */
#define I2C_STAT_M_RX_SLAR_NACK               (0x4B)/*!< SLA+R has been transmitted, NACK has been received */
#define I2C_STAT_M_RX_DAT_ACK                 (0x1D)/*!< Data has been received, ACK has been returned */
#define I2C_STAT_M_RX_DAT_NACK                (0x5D)/*!< Data has been received, NACK has been returned */




/**
 * @brief	I2C master events
 */
typedef enum {
  I2C_EVENT_WAIT = 1, /**< I2C Wait event */
  I2C_EVENT_DONE,     /**< Done event that wakes up Wait event */
  I2C_EVENT_SLAVE_MATCH,  /**< Slave address match event */
  I2C_EVENT_SLAVE_RX,     /**< Slave receive event */
  I2C_EVENT_SLAVE_TX,     /**< Slave transmit event */
} I2C_Event_TypeDef;


/**
 * @brief	Event handler function type
 */
typedef void (*I2C_EventHandler_TypeDef)(I2C_Event_TypeDef event, uint32_t param);



void I2C_DeInit(void);
void I2C_SetClockRate(uint32_t ClockRate);
uint32_t I2C_GetClockRate(void);
void I2C_MastarInit(void);
void I2C_SlaveInit(uint8_t slaveAddr, uint8_t addrMask, I2C_EventHandler_TypeDef eventHandler);

uint8_t I2C_MasterReadOneByte(uint8_t slvAddr);
void I2C_MasterWriteOneByte(uint8_t slvAddr, uint8_t dat);
void I2C_MasterReadBytes(uint8_t slvAddr, uint8_t *pBuffer, int rdlen);
void I2C_MasterWriteBytes(uint8_t slvAddr, uint8_t *pData, int len);

#define I2C_WriteData(dat) (I2C->DAT = dat)


#ifdef __cplusplus
}
#endif

#endif /* __SM32F030_I2C_H */

