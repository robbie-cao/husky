/*
 * Shared by App and OTA
 */
#include "common.h"
#include "hal_i2c.h"
#include "led.h"

#define DEBUG_DTHR         0

#define DEBUG_WRITEVOLUME  0

#define FILTER_NUM         3    // Press button duration time 150ms. Unit: 50ms
#define DRUATION_CNT_NUM   30   // Press button duration time 3min for Plastic shell. Unit: 100ms

#define TEST_AUTO_SIMU     0

#define LOG_TAG   "MAIN"

#define CHECK_HEARTBEAT    1


/*********************************************************************
 * GLOBAL VARIABLES
 */
uint8 mTaskId;              // Task ID for internal task/event processing
uint8 mEvtParam   = 0;      // OSAL event param
void* mEvtData    = NULL;   // OSAL event data


/*********************************************************************
 * LOCAL VARIABLES
 */


/*********************************************************************
 * LOCAL FUNCTIONS
 */
static void Task_PeriodicTask(void);
static void Task_ProcessOsalMsg(osal_event_hdr_t *pMsg);

/*********************************************************************
 * @fn      Task_PeriodicTask
 *
 * @brief   Perform a periodic application task.
 *
 * @param   none
 *
 * @return  none
 */
static void Task_PeriodicTask(void)
{

}

/*********************************************************************
 * @fn      Task_ProcessOsalMsg
 *
 * @brief   Process an incoming task message.
 *
 * @param   pMsg - message to process
 *
 * @return  none
 */
static void Task_ProcessOsalMsg(osal_event_hdr_t *pMsg)
{
  switch (pMsg->event)
  {
    default:
      // Do nothing
      break;
  }
}

/*********************************************************************
 * GLOBAL FUNCTIONS
 */

/*********************************************************************
 * @fn      Task_ProcessEvent
 *
 * @brief   Application Task event processor.  This function
 *          is called to process all events for the task.  Events
 *          include timers, messages and any other user defined events.
 *
 * @param   taskId - The OSAL assigned task ID.
 * @param   events - events to process.  This is a bit map and can
 *                   contain more than one event.
 *
 * @return  events not processed
 */
uint16 Task_ProcessEvent(uint8 taskId, uint16 events)
{
  VOID taskId; // OSAL required parameter that isn't used in this function

  if (events & SYS_EVENT_MSG)
  {
    uint8 *pMsg = NULL;

    pMsg = osal_msg_receive(mTaskId);

    while (pMsg)
    {
      /* Do something here */
      Task_ProcessOsalMsg((osal_event_hdr_t *)pMsg);

      /* De-allocate */
      VOID osal_msg_deallocate(pMsg);
      /* Next */
      pMsg = osal_msg_receive(mTaskId);
    }

    // Return unprocessed events
    return (events ^ SYS_EVENT_MSG);
  }

  // Discard unknown events
  return 0;
}

void Task_Init(uint8 taskId)
{
  mTaskId = taskId;

  // !!!PAY ATTENTION TO THE ORDER OF INIT!!!

  UART_Init(NULL);

  // Product and version info
  LOG("\r\n");
  LOG("Init\r\n");

#if defined HAL_IMAGE_A
  LOG("OTA\r\n");
#elif defined HAL_IMAGE_B
  LOG("App\r\n");
#else
  LOG("Std\r\n");
#endif

  // Enable clock divide on halt
  // This reduces active current while radio is active and CC254x MCU
  // is halted
  HCI_EXT_ClkDivOnHaltCmd(HCI_EXT_ENABLE_CLK_DIVIDE_ON_HALT);
}

/* vim: set ts=2 sw=2 tw=0 list : */
