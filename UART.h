/******************************************************************************
*  Module:    UART
*  File name: UART.h
*  Created on: Oct 10, 2021
*  Author: Abdelaziz Mohammad
*******************************************************************************/

#ifndef UART_H_
#define UART_H_

/*******************************************************************************
*                                                                              *
*                                  INCLUDES                                    *
*                                                                              *
********************************************************************************/
#include "std_types.h"
/*******************************************************************************
*                                                                              *
*                                  Definitions                                 *
*                                                                              *
********************************************************************************/


/*******************************************************************************
*                                                                              *
*                       External   Global Variables                            *
*                                                                              *
********************************************************************************/
 extern uint16 g_UBRR_value;
 extern uint8  g_speed_mode_division_factor;

/*******************************************************************************
*                                                                              *
*                             User-Defined Data Types                          *
*                                                                              *
********************************************************************************/
/*******************************************************************************
* Name: Operation_Mode
* Type: Enumeration
* Range: Receiver - Transmitter - Transmitter_Receiver
* Description: Data Type for symbolic name for UART Operation Mode
********************************************************************************/
typedef enum
{
	Receiver,
	Transmitter,
	Transmitter_Receiver
}Operation_Mode;
/*******************************************************************************
* Name: Transmission_Speed
* Type: Enumeration
* Range: Normal - Double
* Description: Data Type for symbolic name for UART Transmission Speed
********************************************************************************/
typedef enum
{
	Normal_Speed,
	Double_Speed
}Transmission_Speed;
/*******************************************************************************
* Name: Synchronization
* Type: Enumeration
* Range: Asynchronous - Synchronous
* Description: Data Type for symbolic name for UART Synchronization
********************************************************************************/
typedef enum
{
	Asynchronous,
	Synchronous
}Synchronization;
/*******************************************************************************
* Name: Parity_Bit
* Type: Enumeration
* Range: Disabled - Odd - Even
* Description: Data Type for symbolic name for UART Parity Bit
********************************************************************************/
typedef enum
{
	Parity_Disabled,
	Parity_Odd,
	Parity_Even
}Parity_Bit;
/*******************************************************************************
* Name: Stop_Bit
* Type: Enumeration
* Range: StopBit_1 - StopBit_2
* Description: Data Type for symbolic name for UART Data Frame Stop Bit
********************************************************************************/
typedef enum
{
	StopBit_1,
	StopBit_2
}Stop_Bit;
/*******************************************************************************
* Name: DataFrame_Bits
* Type: Enumeration
* Range: 5 Bits : 9 Bits
* Description: Data Type for symbolic name for UART Data Frame Bits number
********************************************************************************/
typedef enum
{
	DataFrame_5Bits,
	DataFrame_6Bits,
	DataFrame_7Bits,
	DataFrame_8Bits,
	DataFrame_9Bits=7
}DataFrame_Bits;
/*******************************************************************************
* Name: Baud_Rate
* Type: Enumeration
* Range: 9600 - 14400 - 19200 -  115200
* Description: Data Type for symbolic name for UART Baud Rate
********************************************************************************/
typedef enum
{
    BaudRate_9600,
	BaudRate_14400,
	BaudRate_19200,
	BaudRate_115200,
}Baud_Rate;
/*******************************************************************************
* Name: RX_Interrupt
* Type: Enumeration
* Range: RX_InterruptDisable - RX_InterruptEnable
* Description: Data Type for symbolic name for UART RX Interrupt
********************************************************************************/
typedef enum
{
	RX_InterruptDisable,
	RX_InterruptEnable,
}RX_Interrupt;
/*******************************************************************************
* Name: TX_Interrupt
* Type: Enumeration
* Range: TX_InterruptDisable - TX_InterruptEnable
* Description: Data Type for symbolic name for UART TX Interrupt
********************************************************************************/
typedef enum
{
	TX_InterruptDisable,
	TX_InterruptEnable,
}TX_Interrupt;
/*******************************************************************************
* Name: UART_ConfigType
* Type: Structure
* Range: Hardware dependent structure
* Description: Type of the external data structure containing the initialization
*              data for this module. This is the one that is sent to the init
*              function.
********************************************************************************/
typedef struct
{
	Operation_Mode operation_mode;
	Transmission_Speed speed;
	Synchronization  synchronization;
	Parity_Bit parity;
	Stop_Bit stop_bit;
	DataFrame_Bits dataframe_bits;
	Baud_Rate baud_rate;
	RX_Interrupt rx_interrupt;
	TX_Interrupt tx_interrupt;
}UART_ConfigType;
/*******************************************************************************
*                                                                              *
*                                  FUNCTIONS PROTOTYPE                         *
*                                                                              *
********************************************************************************/
/*******************************************************************************
* Service Name:       UART_Init
* Sync/Async:         Synchronous
* Reentrancy:         Non Reentrant
* Parameters (in):    configurations - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Initialize the UART module.
********************************************************************************/
void UART_Init(const UART_ConfigType * Config_Ptr);
/*******************************************************************************
* Service Name:       UART_sendByte
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    Data to be sent
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Send a Byte to other devices.
********************************************************************************/
void UART_sendByte(const uint8 data );
/*******************************************************************************
* Service Name:       UART_receiveByte
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       uint8
* Description:        receive a Byte from other devices
********************************************************************************/
uint8 UART_receiveByte (void);
/*******************************************************************************
* Service Name:       UART_sendString
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    String to be sent
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description:        Send a String to other devices.
********************************************************************************/
void UART_sendString( const uint8 * Str);
/*******************************************************************************
* Service Name:       UART_receiveString
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       uint8
* Description:        receive a stringfrom other devices
********************************************************************************/
void UART_receiveString (uint8 *Str);

void uart_init(void);
#endif /* UART_H_ */
