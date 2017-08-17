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

#define configUSE_PREEMPTION                     1
#define configUSE_IDLE_HOOK                      0
#define configUSE_TICK_HOOK                      0

/*
 * tune this to the actual frequency used by the system timer peripheral
 * after reset with no PLL programming
 * - Z4 is running at 16MHz
 * - PIT channels running on the F40 clock at 4MHz
 */
#define configCPU_CLOCK_HZ                       ( 48000000UL ) /* 48MHz */
#define configTICK_RATE_HZ                       ( ( TickType_t ) 1000 )

#define configBUS_CLOCK_HZ                       24000000   /* 24MHz, not in demo_work */

#define configMAX_PRIORITIES                     ( 8 )      /* 7 */
#define configMINIMAL_STACK_SIZE                 ( ( unsigned short ) 200 )     /* 512 */
#define configTOTAL_HEAP_SIZE                    ( ( size_t ) 8192 )        /* 8KB vs. 48KB, */
#define configMAX_TASK_NAME_LEN                  ( 12 )         /* 13 */
#define configUSE_TRACE_FACILITY                 0
#define configUSE_16_BIT_TICKS                   0
#define configIDLE_SHOULD_YIELD                  1
#define configUSE_MUTEXES                        1
#define configQUEUE_REGISTRY_SIZE                0      /* not in demo_work */
#define configCHECK_FOR_STACK_OVERFLOW           0      /* 2 */
#define configUSE_RECURSIVE_MUTEXES              1
#define configUSE_MALLOC_FAILED_HOOK             0      /* not in demo_work */
#define configUSE_APPLICATION_TASK_TAG           0
#define configUSE_COUNTING_SEMAPHORES            1
/* Additional settings can be defined in the property Settings > User settings > Definitions of the FreeRTOS component */
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS  2

/* Software timer definitions. */
#define configUSE_TIMERS                         1
#define configTIMER_TASK_PRIORITY                ( 6 )  /* ( 3 vs. (configMAX_PRIORITIES) - 1 ) */
#define configTIMER_QUEUE_LENGTH                 10     /* 5 */
#define configTIMER_TASK_STACK_DEPTH             128    /* ( configMINIMAL_STACK_SIZE * 2 ) */

/* Calypso specific: pit channel to use 0-15 */
#define configUSE_PIT_CHANNEL                     15

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES                    0
#define configMAX_CO_ROUTINE_PRIORITIES          ( 2 )     /* 4 */

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet                 1
#define INCLUDE_uxTaskPriorityGet                1
#define INCLUDE_vTaskDelete                      1
#define INCLUDE_vTaskSuspend                     1

#define INCLUDE_vTaskDelayUntil                  1
#define INCLUDE_vTaskDelay                       1
#define INCLUDE_eTaskGetState                    0      /* 1 */

#define INCLUDE_uxTaskGetStackHighWaterMark      1      /* 0 */
#define INCLUDE_xTaskGetSchedulerState           1      /* 0 */
#define INCLUDE_xTaskGetCurrentTaskHandle        1
#define INCLUDE_xTaskGetIdleTaskHandle           0      /* not in demo_work */

#define INCLUDE_xQueueGetMutexHolder             1
#define INCLUDE_xTimerPendFunctionCall           1

#define INCLUDE_pcTaskGetTaskName                0
#define INCLUDE_xEventGroupSetBitFromISR         1


/* This demo makes use of one or more example stats formatting functions.  These
format the raw data provided by the uxTaskGetSystemState() function in to human
readable ASCII form.  See the notes in the implementation of vTaskList() within
FreeRTOS/Source/tasks.c for limitations. */
#define configUSE_STATS_FORMATTING_FUNCTIONS     0

/* Run time stats gathering definitions. */
#ifdef __ICCARM__
    /* The #ifdef just prevents this C specific syntax from being included in
    assembly files. */
    void vMainConfigureTimerForRunTimeStats( void );
    unsigned long ulMainGetRunTimeCounterValue( void );
#endif
#if defined(__GNUC__) && !defined(__ASSEMBLER__)
    /* The #ifdef just prevents this C specific syntax from being included in
    assembly files. */
    void vMainConfigureTimerForRunTimeStats( void );
    unsigned long ulMainGetRunTimeCounterValue( void );
#endif


#define configGENERATE_RUN_TIME_STATS            0 /* 1: generate runtime statistics; 0: no runtime statistics */

/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY  0x00

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configMAX_API_CALL_INTERRUPT_PRIORITY   (15) /* using highest priority */
  
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#ifndef configMAX_SYSCALL_INTERRUPT_PRIORITY
  #define configMAX_SYSCALL_INTERRUPT_PRIORITY   ( 1 )
#endif

/* Definition assert() function. */
#define configASSERT(x)                          if((x)==0) { taskDISABLE_INTERRUPTS(); for( ;; ); }   

/* Tickless Idle Mode */
#define configUSE_TICKLESS_IDLE                  0 
#define configEXPECTED_IDLE_TIME_BEFORE_SLEEP    2 
#define configUSE_TICKLESS_IDLE_DECISION_HOOK    0 
#endif /* FREERTOS_CONFIG_H */
