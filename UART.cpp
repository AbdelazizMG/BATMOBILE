/******************************************************************************
*  Module:    UART
*  File name: UART.h
*  Created on: Oct 10, 2021
*  Author: Abdelaziz Mohammad
*******************************************************************************/
/*******************************************************************************
*                                                                              *
*                                  INCLUDES                                    *
*                                                                              *
********************************************************************************/
#include "UART.h"
#include "std_types.h"
#include "avr/io.h"
#include "common_macros.h"
/*******************************************************************************
*                                                                              *
*                                  Global Variables                            *
*                                                                              *
********************************************************************************/
 uint16 g_UBRR_value = 0;
 uint8  g_speed_mode_division_factor = 0;
 /*******************************************************************************
 *                                                                              *
 *                          Interrupt Service Routine                           *
 *                                                                              *
 ********************************************************************************/

/*******************************************************************************
*                                                                              *
*                              FUNCTIONS Definitions                           *
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
void UART_Init(const UART_ConfigType * Config_Ptr)
{

    
	/*Config Operation Mode*/
    switch( Config_Ptr ->operation_mode)
    {
      case Receiver:                SET_BIT(UCSR0B,RXEN0);
                                    CLEAR_BIT(UCSR0B,TXEN0);
    	                               break;

      case Transmitter:             SET_BIT(UCSR0B,TXEN0);
                                    CLEAR_BIT(UCSR0B,RXEN0);
    	                               break;
      case Transmitter_Receiver:    SET_BIT(UCSR0B,RXEN0);
                                    SET_BIT(UCSR0B,TXEN0);
                                    
    	                               break;
    }

	/*Config Synchronization of UART*/
	switch ( Config_Ptr->synchronization)
	{
	 case Asynchronous: CLEAR_BIT(UCSR0C,UMSEL01);
	                    CLEAR_BIT(UCSR0C,UMSEL00);
                      
		                break;
	 case Synchronous:  SET_BIT(UCSR0C,UMSEL00);
	                    CLEAR_BIT(UCSR0C,UMSEL01);
	 		            break;
	}

	/*Config Parity Bit of UART*/
	switch ( Config_Ptr ->parity)
	{
	  case Parity_Disabled:
		                    CLEAR_BIT(UCSR0C,UPM00);
	                      CLEAR_BIT(UCSR0C,UPM01);
                        
	                        break;
	  case Parity_Odd:
		                    SET_BIT(UCSR0C,UPM00);
                        SET_BIT(UCSR0C,UPM01);
                            break;
	  case Parity_Even:
		                    CLEAR_BIT(UCSR0C,UPM00);
                        SET_BIT(UCSR0C,UPM01);
                            break;
	}

	/*Config Number of Stop Bits of UART*/
    switch( Config_Ptr ->stop_bit)
    {
    case StopBit_1:  CLEAR_BIT(UCSR0C,USBS0);
    	             break;
    case StopBit_2:  SET_BIT(UCSR0C,USBS0);
    	             break;
    }

    /*Config Number of Data Frame Bits*/
    switch ( Config_Ptr ->dataframe_bits )
    {
    case DataFrame_5Bits:  CLEAR_BIT(UCSR0C,UCSZ00);
                           CLEAR_BIT(UCSR0C,UCSZ01);
                           CLEAR_BIT(UCSR0B,UCSZ02);
    	                   break;
    case DataFrame_6Bits:  SET_BIT(UCSR0C,UCSZ00);
                           CLEAR_BIT(UCSR0C,UCSZ01);
                           CLEAR_BIT(UCSR0B,UCSZ02);
    	                   break;
    case DataFrame_7Bits:  CLEAR_BIT(UCSR0C,UCSZ00);
                           SET_BIT(UCSR0C,UCSZ01);
                           CLEAR_BIT(UCSR0B,UCSZ02);
    	                   break;
    case DataFrame_8Bits:  SET_BIT(UCSR0C,UCSZ00);
                           SET_BIT(UCSR0C,UCSZ01);
                           CLEAR_BIT(UCSR0B,UCSZ02);
    	                   break;
    case DataFrame_9Bits:  SET_BIT(UCSR0C,UCSZ00);
                           SET_BIT(UCSR0C,UCSZ01);
                           SET_BIT(UCSR0B,UCSZ02);
    	                   break;
    }


    switch( Config_Ptr ->baud_rate)
    {
    case BaudRate_9600:   /*For 1 MHz  value = 12 , For 8MHz value = 103*/
    	                  UBRR0H = (uint8)9600>>8;
                           UBRR0L = (uint8)9600;
    	                  break;
    	                  /*There is a bug in the equation shown blow */
    case BaudRate_14400:   UBRR0H = (uint8)14400>>8;
                           UBRR0L = (uint8)14400;
    	                  break;
    case BaudRate_19200:   UBRR0H = (uint8)19200>>8;
                           UBRR0L = (uint8)19200;
    	                  break;
    case BaudRate_115200: UBRR0H = (uint8)115200>>8;
                          UBRR0L = (uint8)115200;
    	                  break;
    }

}
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
void UART_sendByte( const uint8 data )
{
     /*Wait until Flag = 1 , etc: UDR is empty and ready to be loaded with data*/
     while (BIT_IS_CLEAR(UCSR0A,UDRE0));
     UDR0 = data;
}
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
uint8 UART_receiveByte (void)
{
	 /*Wait until Flag = 1 , etc: UDR is Loaded with received Data then return UDR*/
	  //while (BIT_IS_CLEAR(UCSR0A,RXC0));
     while( ! (UCSR0A & ( 1 << UDRE0 )));
      return UDR0;
}
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
void UART_sendString( const uint8 * Str)
{
	uint8 i = 0;

		/* Send the whole string */
		while(Str[i] != '\0')
		{
			UART_sendByte(Str[i]);
			i++;
		}
}
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
void UART_receiveString (uint8 * Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_receiveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_receiveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';

}

void uart_init(void)
{
  UBRR0 = (uint8)9600;

  UCSR0A |=  ( 1 << U2X0 ) ;

  UCSR0B |= ( 1 << RXEN0) | ( 1 << TXEN0 ) ;

  UCSR0C |= ( 1 << UCSZ01 ) | ( UCSZ00 ) ;

}
