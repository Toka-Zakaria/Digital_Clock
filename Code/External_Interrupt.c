/**********************************************************************************
 * [FILE NAME]: External_Interrupt.c
 *
 * [AUTHOR]: Toka Zakaria Mohamed Ramadan
 *
 * [DATE CREATED]: Sep 6, 2021
 *
 * [Description]: File to initialize all external interrupts in ATmega32
 ***********************************************************************************/

#include"External_Interrupt_interface.h"
#include"common_macros.h"

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_INT0_callBackPtr)(void) = NULL_PTR;
static volatile void (*g_INT1_callBackPtr)(void) = NULL_PTR;
static volatile void (*g_INT2_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
/**************************************************************************
 *                            Interrupt0                                  *
 * ************************************************************************/
ISR(INT0_vect)
{
	if(g_INT0_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_INT0_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}

	/* Clear the flag if interrupt 0 at the end of ISR */

	GENERAL_INTERRUPT_FLAG_REGISTER = SET_BIT(GENERAL_INTERRUPT_FLAG_REGISTER, EXTERNAL_INTERRUPT_FLAG_0);
}


/**************************************************************************
 *                            Interrupt1                                  *
 * ************************************************************************/

ISR(INT1_vect)
{
	if(g_INT1_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_INT1_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}


	/* Clear the flag if interrupt 1 at the end of ISR */

	GENERAL_INTERRUPT_FLAG_REGISTER = SET_BIT(GENERAL_INTERRUPT_FLAG_REGISTER, EXTERNAL_INTERRUPT_FLAG_1);
}


/**************************************************************************
 *                            Interrupt2                                  *
 * ************************************************************************/
ISR(INT2_vect)
{
	if(g_INT2_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_INT2_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}


	/* Clear the flag if interrupt 2 at the end of ISR */

	GENERAL_INTERRUPT_FLAG_REGISTER = SET_BIT(GENERAL_INTERRUPT_FLAG_REGISTER, EXTERNAL_INTERRUPT_FLAG_2);
}

/***************************************************************************************************
 * [Function Name]: INT0_Init
 *
 * [Description]:  Function to Initialize External Interrupt Driver
 *                 - Working in Interrupt Mode
 *                 - Choose External interrupt control edge
 *                 - Choose INTERRUPT_ID (INT0, INT1, INT2)
 *
 *
 * [Args]:         INT0_config_PTR
 *
 * [In]            INT0_config_PTR: Pointer to Timer Configuration Structure
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void INT0_Init(const INT0_ConfigType * INT0_config_PTR)
{

	/*configure pin of interrupt0 as input pin*/
	INTERRUPT0_DIRECTION_PORT = CLEAR_BIT(INTERRUPT0_DIRECTION_PORT, INTERRUPT0_PIN);

	/*static configuration of internal pull up resistance*/
#if (INTERNAL_PULL_UP_INT0 != FALSE)
	{

		/*Activate internal pull up for interrupt 0*/
		INTERRUPT0_DATA_PORT = SET_BIT(INTERRUPT0_DATA_PORT, INTERRUPT0_PIN);

	}/*end of INTERNAL_PULL_UP_INT0  */
#endif


	/*configure the control edge for interrupt 0*/
	MCU_CONTROL_REGISTER = (MCU_CONTROL_REGISTER & 0XFC) | (INT0_config_PTR->INT0_senseControl) ;

	/*activate external interrupt 0 interrupt enable*/
	GENERAL_INTERRUPT_CONTROL_REGISTER = (GENERAL_INTERRUPT_CONTROL_REGISTER & 0XBF) | (1<<EXTRNAL_INTERRUPT0_ENABL_BIT);

}
/***************************************************************************************************
 * [Function Name]: INT1_Init
 *
 * [Description]:  Function to Initialize External Interrupt Driver
 *                 - Working in Interrupt Mode
 *                 - Choose External interrupt control edge
 *
 * [Args]:         INT1_config_PTR
 *
 * [In]            INT1_config_PTR: Pointer to Timer Configuration Structure
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void INT1_Init(const INT1_ConfigType * INT1_config_PTR)
{

	/*configure interrupt 1 pin as input pin*/
	INTERRUPT1_DIRECTION_PORT = CLEAR_BIT(INTERRUPT1_DIRECTION_PORT, INTERRUPT1_PIN);

	/*static configuration for the internal interrupt resistance*/
#if (INTERNAL_PULL_UP_INT1 != FALSE)
	{

		/*Activate internal pull up for interrupt 0*/
		INTERRUPT1_DATA_PORT = SET_BIT(INTERRUPT1_DATA_PORT, INTERRUPT1_PIN);

	}/*end of INTERNAL_PULL_UP_INT0  */
#endif


	/*configure control edge for interrupt 1*/
	MCU_CONTROL_REGISTER = (MCU_CONTROL_REGISTER & 0XF3) |
			( (INT1_config_PTR->INT1_senseControl)<< INTERRUPT1_SENSE_CONTROL_BITS_SHIFT_VALUE);

	/*active external interrupt interrupt enable for interrupt 1*/
	GENERAL_INTERRUPT_CONTROL_REGISTER = (GENERAL_INTERRUPT_CONTROL_REGISTER & 0X7F) | (1<<EXTRNAL_INTERRUPT1_ENABL_BIT);
}
/***************************************************************************************************
 * [Function Name]: INT2_Init
 *
 * [Description]:  Function to Initialize External Interrupt Driver
 *                 - Working in Interrupt Mode
 *                 - Choose External interrupt control edge
 *
 * [Args]:         INT2_config_PTR
 *
 * [In]            INT2_config_PTR: Pointer to Timer Configuration Structure
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void INT2_Init(const INT2_ConfigType * INT2_config_PTR)
{
	/*configure interrupt 2 pin as input pin */
	INTERRUPT2_DIRECTION_PORT = CLEAR_BIT(INTERRUPT2_DIRECTION_PORT, INTERRUPT2_PIN);

	/*static configuration for interrupt 2 resistance*/
#if (INTERNAL_PULL_UP_INT2 != FALSE)
	{

		/*Activate internal pull up for interrupt 0*/
		INTERRUPT2_DATA_PORT = SET_BIT(INTERRUPT2_DATA_PORT, INTERRUPT2_PIN);

	}/*end of INTERNAL_PULL_UP_INT0  */
#endif

	/*configure control edge for interrupt 2*/
	MCU_CONTROL_AND_STATUS_REGISTER = (MCU_CONTROL_AND_STATUS_REGISTER & 0XBF) |
			                  ( ((INT2_config_PTR->INT2_senseControl) & 0X01)<< INTERRUPT_SENSE_CONTROL_2);

	/*Active external interrupt interrupt enable*/
	GENERAL_INTERRUPT_CONTROL_REGISTER = (GENERAL_INTERRUPT_CONTROL_REGISTER & 0XCF) | (1<<EXTRNAL_INTERRUPT2_ENABL_BIT);
}


/***************************************************************************************************
 * [Function Name]: INT0_setCallBack
 *
 * [Description]:  Function to set the Call Back function address.
 *
 * [Args]:         INT0_ptr
 *
 * [In]            INT0_ptr: -Pointer to function
 *                        -To use it to save receive the function call back name
 *                        -To store it in the global pointer to function to use it in
 *                         calling stored function by pointer way to do specific operation
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void INT0_setCallBack(void(*INT0_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_INT0_callBackPtr = INT0_ptr;

}
/***************************************************************************************************
 * [Function Name]: INT1_setCallBack
 *
 * [Description]:  Function to set the Call Back function address.
 *
 * [Args]:         INT1_ptr
 *
 * [In]            INT1_ptr: -Pointer to function
 *                        -To use it to save receive the function call back name
 *                        -To store it in the global pointer to function to use it in
 *                         calling stored function by pointer way to do specific operation
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void INT1_setCallBack(void(*INT1_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_INT1_callBackPtr = INT1_ptr;

}
/***************************************************************************************************
 * [Function Name]: INT2_setCallBack
 *
 * [Description]:  Function to set the Call Back function address.
 *
 * [Args]:         INT2_ptr
 *
 * [In]            INT2_ptr: -Pointer to function
 *                        -To use it to save receive the function call back name
 *                        -To store it in the global pointer to function to use it in
 *                         calling stored function by pointer way to do specific operation
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void INT2_setCallBack(void(*INT2_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_INT2_callBackPtr = INT2_ptr;

}
/***************************************************************************************************
 * [Function Name]: INT0_DeInit
 *
 * [Description]:  Function to DeInit Interrupt0 to return to its default values
 *                 & stop the configuration
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
void INT0_DeInit(void)
{

	/*clear all bits of interrupt 0*/
	MCU_CONTROL_REGISTER = (MCU_CONTROL_REGISTER & 0XFC);
	GENERAL_INTERRUPT_CONTROL_REGISTER = (GENERAL_INTERRUPT_CONTROL_REGISTER & 0XBF);

}
/***************************************************************************************************
 * [Function Name]: INT1_DeInit
 *
 * [Description]:  Function to DeInit Interrupt1 to return to its default values
 *                 & stop the configuration
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
void INT1_DeInit(void)
{
	/*clear all bits of interrupt 1*/
	MCU_CONTROL_REGISTER = (MCU_CONTROL_REGISTER & 0XF3);

	GENERAL_INTERRUPT_CONTROL_REGISTER = (GENERAL_INTERRUPT_CONTROL_REGISTER & 0X7F);
}
/***************************************************************************************************
 * [Function Name]: INT2_DeInit
 *
 * [Description]:  Function to DeInit Interrupt2 to return to its default values
 *                 & stop the configuration
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
void INT2_DeInit(void)
{
	/*clear all bits of interrupt 2*/
	MCU_CONTROL_AND_STATUS_REGISTER = (MCU_CONTROL_AND_STATUS_REGISTER & 0XBF);

	GENERAL_INTERRUPT_CONTROL_REGISTER = (GENERAL_INTERRUPT_CONTROL_REGISTER & 0XCF);
}
/***************************************************************************************************
 * [Function Name]: INT0_changeInterrupt_senseControl
 *
 * [Description]:  Function to redefine the interrupt sense control edge
 *
 * [Args]:         INT0SenseControl
 *
 * [In]            INT0SenseControl: to carry the type of the edge of INT sense control
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void INT0_changeInterrupt_senseControl(Interrupt0_senseControl INT0SenseControl)
{

	/*configure the control edge for interrupt 0*/
	MCU_CONTROL_REGISTER = (MCU_CONTROL_REGISTER & 0XFC) | INT0SenseControl;

}
/***************************************************************************************************
 * [Function Name]: INT1_changeInterrupt_senseControl
 *
 * [Description]:  Function to redefine the interrupt sense control edge
 *
 * [Args]:         INT1SenseControl
 *
 * [In]            INT1SenseControl: to carry the type of the edge of INT sense control
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void INT1_changeInterrupt_senseControl(Interrupt1_senseControl INT1SenseControl)
{

	/*configure the control edge for interrupt 1*/
	MCU_CONTROL_REGISTER = (MCU_CONTROL_REGISTER & 0XF3) |
			     (INT1SenseControl << INTERRUPT1_SENSE_CONTROL_BITS_SHIFT_VALUE);

}
/***************************************************************************************************
 * [Function Name]: INT2_changeInterrupt_senseControl
 *
 * [Description]:  Function to redefine the interrupt sense control edge
 *
 * [Args]:         INT2SenseControl
 *
 * [In]            INT2SenseControl: to carry the type of the edge of INT sense control
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void INT2_changeInterrupt_senseControl(Interrupt2_senseControl INT2SenseControl)
{
	/*configure the control edge for interrupt 2*/
	MCU_CONTROL_AND_STATUS_REGISTER = (MCU_CONTROL_AND_STATUS_REGISTER & 0XBF) |
			                                ( (INT2SenseControl & 0X01) << INTERRUPT_SENSE_CONTROL_2);
}
/***************************************************************************************************/
