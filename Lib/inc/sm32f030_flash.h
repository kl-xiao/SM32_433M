#ifndef __SM32F030_FLASH_H
#define __SM32F030_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "sm32f030.h"




#define CNF_FLASH_ADDRESS(ADDRESS) ((ADDRESS) < 0x8000)




ErrorStatus Flash_EraseSector(uint32_t SectorAddress);
ErrorStatus FLASH_ProgramWord(uint32_t Address, uint32_t Data);
ErrorStatus FLASH_ProgramWordArray(uint32_t Address, uint32_t* Array, uint8_t Len);



#ifdef __cplusplus
}
#endif

#endif /* __SM32F030_FLASH_H */

