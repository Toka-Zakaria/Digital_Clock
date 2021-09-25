/**********************************************************************************
 * [FILE NAME]: timer.c
 *
 * [AUTHOR]: Toka Zakaria Mohamed Ramadan
 *
 * [DATE CREATED]: Sep 3, 2021
 *
 * [Description]: File to initialize All Timers in Atmega16
 ***********************************************************************************/
#include"timer_interface.h"
#include"common_macros.h"

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_Timer0_callBackPtr)(void) = NULL_PTR;
static volatile void (*g_Timer1_callBackPtr)(void) = NULL_PTR;
static volatile void (*g_Timer2_callBackPtr)(void) = NULL_PTR;


/**************************************************************************
 *                  Timer0_Interrupt_Service_Routines                     *
 * ************************************************************************/
ISR(TIMER0_OVF_vect)
{
	if(g_Timer0_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer0_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}

	/* Clear the flag of timer0 over flow Interrupt*/
	TIMER0_INTERRUPT_FLAG_REGISTER = SET_BIT(TIMER0_INTERRUPT_FLAG_REGISTER, TIMER0_OVERFLOW_FLAG);
}

ISR(TIMER0_COMP_vect)
{
	if(g_Timer0_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer0_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
	/* Clear the flag of timer0 compare Interrupt*/
	TIMER0_INTERRUPT_FLAG_REGISTER = SET_BIT(TIMER0_INTERRUPT_FLAG_REGISTER, TIMER0_COMPARE_FLAG);
}
/**************************************************************************
 *                  Timer1_Interrupt_Service_Routines                     *
 * ************************************************************************/
ISR(TIMER1_OVF_vect)
{
	if(g_Timer1_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer1_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}

	/* Clear the flag of timer1 over flow Interrupt*/
	TIMER1_INTERRUPT_FLAG_REGISTER = SET_BIT(TIMER1_INTERRUPT_FLAG_REGISTER, TIMER1_OVERFLOW_FLAG);

}

ISR(TIMER1_COMPA_vect)
{
	if(g_Timer1_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer1_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
	/* Clear the flag of timer1 compare Interrupt for channelA*/
	TIMER1_INTERRUPT_FLAG_REGISTER = SET_BIT(TIMER1_INTERRUPT_FLAG_REGISTER, TIMER1_OUTPUT_COMPARE_A_MATCH_FLAG);
}

ISR(TIMER1_COMPB_vect)
{
	if(g_Timer1_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer1_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
	/* Clear the flag of timer1 compare Interrupt for channelB*/
	TIMER1_INTERRUPT_FLAG_REGISTER = SET_BIT(TIMER1_INTERRUPT_FLAG_REGISTER, TIMER1_OUTPUT_COMPARE_B_MATCH_FLAG);

}

/**************************************************************************
 *                  Timer2_Interrupt_Service_Routines                     *
 * ************************************************************************/
ISR(TIMER2_OVF_vect)
{
	if(g_Timer2_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer2_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}

	/* Clear the flag of timer0 over flow Interrupt*/
	TIMER2_INTERRUPT_FLAG_REGISTER = SET_BIT(TIMER2_INTERRUPT_FLAG_REGISTER, TIMER2_OVERFLOW_FLAG);
}

ISR(TIMER2_COMP_vect)
{
	if(g_Timer2_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer2_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
	/* Clear the flag of timer0 compare Interrupt*/
	TIMER2_INTERRUPT_FLAG_REGISTER = SET_BIT(TIMER2_INTERRUPT_FLAG_REGISTER, TIMER2_COMPARE_FLAG);
}
/******************************************************************************/


/**************************************************************************
 *                              Timer0                                    *
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
void Timer0_Init(const Timer0_ConfigType* config_PTR)
{

	/*
	 * Configure initial value for Timer0 to start count from it
	 * Anding with 0XFF to make sure the value won't exceed
	 * 255 as it is 8-bit Timer
	 */

	TIMER0_CONTROL_REGIRSTER = ( (config_PTR->timer0_InitialValue) ) & 0XFF;

	/*
	 * Configure Clock Pre-scaler value for Timer0 in TCCR0 Register
	 * Anding with 0XF8 to make sure the first 3-bits in TCCR0 register=0
	 * ORing with the selected timer clock to include it in the first 3-bits
	 * and keep the other bits as they are
	 */

	TIMER0_CONTROL_REGIRSTER = (TIMER0_CONTROL_REGIRSTER  & TIMER0_CLOCK_MASK_CLEAR) |
			(config_PTR->timer0_clock);


	switch ( (config_PTR->timer0_mode) )
	{

	case Overflow:

		/*
		 * Configure wave form generation mode to work with normal mode
		 * Clear WGM00 bit in TCCR0 register
		 * Clear WGM01 bit in TCCR0 register
		 */
		TIMER0_CONTROL_REGIRSTER  = CLEAR_BIT(TIMER0_CONTROL_REGIRSTER , TIMER0_WAVE_FORM_GENERATION_BIT0);
		TIMER0_CONTROL_REGIRSTER  = CLEAR_BIT(TIMER0_CONTROL_REGIRSTER , TIMER0_WAVE_FORM_GENERATION_BIT1);

		/*
		 * Configure compare output mode to work with normal port operation
		 * Decide the mode of OC0 from compare output modes with non PWM
		 * Configure COM00 bit in TCCR0 register
		 * Configure COM01 bit in TCCR0 register
		 */
		TIMER0_CONTROL_REGIRSTER = (TIMER0_CONTROL_REGIRSTER & TIMER0_COM0_MASK_CLEAR ) |
				((config_PTR->Compare_Mode_NonPWM)<<COM0_SHIFT_VALUE);

		/*
		 * Configure FOC0 bit in the TCCR0 register to be active
		 * As Timer0 is non-PWM
		 * Make FOC0 to be Active as it is overflow mode
		 */
		TIMER0_CONTROL_REGIRSTER = SET_BIT(TIMER0_CONTROL_REGIRSTER,TIMER0_FORCE_OUTPUT_COMPARE_BIT);

		/*
		 * Enable Timer0 overflow interrupt
		 * wait for: -Enable I-bit "mask bit" in the SREG register
		 *           -TOV0 bit in the TIFR register to be set
		 * Timer0 overflow mode is ready to work after that
		 */
		TIMER0_INTERRUPT_MASK_REGISTER = SET_BIT(TIMER0_INTERRUPT_MASK_REGISTER, TIMER0_OUTPUT_OVERFLOW_INTERRUPT);
		break;


	case PWM_PhaseCorrect:

		/*
		 * Configure OC0 as Output PIN
		 * the pin where the PWM signal is generated from MC
		 */

		OC0_DIRECTION_PORT = SET_BIT(OC0_DIRECTION_PORT, OC0_PIN);

		/*
		 *Clear force output compare bit in Timer/Counter control register
		 *to work with pulse width modulation
		 */
		TIMER0_CONTROL_REGIRSTER = CLEAR_BIT(TIMER0_CONTROL_REGIRSTER, TIMER0_FORCE_OUTPUT_COMPARE_BIT);

		/*
		 * Configure wave form generation mode to work with normal mode
		 * SET WGM00 bit in TCCR0 register
		 * Clear WGM01 bit in TCCR0 register
		 */
		TIMER0_CONTROL_REGIRSTER = SET_BIT(TIMER0_CONTROL_REGIRSTER, TIMER0_WAVE_FORM_GENERATION_BIT0);
		TIMER0_CONTROL_REGIRSTER = CLEAR_BIT(TIMER0_CONTROL_REGIRSTER, TIMER0_WAVE_FORM_GENERATION_BIT1);

		/*
		 * Configure compare output mode to work with normal port operation
		 * Decide the mode of OC0 from compare output modes with PWM_PhaseCorrect
		 * Configure COM00 bit in TCCR0 register
		 * Configure COM01 bit in TCCR0 register
		 */
		TIMER0_CONTROL_REGIRSTER = (TIMER0_CONTROL_REGIRSTER & TIMER0_COM0_MASK_CLEAR ) |
				((config_PTR->Compare_Mode_PWM_PhaseCorrect)<<COM0_SHIFT_VALUE);

		/*
		 * Configure Compare match value for Timer0 to start count till reach it
		 * Anding with 0XFF to make sure the value won't exceed
		 * 255 as it is 8-bit Timer
		 */
		TIMER0_OUTPUT_COMPARE_REGISTER = ((config_PTR->timer0_compare_MatchValue)) & 0XFF;

		break; /*End of PWM_PhaseCorrect*/


	case CTC:

		/*
		 * Configure wave form generation mode to work with CTC mode
		 * Clear WGM00 bit in TCCR0 register
		 * Clear WGM01 bit in TCCR0 register
		 */
		TIMER0_CONTROL_REGIRSTER = CLEAR_BIT(TIMER0_CONTROL_REGIRSTER, TIMER0_WAVE_FORM_GENERATION_BIT0);
		TIMER0_CONTROL_REGIRSTER = SET_BIT(TIMER0_CONTROL_REGIRSTER, TIMER0_WAVE_FORM_GENERATION_BIT1);

		/*
		 * Configure compare output mode to work with normal port operation
		 * Decide the mode of OC0 from compare output modes with non PWM
		 * Configure COM00 bit in TCCR0 register
		 * Configure COM01 bit in TCCR0 register
		 */
		TIMER0_CONTROL_REGIRSTER = (TIMER0_CONTROL_REGIRSTER & TIMER0_COM0_MASK_CLEAR ) |
				((config_PTR->Compare_Mode_NonPWM)<<COM0_SHIFT_VALUE);

		/*
		 * Configure FOC0 bit in the TCCR0 register to be active
		 * As Timer0 is non-PWM
		 * Make FOC0 to be Active as it is compare mode
		 */
		TIMER0_CONTROL_REGIRSTER = SET_BIT(TIMER0_CONTROL_REGIRSTER, TIMER0_FORCE_OUTPUT_COMPARE_BIT);

		/*
		 * Configure Compare match value for Timer0 to start count from it
		 * Anding with 0XFF to make sure the value won't exceed
		 * 255 as it is 8-bit Timer
		 */
		TIMER0_OUTPUT_COMPARE_REGISTER = ((config_PTR->timer0_compare_MatchValue)) & 0XFF;

		/*
		 * Enable Timer0 compare match interrupt
		 * wait for: -Enable I-bit "mask bit" in the SREG register
		 *           -OCF0 bit in the TIFR register to be set
		 * Timer0 compare match mode is ready to work after that
		 */
		TIMER0_INTERRUPT_MASK_REGISTER = SET_BIT(TIMER0_INTERRUPT_MASK_REGISTER, TIMER0_OUTPUT_COMPARE_MATCH_INTERRUPT);

		break; /*End of compare mode*/

	case FAST_PWM:
		/*
		 * Configure OC0 as Output PIN
		 * the pin where the PWM signal is generated from MC
		 */

		OC0_DIRECTION_PORT = SET_BIT(OC0_DIRECTION_PORT, OC0_PIN);

		/*
		 *Clear force output compare bit in Timer/Counter control register
		 *to work with pulse width modulation
		 */
		TIMER0_CONTROL_REGIRSTER = CLEAR_BIT(TIMER0_CONTROL_REGIRSTER, TIMER0_FORCE_OUTPUT_COMPARE_BIT);

		/*
		 * Configure wave form generation mode to work with FAST PWM mode
		 * SET WGM00 bit in TCCR0 register
		 * SET WGM01 bit in TCCR0 register
		 */
		TIMER0_CONTROL_REGIRSTER = SET_BIT(TIMER0_CONTROL_REGIRSTER, TIMER0_WAVE_FORM_GENERATION_BIT0);
		TIMER0_CONTROL_REGIRSTER = SET_BIT(TIMER0_CONTROL_REGIRSTER, TIMER0_WAVE_FORM_GENERATION_BIT1);

		/*
		 * Configure compare output mode to work with normal port operation
		 * Decide the mode of OC0 from compare output modes with Fast PWM
		 * Configure COM00 bit in TCCR0 register
		 * Configure COM01 bit in TCCR0 register
		 */
		TIMER0_CONTROL_REGIRSTER = (TIMER0_CONTROL_REGIRSTER & TIMER0_COM0_MASK_CLEAR ) |
				((config_PTR->Compare_Mode_FASTPWM)<<COM0_SHIFT_VALUE);

		/*
		 * Configure Compare match value for Timer0 to start count till reach it
		 * Anding with 0XFF to make sure the value won't exceed
		 * 255 as it is 8-bit Timer
		 */
		TIMER0_OUTPUT_COMPARE_REGISTER = ((config_PTR->timer0_compare_MatchValue)) & 0XFF;

		break;/*End of Fast PWM*/
	}/*End of switch case for timer0_mode*/

}/*End of Timer0_Init*/

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
void Timer0_setCallBack( void(*a_ptr)(void) )
{
	g_Timer0_callBackPtr = a_ptr;
}
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
void Timer0_DeInit(void)
{

	/*Clear all register in Timer0*/
	TIMER0_CONTROL_REGIRSTER        &= 0X00;
	TIMER0_INITIAL_VALUE_REGISTER   &= 0X00;
	TIMER0_OUTPUT_COMPARE_REGISTER  &= 0X00;
	TIMER0_INTERRUPT_MASK_REGISTER  &= 0X00;

}/*End of Timer0_DEInit*/
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
void Timer0_Stop(void)
{
	/*
	 * Clear the first 3-bits in TCCR0 register
	 * stop the clock of the timer
	 * timer0 will stop incrementing
	 */
	TIMER0_CONTROL_REGIRSTER = (TIMER0_CONTROL_REGIRSTER  & TIMER0_CLOCK_MASK_CLEAR);
}
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
void Timer0_Start(Timer_Clock timer0_clock_value)
{
	/*
	 * Clear the first 3-bits in TCCR0 register
	 * stop the clock of the timer
	 * timer0 will stop incrementing
	 */
	TIMER0_CONTROL_REGIRSTER = (TIMER0_CONTROL_REGIRSTER  & TIMER0_CLOCK_MASK_CLEAR) | timer0_clock_value ;
}
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
void Timer0_Change_CompareMatchValue(uint8 timer0_newCompareValue)
{
	/*
	 * Clear Output Compare Match register for Timer0
	 * then put the new compare value in it, Anding with 0XFF to make
	 * sure the value won't exceed 255 as it is 8-bit Timer
	 */
	TIMER0_OUTPUT_COMPARE_REGISTER = (TIMER0_OUTPUT_COMPARE_REGISTER & 0X00) |
			(timer0_newCompareValue & 0XFF);
}

/**************************************************************************
 *                              Timer1                                    *
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
 * [In]            Timer1_config_Ptr: Pointer to Timer Configuration Structure
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void Timer1_Init(const Timer1_ConfigType* Timer1_config_PTR)
{

	/*
	 * Configure initial value for Timer1 to start count from it
	 * Anding with 0XFFFF to make sure the value won't exceed
	 *  0XFFFF as it is 16-bit Timer
	 */
	TIMER1_INITIAL_VALUE_REGISTER = ( (Timer1_config_PTR->timer1_InitialValue) ) & 0XFFFF;

	/*
	 * Configure Clock Pre-scaler value for Timer0 in TCCR1B Register
	 * Anding with 0XF8 to make sure the first 3-bits in TCCR1B register=0
	 * ORing with the selected timer clock to include it in the first 3-bits
	 * and keep the other bits as they are
	 */
	TIMER1_CONTROL_REGIRSTER_B =  (TIMER1_CONTROL_REGIRSTER_B & TIMER1_CLOCK_MASK_CLEAR) |
			(Timer1_config_PTR->timer1_clock);

	switch ( (Timer1_config_PTR->timer1_mode) )
	{
	/**************************************************************************
	 *                            Timer1_Normal_Mode
	 * ************************************************************************/
	case Normal:
		/*
		 * Configure wave form generation mode to work with normal mode
		 * Clear WGM10/WMG11 bit in TCCR1A register
		 */
		TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT10);
		TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT11);

		/*
		 * Configure wave form generation mode to work with normal mode
		 * Clear WGM12/WMG13 bit in TCCR1B register
		 */
		TIMER1_CONTROL_REGIRSTER_B =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT12);
		TIMER1_CONTROL_REGIRSTER_B =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT13);

		switch( (Timer1_config_PTR->channel) )
		{

		case ChannelA:
			/*
			 * Configure compare output mode to work with Timer1
			 * with one mode from 4 modes in TCCR1A
			 * Configure COM1A0/COM1A1 bits in TCCR1A register
			 */
			TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1A_MASK_CLEAR) |
			((Timer1_config_PTR->Compare_Mode_NonPWM)<<COM1A_SHIFT_VALUE);

			/*
			 * Configure FOC1A bit in the TCCR1 register to be active
			 * As Timer1 is non-PWM
			 * Make FOC1A to be Active as it is overflow mode
			 */
			TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_FORCE_OUTPUT_COMPARE_BIT_A);

			break; /*End of Channel A*/

		case ChannelB:

			/*
			 * Configure compare output mode to work with Timer1
			 * with one mode from 4 modes in TCCR1A
			 * Configure COM1B0/COM1B1 bits in TCCR1A register
			 */
			TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1B_MASK_CLEAR) |
			((Timer1_config_PTR->Compare_Mode_NonPWM)<<COM1B_SHIFT_VALUE);

			/*
			 * Configure FOC1B bit in the TCCR1 register to be active
			 * As Timer1 is non-PWM
			 * Make FOC1B to be Active as it is overflow mode
			 */
			TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_FORCE_OUTPUT_COMPARE_BIT_B);
			break;/*End of channel B*/
		}/*End of Channel Type*/

		/*
		 * Enable Timer1 overflow interrupt
		 * wait for: -Enable I-bit "mask bit" in the SREG register
		 *           -TOV1 bit in the TIFR register to be set
		 * Timer1 overflow mode is ready to work after that
		 */
		TIMER1_INTERRUPT_MASK_REGISTER = SET_BIT(TIMER1_INTERRUPT_MASK_REGISTER,TIMER1_OUTPUT_OVERFLOW_INTERRUPT);
		break; /*end of normal mode*/
		/**************************************************************************
		 *                     Timer1_PWM_PhaseCorrect_8bit_Mode
		 * ************************************************************************/
		case PWM_PhaseCorrect_8bit:
			/*
			 * Configure wave form generation mode to work with PWM_PhaseCorrect_8bit mode
			 * Set WGM10 bit in TCCR1A register
			 * Clear WGM11 bit in TCCR1A register
			 */
			TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT10);
			TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT11);

			/*
			 * Configure wave form generation mode to work with PWM_PhaseCorrect_8bit mode
			 * Clear WGM12/WMG13 bit in TCCR1B register
			 */
			TIMER1_CONTROL_REGIRSTER_B =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT12);
			TIMER1_CONTROL_REGIRSTER_B =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT13);

			switch(Timer1_config_PTR->channel)
			{

			case ChannelA:
				/*
				 * Configure OC1A as Output PIN
				 * the pin where the PWM signal is generated from MC
				 */
				OC1A_DIRECTION_PORT = SET_BIT(OC1A_DIRECTION_PORT, OC1A_PIN);

				/*
				 * Configure FOC1A bit in the TCCR1 register to be low
				 * As Timer1 is PWM mode
				 * Make FOC1A to be low as it is PWM_PhaseCorrect_8bit mode
				 */
				TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_A);
				/*
				 * Configure compare output mode to work with Timer1
				 * with one mode from 4 modes in TCCR1A
				 * Configure COM1A0/COM1A1 bits in TCCR1A register
				 */
				TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1A_MASK_CLEAR) |
						((Timer1_config_PTR->Compare_Mode_PWM_PhaseCorrect)<<COM1A_SHIFT_VALUE);
				/*
				 * Configure Compare match value for Timer1 to start count from it
				 * Anding with 0XFFFF to make sure the value won't exceed
				 * OXFFFF as it is 16-bit Timer
				 */
				TIMER1_OUTPUT_COMPARE_REGISTER_A = ((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF;

				break; /*End of channel A*/

			case ChannelB:
				/*
				 * Configure OC1A as Output PIN
				 * the pin where the PWM signal is generated from MC
				 */
				OC1B_DIRECTION_PORT = SET_BIT(OC1B_DIRECTION_PORT, OC1B_PIN);

				/*
				 * Configure FOC1B bit in the TCCR1 register to be low
				 * As Timer1 is PWM
				 * Make FOC1B to be low as it is PWM_PhaseCorrect_8bit mode
				 */
				TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_B);

				/*
				 * Configure compare output mode to work with Timer1
				 * with one mode from 4 modes in TCCR1A
				 * Configure COM1B0/COM1B1 bits in TCCR1A register
				 */
				TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1B_MASK_CLEAR) |
						((Timer1_config_PTR->Compare_Mode_PWM_PhaseCorrect)<<COM1B_SHIFT_VALUE);

				/*
				 * Configure Compare match value for Timer1 to start count from it
				 * Anding with 0XFFFF to make sure the value won't exceed
				 * OXFFFF as it is 16-bit Timer
				 * to make it count right put OCR1A  greater than the value in OCR1B by 1
				 */
				TIMER1_OUTPUT_COMPARE_REGISTER_A = (((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF) + 1;
				TIMER1_OUTPUT_COMPARE_REGISTER_B = ((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF;

				break;/*End of channel B*/
			}/*End of Channel Type switch case*/
			break;/*End of PWM_PhaseCorrect_8bit mode*/
			/**************************************************************************
			 *                     Timer1_PWM_PhaseCorrect_9bit_Mode
			 * ************************************************************************/
			case PWM_PhaseCorrect_9bit:
				/*
				 * Configure wave form generation mode to work with PWM_PhaseCorrect_9bit mode
				 * Clear WGM10 bit in TCCR1A register
				 * Set WGM11 bit in TCCR1A register
				 */
				TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT10);
				TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT11);

				/*
				 * Configure wave form generation mode to work with PWM_PhaseCorrect_9bit mode
				 * Clear WGM12/WMG13 bit in TCCR1B register
				 */
				TIMER1_CONTROL_REGIRSTER_B =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT12);
				TIMER1_CONTROL_REGIRSTER_B =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT13);

				switch(Timer1_config_PTR->channel)
				{

				case ChannelA:
					/*
					 * Configure OC1A as Output PIN
					 * the pin where the PWM signal is generated from MC
					 */
					OC1A_DIRECTION_PORT = SET_BIT(OC1A_DIRECTION_PORT, OC1A_PIN);

					/*
					 * Configure FOC1A bit in the TCCR1 register to be low
					 * As Timer1 is PWM mode
					 * Make FOC1A to be low as it is PWM_PhaseCorrect_9bit mode
					 */
					TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_A);
					/*
					 * Configure compare output mode to work with Timer1
					 * with one mode from 4 modes in TCCR1A
					 * Configure COM1A0/COM1A1 bits in TCCR1A register
					 */
					TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1A_MASK_CLEAR) |
							((Timer1_config_PTR->Compare_Mode_PWM_PhaseCorrect)<<COM1A_SHIFT_VALUE);
					/*
					 * Configure Compare match value for Timer1 to start count from it
					 * Anding with 0XFFFF to make sure the value won't exceed
					 * OXFFFF as it is 16-bit Timer
					 */
					TIMER1_OUTPUT_COMPARE_REGISTER_A = ((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF;

					break; /*End of channel A*/

				case ChannelB:
					/*
					 * Configure OC1A as Output PIN
					 * the pin where the PWM signal is generated from MC
					 */
					OC1B_DIRECTION_PORT = SET_BIT(OC1B_DIRECTION_PORT, OC1B_PIN);

					/*
					 * Configure FOC1B bit in the TCCR1 register to be low
					 * As Timer1 is PWM
					 * Make FOC1B to be low as it is PWM_PhaseCorrect_9bit mode
					 */
					TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_B);

					/*
					 * Configure compare output mode to work with Timer1
					 * with one mode from 4 modes in TCCR1A
					 * Configure COM1B0/COM1B1 bits in TCCR1A register
					 */
					TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1B_MASK_CLEAR) |
							((Timer1_config_PTR->Compare_Mode_PWM_PhaseCorrect)<<COM1B_SHIFT_VALUE);

					/*
					 * Configure Compare match value for Timer1 to start count from it
					 * Anding with 0XFFFF to make sure the value won't exceed
					 * OXFFFF as it is 16-bit Timer
					 * to make it count right put OCR1A  greater than the value in OCR1B by 1
					 */
					TIMER1_OUTPUT_COMPARE_REGISTER_A = (((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF) + 1;
					TIMER1_OUTPUT_COMPARE_REGISTER_B = ((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF;

					break;/*End of channel B*/
				}/*End of Channel Type switch case*/
				break;/*End of PWM_PhaseCorrect_9bit mode*/
				/**************************************************************************
				 *                     Timer1_PWM_PhaseCorrect_10bit_Mode
				 * ************************************************************************/
				case PWM_PhaseCorrect_10bit:
					/*
					 * Configure wave form generation mode to work with PWM_PhaseCorrect_10bit mode
					 * Set WGM10 bit in TCCR1A register
					 * Set WGM11 bit in TCCR1A register
					 */
					TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT10);
					TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT11);

					/*
					 * Configure wave form generation mode to work with PWM_PhaseCorrect_10bit mode
					 * Clear WGM12/WMG13 bit in TCCR1B register
					 */
					TIMER1_CONTROL_REGIRSTER_B =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT12);
					TIMER1_CONTROL_REGIRSTER_B =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT13);

					switch(Timer1_config_PTR->channel)
					{

					case ChannelA:
						/*
						 * Configure OC1A as Output PIN
						 * the pin where the PWM signal is generated from MC
						 */
						OC1A_DIRECTION_PORT = SET_BIT(OC1A_DIRECTION_PORT, OC1A_PIN);

						/*
						 * Configure FOC1A bit in the TCCR1 register to be low
						 * As Timer1 is PWM mode
						 * Make FOC1A to be low as it is PWM_PhaseCorrect_10bit mode
						 */
						TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_A);
						/*
						 * Configure compare output mode to work with Timer1
						 * with one mode from 4 modes in TCCR1A
						 * Configure COM1A0/COM1A1 bits in TCCR1A register
						 */
						TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1A_MASK_CLEAR) |
								((Timer1_config_PTR->Compare_Mode_PWM_PhaseCorrect)<<COM1A_SHIFT_VALUE);
						/*
						 * Configure Compare match value for Timer1 to start count from it
						 * Anding with 0XFFFF to make sure the value won't exceed
						 * OXFFFF as it is 16-bit Timer
						 */
						TIMER1_OUTPUT_COMPARE_REGISTER_A = ((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF;

						break; /*End of channel A*/

					case ChannelB:
						/*
						 * Configure OC1A as Output PIN
						 * the pin where the PWM signal is generated from MC
						 */
						OC1B_DIRECTION_PORT = SET_BIT(OC1B_DIRECTION_PORT, OC1B_PIN);

						/*
						 * Configure FOC1B bit in the TCCR1 register to be low
						 * As Timer1 is PWM
						 * Make FOC1B to be low as it is PWM_PhaseCorrect_10bit mode
						 */
						TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_B);

						/*
						 * Configure compare output mode to work with Timer1
						 * with one mode from 4 modes in TCCR1A
						 * Configure COM1B0/COM1B1 bits in TCCR1A register
						 */
						TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1B_MASK_CLEAR) |
								((Timer1_config_PTR->Compare_Mode_PWM_PhaseCorrect)<<COM1B_SHIFT_VALUE);

						/*
						 * Configure Compare match value for Timer1 to start count from it
						 * Anding with 0XFFFF to make sure the value won't exceed
						 * OXFFFF as it is 16-bit Timer
						 * to make it count right put OCR1A  greater than the value in OCR1B by 1
						 */
						TIMER1_OUTPUT_COMPARE_REGISTER_A = (((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF) + 1;
						TIMER1_OUTPUT_COMPARE_REGISTER_B = ((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF;

						break;/*End of channel B*/
					}/*End of Channel Type switch case*/
					break;/*End of PWM_PhaseCorrect_10bit*/
					/**************************************************************************
					 *                        Timer1_CTC_OCR1A_Mode
					 * ************************************************************************/
					case CTC_OCR1A:

						/*
						 * Configure wave form generation mode to work with compare mode
						 * Clear WGM10/WMG11 bit in TCCR1A register
						 */
						TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT10);
						TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT11);

						/*
						 * Configure wave form generation mode to work with normal mode
						 * Clear WMG13 bit in TCCR1B register
						 * Set WMG12 bit in TCCR1B register
						 */
						TIMER1_CONTROL_REGIRSTER_B =  SET_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT12);
						TIMER1_CONTROL_REGIRSTER_B =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT13);

						switch(Timer1_config_PTR->channel)
						{

						case ChannelA:

							/*
							 * Configure FOC1A bit in the TCCR1 register to be active
							 * As Timer1 is non-PWM
							 * Make FOC1A to be Active as it is compare mode
							 */
							TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_A);
							/*
							 * Configure compare output mode to work with Timer1
							 * with one mode from 4 modes in TCCR1A
							 * Configure COM1A0/COM1A1 bits in TCCR1A register
							 */
							TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1A_MASK_CLEAR) |
									((Timer1_config_PTR->Compare_Mode_NonPWM)<<COM1A_SHIFT_VALUE);
							/*
							 * Configure Compare match value for Timer1 to start count from it
							 * Anding with 0XFFFF to make sure the value won't exceed
							 * OXFFFF as it is 16-bit Timer
							 */
							TIMER1_OUTPUT_COMPARE_REGISTER_A = ((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF;
							/*
							 * Enable Timer1 compare match interrupt
							 * wait for: -Enable I-bit "mask bit" in the SREG register
							 *           -OCF1 bit in the TIFR register to be set
							 * Timer1 compare match mode is ready to work after that
							 */
							TIMER1_INTERRUPT_MASK_REGISTER = SET_BIT(TIMER1_INTERRUPT_MASK_REGISTER,TIMER1_OUTPUT_COMPARE_MATCH_INTERRUPT_A);

							break; /*End of channel A*/

						case ChannelB:

							/*
							 * Configure FOC1B bit in the TCCR1 register to be active
							 * As Timer1 is non-PWM
							 * Make FOC1B to be Active as it is compare mode
							 */
							TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_B);

							/*
							 * Configure compare output mode to work with Timer1
							 * with one mode from 4 modes in TCCR1A
							 * Configure COM1B0/COM1B1 bits in TCCR1A register
							 */
							TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1B_MASK_CLEAR) |
									((Timer1_config_PTR->Compare_Mode_NonPWM)<<COM1B_SHIFT_VALUE);

							/*
							 * Configure Compare match value for Timer1 to start count from it
							 * Anding with 0XFFFF to make sure the value won't exceed
							 * OXFFFF as it is 16-bit Timer
							 * to make it count right put OCR1A  greater than the value in OCR1B by 1
							 */
							TIMER1_OUTPUT_COMPARE_REGISTER_A = (((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF) + 1;
							TIMER1_OUTPUT_COMPARE_REGISTER_B = ((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF;

							/*
							 * Enable Timer1 compare match interrupt
							 * wait for: -Enable I-bit "mask bit" in the SREG register
							 *           -OCF1 bit in the TIFR register to be set
							 * Timer1 compare match mode is ready to work after that
							 */
							TIMER1_INTERRUPT_MASK_REGISTER = SET_BIT(TIMER1_INTERRUPT_MASK_REGISTER,TIMER1_OUTPUT_COMPARE_MATCH_INTERRUPT_B);

							break;/*End of channel B*/
						}/*End of Channel Type switch case*/
						break;/*End of CTC_OCR1A mode*/
						/**************************************************************************
						 *                        Timer1_FAST_PWM_8bit_Mode
						 * ************************************************************************/
						case FAST_PWM_8bit:

							/*
							 * Configure wave form generation mode to work with FAST_PWM_8bit mode
							 * Set WGM10 bit in TCCR1A register
							 * Clear WGM11 bit in TCCR1A register
							 */
							TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT10);
							TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT11);

							/*
							 * Configure wave form generation mode to work with FAST_PWM_8bit mode
							 * Set WGM12 bit in TCCR1B register
							 * Clear WMG13 bit in TCCR1B register
							 */
							TIMER1_CONTROL_REGIRSTER_B =  SET_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT12);
							TIMER1_CONTROL_REGIRSTER_B =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT13);

							switch(Timer1_config_PTR->channel)
							{

							case ChannelA:
								/*
								 * Configure OC1A as Output PIN
								 * the pin where the PWM signal is generated from MC
								 */
								OC1A_DIRECTION_PORT = SET_BIT(OC1A_DIRECTION_PORT, OC1A_PIN);

								/*
								 * Configure FOC1A bit in the TCCR1 register to be low
								 * As Timer1 is PWM mode
								 * Make FOC1A to be low as it is FAST_PWM_8bit mode
								 */
								TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_A);
								/*
								 * Configure compare output mode to work with Timer1
								 * with one mode from 4 modes in TCCR1A
								 * Configure COM1A0/COM1A1 bits in TCCR1A register
								 */
								TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1A_MASK_CLEAR) |
										((Timer1_config_PTR->Compare_Mode_FASTPWM)<<COM1A_SHIFT_VALUE);
								/*
								 * Configure Compare match value for Timer1 to start count from it
								 * Anding with 0XFFFF to make sure the value won't exceed
								 * OXFFFF as it is 16-bit Timer
								 */
								TIMER1_OUTPUT_COMPARE_REGISTER_A = ((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF;

								break; /*End of channel A*/

							case ChannelB:
								/*
								 * Configure OC1A as Output PIN
								 * the pin where the PWM signal is generated from MC
								 */
								OC1B_DIRECTION_PORT = SET_BIT(OC1B_DIRECTION_PORT, OC1B_PIN);

								/*
								 * Configure FOC1B bit in the TCCR1 register to be low
								 * As Timer1 is PWM
								 * Make FOC1B to be low as it is FAST_PWM_8bit mode
								 */
								TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_B);

								/*
								 * Configure compare output mode to work with Timer1
								 * with one mode from 4 modes in TCCR1A
								 * Configure COM1B0/COM1B1 bits in TCCR1A register
								 */
								TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1B_MASK_CLEAR) |
										((Timer1_config_PTR->Compare_Mode_FASTPWM)<<COM1B_SHIFT_VALUE);

								/*
								 * Configure Compare match value for Timer1 to start count from it
								 * Anding with 0XFFFF to make sure the value won't exceed
								 * OXFFFF as it is 16-bit Timer
								 * to make it count right put OCR1A  greater than the value in OCR1B by 1
								 */
								TIMER1_OUTPUT_COMPARE_REGISTER_A = (((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF) + 1;
								TIMER1_OUTPUT_COMPARE_REGISTER_B = ((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF;

								break;/*End of channel B*/
							}/*End of Channel Type switch case*/

							break;/*End of FAST_PWM_8BIT*/
							/**************************************************************************
							 *                        Timer1_FAST_PWM_9bit_Mode
							 * ************************************************************************/
							case FAST_PWM_9bit:

								/*
								 * Configure wave form generation mode to work with FAST_PWM_9bit mode
								 * Clear WGM10 bit in TCCR1A register
								 * Set WGM11 bit in TCCR1A register
								 */
								TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT10);
								TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT11);

								/*
								 * Configure wave form generation mode to work with FAST_PWM_9bit mode
								 * Set WGM12 bit in TCCR1B register
								 * Clear WMG13 bit in TCCR1B register
								 */
								TIMER1_CONTROL_REGIRSTER_B =  SET_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT12);
								TIMER1_CONTROL_REGIRSTER_B =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT13);

								switch(Timer1_config_PTR->channel)
								{

								case ChannelA:
									/*
									 * Configure OC1A as Output PIN
									 * the pin where the PWM signal is generated from MC
									 */
									OC1A_DIRECTION_PORT = SET_BIT(OC1A_DIRECTION_PORT, OC1A_PIN);

									/*
									 * Configure FOC1A bit in the TCCR1 register to be low
									 * As Timer1 is PWM mode
									 * Make FOC1A to be low as it is FAST_PWM_9bit mode
									 */
									TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_A);
									/*
									 * Configure compare output mode to work with Timer1
									 * with one mode from 4 modes in TCCR1A
									 * Configure COM1A0/COM1A1 bits in TCCR1A register
									 */
									TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1A_MASK_CLEAR) |
											((Timer1_config_PTR->Compare_Mode_FASTPWM)<<COM1A_SHIFT_VALUE);
									/*
									 * Configure Compare match value for Timer1 to start count from it
									 * Anding with 0XFFFF to make sure the value won't exceed
									 * OXFFFF as it is 16-bit Timer
									 */
									TIMER1_OUTPUT_COMPARE_REGISTER_A = ((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF;

									break; /*End of channel A*/

								case ChannelB:
									/*
									 * Configure OC1A as Output PIN
									 * the pin where the PWM signal is generated from MC
									 */
									OC1B_DIRECTION_PORT = SET_BIT(OC1B_DIRECTION_PORT, OC1B_PIN);

									/*
									 * Configure FOC1B bit in the TCCR1 register to be low
									 * As Timer1 is PWM
									 * Make FOC1B to be low as it is FAST_PWM_9bit mode
									 */
									TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_B);

									/*
									 * Configure compare output mode to work with Timer1
									 * with one mode from 4 modes in TCCR1A
									 * Configure COM1B0/COM1B1 bits in TCCR1A register
									 */
									TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1B_MASK_CLEAR) |
											((Timer1_config_PTR->Compare_Mode_FASTPWM)<<COM1B_SHIFT_VALUE);

									/*
									 * Configure Compare match value for Timer1 to start count from it
									 * Anding with 0XFFFF to make sure the value won't exceed
									 * OXFFFF as it is 16-bit Timer
									 * to make it count right put OCR1A  greater than the value in OCR1B by 1
									 */
									TIMER1_OUTPUT_COMPARE_REGISTER_A = (((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF) + 1;
									TIMER1_OUTPUT_COMPARE_REGISTER_B = ((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF;

									break;/*End of channel B*/
								}/*End of Channel Type switch case*/
								break;/*End of FAST_PWM_9BIT*/
								/**************************************************************************
								 *                        Timer1_FAST_PWM_10bit_Mode
								 * ************************************************************************/
								case FAST_PWM_10bit:

									/*
									 * Configure wave form generation mode to work with FAST_PWM_10bit mode
									 * Set WGM10 bit in TCCR1A register
									 * Set WGM11 bit in TCCR1A register
									 */
									TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT10);
									TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT11);

									/*
									 * Configure wave form generation mode to work with FAST_PWM_10bit mode
									 * Set WGM12 bit in TCCR1B register
									 * Clear WMG13 bit in TCCR1B register
									 */
									TIMER1_CONTROL_REGIRSTER_B =  SET_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT12);
									TIMER1_CONTROL_REGIRSTER_B =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT13);

									switch(Timer1_config_PTR->channel)
									{

									case ChannelA:
										/*
										 * Configure OC1A as Output PIN
										 * the pin where the PWM signal is generated from MC
										 */
										OC1A_DIRECTION_PORT = SET_BIT(OC1A_DIRECTION_PORT, OC1A_PIN);

										/*
										 * Configure FOC1A bit in the TCCR1 register to be low
										 * As Timer1 is PWM mode
										 * Make FOC1A to be low as it is FAST_PWM_10bit mode
										 */
										TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_A);
										/*
										 * Configure compare output mode to work with Timer1
										 * with one mode from 4 modes in TCCR1A
										 * Configure COM1A0/COM1A1 bits in TCCR1A register
										 */
										TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1A_MASK_CLEAR) |
												((Timer1_config_PTR->Compare_Mode_FASTPWM)<<COM1A_SHIFT_VALUE);
										/*
										 * Configure Compare match value for Timer1 to start count from it
										 * Anding with 0XFFFF to make sure the value won't exceed
										 * OXFFFF as it is 16-bit Timer
										 */
										TIMER1_OUTPUT_COMPARE_REGISTER_A = ((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF;

										break; /*End of channel A*/

									case ChannelB:
										/*
										 * Configure OC1A as Output PIN
										 * the pin where the PWM signal is generated from MC
										 */
										OC1B_DIRECTION_PORT = SET_BIT(OC1B_DIRECTION_PORT, OC1B_PIN);

										/*
										 * Configure FOC1B bit in the TCCR1 register to be low
										 * As Timer1 is PWM
										 * Make FOC1B to be low as it is FAST_PWM_10bit mode
										 */
										TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_B);

										/*
										 * Configure compare output mode to work with Timer1
										 * with one mode from 4 modes in TCCR1A
										 * Configure COM1B0/COM1B1 bits in TCCR1A register
										 */
										TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1B_MASK_CLEAR) |
												((Timer1_config_PTR->Compare_Mode_FASTPWM)<<COM1B_SHIFT_VALUE);

										/*
										 * Configure Compare match value for Timer1 to start count from it
										 * Anding with 0XFFFF to make sure the value won't exceed
										 * OXFFFF as it is 16-bit Timer
										 * to make it count right put OCR1A  greater than the value in OCR1B by 1
										 */
										TIMER1_OUTPUT_COMPARE_REGISTER_A = (((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF) + 1;
										TIMER1_OUTPUT_COMPARE_REGISTER_B = ((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF;

										break;/*End of channel B*/
									}/*End of Channel Type switch case*/
									break;/*End of FAST_PMW_10BIT mode*/
									/**************************************************************************
									 *                      Timer1_PWM_Phase_FrequencyCorrect_ICR1_Mode
									 * ************************************************************************/
									case PWM_Phase_FrequencyCorrect_ICR1:
										/*
										 * Configure wave form generation mode to work with PWM_Phase_FrequencyCorrect_ICR1 mode
										 * Clear WGM10 bit in TCCR1A register
										 * Clear WGM11 bit in TCCR1A register
										 */
										TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT10);
										TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT11);

										/*
										 * Configure wave form generation mode to work with PWM_Phase_FrequencyCorrect_ICR1 mode
										 * Clear WGM12 bit in TCCR1B register
										 * Set WMG13 bit in TCCR1B register
										 */
										TIMER1_CONTROL_REGIRSTER_B =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT12);
										TIMER1_CONTROL_REGIRSTER_B =  SET_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT13);

										/*
										 * Configure Input capture value for Timer1 to be the top from it
										 * Anding with 0XFFFF to make sure the value won't exceed
										 * OXFFFF as it is 16-bit Timer
										 */
										TIMER1_INPUT_CAPTURE_REGISTER  = ( (Timer1_config_PTR->timer1_InputCaptureValue) & 0XFFFF) ;

										switch(Timer1_config_PTR->channel)
										{

										case ChannelA:
											/*
											 * Configure OC1A as Output PIN
											 * the pin where the PWM signal is generated from MC
											 */
											OC1A_DIRECTION_PORT = SET_BIT(OC1A_DIRECTION_PORT, OC1A_PIN);

											/*
											 * Configure FOC1A bit in the TCCR1 register to be low
											 * As Timer1 is PWM mode
											 * Make FOC1A to be low as it is FAST_PWM_10bit mode
											 */
											TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_A);
											/*
											 * Configure compare output mode to work with Timer1
											 * with one mode from 4 modes in TCCR1A
											 * Configure COM1A0/COM1A1 bits in TCCR1A register
											 */
											TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1A_MASK_CLEAR) |
													((Timer1_config_PTR->Compare_Mode_PWM_PhaseCorrect)<<COM1A_SHIFT_VALUE);
											/*
											 * Configure Compare match value for Timer1 to start count from it
											 * Anding with 0XFFFF to make sure the value won't exceed
											 * OXFFFF as it is 16-bit Timer
											 */
											TIMER1_OUTPUT_COMPARE_REGISTER_A = ((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF;

											break; /*End of channel A*/

										case ChannelB:
											/*
											 * Configure OC1A as Output PIN
											 * the pin where the PWM signal is generated from MC
											 */
											OC1B_DIRECTION_PORT = SET_BIT(OC1B_DIRECTION_PORT, OC1B_PIN);

											/*
											 * Configure FOC1B bit in the TCCR1 register to be low
											 * As Timer1 is PWM
											 * Make FOC1B to be low as it is FAST_PWM_10bit mode
											 */
											TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_B);

											/*
											 * Configure compare output mode to work with Timer1
											 * with one mode from 4 modes in TCCR1A
											 * Configure COM1B0/COM1B1 bits in TCCR1A register
											 */
											TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1B_MASK_CLEAR) |
													((Timer1_config_PTR->Compare_Mode_PWM_PhaseCorrect)<<COM1B_SHIFT_VALUE);

											/*
											 * Configure Compare match value for Timer1 to start count from it
											 * Anding with 0XFFFF to make sure the value won't exceed
											 * OXFFFF as it is 16-bit Timer
											 * to make it count right put OCR1A  greater than the value in OCR1B by 1
											 */
											TIMER1_OUTPUT_COMPARE_REGISTER_A = (((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF) + 1;
											TIMER1_OUTPUT_COMPARE_REGISTER_B = ((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF;

											break;/*End of channel B*/
										}/*End of Channel Type switch case*/
										break;/*End of PWM_Phase_FrequencyCorrect_ICR1 mode*/
										/**************************************************************************
										 *                Timer1_PWM_Phase_FrequencyCorrect_OCR1A_Mode
										 * ************************************************************************/
										case PWM_Phase_FrequencyCorrect_OCR1A:
											/*
											 * Configure wave form generation mode to work with PWM_Phase_FrequencyCorrect_OCR1A mode
											 * Set WGM10 bit in TCCR1A register
											 * Clear WGM11 bit in TCCR1A register
											 */
											TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT10);
											TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT11);

											/*
											 * Configure wave form generation mode to work with PWM_Phase_FrequencyCorrect_OCR1A mode
											 * Clear WGM12 bit in TCCR1B register
											 * Set WMG13 bit in TCCR1B register
											 */
											TIMER1_CONTROL_REGIRSTER_B =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT12);
											TIMER1_CONTROL_REGIRSTER_B =  SET_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT13);

											switch(Timer1_config_PTR->channel)
											{

											case ChannelA:
												/*
												 * Configure OC1A as Output PIN
												 * the pin where the PWM signal is generated from MC
												 */
												OC1A_DIRECTION_PORT = SET_BIT(OC1A_DIRECTION_PORT, OC1A_PIN);

												/*
												 * Configure FOC1A bit in the TCCR1 register to be low
												 * As Timer1 is PWM mode
												 * Make FOC1A to be low as it is FAST_PWM_10bit mode
												 */
												TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_A);
												/*
												 * Configure compare output mode to work with Timer1
												 * with one mode from 4 modes in TCCR1A
												 * Configure COM1A0/COM1A1 bits in TCCR1A register
												 */
												TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1A_MASK_CLEAR) |
														((Timer1_config_PTR->Compare_Mode_PWM_PhaseCorrect)<<COM1A_SHIFT_VALUE);
												/*
												 * Configure Compare match value for Timer1 to start count from it
												 * Anding with 0XFFFF to make sure the value won't exceed
												 * OXFFFF as it is 16-bit Timer
												 */
												TIMER1_OUTPUT_COMPARE_REGISTER_A = ((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF;

												break; /*End of channel A*/

											case ChannelB:
												/*
												 * Configure OC1A as Output PIN
												 * the pin where the PWM signal is generated from MC
												 */
												OC1B_DIRECTION_PORT = SET_BIT(OC1B_DIRECTION_PORT, OC1B_PIN);

												/*
												 * Configure FOC1B bit in the TCCR1 register to be low
												 * As Timer1 is PWM
												 * Make FOC1B to be low as it is FAST_PWM_10bit mode
												 */
												TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_B);

												/*
												 * Configure compare output mode to work with Timer1
												 * with one mode from 4 modes in TCCR1A
												 * Configure COM1B0/COM1B1 bits in TCCR1A register
												 */
												TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1B_MASK_CLEAR) |
														((Timer1_config_PTR->Compare_Mode_PWM_PhaseCorrect)<<COM1B_SHIFT_VALUE);

												/*
												 * Configure Compare match value for Timer1 to start count from it
												 * Anding with 0XFFFF to make sure the value won't exceed
												 * OXFFFF as it is 16-bit Timer
												 * to make it count right put OCR1A  greater than the value in OCR1B by 1
												 */
												TIMER1_OUTPUT_COMPARE_REGISTER_A = (((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF) + 1;
												TIMER1_OUTPUT_COMPARE_REGISTER_B = ((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF;

												break;/*End of channel B*/
											}/*End of Channel Type switch case*/
											break;/*End of PWM_Phase_FrequencyCorrct_OCR1A mode*/
											/**************************************************************************
											 *                    Timer1_PWM_PhaseCorrect_ICR1_Mode
											 * ************************************************************************/
											case PWM_PhaseCorrect_ICR1:
												/*
												 * Configure wave form generation mode to work with PWM_PhaseCorrect_ICR1 mode
												 * Clear WGM10 bit in TCCR1A register
												 * Clear WGM11 bit in TCCR1A register
												 */
												TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT10);
												TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT11);

												/*
												 * Configure wave form generation mode to work with PWM_PhaseCorrect_ICR1 mode
												 * Clear WGM12 bit in TCCR1B register
												 * Set WMG13 bit in TCCR1B register
												 */
												TIMER1_CONTROL_REGIRSTER_B =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT12);
												TIMER1_CONTROL_REGIRSTER_B =  SET_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT13);

												/*
												 * Configure Input capture value for Timer1 to be the top from it
												 * Anding with 0XFFFF to make sure the value won't exceed
												 * OXFFFF as it is 16-bit Timer
												 */
												TIMER1_INPUT_CAPTURE_REGISTER  = ( (Timer1_config_PTR->timer1_InputCaptureValue) & 0XFFFF) ;

												switch(Timer1_config_PTR->channel)
												{

												case ChannelA:
													/*
													 * Configure OC1A as Output PIN
													 * the pin where the PWM signal is generated from MC
													 */
													OC1A_DIRECTION_PORT = SET_BIT(OC1A_DIRECTION_PORT, OC1A_PIN);

													/*
													 * Configure FOC1A bit in the TCCR1 register to be low
													 * As Timer1 is PWM mode
													 * Make FOC1A to be low as it is FAST_PWM_10bit mode
													 */
													TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_A);
													/*
													 * Configure compare output mode to work with Timer1
													 * with one mode from 4 modes in TCCR1A
													 * Configure COM1A0/COM1A1 bits in TCCR1A register
													 */
													TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1A_MASK_CLEAR) |
															((Timer1_config_PTR->Compare_Mode_PWM_PhaseCorrect)<<COM1A_SHIFT_VALUE);
													/*
													 * Configure Compare match value for Timer1 to start count from it
													 * Anding with 0XFFFF to make sure the value won't exceed
													 * OXFFFF as it is 16-bit Timer
													 */
													TIMER1_OUTPUT_COMPARE_REGISTER_A = ((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF;

													break; /*End of channel A*/

												case ChannelB:
													/*
													 * Configure OC1A as Output PIN
													 * the pin where the PWM signal is generated from MC
													 */
													OC1B_DIRECTION_PORT = SET_BIT(OC1B_DIRECTION_PORT, OC1B_PIN);

													/*
													 * Configure FOC1B bit in the TCCR1 register to be low
													 * As Timer1 is PWM
													 * Make FOC1B to be low as it is FAST_PWM_10bit mode
													 */
													TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_B);

													/*
													 * Configure compare output mode to work with Timer1
													 * with one mode from 4 modes in TCCR1A
													 * Configure COM1B0/COM1B1 bits in TCCR1A register
													 */
													TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1B_MASK_CLEAR) |
															((Timer1_config_PTR->Compare_Mode_PWM_PhaseCorrect)<<COM1B_SHIFT_VALUE);

													/*
													 * Configure Compare match value for Timer1 to start count from it
													 * Anding with 0XFFFF to make sure the value won't exceed
													 * OXFFFF as it is 16-bit Timer
													 * to make it count right put OCR1A  greater than the value in OCR1B by 1
													 */
													TIMER1_OUTPUT_COMPARE_REGISTER_A = (((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF) + 1;
													TIMER1_OUTPUT_COMPARE_REGISTER_B = ((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF;

													break;/*End of channel B*/
												}/*End of Channel Type switch case*/
												break;/*End of PWM_PhaseCorrect_ICR1s mode*/
												/**************************************************************************
												 *                    Timer1_PWM_PhaseCorrect_OCR1A_Mode
												 * ************************************************************************/
												case PWM_PhaseCorrect_OCR1A:
													/*
													 * Configure wave form generation mode to work with PWM_Phase_FrequencyCorrect_OCR1A mode
													 * Set WGM10 bit in TCCR1A register
													 * Set WGM11 bit in TCCR1A register
													 */
													TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT10);
													TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT11);

													/*
													 * Configure wave form generation mode to work with PWM_Phase_FrequencyCorrect_OCR1A mode
													 * Clear WGM12 bit in TCCR1B register
													 * Set WMG13 bit in TCCR1B register
													 */
													TIMER1_CONTROL_REGIRSTER_B =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT12);
													TIMER1_CONTROL_REGIRSTER_B =  SET_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT13);

													switch(Timer1_config_PTR->channel)
													{

													case ChannelA:
														/*
														 * Configure OC1A as Output PIN
														 * the pin where the PWM signal is generated from MC
														 */
														OC1A_DIRECTION_PORT = SET_BIT(OC1A_DIRECTION_PORT, OC1A_PIN);

														/*
														 * Configure FOC1A bit in the TCCR1 register to be low
														 * As Timer1 is PWM mode
														 * Make FOC1A to be low as it is PWM_PhaseCorrect_OCR1A mode
														 */
														TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_A);
														/*
														 * Configure compare output mode to work with Timer1
														 * with one mode from 4 modes in TCCR1A
														 * Configure COM1A0/COM1A1 bits in TCCR1A register
														 */
														TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1A_MASK_CLEAR) |
																((Timer1_config_PTR->Compare_Mode_PWM_PhaseCorrect)<<COM1A_SHIFT_VALUE);
														/*
														 * Configure Compare match value for Timer1 to start count from it
														 * Anding with 0XFFFF to make sure the value won't exceed
														 * OXFFFF as it is 16-bit Timer
														 */
														TIMER1_OUTPUT_COMPARE_REGISTER_A = ((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF;

														break; /*End of channel A*/

													case ChannelB:
														/*
														 * Configure OC1A as Output PIN
														 * the pin where the PWM signal is generated from MC
														 */
														OC1B_DIRECTION_PORT = SET_BIT(OC1B_DIRECTION_PORT, OC1B_PIN);

														/*
														 * Configure FOC1B bit in the TCCR1 register to be low
														 * As Timer1 is PWM
														 * Make FOC1B to be low as it is FAST_PWM_10bit mode
														 */
														TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_B);

														/*
														 * Configure compare output mode to work with Timer1
														 * with one mode from 4 modes in TCCR1A
														 * Configure COM1B0/COM1B1 bits in TCCR1A register
														 */
														TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1B_MASK_CLEAR) |
																((Timer1_config_PTR->Compare_Mode_PWM_PhaseCorrect)<<COM1B_SHIFT_VALUE);

														/*
														 * Configure Compare match value for Timer1 to start count from it
														 * Anding with 0XFFFF to make sure the value won't exceed
														 * OXFFFF as it is 16-bit Timer
														 * to make it count right put OCR1A  greater than the value in OCR1B by 1
														 */
														TIMER1_OUTPUT_COMPARE_REGISTER_A = (((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF) + 1;
														TIMER1_OUTPUT_COMPARE_REGISTER_B = ((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF;

														break;/*End of channel B*/
													}/*End of Channel Type switch case*/
													break;/*End of PWM_PhaseCorrect_OCR1A mode*/
													/**************************************************************************
													 *                          Timer1_CTC_ICR1_Mode
													 * ************************************************************************/
												case CTC_ICR1:
													/*
													 * Configure wave form generation mode to work with CTC_ICR1 mode
													 * Set WMG10 bit in TCCR1A register
													 * Set WMG11 bit in TCCR1A register
													 */
													TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT10);
													TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT11);

													/*
													 * Configure wave form generation mode to work with CTC_ICR1 mode
													 * Set WMG13 bit in TCCR1B register
													 * Set WMG12 bit in TCCR1B register
													 */
													TIMER1_CONTROL_REGIRSTER_B =  SET_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT12);
													TIMER1_CONTROL_REGIRSTER_B =  SET_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT13);
													/*
													 * Configure Input capture value for Timer1 to be the top from it
													 * Anding with 0XFFFF to make sure the value won't exceed
													 * OXFFFF as it is 16-bit Timer
													 */
													TIMER1_INPUT_CAPTURE_REGISTER  = ( (Timer1_config_PTR->timer1_InputCaptureValue) & 0XFFFF) ;

													switch(Timer1_config_PTR->channel)
													{

													case ChannelA:

														/*
														 * Configure FOC1A bit in the TCCR1 register to be active
														 * As Timer1 is non-PWM
														 * Make FOC1A to be Active as it is compare mode
														 */
														TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_A);
														/*
														 * Configure compare output mode to work with Timer1
														 * with one mode from 4 modes in TCCR1A
														 * Configure COM1A0/COM1A1 bits in TCCR1A register
														 */
														TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1A_MASK_CLEAR) |
																((Timer1_config_PTR->Compare_Mode_NonPWM)<<COM1A_SHIFT_VALUE);
														/*
														 * Configure Compare match value for Timer1 to start count from it
														 * Anding with 0XFFFF to make sure the value won't exceed
														 * OXFFFF as it is 16-bit Timer
														 */
														TIMER1_OUTPUT_COMPARE_REGISTER_A = ((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF;
														/*
														 * Enable Timer1 compare match interrupt
														 * wait for: -Enable I-bit "mask bit" in the SREG register
														 *           -OCF1 bit in the TIFR register to be set
														 * Timer1 compare match mode is ready to work after that
														 */
														TIMER1_INTERRUPT_MASK_REGISTER = SET_BIT(TIMER1_INTERRUPT_MASK_REGISTER,TIMER1_OUTPUT_COMPARE_MATCH_INTERRUPT_A);

														break; /*End of channel A*/

													case ChannelB:

														/*
														 * Configure FOC1B bit in the TCCR1 register to be active
														 * As Timer1 is non-PWM
														 * Make FOC1B to be Active as it is compare mode
														 */
														TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_B);

														/*
														 * Configure compare output mode to work with Timer1
														 * with one mode from 4 modes in TCCR1A
														 * Configure COM1B0/COM1B1 bits in TCCR1A register
														 */
														TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1B_MASK_CLEAR) |
																((Timer1_config_PTR->Compare_Mode_NonPWM)<<COM1B_SHIFT_VALUE);

														/*
														 * Configure Compare match value for Timer1 to start count from it
														 * Anding with 0XFFFF to make sure the value won't exceed
														 * OXFFFF as it is 16-bit Timer
														 * to make it count right put OCR1A  greater than the value in OCR1B by 1
														 */
														TIMER1_OUTPUT_COMPARE_REGISTER_A = (((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF) + 1;
														TIMER1_OUTPUT_COMPARE_REGISTER_B = ((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF;

														/*
														 * Enable Timer1 compare match interrupt
														 * wait for: -Enable I-bit "mask bit" in the SREG register
														 *           -OCF1 bit in the TIFR register to be set
														 * Timer1 compare match mode is ready to work after that
														 */
														TIMER1_INTERRUPT_MASK_REGISTER = SET_BIT(TIMER1_INTERRUPT_MASK_REGISTER,TIMER1_OUTPUT_COMPARE_MATCH_INTERRUPT_B);

														break;/*End of channel B*/
													}/*End of Channel Type switch case*/

													break;/*End of CTC_ICR1 mode*/

													/**************************************************************************
													 *                              Timer1_Reserved_Mode
													 * ************************************************************************/
													case Reserved_Mode:
														break;
													/**************************************************************************
													 *                       Timer1_FAST_PWM_ICR1_Mode
													 * ************************************************************************/
												case FAST_PWM_ICR1:
													/*
													 * Configure wave form generation mode to work with PWM_PhaseCorrect_ICR1 mode
													 * Clear WGM10 bit in TCCR1A register
													 * Set WGM11 bit in TCCR1A register
													 */
													TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT10);
													TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT11);

													/*
													 * Configure wave form generation mode to work with FAST_PWM_ICR1 mode
													 * Set WGM12 bit in TCCR1B register
													 * Set WMG13 bit in TCCR1B register
													 */
													TIMER1_CONTROL_REGIRSTER_B =  SET_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT12);
													TIMER1_CONTROL_REGIRSTER_B =  SET_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT13);

													/*
													 * Configure Input capture value for Timer1 to be the top from it
													 * Anding with 0XFFFF to make sure the value won't exceed
													 * OXFFFF as it is 16-bit Timer
													 */
													TIMER1_INPUT_CAPTURE_REGISTER  = ( (Timer1_config_PTR->timer1_InputCaptureValue) & 0XFFFF) ;

													switch(Timer1_config_PTR->channel)
													{

													case ChannelA:
														/*
														 * Configure OC1A as Output PIN
														 * the pin where the PWM signal is generated from MC
														 */
														OC1A_DIRECTION_PORT = SET_BIT(OC1A_DIRECTION_PORT, OC1A_PIN);

														/*
														 * Configure FOC1A bit in the TCCR1 register to be low
														 * As Timer1 is PWM mode
														 * Make FOC1A to be low as it is FAST_PWM_ICR1 mode
														 */
														TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_A);
														/*
														 * Configure compare output mode to work with Timer1
														 * with one mode from 4 modes in TCCR1A
														 * Configure COM1A0/COM1A1 bits in TCCR1A register
														 */
														TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1A_MASK_CLEAR) |
																((Timer1_config_PTR->Compare_Mode_FASTPWM)<<COM1A_SHIFT_VALUE);
														/*
														 * Configure Compare match value for Timer1 to start count from it
														 * Anding with 0XFFFF to make sure the value won't exceed
														 * OXFFFF as it is 16-bit Timer
														 */
														TIMER1_OUTPUT_COMPARE_REGISTER_A = ((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF;

														break; /*End of channel A*/

													case ChannelB:
														/*
														 * Configure OC1A as Output PIN
														 * the pin where the PWM signal is generated from MC
														 */
														OC1B_DIRECTION_PORT = SET_BIT(OC1B_DIRECTION_PORT, OC1B_PIN);

														/*
														 * Configure FOC1B bit in the TCCR1 register to be low
														 * As Timer1 is PWM
														 * Make FOC1B to be low as it is FAST_PWM_ICR1 mode
														 */
														TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_B);

														/*
														 * Configure compare output mode to work with Timer1
														 * with one mode from 4 modes in TCCR1A
														 * Configure COM1B0/COM1B1 bits in TCCR1A register
														 */
														TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1B_MASK_CLEAR) |
																((Timer1_config_PTR->Compare_Mode_FASTPWM)<<COM1B_SHIFT_VALUE);

														/*
														 * Configure Compare match value for Timer1 to start count from it
														 * Anding with 0XFFFF to make sure the value won't exceed
														 * OXFFFF as it is 16-bit Timer
														 * to make it count right put OCR1A  greater than the value in OCR1B by 1
														 */
														TIMER1_OUTPUT_COMPARE_REGISTER_A = (((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF) + 1;
														TIMER1_OUTPUT_COMPARE_REGISTER_B = ((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF;

														break;/*End of channel B*/
													}/*End of Channel Type switch case*/
													break;/*End of FAST_PWM_ICR1 mode*/
													/**************************************************************************
													 *                       Timer1_FAST_PWM_OCR1A_Mode
													 * ************************************************************************/
												case FAST_PWM_OCR1A:
													/*
													 * Configure wave form generation mode to work with FAST_PWM_OCR1A mode
													 * Set WGM10 bit in TCCR1A register
													 * Set WGM11 bit in TCCR1A register
													 */
													TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT10);
													TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A, TIMER1_WAVE_FORM_GENERATION_BIT11);

													/*
													 * Configure wave form generation mode to work with PWM_PhaseCorrect_ICR1 mode
													 * Set WGM12 bit in TCCR1B register
													 * Set WMG13 bit in TCCR1B register
													 */
													TIMER1_CONTROL_REGIRSTER_B =  SET_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT12);
													TIMER1_CONTROL_REGIRSTER_B =  SET_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT13);

													switch(Timer1_config_PTR->channel)
													{

													case ChannelA:
														/*
														 * Configure OC1A as Output PIN
														 * the pin where the PWM signal is generated from MC
														 */
														OC1A_DIRECTION_PORT = SET_BIT(OC1A_DIRECTION_PORT, OC1A_PIN);

														/*
														 * Configure FOC1A bit in the TCCR1 register to be low
														 * As Timer1 is PWM mode
														 * Make FOC1A to be low as it is FAST_PWM_OCR1A mode
														 */
														TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_A);
														/*
														 * Configure compare output mode to work with Timer1
														 * with one mode from 4 modes in TCCR1A
														 * Configure COM1A0/COM1A1 bits in TCCR1A register
														 */
														TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1A_MASK_CLEAR) |
																((Timer1_config_PTR->Compare_Mode_FASTPWM)<<COM1A_SHIFT_VALUE);
														/*
														 * Configure Compare match value for Timer1 to start count from it
														 * Anding with 0XFFFF to make sure the value won't exceed
														 * OXFFFF as it is 16-bit Timer
														 */
														TIMER1_OUTPUT_COMPARE_REGISTER_A = ((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF;

														break; /*End of channel A*/

													case ChannelB:
														/*
														 * Configure OC1A as Output PIN
														 * the pin where the PWM signal is generated from MC
														 */
														OC1B_DIRECTION_PORT = SET_BIT(OC1B_DIRECTION_PORT, OC1B_PIN);

														/*
														 * Configure FOC1B bit in the TCCR1 register to be low
														 * As Timer1 is PWM
														 * Make FOC1B to be low as it is FAST_PWM_OCR1A mode
														 */
														TIMER1_CONTROL_REGIRSTER_A =  CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_B);

														/*
														 * Configure compare output mode to work with Timer1
														 * with one mode from 4 modes in TCCR1A
														 * Configure COM1B0/COM1B1 bits in TCCR1A register
														 */
														TIMER1_CONTROL_REGIRSTER_A = (TIMER1_CONTROL_REGIRSTER_A & TIMER1_COM1B_MASK_CLEAR) |
																((Timer1_config_PTR->Compare_Mode_FASTPWM)<<COM1B_SHIFT_VALUE);

														/*
														 * Configure Compare match value for Timer1 to start count from it
														 * Anding with 0XFFFF to make sure the value won't exceed
														 * OXFFFF as it is 16-bit Timer
														 * to make it count right put OCR1A  greater than the value in OCR1B by 1
														 */
														TIMER1_OUTPUT_COMPARE_REGISTER_A = (((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF) + 1;
														TIMER1_OUTPUT_COMPARE_REGISTER_B = ((Timer1_config_PTR->timer1_compare_MatchValue)) & 0XFFFF;

														break;/*End of channel B*/
													}/*End of Channel Type switch case*/
													break;/*End of FAST_PWM_OCR1A mode*/
	}/*End of switch case timer1_mode*/
}/*End of Timer1_Init function */

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
void Timer1_setCallBack( void(*a_ptr)(void) )
{
	g_Timer1_callBackPtr = a_ptr;
}
/***************************************************************************************************
 * [Function Name]: Timer1_DeInit
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
void Timer1_DeInit(void)
{

	/*Clear all register in Timer1*/
	TIMER1_CONTROL_REGIRSTER_A         &= 0X00;
	TIMER1_CONTROL_REGIRSTER_B         &= 0X00;
	TIMER1_INITIAL_VALUE_REGISTER      &= 0X00;
	TIMER1_OUTPUT_COMPARE_REGISTER_A   &= 0X00;
	TIMER1_OUTPUT_COMPARE_REGISTER_B   &= 0X00;
	TIMER1_INTERRUPT_MASK_REGISTER     &= 0X00;
	TIMER1_INPUT_CAPTURE_REGISTER      &= 0X00;

}/*End of Timer0_DEInit*/


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
void Timer1_Stop(void)
{

	/*
	 * Clear the first 3-bits in TCCR1B register
	 * stop the clock of the timer
	 * timer1 will stop incrementing
	 */
	TIMER1_CONTROL_REGIRSTER_B  =  (TIMER1_CONTROL_REGIRSTER_B  & TIMER1_CLOCK_MASK_CLEAR) ;
}
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
void Timer1_Start(Timer_Clock timer1_clock_value)
{
	/*
	 * Clear the first 3-bits in TCCR1B register
	 * stop the clock of the timer
	 * timer1 will stop incrementing
	 */
	TIMER1_CONTROL_REGIRSTER_B  =  (TIMER1_CONTROL_REGIRSTER_B  & TIMER1_CLOCK_MASK_CLEAR) | timer1_clock_value;
}
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
void Timer1_Change_CompareMatchValue(uint16 timer1_newCompareValue, Channel_Type channel)
{
	/*
	 * Clear Output Compare Match register for Timer1
	 * then put the new compare value in it, Anding with 0XFFFF to make
	 * sure the value won't exceed 0xffff as it is 16-bit Timer
	 */
	switch (channel)
	{
	case ChannelA:
		TIMER1_OUTPUT_COMPARE_REGISTER_A = (TIMER1_OUTPUT_COMPARE_REGISTER_A & 0X0000) |  (timer1_newCompareValue & 0XFFFF);
		break;

	case ChannelB:
		TIMER1_OUTPUT_COMPARE_REGISTER_A = ( (TIMER1_OUTPUT_COMPARE_REGISTER_A & 0X0000) |  (timer1_newCompareValue & 0XFFFF) ) + 1;
		TIMER1_OUTPUT_COMPARE_REGISTER_B =   (TIMER1_OUTPUT_COMPARE_REGISTER_B & 0X0000) |  (timer1_newCompareValue & 0XFFFF);

		break;

	}/*End of switch case*/

}


/**************************************************************************
 *                              Timer2                                    *
 **************************************************************************/
/***************************************************************************************************
 * [Function Name]: Timer2_init
 *
 * [Description]:  Function to Initialize Timer2 Driver
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
void Timer2_Init(const Timer2_ConfigType* config_PTR)
{

	/*
	 * Configure initial value for Timer2 to start count from it
	 * Anding with 0XFF to make sure the value won't exceed
	 * 255 as it is 8-bit Timer
	 */

	TIMER2_CONTROL_REGIRSTER = ( (config_PTR->timer2_InitialValue) ) & 0XFF;

	/*
	 * Configure Clock Pre-scaler value for Timer2 in TCCR2 Register
	 * Anding with 0XF8 to make sure the first 3-bits in TCCR2 register=0
	 * ORing with the selected timer clock to include it in the first 3-bits
	 * and keep the other bits as they are
	 */

	TIMER2_CONTROL_REGIRSTER = (TIMER2_CONTROL_REGIRSTER  & TIMER2_CLOCK_MASK_CLEAR) |
			(config_PTR->timer2_clock);


	switch ( (config_PTR->timer2_mode) )
	{

	case Overflow:

		/*
		 * Configure wave form generation mode to work with normal mode
		 * Clear WGM20 bit in TCCR2 register
		 * Clear WGM21 bit in TCCR0 register
		 */
		TIMER2_CONTROL_REGIRSTER  = CLEAR_BIT(TIMER2_CONTROL_REGIRSTER , TIMER2_WAVE_FORM_GENERATION_BIT0);
		TIMER2_CONTROL_REGIRSTER  = CLEAR_BIT(TIMER2_CONTROL_REGIRSTER , TIMER2_WAVE_FORM_GENERATION_BIT1);

		/*
		 * Configure compare output mode to work with normal port operation
		 * Decide the mode of OC2 from compare output modes with non PWM
		 * Configure COM20 bit in TCCR2 register
		 * Configure COM21 bit in TCCR2 register
		 */
		TIMER2_CONTROL_REGIRSTER = (TIMER2_CONTROL_REGIRSTER & TIMER2_COM2_MASK_CLEAR ) |
				((config_PTR->Compare_Mode_NonPWM)<<COM2_SHIFT_VALUE);

		/*
		 * Configure FOC2 bit in the TCCR2 register to be active
		 * As Timer2 is non-PWM
		 * Make FOC2 to be Active as it is overflow mode
		 */
		TIMER2_CONTROL_REGIRSTER = SET_BIT(TIMER2_CONTROL_REGIRSTER,TIMER2_FORCE_OUTPUT_COMPARE_BIT);

		/*
		 * Enable Timer2 overflow interrupt
		 * wait for: -Enable I-bit "mask bit" in the SREG register
		 *           -TOV2 bit in the TIFR register to be set
		 * Timer2 overflow mode is ready to work after that
		 */
		TIMER2_INTERRUPT_MASK_REGISTER = SET_BIT(TIMER2_INTERRUPT_MASK_REGISTER, TIMER2_OUTPUT_OVERFLOW_INTERRUPT);
		break;


	case PWM_PhaseCorrect:

		/*
		 * Configure OC2 as Output PIN
		 * the pin where the PWM signal is generated from MC
		 */

		OC2_DIRECTION_PORT = SET_BIT(OC2_DIRECTION_PORT, OC2_PIN);

		/*
		 *Clear force output compare bit in Timer/Counter control register
		 *to work with pulse width modulation
		 */
		TIMER2_CONTROL_REGIRSTER = CLEAR_BIT(TIMER2_CONTROL_REGIRSTER, TIMER2_FORCE_OUTPUT_COMPARE_BIT);

		/*
		 * Configure wave form generation mode to work with PWM_PhaseCorrect mode
		 * SET WGM20 bit in TCCR0 register
		 * Clear WGM21 bit in TCCR0 register
		 */
		TIMER2_CONTROL_REGIRSTER = SET_BIT(TIMER2_CONTROL_REGIRSTER, TIMER2_WAVE_FORM_GENERATION_BIT0);
		TIMER2_CONTROL_REGIRSTER = CLEAR_BIT(TIMER2_CONTROL_REGIRSTER, TIMER2_WAVE_FORM_GENERATION_BIT1);

		/*
		 * Configure compare output mode to work with normal port operation
		 * Decide the mode of OC2 from compare output modes with PWM_PhaseCorrect
		 * Configure COM20 bit in TCCR2 register
		 * Configure COM21 bit in TCCR2 register
		 */
		TIMER2_CONTROL_REGIRSTER = (TIMER2_CONTROL_REGIRSTER & TIMER2_COM2_MASK_CLEAR ) |
				((config_PTR->Compare_Mode_PWM_PhaseCorrect)<<COM2_SHIFT_VALUE);

		/*
		 * Configure Compare match value for Timer2 to start count till reach it
		 * Anding with 0XFF to make sure the value won't exceed
		 * 255 as it is 8-bit Timer
		 */
		TIMER2_OUTPUT_COMPARE_REGISTER = ((config_PTR->timer2_compare_MatchValue)) & 0XFF;

		break; /*End of PWM_PhaseCorrect*/


	case CTC:

		/*
		 * Configure wave form generation mode to work with CTC mode
		 * Clear WGM20 bit in TCCR2 register
		 * Clear WGM21 bit in TCCR2 register
		 */
		TIMER2_CONTROL_REGIRSTER = CLEAR_BIT(TIMER2_CONTROL_REGIRSTER, TIMER2_WAVE_FORM_GENERATION_BIT0);
		TIMER2_CONTROL_REGIRSTER = SET_BIT(TIMER2_CONTROL_REGIRSTER, TIMER2_WAVE_FORM_GENERATION_BIT1);

		/*
		 * Configure compare output mode to work with normal port operation
		 * Decide the mode of OC0 from compare output modes with non PWM
		 * Configure COM20 bit in TCCR0 register
		 * Configure COM21 bit in TCCR0 register
		 */
		TIMER2_CONTROL_REGIRSTER = (TIMER2_CONTROL_REGIRSTER & TIMER2_COM2_MASK_CLEAR ) |
				((config_PTR->Compare_Mode_NonPWM)<<COM2_SHIFT_VALUE);

		/*
		 * Configure FOC0 bit in the TCCR2 register to be active
		 * As Timer2 is non-PWM
		 * Make FOC2 to be Active as it is compare mode
		 */
		TIMER2_CONTROL_REGIRSTER = SET_BIT(TIMER2_CONTROL_REGIRSTER, TIMER2_FORCE_OUTPUT_COMPARE_BIT);

		/*
		 * Configure Compare match value for Timer2 to start count from it
		 * Anding with 0XFF to make sure the value won't exceed
		 * 255 as it is 8-bit Timer
		 */
		TIMER2_OUTPUT_COMPARE_REGISTER = ((config_PTR->timer2_compare_MatchValue)) & 0XFF;

		/*
		 * Enable Timer0 compare match interrupt
		 * wait for: -Enable I-bit "mask bit" in the SREG register
		 *           -OCF0 bit in the TIFR register to be set
		 * Timer0 compare match mode is ready to work after that
		 */
		TIMER2_INTERRUPT_MASK_REGISTER = SET_BIT(TIMER2_INTERRUPT_MASK_REGISTER, TIMER2_OUTPUT_COMPARE_MATCH_INTERRUPT);

		break; /*End of compare mode*/

	case FAST_PWM:
		/*
		 * Configure OC2 as Output PIN
		 * the pin where the PWM signal is generated from MC
		 */

		OC2_DIRECTION_PORT = SET_BIT(OC2_DIRECTION_PORT, OC2_PIN);

		/*
		 *Clear force output compare bit in Timer/Counter control register
		 *to work with pulse width modulation
		 */
		TIMER2_CONTROL_REGIRSTER = CLEAR_BIT(TIMER2_CONTROL_REGIRSTER, TIMER2_FORCE_OUTPUT_COMPARE_BIT);

		/*
		 * Configure wave form generation mode to work with FAST PWM mode
		 * SET WGM20 bit in TCCR2 register
		 * SET WGM21 bit in TCCR2 register
		 */
		TIMER2_CONTROL_REGIRSTER = SET_BIT(TIMER2_CONTROL_REGIRSTER, TIMER2_WAVE_FORM_GENERATION_BIT0);
		TIMER2_CONTROL_REGIRSTER = SET_BIT(TIMER2_CONTROL_REGIRSTER, TIMER2_WAVE_FORM_GENERATION_BIT1);

		/*
		 * Configure compare output mode to work with normal port operation
		 * Decide the mode of OC2 from compare output modes with non PWM
		 * Configure COM20 bit in TCCR2 register
		 * Configure COM21 bit in TCCR2 register
		 */
		TIMER2_CONTROL_REGIRSTER = (TIMER2_CONTROL_REGIRSTER & TIMER2_COM2_MASK_CLEAR ) |
				((config_PTR->Compare_Mode_FASTPWM)<<COM2_SHIFT_VALUE);

		/*
		 * Configure Compare match value for Timer2 to start count till reach it
		 * Anding with 0XFF to make sure the value won't exceed
		 * 255 as it is 8-bit Timer
		 */
		TIMER2_OUTPUT_COMPARE_REGISTER = ((config_PTR->timer2_compare_MatchValue)) & 0XFF;

		break;/*End of Fast PWM*/

	}/*End of switch case for timer2_mode*/

}/*End of Timer2_Init*/

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
void Timer2_setCallBack( void(*a_ptr)(void) )
{
	g_Timer2_callBackPtr = a_ptr;
}
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
void Timer2_DeInit(void)
{

	/*Clear all register in Timer0*/
	TIMER2_CONTROL_REGIRSTER        &= 0X00;
	TIMER2_INITIAL_VALUE_REGISTER   &= 0X00;
	TIMER2_OUTPUT_COMPARE_REGISTER  &= 0X00;
	TIMER2_INTERRUPT_MASK_REGISTER  &= 0X00;

}/*End of Timer0_DEInit*/
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
void Timer2_Stop(void)
{
	/*
	 * Clear the first 3-bits in TCCR0 register
	 * stop the clock of the timer
	 * timer0 will stop incrementing
	 */
	TIMER2_CONTROL_REGIRSTER = (TIMER2_CONTROL_REGIRSTER  & TIMER2_CLOCK_MASK_CLEAR);
}
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
void Timer2_Start(Timer_Clock timer2_clock_value)
{
	/*
	 * Clear the first 3-bits in TCCR0 register
	 * stop the clock of the timer
	 * timer0 will stop incrementing
	 */
	TIMER2_CONTROL_REGIRSTER = (TIMER2_CONTROL_REGIRSTER  & TIMER2_CLOCK_MASK_CLEAR) | timer2_clock_value ;
}
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
void Timer2_Change_CompareMatchValue(uint8 timer2_newCompareValue)
{
	/*
	 * Clear Output Compare Match register for Timer0
	 * then put the new compare value in it, Anding with 0XFF to make
	 * sure the value won't exceed 255 as it is 8-bit Timer
	 */
	TIMER2_OUTPUT_COMPARE_REGISTER = (TIMER2_OUTPUT_COMPARE_REGISTER & 0X00) |
			(timer2_newCompareValue & 0XFF);
}
/****************************************************************************************************/

