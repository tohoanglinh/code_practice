/*
 * pit.c
 *
 *  Created on: Mar 4, 2017
 *      Author: linhth8
 */

/**
 * @file      pit.c
 * @developer LinhTH8
 * @mentor    AnhNN14
 * @topic     MCP_PIT
 */

#include "pit.h"
#include "misc.h"
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void PIT_IRQHandler(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
Boolean g_flag_pit_irq;

/*******************************************************************************
 * Code
 ******************************************************************************/
void PIT_Init(uint8_t channel, double pit_delay)
{
    /* load value */
    uint32_t pit_load_value;

    /* enable clock */
    SIM->SCGC6 |= SIM_SCGC6_PIT(1);

    /* turn on PIT, by writing 0 to MDIS bit in PIT_MCR register */
    PIT->MCR &= PIT_MCR_FRZ(0);
    PIT->MCR &= PIT_MCR_MDIS(0);

      /*
       * PIT use peripheral bus clock = systemclock / OUTDIV4
       * at reset OUTDIV4 001: divide-by-2
       */
      pit_load_value = (uint32_t) (pit_delay * (SystemCoreClock / 2) - 1);
      PIT->CHANNEL[channel].LDVAL = PIT_LDVAL_TSV(pit_load_value);

      /* enable interrupt */
      PIT->CHANNEL[channel].TCTRL |= PIT_TCTRL_TIE(1);

      /* start timer */
      PIT->CHANNEL[channel].TCTRL |= PIT_TCTRL_TEN(1);
}

void PIT_IRQHandler(void)
{
    /* update software flag by setting g_flag_pit_irq to 1 */
    g_flag_pit_irq = TRUE;

    /* clear hardware flag */
    PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF(1);
}
