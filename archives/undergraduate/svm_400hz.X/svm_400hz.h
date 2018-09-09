/* 
 * File:   svm_400hz.h
 * Author: Hoang-Linh TO
 * Date:   2014-06-20
 * Tools:  MPLAB X IDE v2.10; XC16 v1.21 (2014)
 * How-to-run:
 *    - Run --> Build all
 */

#ifndef SVM_400HZ_H
#define	SVM_400HZ_H

#ifdef	__cplusplus
extern "C" {

#endif

#include <xc.h> // 2.5. ANSI STD (Generic Header File), must include.
#include <p30F4011.h>

    void InitMCPWM(void); // Initialize MCPWM with freq = 20Khz, Complementary Mode, Center-Aligned
    void InitUserIO(void); // initalizie I/O port
    void SVM(unsigned int angle);
    void scale_t(void);

    /* Declare variables: angle1, angle2, as global, to store normalized
     * angle value to calculate t1 and t2.
     * half_t0, t1, and t2: time period to build space vectors.
     */
    unsigned int angle1, angle2;
    unsigned int half_t0, t1, t2, tpwm;
    unsigned int Phase, Delta_Phase, Phase_Offset;
    unsigned int phase_angle;

    /* Define constants: frequency of crystal, pwm, deadtime, delta_phase
     * Use crystal 8MIPS
     */
#define FCY 8000000 //8 MIPS
#define FPWM 20000 // 20 kHz
#define DEADTIME (unsigned int)(0.000001*FCY)
#define delta_phase (unsigned int)(65536*400/FPWM) // delta_phase = 0x51E

#define VECTOR1 0           // 0 degree
#define VECTOR2 0x2aaa      // 60 degrees
#define VECTOR3 0x5555      // 120 degrees
#define VECTOR4 0x8000      // 180 degrees
#define VECTOR5 0xaaaa      // 240 degrees
#define VECTOR6 0xd555      // 300 degrees
#define SIXTY_DEG 0x2aaa
#define nbit 6

    /* Sine table: 171 elements, represent angles from 0 --> 60 deg
     * (Why? with 360 deg, we need 1024 elements --> 60 deg need 1024*(60/360) = 171)
     * Attribute: far. This means sine table can be allocate anywhere in data memory
     * This sine table has constant as elements. We will put them in memory .const of dsPIC30F
     * int i __attribute__((space(auto_psv));
     */
    int sinetable[] __attribute__ ((far, space(auto_psv))) =
    {0,201,402,603,804,1005,1206,1407,1608,1809,2009,2210,2410,2611,2811,
    3012,3212,3412,3612,3811,4011,4210,4410,4609,4808,5007,5205,5404,5602,
    5800,5998,6195,6393,6590,6786,6983,7179,7375,7571,7767,7962,8157,8351,
    8545,8739,8933,9126,9319,9512,9704,9896,10087,10278,10469,10659,10849,
    11039,11228,11417,11605,11793,11980,12167,12353,12539,12725,12910,13094,
    13279,13462,13645,13828,14010,14191,14372,14553,14732,14912,15090,15269,
    15446,15623,15800,15976,16151,16325,16499,16673,16846,17018,17189,17360,
    17530,17700,17869,18037,18204,18371,18537,18703,18868,19032,19195,19357,
    19519,19680,19841,20000,20159,20317,20475,20631,20787,20942,21096,21250,
    21403,21554,21705,21856,22005,22154,22301,22448,22594,22739,22884,23027,
    23170,23311,23452,23592,23731,23870,24007,24143,24279,24413,24547,24680,
    24811,24942,25072,25201,25329,25456,25582,25708,25832,25955,26077,26198,
    26319,26438,26556,26674,26790,26905,27019,27133,27245,27356,27466,27575,
    27683,27790,27896,28001,28105,28208,28310,28411};

#ifdef	__cplusplus
}
#endif

#endif	/* SVM_400HZ_H */

