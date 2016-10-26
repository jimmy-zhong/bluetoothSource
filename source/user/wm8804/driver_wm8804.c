

#include "driver_wm8804.h"
#include <i2c.h>

#define DEVICE_ADD          0x76

#define WRITE_DATA_TO_WM8804(pData, data_len)      I2cTransfer(DEVICE_ADD, pData, data_len, (void *) 0, 0)
#define READ_DATA_FROM_WM8804(pData, data_len)     I2cTransfer(DEVICE_ADD, NULL, 0, pData, data_len)

const uint8 PWR_ON[] = {0x1E,0x04};
const uint8 PWR_OFF[] = {0x1E,0x00};


void drv_wm8804_init(void)
{
    WRITE_DATA_TO_WM8804(PWR_ON, sizeof(PWR_ON));
}



