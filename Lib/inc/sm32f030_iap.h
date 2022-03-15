#ifndef __GVM32F030_IAP_H
#define __GVM32F030_IAP_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>



#define IAP_ADDR_LOCATION       0x1FFF00FC

#define IAP_CMD_ERASE_SECTOR    0x11
#define IAP_CMD_PROGRAM_WORD    0x15
#define IAP_CMD_READ_BSL_VER    0x31



#define IAP_STATUS_CMD_SUCC      0x00
#define IAP_STATUS_INVALID_ADDR  0x01
#define IAP_STATUS_ERASE_FAILED  0x02
#define IAP_STATUS_PROG_FAILED   0x03
#define IAP_STATUS_NOT_BLANK     0x04
#define IAP_STATUS_INVALID_CMD   0x05

typedef void (*IAP)(uint32_t [], uint32_t []);



#ifdef __cplusplus
}
#endif

#endif /* __GVM32F030_IAP_H */
