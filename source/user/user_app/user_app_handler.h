

#ifndef _USER_APP_HANDLER_H_
#define _USER_APP_HANDLER_H_


typedef enum
{
    USER_APP_TIME_INIT = 0x1000,
    USER_APP_TIME_TICK,
    END_OF_USER_EVT
}tUserAppEvt;


void user_app_handler(Task task, MessageId id, Message message);

#endif

