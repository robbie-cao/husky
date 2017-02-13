#ifndef __COMMON_H__
#define __COMMON_H__

/*
 * Standard C lib
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * TI SDK
 */
// Common define
#include "comdef.h"
#include "bcomdef.h"

// OSAL
#include "OSAL.h"
#include "OSAL_PwrMgr.h"

// Board
#include "OnBoard.h"

// Ble
#include "gatt.h"
#include "hci.h"

/*
 * Profiles
 */

/*
 * Drivers
 */
#include "uart.h"
#include "led.h"

/*
 * State machine
 */

/*
 * Utils
 */
#include "util.h"
#include "log.h"

/*
 * System
 */


// Status code
// Compatible to Generic Status Return Values
// defined in comdef.h
#define COMMON_STATUS_SUCCESS                    0x00
#define COMMON_STATUS_FAILURE                    0x01
#define COMMON_STATUS_INVALIDPARAMETER           0x02
#define COMMON_STATUS_INVALID_TASK               0x03
#define COMMON_STATUS_MSG_BUFFER_NOT_AVAIL       0x04
#define COMMON_STATUS_INVALID_MSG_POINTER        0x05
#define COMMON_STATUS_INVALID_EVENT_ID           0x06
#define COMMON_STATUS_INVALID_INTERRUPT_ID       0x07
#define COMMON_STATUS_NO_TIMER_AVAIL             0x08
#define COMMON_STATUS_NV_ITEM_UNINIT             0x09
#define COMMON_STATUS_NV_OPER_FAILED             0x0A


/*
 * App Task Events
 */
/* System Event */
#define COMMON_TASK_EVT_SYS_START                0x0001
#define COMMON_TASK_EVT_SYS_PERIODIC_TIMER       0x0002
#define COMMON_TASK_EVT_SYS_PM                   0x0004
#define COMMON_TASK_EVT_SYS_GP                   0x0008

/*  Button/Key Event */
#define COMMON_TASK_EVT_BUTTON                   0x0010          // Press/Release
#define COMMON_TASK_EVT_BUTTON_LP                0x0020          // Long Press
#define COMMON_TASK_EVT_BUTTON_CLK               0x0040          // Double Click

#define COMMON_TASK_EVT_KEY                      0x0080          // Press/Release
#define COMMON_TASK_EVT_KEY_LP                   0x0100          // Long Press
#define COMMON_TASK_EVT_KEY_CLK                  0x0200          // Double Click

#define COMMON_TASK_EVT_KEY_MAGIC                0x0400          // Magic Key

/* General Purpose Event */
#define COMMON_TASK_EVT_PROFILE_GP               0x0800          // GP Timer/Event

/* System Reserved Event */
#if defined (PLUS_BROADCASTER)
#define COMMON_APP_ADV_IN_CONNECTION_EVT         0x4000
#endif
/* 0x8000 is reserved as SYS_EVENT_MSG */

#define COMMON_TIME_START_DEVICE_DELAY           3000            // ms

// How often to perform periodic event
#define COMMON_TIME_PERIODIC_TIMER_INTV          1000            // ms

#if 0   // For DEBUG
#define COMMON_TIME_POWER_SAVE_WAIT              ((uint32)20 * 1000)     // ms, 20 sec
#define COMMON_TIME_DEEP_SLEEP_WAIT              ((uint32)1 * 30 * 1000) // ms, 30 sec
#else
#define COMMON_TIME_POWER_SAVE_WAIT              ((uint32)60 * 1000)     // ms, 60 sec
#define COMMON_TIME_DEEP_SLEEP_WAIT              ((uint32)3 * 60 * 1000) // ms, 3 min
#endif
#define COMMON_TIME_DEEP_SLEEP_DELAY             ((uint32)5 * 1000)      // ms, 5 sec

#define COMMON_TIME_MAGIC_KEY_WINDOW             5000            // ms, 5 sec

#define COMMON_TIME_KEYBOARD_DEBONCE             10              // ms


#define COMMON_SLEEP_RESET_P0_6                  1



uint16 Task_ProcessEvent(uint8 taskId, uint16 events);
void   Task_Init(uint8 taskId);


extern uint8 mTaskId;     // Task ID for internal task/event processing
extern uint8 mEvtParam;   // OSAL event param
extern void* mEvtData;    // OSAL event data

#endif /* __COMMON_H__ */

/* vim: set ts=2 sw=2 tw=0 list : */
