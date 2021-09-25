/**********************************************************************************
 * [FILE NAME]:  app_file.c
 *
 * [AUTHOR]: Toka Zakaria Mohamed
 *
 * [DATE CREATED]: Sep 24, 2021
 *
 * [Description]: File to contain the application Functions of the Digital Clock
 ***********************************************************************************/

#include"app_file.h"

/***************************************************************************************************
 * [Function Name]: display
 *
 * [Description]:  Function to display the time of the clock
 *
 * [Args]:         NONE
 *
 * [In]            NONE
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void display(void)
{
	/*
	 * Force the LCD to hide the cursor while displaying the CLOCK
	 */
	LCD_sendCommand(HIDE_CURSOR_COMMAND);

	/*
	 * Part which responsible to display the digits of hour
	 */
	LCD_goToRowColumn(DIGITAL_CLOCK_ROW,HOUR_TENS_COLUMN);
	LCD_intgerToString( TENS(g_hours) );
	LCD_goToRowColumn(DIGITAL_CLOCK_ROW,HOUR_UNITS_COLUMN);
	LCD_intgerToString( UNITS(g_hours) );

	/*
	 * Part which responsible to display first comma between hours and minutes
	 */
	LCD_goToRowColumn(DIGITAL_CLOCK_ROW, FIRST_COMMA_COLUMN);
	LCD_displayCharacter(':');

	/*
	 * Part which responsible to display the digits of minutes
	 */
	LCD_goToRowColumn(DIGITAL_CLOCK_ROW, MINUTES_TENS_COLUMN);
	LCD_intgerToString( TENS(g_minutes) );
	LCD_goToRowColumn(DIGITAL_CLOCK_ROW, MINUTES_UNITS_COLUMN);
	LCD_intgerToString( UNITS(g_minutes) );

	/*
	 * Part which responsible to display second comma between minutes and seconds
	 */
	LCD_goToRowColumn(DIGITAL_CLOCK_ROW, SECOND_COMMA_COLUMN);
	LCD_displayCharacter(':');

	/*
	 * Part which responsible to display the digits of seconds
	 */
	LCD_goToRowColumn(DIGITAL_CLOCK_ROW, SECONDS_TENS_COLUMN);
	LCD_intgerToString( TENS(g_seconds) );
	LCD_goToRowColumn(DIGITAL_CLOCK_ROW, SECONDS_UNITS_COLUMN);
	LCD_intgerToString( UNITS(g_seconds) );
}
/***************************************************************************************************
 * [Function Name]: DigitalClock
 *
 * [Description]:  Function to measure hours, minutes and seconds of the clock
 *
 * [Args]:         NONE
 *
 * [In]            NONE
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void DigitalClock(void)
{
	/*
	 * Check if the interrupt of the Timer1 happen or not
	 */
	if (g_tick == TRUE)
	{
		/*
		 * Increment the seconds of the StopWatch
		 */
		g_seconds++;
		/*
		 * Check if 1 minute passed or not if yes increment
		 *minutes1 and start the seconds to increment
		 * from 0 again
		 */
		if(g_seconds >= MAXIMUM_SECONDS)
		{

			/*
			 * clear the variable of seconds to begin from start again
			 * indicate that 1 minute passed
			 */
			g_seconds= INITIAL_COUNT;
			/*
			 * Increment variable of minutes to start appear on
			 * the 7 segments, incrementing every 60 seconds
			 */
			g_minutes++;

		}/*End of seconds condition*/


		/*
		 * Check if 1 hour passed or not if yes increment hours 1
		 * and start the Minutes & Seconds to increment from 0 again
		 */
		if(g_minutes >= MAXIMUM_MINUTES)
		{

			/*
			 * clear the variable of seconds to begin from start again
			 * indicate that 1 minute passed
			 */
			g_seconds = INITIAL_COUNT;
			/*
			 * clear the variable of minutes to begin from start again
			 * indicate that 1 hour passed
			 */
			g_minutes = INITIAL_COUNT;
			/*
			 * Increment variable of hours to start appear on
			 * the 7 segments, incrementing every 60 minutes
			 */
			g_hours++;

		}/*end of minutes condition*/


		/*
		 * Check if 1 hour passed or not if yes increment hours 1
		 *and start the Minutes & Seconds hours to increment from 0 again
		 *and this condition is true every 1000 melly seconds
		 */

		if(g_hours >= MAXIMUM_HOURS)
		{

			/*
			 * clear the variable of seconds to begin from start again
			 * indicate that 1 minute passed
			 */
			g_seconds = INITIAL_COUNT;
			/*
			 * clear the variable of minutes to begin from start again
			 * indicate that 1 hour passed
			 */
			g_minutes = INITIAL_COUNT;
			/*
			 * clear the variable of minutes to begin from start again
			 * indicate that 1 day passed
			 */
			g_hours = INITIAL_COUNT;
		}

		/*
		 * Return the value of tick to be 0 again to be
		 * ready for the next
		 */
		g_tick = FALSE;

	}/*end of first if statement*/

}
/***************************************************************************************************
 * [Function Name]: tick
 *
 * [Description]:  Call back function of Timer
 *
 * [Args]:         NONE
 *
 * [In]            NONE
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void tick(void)
{
	/*Change the state of the tick variable to know that the time interrupt has occurred*/
	g_tick = TRUE;
}
/***************************************************************************************************
 * [Function Name]: Right
 *
 * [Description]:  Call back function of Interrupt 0 which responsible for right button
 *
 * [Args]:         NONE
 *
 * [In]            NONE
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void Right(void)
{
	/*
	 * Stop the timer if Right button has pressed as that
	 * indicates system into Set Clock State
	 */
	Timer1_Stop();
	/*
	 * Change the State of OK button that to enter Set Clock State
	 */
	g_OK = FALSE;
	/*
	 * Increment the position of the cursor to go right
	 * in every increment "Every right button press"
	 */
	g_cursorPosition++;

	/*
	 * Conditions to handle the cursor position
	 * to prevent the cursor from pointing at Commas
	 * or pointing at any position except clock digits
	 */

	/*
	 * Force the position of cursor to go for first minutes digit
	 * if it is the first comma position
	 */
	if(g_cursorPosition == (FIRST_COMMA_COLUMN + 1) )
	{
		g_cursorPosition = (MINUTES_TENS_COLUMN + 1);
	}
	/*
	 * Force the position of cursor to go for first seconds digit
	 * if it is the second comma position
	 */
	else if(g_cursorPosition == (SECOND_COMMA_COLUMN+1) )
	{
		g_cursorPosition =  (SECONDS_TENS_COLUMN + 1) ;
	}
	/*
	 * Force the position of cursor to go for first hours digit
	 * if it is the end of clock digits position
	 */
	else if (g_cursorPosition == (END_OF_CLOCK_COLUMN + 1))
	{
		g_cursorPosition = (HOUR_TENS_COLUMN + 1);
	}

}
/***************************************************************************************************
 * [Function Name]: Left
 *
 * [Description]:  Call back function of Interrupt 1 which responsible for left button
 *
 * [Args]:         NONE
 *
 * [In]            NONE
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void Left(void)
{
	/*
	 * Stop the timer if Right button has pressed as that
	 * indicates system into Set Clock State
	 */
	Timer1_Stop();
	/*
	 * Change the State of OK button that to enter Set Clock State
	 */
	g_OK = FALSE;
	/*
	 * Decrement the position of the cursor to go left
	 * in every decrement "Every left button press"
	 */
	g_cursorPosition--;
	/*
	 * Conditions to handle the cursor position
	 * to prevent the cursor from pointing at Commas
	 * or pointing at any position except clock digits
	 */

	/*
	 * Force the position of cursor to go to stop at first element
	 * if the position at first hour digit
	 */
	if(g_cursorPosition <= HOUR_TENS_COLUMN)
	{
		g_cursorPosition = (HOUR_TENS_COLUMN + 1);
	}
	/*
	 * Force the position of cursor to go for units of hour digit
	 * if it is the first comma position
	 */
	else if(g_cursorPosition == (FIRST_COMMA_COLUMN + 1) )
	{
		g_cursorPosition = HOUR_UNITS_COLUMN + 1;
	}
	/*
	 * Force the position of cursor to go for units of minutes digit
	 * if it is the end of clock digits position
	 */
	else if(g_cursorPosition == (SECOND_COMMA_COLUMN + 1) )
	{
		g_cursorPosition =  MINUTES_UNITS_COLUMN + 1;
	}
}
/***************************************************************************************************
 * [Function Name]: OK_FUNC
 *
 * [Description]:  Call back function of Interrupt 2 which responsible for OK button
 *
 * [Args]:         NONE
 *
 * [In]            NONE
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void OK_FUNC(void)
{
	/*
	 * Restart the timer if the OK button is pressed
	 */
	Timer1_Start(F_CPU_1024);
	/*
	 * Change the state of OK button to enter the Default State
	 */
	g_OK = TRUE;
	/*
	 * Return the cursor to the initial position in default state
	 */
	g_cursorPosition = INITIAL_POSITION;


}
/***************************************************************************************************
 * [Function Name]: UP_FUNC
 *
 * [Description]:  Call back function of Interrupt 2 which responsible for UP button
 *
 * [Args]:         NONE
 *
 * [In]            NONE
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void UP_Func(void)
{
	/*local variable to store the units of the hour variable*/
	sint8 up_hourUnits     = INITIAL_VALUE;

	/*local variable to store the tens of the hour variable*/
	sint8 up_hourTens      = INITIAL_VALUE;

	/*local variable to store the units of the minutes variable*/
	sint8 up_minutesUnits  = INITIAL_VALUE;

	/*local variable to store the tens of the minutes variable*/
	sint8 up_minutesTens   = INITIAL_VALUE;

	/*local variable to store the units of the seconds variable*/
	sint8 up_secondsUnits  = INITIAL_VALUE;

	/*local variable to store the tens of the seconds variable*/
	sint8 up_secondsTens   = INITIAL_VALUE;
	/**************************************************************************
	 *                     Handle hours digit Increasing                      *
	 **************************************************************************/
	if(g_cursorPosition == (HOUR_TENS_COLUMN + 1) )
	{
		/*Store the tens of the hour in the variable*/
		up_hourTens = TENS(g_hours);

		/*Increase the stored value by one only as this is one press*/
		up_hourTens++;

		/*Condition to prevent the value of tens from increasing if it
		 * reached the maximum value*/
		if(up_hourTens == MAXIMUM_HOURS_TENS_UP)
		{
			/*if it reached the maximum value of tens return the value to initial value*/
			up_hourTens = INITIAL_VALUE;
		}

		/*Overwrite the new value of the hours on the g_hour variable*/
		g_hours = ( MULTIPLY_BY_TEN(up_hourTens) + UNITS(g_hours) );
	}
	else if(g_cursorPosition == (HOUR_UNITS_COLUMN + 1) )
	{
		/*Store the units of the hour in the variable*/
		up_hourUnits = UNITS(g_hours);

		/*Increase the stored value by one only as this is one press*/
		up_hourUnits++;

		/*Increase the stored value by one only as this is one press*/

		/*Condition to prevent the value of units from increasing if it
		 * reached the maximum value*/
		if(up_hourUnits == MAXIMUM_HOURS_UNITS_UP)
		{
			/*if it reached the maximum value of units return the value to initial value*/
			up_hourUnits = INITIAL_VALUE;
		}

		/*Overwrite the new value of the hours on the g_hour variable*/
		g_hours = ( ( MULTIPLY_BY_TEN(TENS(g_hours) ) ) + up_hourUnits);
	}
	/**************************************************************************
	 *                   Handle Minutes digit Increasing                      *
	 **************************************************************************/
	else if(g_cursorPosition == (MINUTES_TENS_COLUMN + 1))
	{
		/*Store the tens of the minutes in the variable*/
		up_minutesTens = TENS(g_minutes);

		/*Increase the stored value by one only as this is one press*/
		up_minutesTens++;

		/*Condition to prevent the value of tens from increasing if it
		 * reached the maximum value*/
		if(up_minutesTens == MAXIMUM_MINUTES_TENS_UP)
		{
			/*if it reached the maximum value of tens return the value to initial value*/
			up_minutesTens = INITIAL_VALUE;
		}

		/*Overwrite the new value of the hours on the g_minutes variable*/
		g_minutes = ( MULTIPLY_BY_TEN(up_minutesTens) + UNITS(g_minutes) );

	}
	else if(g_cursorPosition == (MINUTES_UNITS_COLUMN + 1))
	{
		/*Store the units of the minutes in the variable*/
		up_minutesUnits = UNITS(g_minutes);

		/*Increase the stored value by one only as this is one press*/
		up_minutesUnits++;

		/*Condition to prevent the value of units from increasing if it
		 * reached the maximum value*/
		if(up_minutesUnits == MAXIMUM_MINUTES_UNITS_UP)
		{
			/*if it reached the maximum value of units return the value to initial value*/
			up_minutesUnits = INITIAL_VALUE;
		}
		/*Overwrite the new value of the hours on the g_minutes variable*/
		g_minutes = ( ( MULTIPLY_BY_TEN(TENS(g_minutes))) + up_minutesUnits);
	}
	/**************************************************************************
	 *                     Handle Seconds digit Increasing                    *
	 **************************************************************************/
	else if (g_cursorPosition == (SECONDS_TENS_COLUMN + 1))
	{
		/*Store the units of the seconds in the variable*/
		up_secondsTens = TENS(g_seconds);

		/*Increase the stored value by one only as this is one press*/
		up_secondsTens++;

		/*Condition to prevent the value of tens from increasing if it
		 * reached the maximum value*/
		if(up_secondsTens == MAXIMUM_SECONDS_TENS_UP)
		{
			/*if it reached the maximum value of tens return the value to initial value*/
			up_secondsTens = INITIAL_VALUE;
		}

		/*Overwrite the new value of the hours on the g_seconds variable*/
		g_seconds = ( (MULTIPLY_BY_TEN(up_secondsTens)) + (UNITS(g_seconds)) );

	}
	else if(g_cursorPosition == (SECONDS_UNITS_COLUMN + 1))
	{
		/*Store the units of the seconds in the variable*/
		up_secondsUnits = UNITS(g_seconds);

		/*Increase the stored value by one only as this is one press*/
		up_secondsUnits++;

		/*Condition to prevent the value of units from increasing if it
		 * reached the maximum value*/
		if(up_secondsUnits == MAXIMUM_SECONDS_UNITS_UP)
		{
			/*if it reached the maximum value of tens return the value to initial value*/
			up_secondsUnits = INITIAL_VALUE;
		}
		/*Overwrite the new value of the hours on the g_seconds variable*/
		g_seconds = ( ( MULTIPLY_BY_TEN(TENS(g_seconds))) + up_secondsUnits);
	}
}
/***************************************************************************************************
 * [Function Name]: down_Func
 *
 * [Description]:  Call back function of Timer
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
void down_Func(void)
{
	/*local variable to store the units of the hour variable*/
	sint8 down_hourUnits     = INITIAL_VALUE;

	/*local variable to store the tens of the hour variable*/
	sint8 down_hourTens      = INITIAL_VALUE;

	/*local variable to store the units of the minutes variable*/
	sint8 down_minutesUnits  = INITIAL_VALUE;

	/*local variable to store the tens of the minutes variable*/
	sint8 down_minutesTens   = INITIAL_VALUE;

	/*local variable to store the units of the seconds variable*/
	sint8 down_secondsUnits  = INITIAL_VALUE;

	/*local variable to store the tens of the seconds variable*/
	sint8 down_secondsTens   = INITIAL_VALUE;
	/**************************************************************************
	 *                     Handle hours digit decreasing                      *
	 **************************************************************************/
	if(g_cursorPosition == (HOUR_TENS_COLUMN + 1))
	{
		/*Store the tens of the hours in the variable*/
		down_hourTens = TENS(g_hours);

		/*decrease the stored value by one only as this is one press*/
		down_hourTens--;

		/*Condition to prevent the value of tens from decreasing if it
	     * reached the initial value*/
		if(down_hourTens <= INITIAL_VALUE)
		{
			/*if it reached the initial value of tens, maintain the value to initial value*/
			down_hourTens = INITIAL_VALUE;
		}

		/*Overwrite the new value of the hours on the g_hours variable*/
		g_hours = ( MULTIPLY_BY_TEN(down_hourTens) + UNITS(g_hours) );
	}
	else if(g_cursorPosition == (HOUR_UNITS_COLUMN + 1) )
	{
		/*Store the units of the hours in the variable*/
		down_hourUnits = UNITS(g_hours);

		/*decrease the stored value by one only as this is one press*/
		down_hourUnits--;

		/*Condition to prevent the value of units from decreasing if it
	     * reached the initial value*/
		if(down_hourUnits <= INITIAL_VALUE)
		{
			/*if it reached the initial value of units, maintain the value to initial value*/
			down_hourUnits = INITIAL_VALUE;
		}

		/*Overwrite the new value of the hours on the g_hours variable*/
		g_hours = (  MULTIPLY_BY_TEN(TENS(g_hours)) + down_hourUnits);
	}
	/**************************************************************************
	 *                     Handle Minutes digit decreasing                     *
	 **************************************************************************/
	else if(g_cursorPosition == (MINUTES_TENS_COLUMN + 1))
	{
		/*Store the tens of the minutes in the variable*/
		down_minutesTens = TENS(g_minutes);

		/*decrease the stored value by one only as this is one press*/
		down_minutesTens--;

		/*Condition to prevent the value of tens from decreasing if it
	     * reached the initial value*/
		if(down_minutesTens <= INITIAL_VALUE)
		{
			/*if it reached the initial value of tens, maintain the value to initial value*/
			down_minutesTens = INITIAL_VALUE;
		}

		/*Overwrite the new value of the minutes on the g_minutes variable*/
		g_minutes = ( MULTIPLY_BY_TEN(down_minutesTens) + UNITS(g_minutes) );
	}
	else if(g_cursorPosition == (MINUTES_UNITS_COLUMN + 1) )
	{
		/*Store the units of the minutes in the variable*/
		down_minutesUnits = UNITS(g_minutes);

		/*decrease the stored value by one only as this is one press*/
		down_minutesUnits--;

		/*Condition to prevent the value of units from decreasing if it
	     * reached the initial value*/
		if(down_minutesUnits <= INITIAL_VALUE)
		{
			/*if it reached the initial value of units, maintain the value to initial value*/
			down_minutesUnits = INITIAL_VALUE;
		}
		/*Overwrite the new value of the minutes on the g_minutes variable*/
		g_minutes = ( MULTIPLY_BY_TEN(TENS(g_minutes)) + down_minutesUnits);
	}
	/**************************************************************************
	 *                     Handle Seconds digit decreasing                     *
	 **************************************************************************/
	else if (g_cursorPosition == (SECONDS_TENS_COLUMN + 1))
	{
		/*Store the tens of the seconds in the variable*/
		down_secondsTens = TENS(g_seconds);

		/*decrease the stored value by one only as this is one press*/
		down_secondsTens--;

		/*Condition to prevent the value of tens from decreasing if it
	     * reached the initial value*/
		if(down_secondsTens <= INITIAL_VALUE)
		{
			/*if it reached the initial value of units, maintain the value to initial value*/
			down_secondsTens = INITIAL_VALUE;
		}

		/*Overwrite the new value of the seconds on the g_seconds variable*/
		g_seconds = ( MULTIPLY_BY_TEN(down_secondsTens) + UNITS(g_seconds) );
	}
	else if(g_cursorPosition == (SECONDS_UNITS_COLUMN + 1) )
	{
		/*Store the units of the seconds in the variable*/
		down_secondsUnits = UNITS(g_seconds);

		/*decrease the stored value by one only as this is one press*/
		down_secondsUnits--;

		/*Condition to prevent the value of units from decreasing if it
	     * reached the initial value*/
		if(down_secondsUnits <= INITIAL_VALUE)
		{
			/*if it reached the initial value of units, maintain the value to initial value*/
			down_secondsUnits = INITIAL_VALUE;
		}
		/*Overwrite the new value of the seconds on the g_seconds variable*/
		g_seconds = ( MULTIPLY_BY_TEN(TENS(g_seconds)) + down_secondsUnits);
	}
}
/**************************************************************************************/


