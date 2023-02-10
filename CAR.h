 /******************************************************************************
 *
 * Module: CAR Header File
 *
 * File Name: CAR.h
 *
 * Description: Header File for CAR
 *
 * Author: Abdelaziz Mohammad
 *
 *******************************************************************************/

#ifndef _CAR_H_
#define _CAR_H_

/*******************************************************************************
*                                   Includes                                   *
*******************************************************************************/
#include "common_macros.h"
#include "std_types.h"

/*******************************************************************************
*                                 Definitions                                  *
*******************************************************************************/
#define CAR_IN1 0
#define CAR_IN2 1
#define CAR_IN3 2
#define CAR_IN4 3
#define CAR_EN1 4
#define CAR_EN2 5

/*******************************************************************************
*                            User-Defined Data Types                           *
*******************************************************************************/
/*******************************************************************************
* Name: CAR_Direction
* Type: Enumeration
* Range: Forward
*        Backward
*        Rigth
*        Left
* Description: Data Type for the Direction of the car
********************************************************************************/
typedef enum {

    Car_Forward,
    Car_Backward,
    Car_Right,
    Car_Left,
    Car_Stop

}CAR_Direction;

/*******************************************************************************
*                             Functions Prototypes                             *
*******************************************************************************/
/*******************************************************************************
* Service Name: CAR_Init
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initialize the CAR module.
********************************************************************************/
void CAR_Init(void);

/*******************************************************************************
* Service Name: CAR_Init
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): CAR_Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Moves the Car into a certain.
********************************************************************************/
void CAR_MOVE(CAR_Direction direction);

#endif