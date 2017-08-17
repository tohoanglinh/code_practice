#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION                        1
#define configUSE_IDLE_HOOK                         0
#define configUSE_TICK_HOOK                         0

/*
 * tune this to the actual frequency used by the system timer peripheral
 * after reset with no PLL programming
 * - Z4 is running at 16MHz
 * - PIT channels running on the F40 clock at 4MHz
 */
#define configCPU_CLOCK_HZ                         ((unsigned portLONG ) 4000000 )
#define configTICK_RATE_HZ                         ((TickType_t) 1000 )

#define configMAX_PRIORITIES                       ( 7 )
#define configMINIMAL_STACK_SIZE                   ((unsigned portSHORT ) 512)
#define configTOTAL_HEAP_SIZE                      ( (size_t) (48 * 1024) )
#define configMAX_TASK_NAME_LEN                    ( 13 )
#define configUSE_TRACE_FACILITY                    0
#define configUSE_16_BIT_TICKS                      0
#define configIDLE_SHOULD_YIELD                     1
#define configUSE_MUTEXES                           1
#define configUSE_RECURSIVE_MUTEXES                 1
#define configUSE_COUNTING_SEMAPHORES               1
#define configCHECK_FOR_STACK_OVERFLOW              2
#define configUSE_APPLICATION_TASK_TAG              0
#define configUSE_FPU                               0       /* not in default_not_work */
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS     2       /* need to add for user setting */

/* Software timer definitions. */
#define configUSE_TIMERS                        1
#define configTIMER_TASK_PRIORITY               ( (configMAX_PRIORITIES) - 1 )
#define configTIMER_QUEUE_LENGTH                5
#define configTIMER_TASK_STACK_DEPTH            ( configMINIMAL_STACK_SIZE * 2 )

/* Calypso specific: pit channel to use 0-15 */
#define configUSE_PIT_CHANNEL                     15

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES                     0
#define configMAX_CO_ROUTINE_PRIORITIES         ( 4 )





/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet                  1
#define INCLUDE_uxTaskPriorityGet                 1
#define INCLUDE_vTaskDelete                       1
#define INCLUDE_vTaskCleanUpResources             1     /* not in default */
#define INCLUDE_vTaskSuspend                      1
#define INCLUDE_vResumeFromISR                    1     /* not in default */


#define INCLUDE_vTaskDelayUntil                   1
#define INCLUDE_vTaskDelay                        1
#define INCLUDE_eTaskGetState                     1

#define INCLUDE_uxTaskGetStackHighWaterMark       0
#define INCLUDE_xTaskGetSchedulerState            0
#define INCLUDE_xTaskGetCurrentTaskHandle         1

#define INCLUDE_xQueueGetMutexHolder              1
#define INCLUDE_xTimerPendFunctionCall            1

#define configMAX_API_CALL_INTERRUPT_PRIORITY     8

#endif /* FREERTOS_CONFIG_H */
