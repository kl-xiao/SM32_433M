#include "sm32f030_crc.h"


#if defined(SM32F030x8)

/**
 * @brief   Computes the 16-bit CRC-CCITT of a given buffer of byte(8-bit) with default seed.
 * @param   pData      : Pointer to the buffer containing the data to be computed
 * @param   dataLen    : Length of the buffer to be computed
 * @return  16-bit CRC-CCITT
 */
uint16_t CRC16_CCITT_ComputeBytes(const uint8_t *pData, uint32_t dataLen)
{
  if(!pData) return 0;

  CRC->MODE = CRC_MODE_CRC_POLY_CCITT | CRC_MODE_SEED_SET;

  while(dataLen--)
  {
    CRC->WR_DATA_BYTE = *pData++;
  }

  return CRC->SUM;
}


/**
 * @brief   Computes the 16-bit CRC-CCITT of a given buffer of byte(8-bit) with user-defined seed.
 * @param   seed       : User-defined seed
 * @param   pData      : Pointer to the buffer containing the data to be computed
 * @param   dataLen    : Length of the buffer to be computed
 * @return  16-bit CRC-CCITT
 */
uint16_t CRC16_CCITT_ComputeBytes_Update(uint16_t seed, const uint8_t *pData, uint32_t dataLen)
{
  if(!pData) return 0;

  CRC->SEED = seed;
  CRC->MODE = CRC_MODE_CRC_POLY_CCITT | CRC_MODE_SEED_OP | CRC_MODE_SEED_SET;

  while(dataLen--)
  {
    CRC->WR_DATA_BYTE = *pData++;
  }

  return CRC->SUM;
}


/**
 * @brief   Computes the 16-bit CRC(Modbus) of a given buffer of byte(8-bit) with default seed.
 * @param   pData      : Pointer to the buffer containing the data to be computed
 * @param   dataLen    : Length of the buffer to be computed
 * @return  16-bit CRC(Modbus)
 */
uint16_t CRC16_Modbus_ComputeBytes(const uint8_t *pData, uint32_t dataLen)
{
  if(!pData) return 0;

  CRC->SEED = 0xFFFF;
  CRC->MODE = CRC_MODE_CRC_POLY_CRC16 | CRC_MODE_BIT_RVS_WR | CRC_MODE_BIT_RVS_SUM | CRC_MODE_SEED_OP | CRC_MODE_SEED_SET;

  while(dataLen--)
  {
    CRC->WR_DATA_BYTE = *pData++;
  }

  return CRC->SUM;
}


/**
 * @brief   Computes the 16-bit CRC(Modbus) of a given buffer of byte(8-bit) with user-defined seed.
 * @param   seed       : User-defined seed
 * @param   pData      : Pointer to the buffer containing the data to be computed
 * @param   dataLen    : Length of the buffer to be computed
 * @return  16-bit CRC(Modbus)
 */
uint16_t CRC16_Modbus_ComputeBytes_Update(uint16_t seed, const uint8_t *pData, uint32_t dataLen)
{
  if(!pData) return 0;

  CRC->SEED = __RBIT(seed) >> 16;
  CRC->MODE = CRC_MODE_CRC_POLY_CRC16 | CRC_MODE_BIT_RVS_WR | CRC_MODE_BIT_RVS_SUM | CRC_MODE_SEED_OP | CRC_MODE_SEED_SET;

  while(dataLen--)
  {
    CRC->WR_DATA_BYTE = *pData++;
  }

  return CRC->SUM;
}


/**
 * @brief   Computes the 16-bit CRC(IBM) of a given buffer of byte(8-bit) with default seed.
 * @param   pData      : Pointer to the buffer containing the data to be computed
 * @param   dataLen    : Length of the buffer to be computed
 * @return  16-bit CRC(IBM)
 */
uint16_t CRC16_IBM_ComputeBytes(const uint8_t *pData, uint32_t dataLen)
{
  if(!pData) return 0;

  CRC->MODE = CRC_MODE_CRC_POLY_CRC16 | CRC_MODE_BIT_RVS_WR | CRC_MODE_BIT_RVS_SUM | CRC_MODE_SEED_SET;

  while(dataLen--)
  {
    CRC->WR_DATA_BYTE = *pData++;
  }

  return CRC->SUM;
}


/**
 * @brief   Computes the 32-bit CRC of a given buffer of byte(8-bit) with default seed.
 * @param   pData      : Pointer to the buffer containing the data to be computed
 * @param   dataLen    : Length of the buffer to be computed
 * @return  32-bit CRC
 */
uint32_t CRC32_ComputeBytes(const uint8_t *pData, uint32_t dataLen)
{
  if(!pData) return 0;

  CRC->MODE = CRC_MODE_CRC_POLY_CRC32 | CRC_MODE_BIT_RVS_WR
        | CRC_MODE_BIT_RVS_SUM | CRC_MODE_CMPL_SUM | CRC_MODE_SEED_SET;

  while(dataLen--)
  {
    CRC->WR_DATA_BYTE = *pData++;
  }

  return CRC->SUM;
}


/**
 * @brief   Computes the 32-bit CRC of a given buffer of byte(8-bit) with user-defined seed.
 * @param   seed       : User-defined seed
 * @param   pData      : Pointer to the buffer containing the data to be computed
 * @param   dataLen    : Length of the buffer to be computed
 * @return  32-bit CRC
 */
uint32_t CRC32_ComputeBytes_Update(uint32_t seed, const uint8_t *pData, uint32_t dataLen)
{
  if(!pData) return 0;

  CRC->SEED = __RBIT(~seed);
  CRC->MODE = CRC_MODE_CRC_POLY_CRC32 | CRC_MODE_BIT_RVS_WR
        | CRC_MODE_BIT_RVS_SUM | CRC_MODE_CMPL_SUM | CRC_MODE_SEED_OP | CRC_MODE_SEED_SET;

  while(dataLen--)
  {
    CRC->WR_DATA_BYTE = *pData++;
  }

  return CRC->SUM;
}


/**
 * @brief   Computes the 32-bit CRC(MPEG2) of a given buffer of byte(8-bit) with default seed.
 * @param   pData      : Pointer to the buffer containing the data to be computed
 * @param   dataLen    : Length of the buffer to be computed
 * @return  32-bit CRC(MPEG2)
 */
uint32_t CRC32_MPEG2_ComputeBytes(const uint8_t *pData, uint32_t dataLen)
{
  if(!pData) return 0;

  CRC->MODE = CRC_MODE_CRC_POLY_CRC32 | CRC_MODE_SEED_SET;

  while(dataLen--)
  {
    CRC->WR_DATA_BYTE = *pData++;
  }

  return CRC->SUM;
}


/**
 * @brief   Computes the 32-bit CRC(MPEG2) of a given buffer of byte(8-bit) with user-defined seed.
 * @param   seed       : User-defined seed
 * @param   pData      : Pointer to the buffer containing the data to be computed
 * @param   dataLen    : Length of the buffer to be computed
 * @return  32-bit CRC(MPEG2)
 */
uint32_t CRC32_MPEG2_ComputeBytes_Update(uint32_t seed, const uint8_t *pData, uint32_t dataLen)
{
  if(!pData) return 0;

  CRC->SEED = seed;
  CRC->MODE = CRC_MODE_CRC_POLY_CRC32 | CRC_MODE_SEED_OP | CRC_MODE_SEED_SET;

  while(dataLen--)
  {
    CRC->WR_DATA_BYTE = *pData++;
  }

  return CRC->SUM;
}





/**
 * @brief   Computes the 32-bit CRC of a given buffer of word(32-bit) with default seed.
 * @param   pData      : Pointer to the buffer containing the data to be computed
 * @param   dataLen    : Length of the buffer to be computed
 * @return  32-bit CRC
 */
uint32_t CRC32_ComputeWords(const uint32_t *pData, uint32_t dataLen)
{
  if(!pData) return 0;

  CRC->MODE = CRC_MODE_CRC_POLY_CRC32 | CRC_MODE_BIT_RVS_WR
        | CRC_MODE_BIT_RVS_SUM | CRC_MODE_CMPL_SUM | CRC_MODE_SEED_SET;

  while(dataLen--)
  {
    CRC->WR_DATA_WORD = *pData++;
  }

  return CRC->SUM;
}


/**
 * @brief   Computes the 32-bit CRC of a given buffer of word(32-bit) with user-defined seed.
 * @param   seed       : User-defined seed
 * @param   pData      : Pointer to the buffer containing the data to be computed
 * @param   dataLen    : Length of the buffer to be computed
 * @return  32-bit CRC
 */
uint32_t CRC32_ComputeWords_Update(uint32_t seed, const uint32_t *pData, uint32_t dataLen)
{
  if(!pData) return 0;

  CRC->SEED = __RBIT(~seed);
  CRC->MODE = CRC_MODE_CRC_POLY_CRC32 | CRC_MODE_BIT_RVS_WR
        | CRC_MODE_BIT_RVS_SUM | CRC_MODE_CMPL_SUM | CRC_MODE_SEED_OP | CRC_MODE_SEED_SET;

  while(dataLen--)
  {
    CRC->WR_DATA_WORD = *pData++;
  }

  return CRC->SUM;
}



/**
 * @brief   Computes the 32-bit CRC(MPEG2) of a given buffer of word(32-bit) with default seed.
 * @param   pData      : Pointer to the buffer containing the data to be computed
 * @param   dataLen    : Length of the buffer to be computed
 * @return  32-bit CRC(MPEG2)
 */
uint32_t CRC32_MPEG2_ComputeWords(const uint32_t *pData, uint32_t dataLen)
{
  if(!pData) return 0;

  CRC->MODE = CRC_MODE_CRC_POLY_CRC32 | CRC_MODE_SEED_SET;

  while(dataLen--)
  {
    CRC->WR_DATA_WORD = *pData++;
  }

  return CRC->SUM;
}


/**
 * @brief   Computes the 32-bit CRC(MPEG2) of a given buffer of word(32-bit) with user-defined seed.
 * @param   seed       : User-defined seed
 * @param   pData      : Pointer to the buffer containing the data to be computed
 * @param   dataLen    : Length of the buffer to be computed
 * @return  32-bit CRC(MPEG2)
 */
uint32_t CRC32_MPEG2_ComputeWords_Update(uint32_t seed, const uint32_t *pData, uint32_t dataLen)
{
  if(!pData) return 0;

  CRC->SEED = seed;
  CRC->MODE = CRC_MODE_CRC_POLY_CRC32 | CRC_MODE_SEED_OP | CRC_MODE_SEED_SET;

  while(dataLen--)
  {
    CRC->WR_DATA_WORD = *pData++;
  }

  return CRC->SUM;
}

#endif
