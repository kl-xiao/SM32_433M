#include "sm15155.h"

void SM15155_Init(SM15155_StructTypedef * SM15155_Struct)
{
    SM15155_Struct->MODE  = rx_buf[4];
    SM15155_Struct->NUM   = rx_buf[3] * 8;
    SM15155_Struct->SLEEP = rx_buf[20];
    for(uint8_t i=0; i<5; i++)
    {
        SM15155_Struct->Current[i]  = rx_buf[i+15];
    }
    for(uint8_t i=0; i<5; i++)
    {
        SM15155_Struct->Duty[i]  = (rx_buf[i*2+5]<<8) | (rx_buf[i*2+6]);
    }    
}

void SM15155_ClearDuty(SM15155_StructTypedef * SM15155_Struct)
{
    SM15155_Struct->Duty[0] = 0;
    SM15155_Struct->Duty[1] = 0;
    SM15155_Struct->Duty[2] = 0;
    SM15155_Struct->Duty[3] = 0;
    SM15155_Struct->Duty[4] = 0;
}

void SM15155_ClearCurrent(SM15155_StructTypedef * SM15155_Struct)
{
    SM15155_Struct->Current[0] = 0;
    SM15155_Struct->Current[1] = 0;
    SM15155_Struct->Current[2] = 0;
    SM15155_Struct->Current[3] = 0;
    SM15155_Struct->Current[4] = 0;
}

void SM15155_SendData(SM15155_StructTypedef *SM15155_Struct)
{
    uint32_t dat = 0;

    ZERO_Rst();
    for(uint8_t i=0; i<SM15155_Struct->NUM; i++)
    {
        ZERO_SendData(SM15155_Struct->Duty[0]);
        ZERO_SendData(SM15155_Struct->Duty[1]);
        ZERO_SendData(SM15155_Struct->Duty[2]);
        ZERO_SendData(SM15155_Struct->Duty[3]);
        ZERO_SendData(SM15155_Struct->Duty[4]);
    }
    if(SM15155_Struct->SLEEP)
    {
        dat = (SM15155_Struct->Current[0] << 27) | (SM15155_Struct->Current[1] << 22) | (SM15155_Struct->Current[2] << 17) |
              (SM15155_Struct->Current[3] << 12) | (SM15155_Struct->Current[4] << 7) | (2<<5) | 0x1f;
    }
    else
    {
        dat = (SM15155_Struct->Current[0] << 27) | (SM15155_Struct->Current[1] << 22) | (SM15155_Struct->Current[2] << 17) |
              (SM15155_Struct->Current[3] << 12) | (SM15155_Struct->Current[4] << 7) | (0<<5) | 0x1f;
    }
    ZERO_SendData(dat>>16);
    ZERO_SendData(dat);
    ZERO_Rst();
}

void SM15155_Action(SM15155_StructTypedef *SM15155_Struct)
{
    SM15155_Struct->Current[0] = 1;
    SM15155_Struct->Current[1] = 1;
    SM15155_Struct->Current[2] = 1;
    SM15155_Struct->Current[3] = 3;
    SM15155_Struct->Current[4] = 4;
    if(!(SM15155_Struct->SLEEP))
    {
        switch (SM15155_Struct->MODE)
        {
            case st2200K:
                SM15155_Struct->Duty[0] = 19484;
                SM15155_Struct->Duty[1] = 8939;
                SM15155_Struct->Duty[2] = 0;
                SM15155_Struct->Duty[3] = 0;
                SM15155_Struct->Duty[4] = 53628;
                break;
            case st2700K:
                SM15155_Struct->Duty[0] = 0;
                SM15155_Struct->Duty[1] = 13435;
                SM15155_Struct->Duty[2] = 0;
                SM15155_Struct->Duty[3] = 9155;
                SM15155_Struct->Duty[4] = 56499;
                break;
            case st3000K:
                SM15155_Struct->Duty[0] = 0;
                SM15155_Struct->Duty[1] = 17760;
                SM15155_Struct->Duty[2] = 0;
                SM15155_Struct->Duty[3] = 15997;
                SM15155_Struct->Duty[4] = 49886;
                break;
            case st4000K:
                SM15155_Struct->Duty[0] = 0;
                SM15155_Struct->Duty[1] = 21502;
                SM15155_Struct->Duty[2] = 0;
                SM15155_Struct->Duty[3] = 37349;
                SM15155_Struct->Duty[4] = 35029;
                break;
            case st6500K:
                SM15155_Struct->Duty[0] = 0;
                SM15155_Struct->Duty[1] = 13284;
                SM15155_Struct->Duty[2] = 8533;
                SM15155_Struct->Duty[3] = 65535;
                SM15155_Struct->Duty[4] = 7904;
                break;
            case stbarra:
                SM15155_Struct->Current[3] = 7;
                SM15155_Struct->Current[4] = 7;
                SM15155_Struct->Duty[0] = 0;
                SM15155_Struct->Duty[1] = 40108;
                SM15155_Struct->Duty[2] = 0;
                SM15155_Struct->Duty[3] = 33817;
                SM15155_Struct->Duty[4] = 45023;
                break;
            case sthabu:
                SM15155_Struct->Current[0] = 9;
                SM15155_Struct->Current[1] = 6;
                SM15155_Struct->Current[2] = 6;
                SM15155_Struct->Current[3] = 17;
                SM15155_Struct->Current[4] = 17;
                SM15155_Struct->Duty[0] = 0;
                SM15155_Struct->Duty[1] = 24314;
                SM15155_Struct->Duty[2] = 0;
                SM15155_Struct->Duty[3] = 30409;
                SM15155_Struct->Duty[4] = 37159;
                break;   
            case stdiy:
                for(uint8_t i=0; i<5; i++)
                {
                    SM15155_Struct->Current[i]  = rx_buf[i+15];
                }
                break;     
            default:
                break;
        }
    }
    else
    {

    }
}