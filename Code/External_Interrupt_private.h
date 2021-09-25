/**********************************************************************************
 * [FILE NAME]: External_Interrupt.c
 *
 * [AUTHOR]: Toka Zakaria Mohamed Ramadan
 *
 * [DATE CREATED]: Sep 6, 2021
 *
 * [Description]: File to configure the registers and bits of the external interrupts
 ***********************************************************************************/

#ifndef EXTERNAL_INTERRUPT_PRIVATE_H_
#define EXTERNAL_INTERRUPT_PRIVATE_H_

#include"std_types.h"

#define MCUCR_REG              (*( (volatile uint8 *)(0X55) ) )
#define MCUCSR_REG             (*( (volatile uint8 *)(0X54) ) )
#define GICR_REG               (*( (volatile uint8 *)(0X5B) ) )
#define GIFR_REG               (*( (volatile uint8 *)(0X5A) ) )


#define ISC00_BIT                       0
#define ISC01_BIT                       1
#define ISC10_BIT                       2
#define ISC11_BIT                       3

#define ISC2_BIT                        6

#define INT0_BIT                        6
#define INT1_BIT                        7
#define INT2_BIT                        5

#define INTF0_BIT                       6
#define INTF1_BIT                       7
#define INTF2_BIT                       5



#define INT0_vect               __vector_1
#define INT1_vect               __vector_2
#define INT2_vect               __vector_18


#define ISR(INTERRUPT)              void INTERRUPT(void)    __attribute__((signal)); \
	                                void INTERRUPT(void)




#endif /* EXTERNAL_INTERRUPT_PRIVATE_H_ */
