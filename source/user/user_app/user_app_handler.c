


#include <message.h>
#include "source_private.h"

#include "io_i2c.h"
#include "io_pio.h"
#include "driver_wm8804.h"
#include "user_app_handler.h"
#include "source_app_msg_handler.h"

uint8 tx_buf[8];

#define USER_APP_MSG_SEND( id, msg) MessageSend(&theSource->app_data.appTask, id, msg)


#define USER_APP_MSG_SEND_LATER(id, time_ms)  MessageSendLater(&theSource->app_data.appTask, id, 0, time_ms)
#define USER_APP_MSG_CANCEL(id)   MessageCancelAll(&theSource->app_data.appTask, id)
#define USER_APP_MSG_BUTTON_SEND(id, time_ms)  MessageSendLater(&theSource->button_data.buttonTask, id, 0, time_ms)
                
void user_app_handler(Task task, MessageId id, Message message)
{
    switch (id)
    {
        case APP_INIT_CFM:
            USER_APP_MSG_CANCEL(USER_APP_TIME_TICK);
            USER_APP_MSG_SEND_LATER(USER_APP_TIME_TICK, 1000);
            io_pio_init();
            IO_I2CEnable(TRUE);
            io_pio_set_level(PIO_AMP_MUTE, PIO_LEVEL_HIGH);
            io_pio_set_level(PIO_EXT_IC_RESET, PIO_LEVEL_HIGH);
            break;
        case USER_APP_TIME_TICK:
            USER_APP_MSG_BUTTON_SEND(BUTTON_MSG_RESET_PAIRED_DEVICE_LIST, 1000);
            break;
        case APP_DISCONNECT_IND:
            USER_APP_MSG_BUTTON_SEND(BUTTON_MSG_RESET_PAIRED_DEVICE_LIST, 1000);
            break;
        default:
        break;
    }
}

