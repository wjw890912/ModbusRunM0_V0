
#include <string.h>
#include <stdio.h>
#include "realyctrl.h"



void HWRealyInit(void)
{
  /*
  config the GPIO pin mode of output and make it push realy for Hold 
  --ref 比特电子 GTLCS207-ER4GS T1 V1 PCB and SHC */

    #ifdef  GTLCS207_ER4GS_V1
	  GPIO_SetMode(P1, BIT0|BIT1|BIT2|BIT3, GPIO_PMD_OUTPUT);//realy A	 磁保持线圈 A组
	  GPIO_SetMode(P0, BIT0|BIT1|BIT2|BIT3, GPIO_PMD_OUTPUT);//realy B   磁保持线圈 B组
	  GPIO_SetMode(P0, BIT4|BIT5|BIT6|BIT7, GPIO_PMD_OUTPUT); //led
	
	  P10=0;
	  P11=0;
	  P12=0;
	  P13=0;
	
	  P00=0;
	  P01=0;
	  P02=0;
	  P03=0;
    #endif

	#ifdef  GTRMS107_ER4AS_V10

	  GPIO_SetMode(P1, BIT4|BIT5|BIT6|BIT7, GPIO_PMD_INPUT ); //key
	  GPIO_SetMode(P2, BIT0|BIT1|BIT2|BIT3, GPIO_PMD_OUTPUT); //relay
	  P20=0;
	  P21=0;
	  P22=0;
	  P23=0;




    #endif

  

} 


void RealyCtrl(Channel_Type Channel,Status_Type status)
{


	  switch (Channel)
	  {

	  	 case CH1:
		 {
		 
		   if(status==OPEN)
		   {
		   
			   CH1_OPEN;
			   #ifndef  GTRMS107_ER4AS_V10
			   CH1_LED=0;
			   #endif

		   }
		   else
		   if(status==CLOSE)
		   {
		   	   CH1_CLOSE;
			   #ifndef  GTRMS107_ER4AS_V10
			   CH1_LED=1;
			   #endif
		   }


		 break;
		 }
	  	 case CH2:
		 {
		 	 if(status==OPEN)
		   {
		   
				 CH2_OPEN;
				 #ifndef  GTRMS107_ER4AS_V10
				 CH2_LED=0;
				 #endif
		   }
		   else
		   if(status==CLOSE)
		   {
		   
				  CH2_CLOSE;
				  #ifndef  GTRMS107_ER4AS_V10
				  CH2_LED=1;
				  #endif
		   }
		 
		 break;
		 }
		 case CH3:
		 {
		 	 if(status==OPEN)
		   {
		   
				CH3_OPEN;
				#ifndef  GTRMS107_ER4AS_V10
				CH3_LED=0;
				#endif
		   }
		   else
		   if(status==CLOSE)
		   {
		   	   CH3_CLOSE;
			   #ifndef  GTRMS107_ER4AS_V10
			   CH3_LED=1;
			   #endif
		   }


		 break;
		 }
		 case CH4:
		 {
		 	  if(status==OPEN)
		   {
		   
				CH4_OPEN;
				#ifndef  GTRMS107_ER4AS_V10
				CH4_LED=0;
				#endif

		   }
		   else
		   if(status==CLOSE)
		   {
		   		 CH4_CLOSE;
				 #ifndef  GTRMS107_ER4AS_V10
				 CH4_LED=1;
				 #endif

		   }
		 
		 break;
		 }
		 case CH5:
		 {
		 
		 
		 break;
		 }
		 case CH6:
		 {
		 
		 
		 break;
		 }
		 case CH7:
		 {
		 
		 
		 break;
		 }
		 case CH8:
		 {
		 
		 
		 
		 break;
          }

		  /*reserve9-24*/
		 case CH9:{break;}
		 case CH10:{break;}
		 case CH11:{break;}
		 case CH12:{break;}
		 case CH13:{break;}
		 case CH14:{break;}
		 case CH15:{break;}
		 case CH16:{break;}
		 case CH17:{break;}
		 case CH18:{break;}
		 case CH19:{break;}
		 case CH20:{break;}
		 case CH21:{break;}
		 case CH22:{break;}
		 case CH23:{break;}
		 case CH24:{break;}
	  
	  }




}

extern UCHAR *Slave_ucSDiscInBuf; //
extern UCHAR *Slave_ucSCoilBuf;//信号寄存器
extern USHORT  *Slave_usSRegInBuf; //输入寄存器
extern USHORT  *Slave_usSRegHoldBuf;//保持寄存器
extern USHORT   usSRegHoldBuf[S_REG_HOLDING_NREGS] ;
USHORT old[REALY_NUM]=0,new[REALY_NUM]=0;
void RealyPoll(void)
{
	char i;

	for(i=CH1;i<REALY_NUM;i++)
	{	   new[i]=	usSRegHoldBuf[i];

			if (new[i]!=old[i])
			{
				  if(new[i]==0)
				  {
				    RealyCtrl(i,CLOSE);
				  
				  }
				  else
				  if(new[i]==1)
				  {
				  	 RealyCtrl(i,OPEN);
				  }
				   old[i]=new[i];
			}

	}


}

void KeyPool(void)
{


		/*sample key data in idle*/
	usSRegHoldBuf[10] = P17;
	usSRegHoldBuf[11] = P16;
	usSRegHoldBuf[12] = P15;
	usSRegHoldBuf[13] = P14;


}
 /*
 获取从机地址
 Get the addr form hardwave switch for HEX .
 */
uint8_t GetHwAddrIint(void)
{


	  uint8_t addr[4]=0;

	  #ifdef  GTLCS207_ER4GS_V1
   /*The first our init the GPIO mode is INPUT */
 GPIO_SetMode(P2, BIT5|BIT6|BIT7, GPIO_PMD_INPUT);
 GPIO_SetMode(P4, BIT4, GPIO_PMD_INPUT);

   	addr[0]=P25;//get bit of ADDR3
	addr[1]=P26;//get bit of ADDR2
	addr[2]=P27;//get bit of ADDR1
	addr[3]=P44;//get bit of ADDR0

	addr[0]<<=3;//get bit of ADDR3
	addr[1]<<=2;//get bit of ADDR2
	addr[2]<<=1;//get bit of ADDR1
	addr[3]<<=0;//get bit of ADDR0
	#endif
	#ifdef  GTRMS107_ER4AS_V10

	 GPIO_SetMode(P0, BIT4|BIT5|BIT6|BIT7, GPIO_PMD_INPUT);
	addr[0]=P07;//get bit of ADDR3
	addr[1]=P06;//get bit of ADDR2
	addr[2]=P05;//get bit of ADDR1
	addr[3]=P04;//get bit of ADDR0

	addr[0]<<=3;//get bit of ADDR3
	addr[1]<<=2;//get bit of ADDR2
	addr[2]<<=1;//get bit of ADDR1
	addr[3]<<=0;//get bit of ADDR0

	
	
	#endif

	return (addr[0]+addr[1]+addr[2]+addr[3]);
}

