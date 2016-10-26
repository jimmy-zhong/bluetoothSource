/**
*  @file      config_product_pio.h
*  @brief    PIO configuration file
*  @author    Bill Wu
*  @date      01-2014
*  @copyright Tymphany Ltd.
*/

#ifndef __CONFIG_PRODUCT_PIO_H__
#define __CONFIG_PRODUCT_PIO_H__


/*****************************
 *   Input PIO config
 *
 *****************************/
typedef enum
{
    PIO_CH_STATUS_DETECT    = 4,
    PIO_AUX_IN_DETECT       = 10,
    PIO_AMP_ALARM           = 12                /* dummy */
} pio_input_t;
#define PIO_INPUT_MASK (PIO_MASK(PIO_AMP_ALARM) \
                    | PIO_MASK(PIO_AUX_IN_DETECT) \
                    | PIO_MASK(PIO_CH_STATUS_DETECT))


/*****************************
 *   Output PIO config
 *
 *****************************/
typedef enum
{
    PIO_AMP_MUTE       = 3,
    PIO_USB_UART       = 22,                        /* dummy */
    PIO_AMP_REGEN      = 16,
    PIO_EXT_IC_RESET   = 0,
    PIO_ISET_1              = 2,
    PIO_ISET_2              = 1,
    PIO_USB_EN      = 17
} pio_output_t;
#define PIO_OUTPUT_MASK (PIO_MASK(PIO_EXT_IC_RESET) \
                    | PIO_MASK(PIO_AMP_REGEN) \
                    | PIO_MASK(PIO_AMP_MUTE) \
                    | PIO_MASK(PIO_USB_UART) \
                    | PIO_MASK(PIO_USB_EN) \
                    | PIO_MASK(PIO_ISET_1) \
                    | PIO_MASK(PIO_ISET_2))


/*****************************
 *   LED PWM PIO config
 *
 *****************************/
#define LED_PIN_BLUE             LED_2
#define LED_PIN_WHITE          LED_1				/* This is GREEN in CA9, because of tri-color LED */
#define LED_PIN_RED               LED_0

/*****************************
 *   BATT_LED PWM PIO config
 *
 *****************************/
#define BATT_LED_PIN_RED         AW9523_P0_1_ADD
#define BATT_LED_PIN_GREEN     AW9523_P1_3_ADD
#define BATT_LED_PIN_BLUE        AW9523_P1_1_ADD

#define MIC_MUTE_LED_PIN            AW9523_P0_3_ADD
#define MIC_UNMUTE_LED_PIN       AW9523_P0_2_ADD


/*****************************
 *   CALL_LED PIO config
 *
 *****************************/
#define CALL_LED_PIN_RED         AW9523_P0_3_ADD
#define CALL_LED_PIN_GREEN     AW9523_P0_2_ADD

/****************************
 *  AUX PIO detect
 *
 ****************************/
#define AUX_IN_PLUGGED_LEVEL PIO_LEVEL_HIGH

#endif  /* __CONFIG_PRODUCT_PIO_H__ */

