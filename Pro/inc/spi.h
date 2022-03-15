#ifndef __SPI_H__
#define __SPI_H__

#include "sm32f030.h"

void spi_init(void);
void spi_config(uint16_t mode);

#endif