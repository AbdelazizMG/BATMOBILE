 /******************************************************************************
 *
 * Module: CAR CPP File
 *
 * File Name: CAR.cpp
 *
 * Description: Implementation File for CAR
 *
 * Author: Abdelaziz Mohammad
 *
 *******************************************************************************/
/*******************************************************************************
*                                   Includes                                   *
*******************************************************************************/
#include "CAR.h"
#include "avr/io.h"


/*******************************************************************************
*                             Functions Body                                   *
*******************************************************************************/
/*******************************************************************************
* Service Name: CAR_Init
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initialize the CAR module by initializing the pins as output pins
*              and make the car stop at the beginning.
********************************************************************************/
void CAR_Init(void)
{
       /*Define IN1:IN4 and EN1:EN2 as output pins*/   
        SET_BIT(DDRB,CAR_IN1);
        SET_BIT(DDRB,CAR_IN2);
        SET_BIT(DDRB,CAR_IN3);
        SET_BIT(DDRB,CAR_IN4);
        SET_BIT(DDRB,CAR_EN1);
        SET_BIT(DDRB,CAR_EN2);

       /*Make the Car stop at the beginning by making both EN1 and EN2 LOW*/
        CLEAR_BIT(PORTB,CAR_EN1);
        CLEAR_BIT(PORTB,CAR_EN2);
}

/*******************************************************************************
* Service Name: CAR_Init
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): CAR_Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Moves the Car into a certain direction.
********************************************************************************/
void CAR_MOVE(CAR_Direction direction)
{
    switch ( direction )
    {
        case Car_Forward:       SET_BIT(PORTB,CAR_IN1);
                                CLEAR_BIT(PORTB,CAR_IN2);
                                SET_BIT(PORTB,CAR_EN1);

                                SET_BIT(PORTB,CAR_IN3);
                                CLEAR_BIT(PORTB,CAR_IN4);
                                SET_BIT(PORTB,CAR_EN2);                                
                                break;

        case Car_Backward:      CLEAR_BIT(PORTB,CAR_IN1);
                                SET_BIT(PORTB,CAR_IN2);
                                SET_BIT(PORTB,CAR_EN1);

                                CLEAR_BIT(PORTB,CAR_IN3);
                                SET_BIT(PORTB,CAR_IN4);
                                SET_BIT(PORTB,CAR_EN2);                                 
                                break;

        case Car_Right:         CLEAR_BIT(PORTB,CAR_IN1);
                                SET_BIT(PORTB,CAR_IN2);
                                SET_BIT(PORTB,CAR_EN1);


                                CLEAR_BIT(PORTB,CAR_EN2);
                                break;

        case Car_Left:          
                                CLEAR_BIT(PORTB,CAR_EN1);

                                CLEAR_BIT(PORTB,CAR_IN1);
                                SET_BIT(PORTB,CAR_IN2);
                                SET_BIT(PORTB,CAR_EN2);
                                
                                break;

        case Car_Stop:          
                                CLEAR_BIT(PORTB,CAR_EN1);
                                CLEAR_BIT(PORTB,CAR_EN2);
                                break; 

        default:                CLEAR_BIT(PORTB,CAR_EN1);
                                CLEAR_BIT(PORTB,CAR_EN2);
                                break;                                                                                                               
    }
}
