/**********************************************************************************
 * [FILE NAME]: External_Interrupt_interface.h
 *
 * [AUTHOR]: Toka Zakaria Mohamed Ramadan
 *
 * [DATE CREATED]: Sep 6, 2021
 *
 * [Description]: File of All types Declaration and Functions prototypes of external
 *                 interrupt configuration.
 *
 ***********************************************************************************/
#ifndef EXTERNAL_INTERRUPT_INTERFACE_H_
#define EXTERNAL_INTERRUPT_INTERFACE_H_

#include"External_Interrupt_private.h"
#include<avr/io.h>


#define INTERNAL_PULL_UP_INT0                  TRUE
#define INTERNAL_PULL_UP_INT1                  TRUE
#define INTERNAL_PULL_UP_INT2                  TRUE

#define INTERRUPT1_SENSE_CONTROL_BITS_SHIFT_VALUE    2


#define MCU_CONTROL_REGISTER                    MCUCR_REG
#define MCU_CONTROL_AND_STATUS_REGISTER         MCUCSR_REG
#define GENERAL_INTERRUPT_CONTROL_REGISTER      GICR_REG
#define GENERAL_INTERRUPT_FLAG_REGISTER         GIFR_REG

#define INTERRUPT_SENSE_CONTROL_0_BIT_0         ISC00_BIT
#define INTERRUPT_SENSE_CONTROL_0_BIT_1         ISC01_BIT
#define INTERRUPT_SENSE_CONTROL_1_BIT_0         ISC10_BIT
#define INTERRUPT_SENSE_CONTROL_1_BIT_1         ISC11_BIT
#define INTERRUPT_SENSE_CONTROL_2               ISC2_BIT

#define EXTERNAL_INTERRUPT_FLAG_0               INTF0_BIT
#define EXTERNAL_INTERRUPT_FLAG_1               INTF1_BIT
#define EXTERNAL_INTERRUPT_FLAG_2               INTF2_BIT

#define EXTRNAL_INTERRUPT0_ENABL_BIT            INT0_BIT
#define EXTRNAL_INTERRUPT1_ENABL_BIT            INT1_BIT
#define EXTRNAL_INTERRUPT2_ENABL_BIT            INT2_BIT


#define INTERRUPT0_DIRECTION_PORT              DDRD
#define INTERRUPT1_DIRECTION_PORT              DDRD
#define INTERRUPT2_DIRECTION_PORT              DDRB

#define INTERRUPT0_DATA_PORT                   PORTD
#define INTERRUPT1_DATA_PORT                   PORTD
#define INTERRUPT2_DATA_PORT                   PORTB

#define INTERRUPT0_PIN                         PD2
#define INTERRUPT1_PIN                         PD3
#define INTERRUPT2_PIN                         PB2


/**************************************************************************
 *                            Interrupt0                                  *
 * ************************************************************************/
typedef enum
{

INT0_Low_level, INT0_Any_logical, INT0_Falling, INT0_Raising

}Interrupt0_senseControl;

/**************************************************************************
 *                            Interrupt1                                  *
 * ************************************************************************/
typedef enum
{

INT1_Low_level, INT1_Any_logical, INT1_Falling, INT1_Raising

}Interrupt1_senseControl;

/**************************************************************************
 *                            Interrupt2                                  *
 * ************************************************************************/
typedef enum
{

INT2_Low_level, INT2_Any_logical, INT2_Falling, INT2_Raising

}Interrupt2_senseControl;


/**************************************************************************
 *                            Interrupt0                                  *
 * ************************************************************************/
typedef struct
{
	Interrupt0_senseControl INT0_senseControl;

}INT0_ConfigType;

/**************************************************************************
 *                            Interrupt1                                  *
 * ************************************************************************/
typedef struct
{
	Interrupt1_senseControl INT1_senseControl;

}INT1_ConfigType;
/**************************************************************************
 *                            Interrupt2                                  *
 * ************************************************************************/
typedef struct
{
	Interrupt2_senseControl INT2_senseControl;

}INT2_ConfigType;
/***************************************************************************************************
 * [Function Name]: INT0_Init
 *
 * [Description]:  Function to Initialize External Interrupt Driver
 *                 - Working in Interrupt Mode
 *                 - Choose External interrupt control edge
 *
 * [Args]:         INT0_config_PTR
 *
 * [In]            INT0_config_PTR: Pointer to Timer Configuration Structure
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void INT0_Init(const INT0_ConfigType * INT0_config_PTR);
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
void INT1_Init(const INT1_ConfigType * INT1_config_PTR);
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
void INT2_Init(const INT2_ConfigType * INT2_config_PTR);
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
void INT0_setCallBack(void(*INT0_ptr)(void));
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
void INT1_setCallBack(void(*INT1_ptr)(void));
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
void INT2_setCallBack(void(*INT2_ptr)(void));
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
void INT0_DeInit(void);
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
void INT1_DeInit(void);
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
void INT2_DeInit(void);
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
void INT0_changeInterrupt_senseControl(Interrupt0_senseControl INT0SenseControl);
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
void INT1_changeInterrupt_senseControl(Interrupt1_senseControl INT1SenseControl);
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
void INT2_changeInterrupt_senseControl(Interrupt2_senseControl INT2SenseControl);
/***************************************************************************************************/

#endif /* EXTERNAL_INTERRUPT_INTERFACE_H_ */
