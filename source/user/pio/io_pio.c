/**
*  @file      io_pio.c
*  @brief     CSR8670 PIO control and dectect
*  @author    Bill Wu
*  @date      11 -2013
*  @copyright Tymphany Ltd.
*/
#include <pio.h>
#include <assert.h>

#include "io_pio.h"

/* For CSR8670, only PIN13~PIN28 can be mapped */
#define PIN_BEGIN (13)
#define PIN_END   (28)
#define PIO_MAP_SUPPORT_MASK ((0xFFFFFFFF >> PIN_BEGIN << PIN_BEGIN) << (31 - PIN_END) >> (31 - PIN_END))

#define PIO_MAP_MASK ((PIO_INPUT_MASK | PIO_OUTPUT_MASK) & PIO_MAP_SUPPORT_MASK)

static void set_pio_direction(void);

/**
 *  PIO init function. Called at system initialization
 *
 * @return void
 */
void io_pio_init(void)
{
    set_pio_direction();
}

/**
 *  Set PIO level. Only output pio can be set.
 *
 * @param pio PIO to be set
 * @param level PIO level
 * @return void
 */
void io_pio_set_level(pio_output_t pio, pio_level_t level)
{
 /*   assert(PIO_MASK(pio) & PIO_OUTPUT_MASK);*/

    if(level == PIO_LEVEL_LOW)
    {
        /*Set EN PIO to Low Level*/
        PioSet32(PIO_MASK(pio), 0);
    }
    else if(level == PIO_LEVEL_HIGH)
    {
        /*Set PIO to High Level*/
        PioSet32(PIO_MASK(pio), PIO_MASK(pio));
    }
    else
    {}
}

/**
 *  Get PIO level. Only input pio can be read.
 *
 * @param pio PIO to be read
 * @return pio_level_t queried pio is high or low.
 */
pio_level_t io_pio_get_level(pio_input_t pio)
{
    if(PioGet32() & PIO_MASK(pio))
    {
        return PIO_LEVEL_HIGH;
    }
    else
    {
        return PIO_LEVEL_LOW;
    }
}

/**
 *  Set level of several PIOs.
 *
 * @param mask Mask of PIOs to be set. Each bit corresponds to a PIO line.
 * @param bits Level of PIOs. each bit corresponds to a PIO line.
 * @return void
 */
void io_pio_set(uint32 mask, uint32 bits)
{
    PioSet32(mask, bits);
}

/**
 *  Get level of several PIOs.
 *
 * @return uint32 Level of PIOs, each bit corresponds to a PIO line.
 */
uint32 io_pio_get(void)
{
    return PioGet32();
}

/**
 *  Set direction of PIOs.
 *
 * @return void
 */
static void set_pio_direction(void)
{
    /* Set the PIN to be PIO  */
    assert(0x0 == PioSetMapPins32(PIO_MAP_MASK, PIO_MAP_MASK));

    /* Set PIO direction as input */
    assert(0x0 == PioSetDir32(PIO_INPUT_MASK, 0));

    /* Set PIO direction as output */
    assert(0x0 == PioSetDir32(PIO_OUTPUT_MASK, PIO_OUTPUT_MASK));
}

