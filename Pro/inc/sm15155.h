#ifndef __SM15155_H
#define __SM15155_H

#include "sm32f030.h"
#include "uart.h"
#include "zero.h"

typedef struct 
{
    uint8_t NUM;
    uint8_t MODE;
    uint8_t SLEEP;
    uint8_t Current[5];
    uint16_t Duty[5];
}SM15155_StructTypedef;

#define st2200K 22
#define st2700K 27
#define st3000K 30
#define st4000K 40
#define st6500K 65
#define stbarra 41
#define sthabu  42
#define stdiy   0

void SM15155_Init(SM15155_StructTypedef * SM15155_Struct);

void SM15155_ClearDuty(SM15155_StructTypedef * SM15155_Struct);
void SM15155_ClearCurrent(SM15155_StructTypedef * SM15155_Struct);

void SM15155_SendData(SM15155_StructTypedef *SM15155_Struct);
void SM15155_Action(SM15155_StructTypedef *SM15155_Struct);

#endif	// __SM15155_H