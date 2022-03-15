#include "spi.h"

void spi_init(void)
{
    SPI_InitTypeDef SPI_InitStruct;
    
    SYSCON_AHBPeriphClockCmd(SYSCON_SYSAHBCLKCTRL_SPIEN | SYSCON_SYSAHBCLKCTRL_GPIOAEN, ENABLE);

    GPIO_Init(PA4, GPIO_Mode_OUT, IOCFG_PA4_FUNC_SPI_SSEL);
    GPIO_Init(PA5, GPIO_Mode_OUT, IOCFG_PA5_FUNC_SPI_SCK);
    GPIO_Init(PA7, GPIO_Mode_OUT, IOCFG_PA7_FUNC_SPI_MOSI);

    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_16b;
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStruct.SPI_NssIdleLevel = SPI_NSS_Idle_High;
    SPI_InitStruct.SPI_ClockPrescaler = 1;
    SPI_Init(&SPI_InitStruct);

    SPI_Cmd(ENABLE);
}

void spi_config(uint16_t mode)
{
    SPI_InitTypeDef SPI_InitStruct;

    if(mode == SPI_Mode_Slave)
    {
        GPIO_Init(PB12,GPIO_Mode_IN,IOCFG_PB12_FUNC_SPI_SSEL);
        GPIO_Init(PB13,GPIO_Mode_IN,IOCFG_PB13_FUNC_SPI_SCK);
        GPIO_Init(PB14,GPIO_Mode_OUT,IOCFG_PB14_FUNC_SPI_MISO);
        GPIO_Init(PB15,GPIO_Mode_IN,IOCFG_PB15_FUNC_SPI_MOSI);

        SPI_InitStruct.SPI_Mode = SPI_Mode_Slave;
        SPI_InitStruct.SPI_DataSize = SPI_DataSize_16b;
        SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
        SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
        SPI_InitStruct.SPI_NssIdleLevel = SPI_NSS_Idle_High;
        SPI_InitStruct.SPI_ClockPrescaler = 12;
    }
    else if(mode == SPI_Mode_Master)
    {
        GPIO_Init(PB12,GPIO_Mode_OUT,IOCFG_PB12_FUNC_SPI_SSEL);
        GPIO_Init(PB13,GPIO_Mode_OUT,IOCFG_PB13_FUNC_SPI_SCK);
        GPIO_Init(PB14,GPIO_Mode_IN,IOCFG_PB14_FUNC_SPI_MISO);
        GPIO_Init(PB15,GPIO_Mode_OUT,IOCFG_PB15_FUNC_SPI_MOSI);

        SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
        SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
        SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
        SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
        SPI_InitStruct.SPI_NssIdleLevel = SPI_NSS_Idle_High;
        SPI_InitStruct.SPI_ClockPrescaler = 12;
    }    

    SPI_Init(&SPI_InitStruct);
    SPI_Cmd(ENABLE);
}