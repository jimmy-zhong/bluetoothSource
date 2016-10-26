/**
*  @file        io_i2c.h
*  @brief       CSR8670 i2c reading and writing
*               Since the CSR's i2c transfer routine is not very comfortable for users, instead of
*               returning failuer or success, only number of ACK is returned! So re-package of it
*               to feedback failure/success is needed!
*  @author      Daniel Duan
*  @date        11 -2013
*  @copyright   Tymphany Ltd.
*/

#ifndef __IO_I2C_H__
#define __IO_I2C_H__

/* the max number of bytes that can be sent or received */
#define I2C_TX_BUFF_MAX_LEN                         (64)
#define I2C_RX_BUFF_MAX_LEN                         (64)

/* the resend times when failure happens */
#define I2C_RESEND_TIMES                            (2)

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
 * @return     bool                TRUE - transfer succeeded, FALSE - transfer failed
 */
bool IO_I2CTransfer(uint16 address, const uint8 *tx, uint16 tx_len, uint8 *rx, uint16 rx_len);

/**
 * A function to enable/disable I2C in CSR. Since sometimes(such as in Service mode), we need to stop I2C in CSR8670
 * side, so the developer can debug the DSP directly.
 *
 * @param      bool                TRUE - enable I2C in CSR side, FALSE - block I2C in CSR side.
 *
 * @return     void
 */
void IO_I2CEnable(bool enable);

/**
* Init I2C, by enabling it
*
* @param      void
*
* @return     void
*/
void IO_I2C_Init(void);

/**
* IO_GetI2CStatus
*
* @param      void
*
* @return     Enable or Disable
*/
bool IO_GetI2CStatus(void);
#endif
