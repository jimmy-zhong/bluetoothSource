/**
*  @file      io_pio.h
*  @brief     CSR8670 PIO control and dectect
*  @author    Bill Wu
*  @date      11 -2013
*  @copyright Tymphany Ltd.
*/

#ifndef __IO_PIO_H__
#define __IO_PIO_H__
#include "config_product_pio.h"

typedef enum
{
    PIO_LEVEL_LOW,
    PIO_LEVEL_HIGH
} pio_level_t;

#define PIO_MASK(pio) (((uint32)1) << pio)

/**
 *  PIO init function. Called at system initialization
 *
 * @return void
 */
void io_pio_init(void);

/**
 *  Set PIO level. Only output pio can be set.
 *
 * @param pio PIO to be set
 * @param level PIO level
 * @return void
 */
void io_pio_set_level(pio_output_t pio, pio_level_t level);

/**
 *  Get PIO level. Only input pio can be read.
 *
 * @param pio PIO to be read
 * @return pio_level_t Queried pio is high or low.
 */
pio_level_t io_pio_get_level(pio_input_t pio);

/**
 *  Set level of several PIOs.
 *
 * @param mask Mask of PIOs to be set. Each bit corresponds to a PIO line.
 * @param bits Level of PIOs. each bit corresponds to a PIO line.
 * @return void
 */
void io_pio_set(uint32 mask, uint32 bits);

/**
 *  Get level of several PIOs.
 *
 * @return uint32 Level of PIOs, each bit corresponds to a PIO line.
 */
uint32 io_pio_get(void);

#endif /* __IO_PIO_H__ */

