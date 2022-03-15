#ifndef __SM32F030_CRC_H
#define __SM32F030_CRC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "sm32f030.h"


#if defined(SM32F030x8)
uint16_t CRC16_CCITT_ComputeBytes(const uint8_t *pData, uint32_t dataLen);
uint16_t CRC16_CCITT_ComputeBytes_Update(uint16_t seed, const uint8_t *pData, uint32_t dataLen);

uint16_t CRC16_Modbus_ComputeBytes(const uint8_t *pData, uint32_t dataLen);
uint16_t CRC16_Modbus_ComputeBytes_Update(uint16_t seed, const uint8_t *pData, uint32_t dataLen);

uint16_t CRC16_IBM_ComputeBytes(const uint8_t *pData, uint32_t dataLen);
#define CRC16_IBM_ComputeBytes_Update CRC16_Modbus_ComputeBytes_Update

uint32_t CRC32_ComputeBytes(const uint8_t *pData, uint32_t dataLen);
uint32_t CRC32_ComputeBytes_Update(uint32_t seed, const uint8_t *pData, uint32_t dataLen);

uint32_t CRC32_MPEG2_ComputeBytes(const uint8_t *pData, uint32_t dataLen);
uint32_t CRC32_MPEG2_ComputeBytes_Update(uint32_t seed, const uint8_t *pData, uint32_t dataLen);


uint32_t CRC32_ComputeWords(const uint32_t *pData, uint32_t dataLen);
uint32_t CRC32_ComputeWords_Update(uint32_t seed, const uint32_t *pData, uint32_t dataLen);

uint32_t CRC32_MPEG2_ComputeWords(const uint32_t *pData, uint32_t dataLen);
uint32_t CRC32_MPEG2_ComputeWords_Update(uint32_t seed, const uint32_t *pData, uint32_t dataLen);
#endif


#ifdef __cplusplus
}
#endif

#endif /* __SM32F030_CRC_H */

