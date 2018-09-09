/* 
 * File:   svm_400hz_main.c
 * Author: Hoang-Linh
 *
 * Created on 2014-6-20, 12:44 (PM)
 */

#include <stdio.h>
#include <stdlib.h>
#include "svm_400hz.h"

_FOSC(CSW_FSCM_OFF & XT_PLL4); //XTL = 8 Mhz --> speed = 8 MPIS
_FWDT(WDT_OFF); //Watchdog timer off
_FBORPOR(MCLR_EN & PBOR_OFF);
_FGS(CODE_PROT_OFF); // Code protection off

void __attribute__ ((interrupt, auto_psv)) _PWMInterrupt(void)
{
    IFS2bits.PWMIF = 0; // Clear Interrupt Flag
    if (phase_angle < 0xffdc)
        {phase_angle += delta_phase;}
    else
        {phase_angle = 0;}
    SVM(phase_angle); // call function SVM to calculate pwm based on phase_angle
    return;
}
/*
 * 
 */
int main(void) {
    InitUserIO();
    InitMCPWM();
    phase_angle = 0;
    SVM(phase_angle);
    for (;;)
    {
        // Do nothing, just wait for interrupt.
    }
    return (EXIT_SUCCESS);
}

// functions definition (from header)
void InitMCPWM (void)
{
    // PWM pins as outputs, FLTA as input
    TRISE = 0x0100;
    // Compute period for desired PWM frequency
    PTPER = (FCY/FPWM - 1) >> 1;
    // Temporarily disable all PWM outputs
    OVDCON = 0x0000;
    // 1:1 Deadtime prescaler
    DTCON1 = DEADTIME;
    // Enable PWM output pins and complementary mode
    PWMCON1 = 0x0077;
    // Interrupt
    IFS2bits.PWMIF = 0;
    IEC2bits.PWMIE = 1;
    // PWM outputs are controlled by PWM module
    OVDCON = 0x3F00;
    // Center aligned PWM operation
    PTCONbits.PTMOD = 2;
    // Reset phase variable
    Phase = 0;
    // Initialize phase increment for 400Hz Sine Wave
    Delta_Phase = delta_phase;
    // Start PWM
    PTCONbits.PTEN = 1;
    return;
}
void InitUserIO (void)
{
    LATB = 0;
    TRISB = 0xffff;
    ADPCFG = 0;
    return;
}
void scale_t (void)
{
    t1 = sinetable[(unsigned char) (angle1 >> nbit)]; // look up values from table
    t2 = sinetable[(unsigned char) (angle2 >> nbit)]; // look up values from table

    // Scale t1 for the duty cycle range
    t1 = ((long)t1*(long)tpwm) >> 15;
    // Scale t2 time
    t2 = ((long)t2*(long)tpwm) >> 15;
}
void SVM(unsigned int angle)
{
    tpwm = PTPER << 1; // left shift operator needs less cycle than multiple operator

    if (angle < VECTOR2)
    {
        angle2 = angle - VECTOR1; // Ref SVM angle to the current sector
        angle1 = SIXTY_DEG - angle2; // Calculate 2nd angle Ref to sector

        scale_t();

        half_t0 = (tpwm - t1 - t2) >> 1; // Calculate half_t0 null time from period and t1,t2

        // Calculate duty cycles for Sector 1 (0 - 59deg)
        PDC1 = t1 + t2 + half_t0;
        PDC2 = t2 + half_t0;
        PDC3 = half_t0;
    }
    else if (angle < VECTOR3)
    {
        angle2 = angle - VECTOR2; // Ref SVM angle to the current sector
        angle1 = SIXTY_DEG - angle2; // Calculate 2nd angle Ref to sector

        scale_t();

        half_t0 = (tpwm - t1 - t2) >> 1; // Calculate half_t0 null time from period and t1,t2

        // Calculate duty cycles for Sector 2 (60 - 119deg)
        PDC1 = t1 + half_t0;
        PDC2 = t1 + t2 + half_t0;
        PDC3 = half_t0;
    }
    else if (angle < VECTOR4)
    {
        angle2 = angle - VECTOR3; // Ref SVM angle to the current sector
        angle1 = SIXTY_DEG - angle2; // Calculate 2nd angle Ref to sector

        scale_t();

        half_t0 = (tpwm - t1 - t2) >> 1; // Calculate half_t0 null time from period and t1,t2

        // Calculate duty cycles for Sector 3 (120 - 179deg)
        PDC1 = half_t0;
        PDC2 = t1 + t2 + half_t0;
        PDC3 = t2 + half_t0;
    }
    else if (angle < VECTOR5)
    {
        angle2 = angle - VECTOR4; // Ref SVM angle to the current sector
        angle1 = SIXTY_DEG - angle2; // Calculate 2nd angle Ref to sector

        scale_t();

        half_t0 = (tpwm - t1 - t2) >> 1; // Calculate half_t0 null time from period and t1,t2

        // Calculate duty cycles for Sector 4 (180 - 239deg)
        PDC1 = half_t0;
        PDC2 = t1 + half_t0;
        PDC3 = t1+ t2 + half_t0;
    }
    else if (angle < VECTOR6)
    {
        angle2 = angle - VECTOR5; // Ref SVM angle to the current sector
        angle1 = SIXTY_DEG - angle2; // Calculate 2nd angle Ref to sector

        scale_t();

        half_t0 = (tpwm - t1 - t2) >> 1; // Calculate half_t0 null time from period and t1,t2

        // Calculate duty cycles for Sector 5 (240 - 299deg)
        PDC1 = t2 + half_t0;
        PDC2 = half_t0;
        PDC3 = t1 + t2 + half_t0;
    }
    else
    {
        angle2 = angle - VECTOR6; // Ref SVM angle to the current sector
        angle1 = SIXTY_DEG - angle2; // Calculate 2nd angle Ref to sector

        scale_t();

        half_t0 = (tpwm - t1 - t2) >> 1; // Calculate half_t0 null time from period and t1,t2

        // Calculate duty cycles for Sector 6 (300 - 359deg)
        PDC1 = t1 + t2 + half_t0;
        PDC2 = half_t0;
        PDC3 = t1 + half_t0;
    }
} /* end SVM(angle)*/