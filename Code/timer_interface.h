/**********************************************************************************
 * [FILE NAME]: timer_interface.h
 *
 * [AUTHOR]: Toka Zakaria Mohamed Ramadan
 *
 * [DATE CREATED]: Sep 3, 2021
 *
 * [Description]: File of All types Declaration and Functions prototypes of timer
 *                configuration.
 *
 ***********************************************************************************/
#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

#include "std_types.h"
#include"timer_private.h"

#include<avr/io.h>


/**************************************************************************
 *                              Timer0                                    *
 * ************************************************************************/
#define TIMER0_CONTROL_REGIRSTER                                   TCCR0_REG
#define TIMER0_INITIAL_VALUE_REGISTER                              TCNT0_REG
#define TIMER0_OUTPUT_COMPARE_REGISTER                             OCR0_REG
#define TIMER0_INTERRUPT_MASK_REGISTER                             TIMSK_REG
#define TIMER0_INTERRUPT_FLAG_REGISTER                             TIFR_REG

/*TIMER0_CONTROL_REGIRSTER*/
#define TIMER0_FORCE_OUTPUT_COMPARE_BIT                             FOC0_BIT
#define TIMER0_WAVE_FORM_GENERATION_BIT0                            WGM00_BIT
#define TIMER0_WAVE_FORM_GENERATION_BIT1                            WGM01_BIT
#define TIMER0_COMPARE_OUTPUT_MODE_BIT0                             COM00_BIT
#define TIMER0_COMPARE_OUTPUT_MODE_BIT1                             COM01_BIT
#define TIMER0_CLOCK_SELECT_BIT0                                    CS00_BIT
#define TIMER0_CLOCK_SELECT_BIT1                                    CS01_BIT
#define TIMER0_CLOCK_SELECT_BIT2                                    CS02_BIT

/*TIMER0_INTERRUPT_MASK_REGISTER*/
#define TIMER0_OUTPUT_OVERFLOW_INTERRUPT                            TOIE0_BIT
#define TIMER0_OUTPUT_COMPARE_MATCH_INTERRUPT                       OCIE0_BIT

/*TIMER0_INTERRUPT_FLAG_REGISTER*/
#define TIMER0_OVERFLOW_FLAG                                        TOVO_BIT
#define TIMER0_COMPARE_FLAG                                         OCF0_BIT

#define TIMER0_CLOCK_MASK_CLEAR                                      0XF8
#define TIMER0_COM0_MASK_CLEAR                                       0XCF
#define COM0_SHIFT_VALUE                                              4
#define OC0_PIN                                                      PB3
#define OC0_DATA_PORT                                                PORTB
#define OC0_DIRECTION_PORT                                           DDRB
/**************************************************************************
 *                              Timer1                                    *
 * ************************************************************************/
/*TIMER1 REGISTERS*/
#define TIMER1_CONTROL_REGIRSTER_A                              TCCR1A_REG
#define TIMER1_CONTROL_REGIRSTER_B                              TCCR1B_REG
#define TIMER1_INITIAL_VALUE_REGISTER                           TCNT1_REG
#define TIMER1_INITIAL_VALUE_LOW_REGISTER                       TCNT1L_REG
#define TIMER1_INITIAL_VALUE_HIGH_REGISTER                      TCNT1H_REG
#define TIMER1_OUTPUT_COMPARE_REGISTER_A_LOW                    OCR1AL_REG
#define TIMER1_OUTPUT_COMPARE_REGISTER_A_HIGH                   OCR1AH_REG
#define TIMER1_OUTPUT_COMPARE_REGISTER_A                        OCR1A_REG
#define TIMER1_OUTPUT_COMPARE_REGISTER_B_LOW                    OCR1BL_REG
#define TIMER1_OUTPUT_COMPARE_REGISTER_B_HIGH                   OCR1BH_REG
#define TIMER1_OUTPUT_COMPARE_REGISTER_B                        OCR1B_REG
#define TIMER1_INPUT_CAPTURE_REGISTER_LOW                       ICR1L_LOW
#define TIMER1_INPUT_CAPTURE_REGISTER_HIGH                      ICR1H_HIGH
#define TIMER1_INPUT_CAPTURE_REGISTER                           ICR1_REG
#define TIMER1_INTERRUPT_MASK_REGISTER                          TIMSK_REG
#define TIMER1_INTERRUPT_FLAG_REGISTER                          TIFR_REG

/*TIMER1_CONTROL_A_REGIRSTER*/
#define TIMER1_WAVE_FORM_GENERATION_BIT10                       WGM10_BIT
#define TIMER1_WAVE_FORM_GENERATION_BIT11                       WGM11_BIT
#define TIMER1_FORCE_OUTPUT_COMPARE_BIT_B                       FOC1B_BIT
#define TIMER1_FORCE_OUTPUT_COMPARE_BIT_A                       FOC1A_BIT
#define TIMER1_COMPARE_OUTPUT_BIT0_CHANNEL_B                    COM1B0_BIT
#define TIMER1_COMPARE_OUTPUT_BIT1_CHANNEL_B                    COM1B1_BIT
#define TIMER1_COMPARE_OUTPUT_BIT0_CHANNEL_A                    COM1A0_BIT
#define TIMER1_COMPARE_OUTPUT_BIT1_CHANNEL_A                    COM1A1_BIT

/*TIMER1_CONTROL_B_REGIRSTER*/
#define TIMER1_CLOCK_SELECT_BIT0                                CS10_BIT
#define TIMER1_CLOCK_SELECT_BIT1                                CS11_BIT
#define TIMER1_CLOCK_SELECT_BIT2                                CS12_BIT
#define TIMER1_INPUT_CAPTURE_NOISE_CANCELER                     ICES1_BIT
#define TIMER1_WAVE_FORM_GENERATION_BIT12                       WGM12_BIT
#define TIMER1_WAVE_FORM_GENERATION_BIT13                       WGM13_BIT

/*TIMER1_INTERRUPT_MASK_REGISTER*/
#define TIMER1_OUTPUT_OVERFLOW_INTERRUPT                        TOIE1_BIT
#define TIMER1_OUTPUT_COMPARE_MATCH_INTERRUPT_A                 OCIE1A_BIT
#define TIMER1_OUTPUT_COMPARE_MATCH_INTERRUPT_B                 OCIE1B_BIT
#define TIMER1_INPUT_CAPTURE_INTERRUPT_ENABLE                   TICIE1_BIT

/*TIMER1_INTERRUPT_FLAG_REGISTER*/
#define  TIMER1_OVERFLOW_FLAG                                   TOV1_BIT
#define  TIMER1_OUTPUT_COMPARE_A_MATCH_FLAG                     OCF1A_BIT
#define  TIMER1_OUTPUT_COMPARE_B_MATCH_FLAG                     OCF1B_BIT
#define  TIMER1_INPUT_CAPTURE_FLAG                              ICF1_BIT

#define OC1A_PIN                                                  PD5
#define OC1A_DATA_PORT                                           PORTD
#define OC1A_DIRECTION_PORT                                      DDRD

#define OC1B_PIN                                                 PD4
#define OC1B_DATA_PORT                                           PORTD
#define OC1B_DIRECTION_PORT                                      DDRD

#define COM1A_SHIFT_VALUE                                        6
#define COM1B_SHIFT_VALUE                                        4

#define TIMER1_CLOCK_MASK_CLEAR                                 0XF8
#define TIMER1_COM1A_MASK_CLEAR                                 0X3F
#define TIMER1_COM1B_MASK_CLEAR                                 0XCF
/**************************************************************************
 *                              Timer2                                    *
 * ************************************************************************/
/*TIMER2 REGISTERS*/
#define TIMER2_CONTROL_REGIRSTER                                TCCR2_REG
#define TIMER2_INITIAL_VALUE_REGISTER                           TCNT2_REG
#define TIMER2_OUTPUT_COMPARE_REGISTER                          OCR2_REG
#define TIMER2_INTERRUPT_MASK_REGISTER                          TIMSK_REG
#define TIMER2_INTERRUPT_FLAG_REGISTER                          TIFR_REG

/*TIMER2_CONTROL_REGIRSTER*/
#define TIMER2_FORCE_OUTPUT_COMPARE_BIT                         FOC2_BIT
#define TIMER2_WAVE_FORM_GENERATION_BIT0                        WGM20_BIT
#define TIMER2_WAVE_FORM_GENERATION_BIT1                        WGM21_BIT
#define TIMER2_COMPARE_OUTPUT_MODE_BIT0                         COM20_BIT
#define TIMER2_COMPARE_OUTPUT_MODE_BIT1                         COM21_BIT
#define TIMER2_CLOCK_SELECT_BIT0                                CS20_BIT
#define TIMER2_CLOCK_SELECT_BIT1                                CS21_BIT
#define TIMER2_CLOCK_SELECT_BIT2                                CS22_BIT

/*TIMER2_INTERRUPT_MASK_REGISTER*/
#define TIMER2_OUTPUT_OVERFLOW_INTERRUPT                        TOIE2_BIT
#define TIMER2_OUTPUT_COMPARE_MATCH_INTERRUPT                   OCIE2_BIT

/*TIMER0_INTERRUPT_FLAG_REGISTER*/
#define TIMER2_OVERFLOW_FLAG                                    TOV2_BIT
#define TIMER2_COMPARE_FLAG                                     OCF2_BIT

#define TIMER2_CLEAR_COMPARE_OUTPUT_MODE_BITS_VALUE               0XCF
#define TIMER2_CLOCK_MASK_CLEAR                                   0XF8

#define TIMER2_COM2_MASK_CLEAR                                    0XCF
#define COM2_SHIFT_VALUE                                           4
#define OC2_PIN                                                   PD7
#define OC2_DATA_PORT                                             PORTD
#define OC2_DIRECTION_PORT                                        DDRD
/****************************************************************************/

/**************************************************************************
 *                       Timer0 & Timer1 & Timer2                         *
 * ************************************************************************/
typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024

}Timer_Clock;

/**************************************************************************
 *                            Timer0 & Timer2
 * ************************************************************************/
typedef enum
{
	Overflow, PWM_PhaseCorrect, CTC, FAST_PWM

}Timer_8BIT_Mode;

typedef enum
{
	Disconnected_NonPWM_8, Toggle_NonPWM_8, Clear_NonPWM_8, Set_NonPWM_8

}CompareOutputMode_NonPWM_8BITS;

typedef enum
{
	Disconnected_FASTPWM_8, Reserved_FASTPWM_8, Clear_FASTPWM_8, Set_FASTPWM_8

}CompareOutputMode_FASTPWM_8BITS;

typedef enum
{
	Disconnected_PWMPhaseCorrect_8, Reserved_PWMPhaseCorrect_8, Clear_PWMPhaseCorrect_8, Set_PWMPhaseCorrect_8

}CompareOutputMode_PWMPhaseCorrect_8BITS;

/**************************************************************************
 *                                Timer1
 * ************************************************************************/
typedef enum
{
	Normal, PWM_PhaseCorrect_8bit,  PWM_PhaseCorrect_9bit ,
	PWM_PhaseCorrect_10bit , CTC_OCR1A, FAST_PWM_8bit,
	FAST_PWM_9bit, FAST_PWM_10bit, PWM_Phase_FrequencyCorrect_ICR1,
	PWM_Phase_FrequencyCorrect_OCR1A, PWM_PhaseCorrect_ICR1, PWM_PhaseCorrect_OCR1A,
	CTC_ICR1, Reserved_Mode, FAST_PWM_ICR1, FAST_PWM_OCR1A

}Timer_16BIT_Mode;

typedef enum
{
	ChannelA, ChannelB

}Channel_Type;


typedef enum
{
	Disconnected_NonPWM_16, Toggle_NonPWM_16, Clear_NonPWM_16, Set_NonPWM_16

}CompareOutputMode_NonPWM_16BITS;

typedef enum
{
	Disconnected_FASTPWM_16, Reserved_FASTPWM_16, Clear_FASTPWM_16, Set_FASTPWM_16

}CompareOutputMode_FASTPWM_16BITS;

typedef enum
{
	Disconnected_PWMPhaseCorrect_16, Reserved_PWMPhaseCorrect_16, Clear_PWMPhaseCorrect_16, Set_PWMPhaseCorrect_16

}CompareOutputMode_PWMPhaseCorrect_16BITS;

/**************************************************************************
 *                                Timer0
 * ************************************************************************/
typedef struct
{
	uint8 timer0_InitialValue;
	uint8 timer0_compare_MatchValue;
	Timer_Clock timer0_clock;
	Timer_8BIT_Mode  timer0_mode;
	CompareOutputMode_NonPWM_8BITS Compare_Mode_NonPWM;
	CompareOutputMode_FASTPWM_8BITS Compare_Mode_FASTPWM;
	CompareOutputMode_PWMPhaseCorrect_8BITS Compare_Mode_PWM_PhaseCorrect;

}Timer0_ConfigType;

/**************************************************************************
 *                                Timer1
 * ************************************************************************/
typedef struct
{
	uint16 timer1_InitialValue;
	uint16 timer1_compare_MatchValue;
	uint16 timer1_InputCaptureValue;
	Timer_Clock timer1_clock;
	Timer_16BIT_Mode  timer1_mode;
	Channel_Type   channel;
	CompareOutputMode_NonPWM_16BITS Compare_Mode_NonPWM;
	CompareOutputMode_FASTPWM_16BITS Compare_Mode_FASTPWM;
	CompareOutputMode_PWMPhaseCorrect_16BITS Compare_Mode_PWM_PhaseCorrect;
}Timer1_ConfigType;
/**************************************************************************
 *                                Timer2
 * ************************************************************************/
typedef struct
{
	uint8 timer2_InitialValue;
	uint8 timer2_compare_MatchValue;
	Timer_Clock timer2_clock;
	Timer_8BIT_Mode  timer2_mode;
	CompareOutputMode_NonPWM_8BITS Compare_Mode_NonPWM;
	CompareOutputMode_FASTPWM_8BITS Compare_Mode_FASTPWM;
	CompareOutputMode_PWMPhaseCorrect_8BITS Compare_Mode_PWM_PhaseCorrect;

}Timer2_ConfigType;

/**************************************************************************
 *                                Timer0
 * ************************************************************************/
/***************************************************************************************************
 * [Function Name]: Timer0_init
 *
 * [Description]:  Function to Initialize Timer0 Driver
 *                 - Working in Interrupt Mode
 *                 - Choose Timer0 initial value
 *                 - Choose Timer_Mode (OverFlow,PWM_PhaseCoorect ,CTC, FAST_PWM)
 *                 - Choose Timer compare match value if using CTC mode
 *                 - Choose Timer_Clock
 *
 *
 * [Args]:         config_PTR
 *
 * [In]            Config_Ptr: Pointer to Timer Configuration Structure
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void Timer0_Init(const Timer0_ConfigType* config_PTR);
/***************************************************************************************************
 * [Function Name]: Timer0_DeInit
 *
 * [Description]:  Function to DeInit the timer to cancel the configuration
 *                   and return to the default mode
 *
 * [Args]:         NONE
 *
 *
 * [In]            NONE
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void Timer0_DeInit(void);
/***************************************************************************************************
 * [Function Name]: Timer0_setCallBack
 *
 * [Description]:  Function to set the Call Back function address.
 *
 * [Args]:         a_Ptr
 *
 * [In]            a_Ptr: -Pointer to function
 *                        -To use it to save receive the function call back name
 *                        -To store it in the global pointer to function to use it in
 *
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void Timer0_setCallBack( void(*a_ptr)(void) );
/***************************************************************************************************
 * [Function Name]: Timer0_stop
 *
 * [Description]:  Function to stop the clock of the timer to stop incrementing
 *
 * [Args]:         NONE
 *
 *
 * [In]            NONE
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void Timer0_Stop(void);
/***************************************************************************************************
 * [Function Name]: Timer0_Start
 *
 * [Description]:  Function to configure the clock of the timer to start count
 *
 * [Args]:        timer0_clock_value
 *
 *
 * [In]           timer0_clock_value:  -Variable from type enum Timer_Clock
 *                                     -To use it to choose the clock of the timer
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void Timer0_Start(Timer_Clock timer0_clock_value);
/***************************************************************************************************
 * [Function Name]: Timer0_Change_CompareMatchValue
 *
 * [Description]:  Function to change the value of compare match in the timer
 *
 * [Args]:         timer0_newCompareValue
 *
 * [In]            timer0_newCompareValue: Variable to carry the new value of the compare
 *                                         match
 * [Out]            NONE
 *
 * [Returns]:       NONE
 ***************************************************************************************************/
void Timer0_Change_CompareMatchValue(uint8 timer0_newCompareValue);
/**************************************************************************
 *                                Timer1
 * ************************************************************************/
/***************************************************************************************************
 * [Function Name]: Timer1_init
 *
 * [Description]:  Function to Initialize Timer1 Driver
 *                 - Working in Interrupt Mode
 *                 - Choose Timer1 initial value
 *                 - Choose Timer1_Mode
 *                 - Choose Timer1 compare match value if using CTC mode
 *                 - Choose Timer1_Clock
 *
 *
 * [Args]:         Timer1_config_PTR
 *
 * [In]            Timer1_Config_Ptr: Pointer to Timer Configuration Structure
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void Timer1_Init(const Timer1_ConfigType* Timer1_config_PTR);
/***************************************************************************************************
 * [Function Name]: Timer1_DeInit
 *
 * [Description]:  Function to DeInit the timer to cancel the configuration
 *                   and return to the default mode
 *
 * [Args]:         timer_type
 *
 *
 * [In]            timer_type: -Variable from type enum Timer_Mode
 *                             -To use it to choose the type of the timer
 *                             -DeInit the required timer
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void Timer1_DeInit(void);
/***************************************************************************************************
 * [Function Name]: Timer1_setCallBack
 *
 * [Description]:  Function to set the Call Back function address.
 *
 * [Args]:         a_Ptr
 *
 * [In]            a_Ptr: -Pointer to function
 *                        -To use it to save receive the function call back name
 *                        -To store it in the global pointer to function to use it in
 *
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void Timer1_setCallBack( void(*a_ptr)(void) );
/***************************************************************************************************
 * [Function Name]: Timer1_stop
 *
 * [Description]:  Function to stop the clock of the timer to stop incrementing
 *
 * [Args]:         NONE
 *
 *
 * [In]            NONE
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void Timer1_Stop(void);
/***************************************************************************************************
 * [Function Name]: Timer1_Start
 *
 * [Description]:  Function to configure the clock of the timer to start count
 *
 * [Args]:        timer1_clock_value
 *
 *
 * [In]           timer1_clock_value:  -Variable from type enum Timer_Clock
 *                                     -To use it to choose the clock of the timer
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void Timer1_Start(Timer_Clock timer1_clock_value);
/***************************************************************************************************
 * [Function Name]: Timer1_Change_CompareMatchValue
 *
 * [Description]:  Function to change the value of compare match in the timer
 *
 * [Args]:         -timer1_newCompareValue
 *                 -channel
 *
 * [In]            -timer1_newCompareValue: Variable to carry the new value of the compare
 *                                          match
 *                 -channel: to know the type of which channel the timer will work
 *
 * [Out]            NONE
 *
 * [Returns]:       NONE
 ***************************************************************************************************/
void Timer1_Change_CompareMatchValue(uint16 timer1_newCompareValue, Channel_Type channel);
/**************************************************************************
 *                                Timer2
 * ************************************************************************/
/***************************************************************************************************
 * [Function Name]: Timer2_init
 *
 * [Description]:  Function to Initialize Timer2 Driver
 *                 - Working in Interrupt Mode
 *                 - Choose Timer2 initial value
 *                 - Choose Timer_Mode (OverFlow,PWM_PhaseCoorect ,CTC, FAST_PWM)
 *                 - Choose Timer compare match value if using CTC mode
 *                 - Choose Timer_Clock
 *
 *
 * [Args]:         config_PTR
 *
 * [In]            Config_Ptr: Pointer to Timer Configuration Structure
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void Timer2_Init(const Timer2_ConfigType* config_PTR);
/***************************************************************************************************
 * [Function Name]: Timer2_DeInit
 *
 * [Description]:  Function to DeInit the timer to cancel the configuration
 *                   and return to the default mode
 *
 * [Args]:         NONE
 *
 *
 * [In]            NONE
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void Timer2_DeInit(void);
/***************************************************************************************************
 * [Function Name]: Timer2_setCallBack
 *
 * [Description]:  Function to set the Call Back function address.
 *
 * [Args]:         a_Ptr
 *
 * [In]            a_Ptr: -Pointer to function
 *                        -To use it to save receive the function call back name
 *                        -To store it in the global pointer to function to use it in
 *
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void Timer2_setCallBack( void(*a_ptr)(void) );
/***************************************************************************************************
 * [Function Name]: Timer2_stop
 *
 * [Description]:  Function to stop the clock of the timer to stop incrementing
 *
 * [Args]:         NONE
 *
 *
 * [In]            NONE
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void Timer2_Stop(void);
/***************************************************************************************************
 * [Function Name]: Timer2_Start
 *
 * [Description]:  Function to configure the clock of the timer to start count
 *
 * [Args]:        timer2_clock_value
 *
 *
 * [In]           timer2_clock_value:  -Variable from type enum Timer_Clock
 *                                     -To use it to choose the clock of the timer
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void Timer2_Start(Timer_Clock timer2_clock_value);
/***************************************************************************************************
 * [Function Name]: Timer2_Change_CompareMatchValue
 *
 * [Description]:  Function to change the value of compare match in the timer
 *
 * [Args]:         timer2_newCompareValue
 *
 * [In]            timer2_newCompareValue: Variable to carry the new value of the compare
 *                                         match
 * [Out]            NONE
 *
 * [Returns]:       NONE
 ***************************************************************************************************/
void Timer2_Change_CompareMatchValue(uint8 timer2_newCompareValue);
/****************************************************************************************************/
#endif /* TIMER_INTERFACE_H_ */
