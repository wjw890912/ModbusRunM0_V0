/*
 * FreeModbus Libary: NUC442 Port
 * Copyright (C) 2013 Armink <armink.ztl@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: portserial.c,v 1.60 2013/08/13 15:07:05 Armink $
 */

#include "port.h"
/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
#include "M051Series.h"
/* ----------------------- static functions ---------------------------------*/
static void prvvUARTTxReadyISR(void);
static void prvvUARTRxISR(void);
/* ----------------------- Start implementation -----------------------------*/

void vMBPortSerialEnable(BOOL xRxEnable, BOOL xTxEnable)
{
	if (xRxEnable) //¿ªÆô»òÕß¹Ø±Õ½ÓÊÕÖÐ¶Ï
	{
	    
		SLAVE_RS485_RECEIVE_MODE;
//	UART_EnableInt(UART3, UART_INTEN_RDAIEN_Msk);
  	//	Sysdelay(1);//1ms
	 UART_ENABLE_INT(UART0, UART_IER_RDA_IEN_Msk); //½ÓÊÕÖÐ¶Ï´ò¿ª
	}
	else
	{
	
	   SLAVE_RS485_SEND_MODE;	
//	UART_DisableInt(UART3, UART_INTEN_RDAIEN_Msk);
      UART_DISABLE_INT(UART0, UART_IER_RDA_IEN_Msk); //½ÓÊÕÖÐ¶Ï¹Ø±Õ
	//	  Sysdelay(1);//1ms

	}
	if (xTxEnable)	//¿ªÆô»òÕß¹Ø±Õ·¢ËÍÖÐ¶Ï
	{

//	UART_EnableInt(UART3,  UART_INTEN_THREIEN_Msk);
   UART_ENABLE_INT(UART0, UART_IER_THRE_IEN_Msk);//·¢ËÍ¿ÕÖÐ¶Ï¿ªÆô

	}
	else
	{
	
   UART_DISABLE_INT(UART0, UART_IER_THRE_IEN_Msk);//·¢ËÍ¿ÕÖÐ¶Ï¹Ø±Õ
  //UART_DisableInt(UART3, UART_INTEN_THREIEN_Msk);

	}
}


  	
    
void vMBPortClose(void)
{



}
//Ä¬ÈÏÒ»¸ö´Ó»ú ´®¿Ú1 ²¨ÌØÂÊ¿ÉÉèÖÃ  ÆæÅ¼¼ìÑé¿ÉÉèÖÃ
BOOL xMBPortSerialInit(UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits,
		eMBParity eParity)
{


		 /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
     SYS_ResetModule(UART0_RST);
	CLK_SetModuleClock(UART0_MODULE , CLK_CLKSEL1_UART_S_HIRC, CLK_CLKDIV_UART(1));
	CLK_EnableModuleClock(UART0_MODULE);
    //Configure UART0 and set UART0 Baudrate 
    UART_Open(UART0, ulBaudRate);
		//UART_EnableInt(UART0, UART_ISR_RDA_IF_Msk);
	


		 /* Enable IP clock */
   // CLK_EnableModuleClock(UART3_MODULE);
    /* Select IP clock source */
   // CLK_SetModuleClock(UART3_MODULE, CLK_CLKSEL1_UARTSEL_HIRC , CLK_CLKDIV0_UART(1));
   /* Set GPD multi-function pins for UART3 RXD and TXD */
  //  SYS->GPD_MFPL |= SYS_GPD_MFPL_PD4MFP_UART3_RXD | SYS_GPD_MFPL_PD5MFP_UART3_TXD  ;
//	GPIO_SetMode(PD, 5, GPIO_MODE_OUTPUT);
//	GPIO_SetMode(PD, 4, GPIO_MODE_INPUT);
  //  UART_Open(UART3, ulBaudRate);
 //   UART_DisableFlowCtrl(UART3);
//	UART_SetLine_Config(UART3, ulBaudRate, UART_WORD_LEN_8,UART_PARITY_NONE,UART_STOP_BIT_1);
	  	
	//ÅäÖÃ485·¢ËÍºÍ½ÓÊÕÄ£Ê½
//    TODO   ÔÝÊ±ÏÈÐ´B13 µÈÖ®ºó×éÍø²âÊÔÊ±ÔÙÐÞ¸Ä
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);

	ENTER_CRITICAL_SECTION(); //¹ØÈ«¾ÖÖÐ¶Ï

	  	UART_ENABLE_INT(UART0, UART_IER_RDA_IEN_Msk); //½ÓÊÕÖÐ¶Ï
	//	UART_ENABLE_INT(UART0, UART_IER_THRE_IEN_Msk);//·¢ËÍ¿ÕÖÐ¶Ï
		
		NVIC_SetPriority(UART0_IRQn, 2 );
	    NVIC_EnableIRQ(UART0_IRQn);



  //	UART_EnableInt(UART3, UART_INTEN_RDAIEN_Msk );
//	NVIC_SetPriority(UART3_IRQn, 2 );
  // 	NVIC_EnableIRQ(UART3_IRQn);	
	EXIT_CRITICAL_SECTION(); //¿ªÈ«¾ÖÖÐ¶Ï		 
	return TRUE;
}

BOOL xMBPortSerialPutByte(CHAR ucByte)//Ð´Ò»¸ö×Ö½Úµ½Ó²¼þ
{

	UART_WRITE(UART0, ucByte);

	return TRUE;
}

BOOL xMBPortSerialGetByte(CHAR * pucByte) //¶ÁÒ»¸ö×Ô¼º´ÓÓ²¼þ
{	   
	*pucByte = UART_READ(UART0);
	return TRUE;
}

/* 
 * Create an interrupt handler for the transmit buffer empty interrupt
 * (or an equivalent) for your target processor. This function should then
 * call pxMBFrameCBTransmitterEmpty( ) which tells the protocol stack that
 * a new character can be sent. The protocol stack will then call 
 * xMBPortSerialPutByte( ) to send the character.
 */
void prvvUARTTxReadyISR(void)
{
	pxMBFrameCBTransmitterEmpty();
}

/* 
 * Create an interrupt handler for the receive interrupt for your target
 * processor. This function should then call pxMBFrameCBByteReceived( ). The
 * protocol stack will then call xMBPortSerialGetByte( ) to retrieve the
 * character.
 */
void prvvUARTRxISR(void)
{
	pxMBFrameCBByteReceived();
}



/*******************************************************************************
 * Function Name  : USART1_IRQHandler
 * Description    : This function handles USART1 global interrupt request.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/


void UART0_IRQHandler(void)
{
    
	   
	if(UART_IS_RX_READY(UART0))
	 {
//			Ï
	prvvUARTRxISR();
//
	
     }
	 else
	 if(UART_IS_TX_EMPTY(UART0))
	 
	  {
	  	prvvUARTTxReadyISR();
	   
	 }
	 else
	 {
	 
	   //do nothing ....
	 }	  
	
}	
