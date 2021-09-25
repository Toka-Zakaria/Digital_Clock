/**********************************************************************************
 * [FILE NAME]: app_file.h
 *
 * [AUTHOR]: Toka Zakaria Mohamed
 *
 * [DATE CREATED]: Sep 24, 2021
 *
 * [Description]: Header file of the Digital Clock
 ***********************************************************************************/

#ifndef APP_FILE_H_
#define APP_FILE_H_

#include"std_types.h"
#include"micro_config.h"
#include"common_macros.h"
#include"timer_interface.h"
#include"External_Interrupt_interface.h"
#include"lcd.h"

/**************************************************************************
 *                          Pre-Processor Macros                          *
 **************************************************************************/

#define TENS(VALUE)                           ((VALUE)/10)
#define UNITS(VALUE)                          ((VALUE)%10)
#define MULTIPLY_BY_TEN(VAR)                   ((VAR)*10)


#define UP_BUTTON_PORT_REG                    PORTA
#define UP_BUTTON_DIRECTION_REG               DDRA
#define UP_BUTTON_INPUT_REG                   PINA
#define UP_BUTTON_PIN                         PA0

#define DOWN_BUTTON_PORT_REG                  PORTA
#define DOWN_BUTTON_DIRECTION_REG             DDRA
#define DOWN_BUTTON_INPUT_REG                 PINA
#define DOWN_BUTTON_PIN                       PA1

#define INITIAL_COUNT                           0

#define INITIAL_VALUE                           0
#define COMPARE_VALUE                           977


#define  MAXIMUM_HOURS                         24
#define  MAXIMUM_SECONDS                       60
#define  MAXIMUM_MINUTES                       60

#define DISPLAY_CURSOR_COMMAND                0X0E
#define DISPLAY_BLINKING_CURSOR_COMMAND       0X0F

#define HIDE_CURSOR_COMMAND                   0x0C

#define DEBOUNCE_TIME                          25


#define DIGITAL_CLOCK_ROW                      0

#define HOUR_TENS_COLUMN                       4
#define HOUR_UNITS_COLUMN                      5
#define FIRST_COMMA_COLUMN                     6


#define MINUTES_TENS_COLUMN                    7
#define MINUTES_UNITS_COLUMN                   8
#define SECOND_COMMA_COLUMN                    9

#define SECONDS_TENS_COLUMN                    10
#define SECONDS_UNITS_COLUMN                   11
#define END_OF_CLOCK_COLUMN                    12
#define INITIAL_POSITION                        HOUR_TENS_COLUMN

#define MAXIMUM_HOURS_TENS_UP                   3
#define MAXIMUM_MINUTES_TENS_UP                 6
#define MAXIMUM_SECONDS_TENS_UP                 6

#define MAXIMUM_HOURS_UNITS_UP                  5
#define MAXIMUM_MINUTES_UNITS_UP                10
#define MAXIMUM_SECONDS_UNITS_UP                10

/**************************************************************************
 *                     Extern Variables                     *
 **************************************************************************/

extern uint8 g_seconds;
extern uint8 g_minutes;
extern uint8 g_hours;
extern uint8 g_tick;
extern sint8 g_cursorPosition;
extern uint8 g_OK;

/**************************************************************************
 *                           Functions Prototypes                         *
 **************************************************************************/

void down_Func(void);

void UP_Func(void);

void display(void);

void DigitalClock(void);

void tick(void);

void Right(void);

void Left(void);

void OK_FUNC(void);




#endif /* APP_FILE_H_ */
