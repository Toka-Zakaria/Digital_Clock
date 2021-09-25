/**********************************************************************************
 * [FILE NAME]: timer_private.h
 *
 * [AUTHOR]: Toka Zakaria Mohamed Ramadan
 *
 * [DATE CREATED]: Sep 3, 2021
 *
 * [Description]: File contains all the registers , bits & Interrupts for timers
 ***********************************************************************************/

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

#include"std_types.h"

/**************************************************************************
 *                      Timer0 Registers & Bits                           *
 * ************************************************************************/

#define TCCR0_REG                            (*( (volatile uint8 *)(0X53) ))
#define TCNT0_REG                            (*( (volatile uint8 *)(0X52) ))
#define OCR0_REG                             (*( (volatile uint8 *)(0X5C) ))
#define SFIOR_REG                            (*( (volatile uint8 *)(0X50) ))

#define CS00_BIT                               0
#define CS01_BIT                               1
#define CS02_BIT                               2
#define WGM01_BIT                              3
#define COM00_BIT                              4
#define COM01_BIT                              5
#define WGM00_BIT                              6
#define FOC0_BIT                               7

#define TOIE0_BIT                              0
#define OCIE0_BIT                              1

#define TOVO_BIT                               0
#define OCF0_BIT                               1

#define PSR10_BIT                              0

/**************************************************************************
 *                      Timer1 Registers & Bits                           *
 **************************************************************************/
#define TCCR1A_REG                           (*( (volatile uint16 *)(0X4F) ))
#define TCCR1B_REG                           (*( (volatile uint16 *)(0X4E) ))
#define TCNT1L_REG                           (*( (volatile uint8  *)(0X4C) ))
#define TCNT1H_REG                           (*( (volatile uint8  *)(0X4D) ))
#define TCNT1_REG                            (*( (volatile uint16 *)(0X4C) ))
#define OCR1AH_REG                           (*( (volatile uint8  *)(0X4B) ))
#define OCR1AL_REG                           (*( (volatile uint8  *)(0X4A) ))
#define OCR1A_REG                            (*( (volatile uint16 *)(0X4A) ))
#define OCR1BH_REG                           (*( (volatile uint8  *)(0X49) ))
#define OCR1BL_REG                           (*( (volatile uint8  *)(0X48) ))
#define OCR1B_REG                            (*( (volatile uint16 *)(0X48) ))
#define ICR1H_REG                            (*( (volatile uint8  *)(0X47) ))
#define ICR1L_REG                            (*( (volatile uint8  *)(0X46) ))
#define ICR1_REG                             (*( (volatile uint16 *)(0X46) ))

#define WGM10_BIT                                  0
#define WGM11_BIT                                  1
#define FOC1B_BIT                                  2
#define FOC1A_BIT                                  3
#define COM1B0_BIT                                 4
#define COM1B1_BIT                                 5
#define COM1A0_BIT                                 6
#define COM1A1_BIT                                 7

#define CS10_BIT                                   0
#define CS11_BIT                                   1
#define CS12_BIT                                   2
#define WGM12_BIT                                  3
#define WGM13_BIT                                  4
#define ICES1_BIT                                  6
#define ICNC1_BIT                                  7

#define TOIE1_BIT                                  2
#define OCIE1B_BIT                                 3
#define OCIE1A_BIT                                 4
#define TICIE1_BIT                                 5

#define TOV1_BIT                                   2
#define OCF1B_BIT                                  3
#define OCF1A_BIT                                  4
#define ICF1_BIT                                   5

/**************************************************************************
 *                      Timer2 Registers & Bits                           *
 * ************************************************************************/

#define TCCR2_REG                            (*( (volatile uint8 *)(0X45) ))
#define TCNT2_REG                            (*( (volatile uint8 *)(0X44) ))
#define OCR2_REG                             (*( (volatile uint8 *)(0X43) ))
#define ASSR_REG                             (*( (volatile uint8 *)(0X42) ))

#define CS20_BIT                               0
#define CS21_BIT                               1
#define CS22_BIT                               2
#define WGM21_BIT                              3
#define COM20_BIT                              4
#define COM21_BIT                              5
#define WGM20_BIT                              6
#define FOC2_BIT                               7

#define TOIE2_BIT                              6
#define OCIE2_BIT                              7

#define TOV2_BIT                               6
#define OCF2_BIT                               7

/**************************************************************************
 *                         Interrupts Registers                           *
 * ************************************************************************/
#define TIMSK_REG                            (*( (volatile uint8 *)(0X59) ))
#define TIFR_REG                             (*( (volatile uint8 *)(0X58) ))
/**************************************************************************
 *          Handing Interrupt service routine & Vector Table              *
 * ************************************************************************/
#define Timer2_COMP_vect              __vector_3
#define Timer2_OVF_vect               __vector_4
#define Timer1_COMPA_vect             __vector_6
#define Timer1_COMPB_vect             __vector_7
#define Timer1_OVF_vect               __vector_8
#define Timer0_OVF_vect               __vector_9
#define Timer0_COMP_vect              __vector_19



#define ISR(INTERRUPT)             void INTERRUPT(void)    __attribute__((signal)); \
                                   void INTERRUPT(void)

#endif /* TIMER_PRIVATE_H_ */
