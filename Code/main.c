/**********************************************************************************
 * [FILE NAME]: main.c
 *
 * [AUTHOR]: Toka Zakaria Mohamed
 *
 * [DATE CREATED]: Sep 24, 2021
 *
 * [Description]: File to contain the application of the Digital Clock
 ***********************************************************************************/

#include"app_file.h"

/********************************************************************
 *                       Global Variables                           *
 *******************************************************************/
/*
 * Variable to check if the interrupt of TIMER1 happen or not
 * global to use it in external function
 */
bool g_tick = FALSE;
/*
 * Variable to increment the value of the seconds
 *global to use it in external function
 *
 */
uint8 g_seconds = INITIAL_COUNT;
/*
 * Variable to increment the value of the minutes
 * global to use it in external function
 *
 */
uint8 g_minutes = INITIAL_COUNT;
/*
 * Variable to increment the value of the hours
 * global to use it in external function
 */
uint8 g_hours = INITIAL_COUNT;
/*
 * Variable to carry the position of the cursor on the LCD
 * global to use it in external function
 */
sint8 g_cursorPosition = INITIAL_POSITION;
/*
 * Variable to to use it to indicate that OK button has pressed
 * global to use it in external function
 */
bool g_OK = TRUE;
/*********************************************************************************/
int main(void)
{
	/*******************************************************************************
	 *                    Variable Declaration and Definitions                     *
	 *******************************************************************************/
	/*
	 * local variable to use it with UP button to make sure that the
	 * functionality is done one time while pressing the button
	 */
	bool UP_flag = TRUE;

	/*
	 * local variable to use it with down button to make sure that the
	 * functionality is done one time while pressing the button
	 */
	bool Down_flag = TRUE;
	/*
	 * local structure  to configure the timer module to be able to count
	 */
	Timer1_ConfigType clock;
	/*
	 * local structure to configure the External Interrupt 0 module to be able to use it
	 */
	INT0_ConfigType right;
	/*
	 * local structure to configure the External Interrupt 1 module to be able to use it
	 */
	INT1_ConfigType left;
	/*
	 * local structure to configure the External Interrupt 2 module to be able to use it
	 */
	INT2_ConfigType  OK;
	/*
	 * Configure Interrupt 0 to work with falling edge
	 */
	right.INT0_senseControl  = INT0_Falling;
	/*
	 * Configure Interrupt 1 to work with falling edge
	 */
	left.INT1_senseControl   = INT1_Falling;
	/*
	 * Configure Interrupt 2 to work with falling edge
	 */
	OK.INT2_senseControl     = INT2_Falling;
	/*
	 * Configure timer structure to:
	 * with initial value --> 0
	 * with compare value --> 1000
	 * with mode --> compare
	 * compare at channel A
	 * No need for OC1A --> Disconnect
	 * Define clock--> F_CPU_1024
	 */
	clock.timer1_InitialValue = INITIAL_VALUE;
	clock.timer1_compare_MatchValue = COMPARE_VALUE;
	clock.timer1_mode = CTC_OCR1A;
	clock.channel = ChannelA;
	clock.Compare_Mode_NonPWM = Disconnected_NonPWM_16;
	clock.timer1_clock = F_CPU_1024;

	/*
	 * Configure the Callback function of timer to do
	 * a specific functionality every interrupt occurrence
	 * in Timer 1
	 */
	Timer1_setCallBack(tick);
	/*
	 * Configure the Callback function of timer to do
	 * a specific functionality every interrupt occurrence
	 * for External Interrupt 0
	 */
	INT0_setCallBack(Right);
	/*
	 * Configure the Callback function of timer to do
	 * a specific functionality every interrupt occurrence
	 * for External Interrupt 1
	 */
	INT1_setCallBack(Left);
	/*
	 * Configure the Callback function of timer to do
	 * a specific functionality every interrupt occurrence
	 * for External Interrupt 2
	 */
	INT2_setCallBack(OK_FUNC);
	/*******************************************************************************
	 *                             Modules Initialization                          *
	 *******************************************************************************/
	/*
	 * Configure Down button as input pin
	 */
	DOWN_BUTTON_DIRECTION_REG = CLEAR_BIT(DOWN_BUTTON_DIRECTION_REG, DOWN_BUTTON_PIN);
	/*
	 * Enable internal Pull Up register for Down button
	 */
	DOWN_BUTTON_PORT_REG = SET_BIT(DOWN_BUTTON_PORT_REG, DOWN_BUTTON_PIN);
	/*
	 * Configure Up button as input pin
	 */
	UP_BUTTON_DIRECTION_REG = CLEAR_BIT(UP_BUTTON_DIRECTION_REG, UP_BUTTON_PIN);
	/*
	 * Enable internal Pull Up register for Down button
	 */

	UP_BUTTON_PORT_REG = SET_BIT(UP_BUTTON_PORT_REG, UP_BUTTON_PIN);
	/*
	 * Initialize LCD to be ready to work
	 */
	LCD_init();
	/*
	 * Initialize Interrupt 0 to be ready to work
	 */
	INT0_Init(&right);
	/*
	 * Initialize Interrupt 1 to be ready to work
	 */
	INT1_Init(&left);
	/*
	 * Initialize Interrupt 2 to be ready to work
	 */
	INT2_Init(&OK);
	/*
	 * Start timer to count
	 */
	Timer1_Init(&clock);
	/*
	 * Enable i-bit in the SREG register
	 */
	SREG |= (1<<7);
	/*******************************************************************************
	 *                                Application                                   *
	 *******************************************************************************/
	while(1)
	{
		/**************************************************************************
		 *                           "Default State"                              *
		 *                          Display The CLOCK                             *
		 **************************************************************************/
		/*
		 * Check if OK button in the default value or not
		 */
		if(g_OK == TRUE)
		{
			/*
			 * Force the LCD to hide the cursor in the default state in displaying clock
			 */
			LCD_sendCommand(HIDE_CURSOR_COMMAND);
			/*
			 * Call the function which responsible to calculate the time
			 */
			DigitalClock();
			/*
			 * Call the function which responsible to display the digits of the digital clock
			 */
			display();
		}
		/**************************************************************************
		 *                         "Interrupt State"                              *
		 *                           Set the Clock                                *
		 **************************************************************************/
		else
		{
			/*
			 * Force the LCD to display the cursor to Know which digit you want to reset
			 */
			LCD_sendCommand(DISPLAY_CURSOR_COMMAND);
			/*
			 * Force the cursor to go left or right in the same row
			 * depending on the value of the position of the cursor
			 * this value depend on time of clicks on left or right buttons
			 */
			LCD_goToRowColumn(DIGITAL_CLOCK_ROW, g_cursorPosition-1);
			/**************************************************************************
			 *                              UP Button                                 *
			 **************************************************************************/
			if( (BIT_IS_CLEAR(UP_BUTTON_INPUT_REG, UP_BUTTON_PIN))  )
			{
				/*
				 * wait some seconds due to bouncing of the button
				 */
				_delay_ms(DEBOUNCE_TIME);
				/*
				 * Ask again to make sure it is a real push on the button
				 */
				if( BIT_IS_CLEAR(UP_BUTTON_INPUT_REG, UP_BUTTON_PIN) )
				{
					/*
					 * Ask about the SW flag of UP button to make sure it will do
					 *the functionality one time only
					 */
					if(UP_flag == TRUE)
					{
						/*
						 * Change the state of the UP button to prevent the program
						 * to enter this area of condition to avoid multiple of this action
						 * during continuous press
						 */
						UP_flag = FALSE;
						/*
						 * Call the function of UP button which responsible to
						 * increase the digit that the cursor point at
						 */
						UP_Func();
						/*
						 * Call the function which responsible to display the digits of the digital clock
						 */
						display();
					}
				}
			}
			else
			{
				/*
				 * Change the state of the UP button to enable the program
				 * to enter the area of condition once again after releasing the button
				 */
				UP_flag = TRUE;
			}
			/**************************************************************************
			 *                              Down Button                               *
			 **************************************************************************/
			if( BIT_IS_CLEAR(DOWN_BUTTON_INPUT_REG, DOWN_BUTTON_PIN) )
			{
				/*
				 * wait some seconds due to bouncing of the button
				 */
				_delay_ms(DEBOUNCE_TIME);
				/*
				 * Ask again to make sure it is a real push on the button
				 */
				if( BIT_IS_CLEAR(DOWN_BUTTON_INPUT_REG, DOWN_BUTTON_PIN) )
				{
					/*
					 *Ask about the SW flag of UP button to make sure it will do
					 *the functionality one time only
					 */
					if(Down_flag == TRUE)
					{
						/*
						 * Change the state of the down button to prevent the program
						 * to enter this area of condition to avoid multiple of this action
						 * during continuous press
						 */
						Down_flag = FALSE;
						/*
						 * Call the function of down button which responsible to
						 * decrease the digit that the cursor point at
						 */
						down_Func();
						/*
						 * Call the function which responsible to display the digits of the digital clock
						 */
						display();
					}
				}
			}
			else
			{
				/*
				 * Change the state of the down button to enable the program
				 * to enter the area of condition once again after releasing the button
				 */
				Down_flag = TRUE;
			}
			/************************************************************************/
		}
	}/*End of super loop*/

	return 0;
}

