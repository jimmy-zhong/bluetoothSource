/**
*  @file        io_i2c.c
*  @brief       CSR8670 i2c reading and writing
*               Since the CSR's i2c transfer routine is not very comfortable for users, instead of
*               returning failuer or success, only number of ACK is returned! So re-package of it
*               to feedback failure/success is needed!
*  @author      Daniel Duan
*  @date        11 -2013
*  @copyright   Tymphany Ltd.
*/
#include <i2c.h>
#include <assert.h>
#include <memory.h>


#include "io_i2c.h"

#define DEBUG_I2Cx

#ifdef DEBUG_I2C
#define I2C_DEBUG(x)          TYM_DEBUG(x)
#else
#define I2C_DEBUG(x)
#endif


#define BUF_INIT_VALUE (0xABCD)

typedef struct
{
    bool      enable;        /* TRUE when I2C is enabled, FALSE when disabled */
} I2C_Ctrl_Blk_t;

static I2C_Ctrl_Blk_t I2C_Ctrl_Blk;


/**
 * Steps:
 * 1/ Sends out slave address;
 * 2/ Sends out bytes stored in tx buffer;
 * 3/ Restarts the transmission;
 * 4/ Receives the bytes sent back by slave.
 *
 * @param      uint16              slave address
 *             const uint8*        pointer to the tx buffer
 *             uint16              tx buffer size in byte
 *             uint8*              pointer to the rx buffer
 *             uint16              number of bytes supposed to be received
 *
 * @return     bool                TRUE - transfer succeeded, or I2C is disabled, FALSE - transfer failed
 */
bool IO_I2CTransfer(uint16 address, const uint8 *tx, uint16 tx_len, uint8 *rx, uint16 rx_len)
{
    uint16 cycle = 0;
    uint16 ack_num = 0;
    uint16 i;

    I2C_DEBUG(("I2C: transfer params: \n"));
    I2C_DEBUG(("I2C: tx_len: %d, rx_len: %d\n", tx_len, rx_len));

    if(!(I2C_Ctrl_Blk.enable))
    {
        I2C_DEBUG(("I2C: I2C is disabled!!! \n"));
        return FALSE;
    }

    if(tx_len > I2C_TX_BUFF_MAX_LEN)
    {
        I2C_DEBUG(("I2C: tx length exceeds 64!!!\n"));
        return FALSE;
    }

    else if(rx_len > I2C_RX_BUFF_MAX_LEN)
    {
        I2C_DEBUG(("I2C: rx length exceeds 64!!!\n"));
        return FALSE;
    }

    while(cycle < I2C_RESEND_TIMES)
    {
        /* If need to read data, set buffer to a 16 bit data */
        if(rx_len != 0)
        {
            memset(rx, BUF_INIT_VALUE, rx_len);
        }

        ack_num = I2cTransfer(address, tx, tx_len, rx, rx_len);
        I2C_DEBUG(("I2C: in cycle[%d], got %d acks back", cycle, ack_num));

        /* Check the read buffer data, if it still init value, means read fail. CSR will set high 8 bits to zero, and
        set low with data */
        for(i = 0; i < rx_len; i++)
        {
            if(rx[i] == BUF_INIT_VALUE)
            {
                return FALSE;
            }
        }

        if(ack_num >= tx_len)
        {
            I2C_DEBUG(("I2C: transfer succeeds in cycle[%d]\n", cycle));
            return TRUE;
        }

        I2C_DEBUG(("I2C: transfer fails in cycle[%d]\n", cycle));
        cycle++;
    }

    return FALSE;
}


/**
 * A function to enable/disable I2C in CSR. Since sometimes(such as in Service mode), we need to stop I2C in CSR8670
 * side, so the developer can debug the DSP directly.
 *
 * @param      bool                TRUE - enable I2C in CSR side, FALSE - block I2C in CSR side.
 *
 * @return     void
 */
void IO_I2CEnable(bool enable)
{
    I2C_DEBUG(("I2C: IO_I2CEnable [%x]!!! \n", enable));

    I2C_Ctrl_Blk.enable = enable;
}

/**
* Init I2C, by enabling it, panics if fails
*
* @param      void
*
* @return     void
*/
void IO_I2C_Init(void)
{
    IO_I2CEnable(TRUE);
}


/**
* IO_GetI2CStatus
*
* @param      void
*
* @return     Enable or Disable
*/
bool IO_GetI2CStatus(void)
{
    return (I2C_Ctrl_Blk.enable);
}


