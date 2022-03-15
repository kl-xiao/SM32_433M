#include "sm32f030_flash.h"
#include "sm32f030_iap.h"




// 擦出扇区
ErrorStatus Flash_EraseSector(uint32_t SectorAddress)
{
  IAP iap_entry = (IAP)(*((uint32_t*) IAP_ADDR_LOCATION));
  uint32_t command[2];
  uint32_t result[2];
  
  /* Check the parameters */
  assert_param(CNF_FLASH_ADDRESS(SectorAddress));
  
  command[0] = IAP_CMD_ERASE_SECTOR;
  command[1] = SectorAddress;
  iap_entry(command, result);

  if(result[0] != IAP_STATUS_CMD_SUCC) return ERROR;
  
  return SUCCESS;
}

// 编程一个字（4Bytes）
ErrorStatus FLASH_ProgramWord(uint32_t Address, uint32_t Data)
{
  IAP iap_entry = (IAP)(*((uint32_t*) IAP_ADDR_LOCATION));
  uint32_t command[3];
  uint32_t result[2];
  
  /* Check the parameters */
  assert_param(CNF_FLASH_ADDRESS(Address));
  
  command[0] = IAP_CMD_PROGRAM_WORD;
  command[1] = Address;
  command[2] = Data;
  iap_entry(command, result);

  if(result[0] != IAP_STATUS_CMD_SUCC) return ERROR;
  
  return SUCCESS;
}

// 编程一个数组到Flash中
// 等同于 调用Len次 FLASH_ProgramWord
// Array 指向的地址必须是4字节对齐的
ErrorStatus FLASH_ProgramWordArray(uint32_t Address, uint32_t* Array, uint8_t Len)
{
  IAP iap_entry = (IAP)(*((uint32_t*) IAP_ADDR_LOCATION));
  uint32_t command[3];
  uint32_t result[2];
  
  /* Check the parameters */
  assert_param(CNF_FLASH_ADDRESS(Address));
  
  while(Len)
  {
    command[0] = IAP_CMD_PROGRAM_WORD;
    command[1] = Address;
    command[2] = *Array;
    iap_entry(command, result);

    if(result[0] != IAP_STATUS_CMD_SUCC) return ERROR;
    
    Address += 4;
    Array++;
    Len--;
  }
  
  return SUCCESS;
}
