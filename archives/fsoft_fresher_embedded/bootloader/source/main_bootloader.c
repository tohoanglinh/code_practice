/**
 * @file      main_bootloader.c
 * @start     Mar 9, 2017
 * @finish    Mar 17, 2017
 * @developer LinhTH8
 * @mentor    MinhNQ2 + HaiND1
 * @topic     MCP_BOOTLOADER
 * @requires  Write a bootloader code in flash
 *      - SREC parse
 *      - UART transmit/receive
 *      - Jump from Boot to App
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include "array.h"
#include "misc.h"
#include "board.h"

#include "gpio.h"
#include "uart.h"
#include "srec.h"
#include "Flash.h"
/*******************************************************************************
 * Typedef
 ******************************************************************************/
typedef void (application_t) (void);

typedef struct vector
{
    uint32_t        stack_addr;     /* intvec[0] is initial Stack Pointer   */
    application_t   *func_p;        /* intvec[1] is initial Program Counter */
} vector_t;
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define APP_START_ADDR_STORAGE 0x1E00
#define APP_SIZE_IN_SECTOR 16U

#define BOOTSW_GPIO GPIOC
#define BOOTSW_PIN 3
#define BOOTSW_PRESSED   ((BOOTSW_GPIO->PDIR >> BOOTSW_PIN) & 1)

/* constants for UART configuration */
#define UART_BAUD_RATE 115200U
#define UART_PRIORITY 1

/* defines for max size of srec data (2-dim array) */
#define MAX_LINES 256U
#define MAX_CHARS 80U
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void App(uint32_t app_start);
void Boot(void);
void BOOT_SwitchFlashMode(char tmp_line[]);
void BOOT_WriteToFlash(void);
/*******************************************************************************
 * Global Variables
 ******************************************************************************/
/* 2-dim array to store srec data */
char g_line[MAX_LINES][MAX_CHARS];

uint8_t g_queue_sender;
uint8_t g_queue_receiver;
uint8_t g_queue_size;

extern SREC_struct_t g_srec;
/*******************************************************************************
 * Main
 ******************************************************************************/
void main(void)
{
    /*------------------------vars------------------------*/

    /*------------------------init------------------------*/
    /* BootSW Init */
    GPIO_Init(BOOTSW_GPIO, BOOTSW_PIN, 1);

    /* UART_Init */
    UART_Init(UART_BAUD_RATE);
    NVIC_Config(UART0_IRQn, UART_PRIORITY);

    /* Display */
    UART_Printf_S(UART_CLEAR_SCREEN);
    UART_Printf_S(UART_GO_TO_HOME);
    UART_Printf_S("FRDM-KL46Z:...\r\n");

    /* pressed --> 0, unpressed --> 1 */
    if (BOOTSW_PRESSED == 0)
    {
      /* boot */
      Boot();
    }
    else
    {
      if (Read_FlashAddress(APP_START_ADDR_STORAGE) == 0x000000)
      {
        /* if no App --> run Boot */
        Boot();
      }
      else
      {
        /* if has App --> run App */
        App(Read_FlashAddress(APP_START_ADDR_STORAGE));
      }
    }
    /*------------------------loop------------------------*/
    while(1);
}

/*******************************************************************************
 * UART0_IRQHandler()
 * - if receive interrupt occurs,
 * -  update line_index
 * -  save all received characters into a 2-dim array
 * -   if the received character is end of line (\r)
 * - ......assign that character to end of string (\0)
 * - ......reset char_index
 ******************************************************************************/
void UART0_IRQHandler (void)
{
  static uint8_t line_index;
  static uint8_t char_index;

  /* if receive interrupt occur */
  if (UART0->S1&UART_S1_RDRF_MASK)
  {
    /* 0 --> 255, 256 will be reset to 0 */
    line_index = g_queue_sender;

    /* save data into a 2-dim array */
    g_line[line_index][char_index] = UART0->D;

    /* continue save into array until reach CR character EOL */
    if (g_line[line_index][char_index] == '\r')
    {
      /* reset the CR character to end of string character */
      g_line[line_index][char_index] = '\0';
      char_index = 0;

      /* update queue indexes of sender and increase queue size */
      g_queue_sender++;
      g_queue_size++;
    }
    else
    {
      /* read the next character */
      char_index++;
    }
  }
}

/*******************************************************************************
 * App(app_start) Procedure
 * - jump to app start address in memory
 ******************************************************************************/
void App(uint32_t app_start)
{
    const vector_t *vector_p            = (vector_t*) app_start;
    volatile uint32_t stack_arr[100]    = {0}; /* Allocate some stack
                                                just to show that the SP
                                                should be reset before the
                                                jump - or the stack won't be
                                                configured correctly */
    __enable_interrupt();

    UART_Printf_S("APP: Running LedBlinking...(^_^)\r\n");

    __disable_interrupt();                      /* 1. Disable interrupts */
    __set_SP(vector_p->stack_addr);             /* 2. Configure stack pointer */
    SCB->VTOR = (uint32_t) app_start;           /* 3. Configure VTOR */
    vector_p->func_p();                         /* 4. Jump to application */
}

/*******************************************************************************
 * Boot() Procedure
 * - parse SREC line
 * - test format and checksum
 * -  ... if OK, switch FlashMode, then Flash if S1,S2,S3, Complete if S7,S8,S9
 * -  ... if NotOK, display corresponding error
 * - update queue at receiver (SREC processing side)
 ******************************************************************************/
void Boot(void)
{
  char tmp_str[UART_MAX_STR_PRINTF];
  static uint8_t line_index;

  UART_Printf_S("BOOT: Waiting for SREC...(@_@)\r\n");

  while (1)
  {
    if (g_queue_size > 0)
    {
      /* 0 --> 255, 256 will be reset to 0 */
      line_index = g_queue_receiver;

      /* display line index */
      sprintf(tmp_str, "Line %d.\r\n", line_index+1);
      UART_Printf_S(tmp_str);

      /* parse SREC */
      SREC_ParseLine(g_line[line_index]);

      /* test format and checksum */
      if (SREC_Format(g_line[line_index]))
      {
        if (g_srec.cal_checksum == g_srec.get_checksum)
        {
          /* save & update start address to a Flash storage (0x1E00) */
          if (line_index == 1)
          {
            Erase_Sector(APP_START_ADDR_STORAGE);
            Program_LongWord(APP_START_ADDR_STORAGE, g_srec.address);
          }

          /* switch flash mode */
          BOOT_SwitchFlashMode(g_line[line_index]);

          /* display all extracted SREC data for debug purpose */
          SREC_DisplayLine(g_line[line_index]);
        }
        else
        {
          /* display checksum error */
          UART_Printf_S(g_line[line_index]);
          UART_Printf_S("\r\nChecksum error\r\n");
          UART_Printf_S("------------------------------------------------\r\n");
        } /* end of if checksum */
      }
      else
      {
        /* display format error */
        UART_Printf_S(g_line[line_index]);
        UART_Printf_S("\r\nFormat error\r\n");
        UART_Printf_S("------------------------------------------------\r\n");
      }  /* end of if format */
      /* update queue indexes of receiver and decrease queue size */
      g_queue_receiver++;
      g_queue_size--;
    }
  }
}

/**
 * @brief: BOOT_SwitchFlashMode. Switch flash mode between 'S'
 * @input tmp_line[] a string array
 * @output: void
 */
void BOOT_SwitchFlashMode(char tmp_line[])
{
  switch (tmp_line[1])
  {
    case '0':
      {
          UART_Printf_S("[S0] Formatting Flash...\r\n");
          Erase_Multi_Sector(Read_FlashAddress(APP_START_ADDR_STORAGE), APP_SIZE_IN_SECTOR);
          break;
      }
    case '1':
    case '2':
    case '3':
      {
          UART_Printf_S("[S1,S2,S3] Writing to Flash...\r\n");
          BOOT_WriteToFlash();
          break;
      }
    case '7':
    case '8':
    case '9':
      {
          UART_Printf_S("[S7,S8,S9] Completing...-->(APP)\r\n");
          App(Read_FlashAddress(APP_START_ADDR_STORAGE));
          break;
      }
    default:
      {
          UART_Printf_S("[N/A] Please recheck...\r\n");
          break;
      }
  }
}

/**
 * @brief: BOOT_WriteToFlash. Check if data_bytecount % 4 or not.
 * If not % 4, then program_longword is called with additional length (+1)
 * @input: tmp_line[] a string array
 * @output: call Program_LongWord to write address and data to Flash memory.
 * @return: void
 */
void BOOT_WriteToFlash(void)
{
  uint8_t i;
  uint8_t tmp_length;

  if ((g_srec.data_bytecount % 4) == 0)
  {
    tmp_length = g_srec.data_bytecount/4;
  }
  else
  {
    tmp_length = g_srec.data_bytecount/4 + 1;
  }

  for (i = 0; i < tmp_length; i++)
  {
    Program_LongWord_8B(g_srec.address + i*4, g_srec.data + i*4);
  }
}