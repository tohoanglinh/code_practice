/*
 * uart.c
 *
 *  Created on: Mar 4, 2017
 *      Author: linhth8
 */

/**
 * @file      uart.c
 * @developer LinhTH8
 * @mentor    HaiND1
 * @topic     MCP_UART (Universal Asynchronous Receiver Transmitter)
 */

#include "uart.h"
#include "array.h"
#include "misc.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define ARRAY_SIZE (OSR_MAX - OSR_MIN + 1)
/*******************************************************************************
 * UART_APP_Layer
 ******************************************************************************/
/**
UART0->S1               0x1010 0010
UART0_S1_TDRE_MASK      0x1000 0000
Result                  0x0000 0000 (if TDE = 0) 0 -> FALSE --> ! = TRUE
Result                  0x1000 0000 (if TDE = 1)#0 -> TRUE --> ! = FALSE
 */
void UART_Printf_C(char ch)
{
    /* Wait until space is available in the FIFO */
    while(!(UART0->S1 & UART0_S1_TDRE_MASK));

    /* If transmit data buffer is empty, Send the character */
    UART0->D = ch;
}

char UART_Scanf_C(void)
{
    /* Wait until character has been received */
    while (!(UART0->S1 & UART0_S1_RDRF_MASK));

    /* If receive data buffer is full, Return the 8-bit data from the receiver */
    return UART0->D;
}

void UART_Printf_S(char str[])
{
    uint8_t tmp_index = 0;

    /* check it's not end of string */
    while (str[tmp_index] != '\0')
    {
      /* transmit each character */
      UART_Printf_C(str[tmp_index]);
      tmp_index++;
    }
}
/*******************************************************************************
 * UART_HAL_Layer
 ******************************************************************************/
void UART_Init(uint32_t baud_rate)
{
  uint8_t osr_optimal;

  osr_optimal = UART0_OsrOptimal(baud_rate);

  UART_BaudRateInit(baud_rate, osr_optimal);
}

/**
* @detail: find the optimal value of OSR based on baudrate input
*
* Over sampling ratio, default 0x0F (16)
* - depend on OSR, receiver has acquisition rate of 4 to 32 samples per bit time.
*     4x (00011)  32x (11111)   16x(01111)
* osr = 0x03 --> acquisition = 4x (0 0011) = osr + 1;
* osr = 0x0F --> acquisition = 16x (0 1111) = osr + 1;
* receiver acquisition rate = osr + 1;
* - should only be changed when both transmitter and receiver are disabled.
* - UART0->C4 = osr;
*
* OSR range: 3 (0b11)--> 31 (0b1111)
* ==> we should allocate arrays with size = (31 - 3) + 1 = 29
*/
uint8_t UART0_OsrOptimal(uint32_t baud_rate)
{
  /* declare and init arrays for calculating osr */
  uint8_t osr[ ARRAY_SIZE ] = {0};
  uint16_t sbr[ ARRAY_SIZE ] = {0};
  uint32_t new_baud_rate[ ARRAY_SIZE ] = {0};
  uint16_t diff[ ARRAY_SIZE ] = {0};
  uint8_t i;

  for (i = 0; i < ARRAY_SIZE; i++)
  {
      /* osr[0] = 0 + 3 = 3; osr[28] = 28 + 3 = 31 */
      osr[i] = i + OSR_MIN;

      /* calculate sbr[i] corresponding to osr[i] */
      sbr[i] = (SystemCoreClock/baud_rate) / (osr[i]+1);

      /* calculate new baudrate based on sbr[i] and osr[i] */
      new_baud_rate[i] = SystemCoreClock/(sbr[i]*(osr[i]+1));

      /* calculate the difference of baudrates, just take the absolute value */
      if (baud_rate > new_baud_rate[i])
      {
        diff[i] = baud_rate - new_baud_rate[i];
      }
      else
      {
        diff[i] = new_baud_rate[i] - baud_rate;
      }
  }

  /* return the optimal osr value, at which difference of baudrates is minimum */
  return (min_array(diff, ARRAY_SIZE) + OSR_MIN);
}
/**
* @detail: init UART to work based on inputs: baudrate and over sampling ratio
*/
uint32_t UART_BaudRateInit(uint32_t baud_rate, uint8_t osr)
{
  uint16_t sbr;
  uint32_t actual_baud_rate;

  /* select clock for UART0 as MCGFLLCLK */
  SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);

  /* disable open-drain mode for output pins of UART0
  * clear bit 16: UART0ODE
  */
  SIM->SOPT5 &= SIM_SOPT5_UART0ODE(0);

  /* select source for UART0 receive data (UART0_RX pin)
  * clear bit 2: UART0RXSRC
  */
  SIM->SOPT5 &= SIM_SOPT5_UART0RXSRC(0);

  /* select source for UART0 transmit data (UART0_TX pin)
  * clear bit 1 and 0: UART0TXSRC
  */
  SIM->SOPT5 &= SIM_SOPT5_UART0TXSRC(0);

  /* set bit 10 for giving clock to UART0 */
  SIM->SCGC4 |= SIM_SCGC4_UART0(1);
  /* set bit 9 for giving clock to PORTA */
  SIM->SCGC5 |= SIM_SCGC5_PORTA(1);

  /* PTA1 as UART0_RX (alternative 2, page 173 RM) */
  UART0_RX_PORT->PCR[UART0_RX_PIN] &= ~PORT_PCR_MUX_MASK;
  UART0_RX_PORT->PCR[UART0_RX_PIN] |= PORT_PCR_MUX(2);
  /* PTA2 as UART0_TX (alternative 2, page 173 RM) */
  UART0_TX_PORT->PCR[UART0_TX_PIN] &= ~PORT_PCR_MUX_MASK;
  UART0_TX_PORT->PCR[UART0_TX_PIN] |= PORT_PCR_MUX(2);

   /* disable TX and RX for updating osr and baud rate */
  UART0->C2 &= UART0_C2_TE(0);
  UART0->C2 &= UART0_C2_RE(0);

    /* load osr value into C4 register */
    UART0->C4 = UART0_C4_OSR(osr);
    /*
    * SBR: Baud Rate Modulor Divisor
    * Calculate sbr based on baudrate, osr, SystemCoreClock
    * SBR[12:0] baud clock divisor for asynchronous UART baud clock (1-->8191)
    * SBR bits are in UART baud rate registers, BDH and BDL.
    *
    * SystemCoreClock default = 20971520 Hz
    * Example to calculate SBR based on baud rate from default clock, OSR = 3.
    *  UART0->BDH = 0x02; // 9600 baud; OSR = 3; module clock 20.97152MHz SBR=546 = 10 0010 0010
    *  UART0->BDL = 0x22;
    *
    *  UART0->BDH = 0x00; // 115200 baud; OSR = 3; clock 20971520Hz; SBR = 45.51 = 0x002D
    *  UART0->BDL = 0x2D;
    */
    sbr = SystemCoreClock / (baud_rate * (osr + 1));

    actual_baud_rate = SystemCoreClock / (sbr * (osr + 1));

    UART0->BDH = sbr >> 8;      /* extract high part */
    UART0->BDL = sbr & 0xFF;    /* extract low part */

    /* Data bit: 8 */
    UART0->C1 &= UART0_C1_M(0);

    /* Parity: None */
    UART0->C1 &= UART0_C1_PE(0);

    /* Stop bits */
    UART0->BDH &= UART0_BDH_SBNS(0);

  #if UART_MODE == INTERRUPT
    /* enable Interrupt for RDRF */
    UART0->C2 |= UART0_C2_RIE(1);
  #endif

  /* enable TX and RX */
  UART0->C2 |= UART0_C2_TE(1);
  UART0->C2 |= UART0_C2_RE(1);

  /* return actual baudrate after configuration */
  return actual_baud_rate;
}

uint8_t UART0_OsrOptimal_HaiND(uint32_t baud_rate, uint32_t clk)
{
  uint16_t sbr = 0;
  uint16_t sbr_temp;
  uint8_t osr = 0;
  uint8_t osr_temp;

  uint32_t calculateBaud;
  uint32_t baudDiff;
  baudDiff = baud_rate;
  uint32_t tempDiff;

  for (osr_temp = (OSR_MIN+1); osr_temp <= (OSR_MAX+1); osr_temp++)
  {
      sbr_temp = (clk/(baudDiff * osr_temp));
      /* set sbr_temp to 1 if the sourceClockInHz cannot satisfy the desire baudrate */
      if (0 == sbr_temp)
      {
          sbr_temp = 1;
          calculateBaud = (clk/(sbr_temp * osr_temp));
          tempDiff = baudDiff - calculateBaud;
      }
      else
      {
          calculateBaud = (clk/(sbr_temp * osr_temp));
          tempDiff = calculateBaud - baudDiff;
          /* select better value between sbr and sbr+1 */
          if (tempDiff > (baudDiff - (clk/((sbr_temp +1) * osr_temp))))
          {
              tempDiff = baudDiff - (clk/((sbr_temp +1) * osr_temp));
              sbr_temp++;
          }
      }
      if (tempDiff < baudDiff)
      {
          baudDiff = tempDiff;
          sbr = sbr_temp;
          osr = osr_temp;
      }
  }
  return (osr+sbr);
}