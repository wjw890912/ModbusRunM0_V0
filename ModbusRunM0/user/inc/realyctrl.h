

#ifndef	REALYCTRL_H
#define REALYCTRL_H

#include "M051Series.h"
#include "port.h"
#include "user_mb_app.h"
/*The realy channel numbers that maxmum is 24 channel*/
typedef enum Channel
{


	   CH1=0,
	   CH2,
	   CH3,
	   CH4,
	   CH5,
	   CH6,
	   CH7,
	   CH8,
	   CH9,
	   CH10,
	   CH11,
	   CH12,
	   CH13,
	   CH14,
	   CH15,
	   CH16,
	   CH17,
	   CH18,
	   CH19,
	   CH20,
	   CH21,
	   CH22,
	   CH23,
	   CH24
}Channel_Type;

typedef enum Status_Realy
{

	  OPEN=1,
	  CLOSE
	  
}Status_Type;










/*
继电器的路数
支持 4路、8路、12路、16路、24路
目前只做4路
*/
#define REALY_NUM    				4
/*

#define GTLCS207_ER4GS_V1  使用PCB板为比特开发的 GTLCS207-ER4GS MB V1  的4路磁保持继电器驱动

*/
//#define GTLCS207_ER4GS_V1
#define GTRMS107_ER4AS_V10
void HWRealyInit(void);
void RealyCtrl(Channel_Type Channel,Status_Type status);
void RealyPoll(void);
void KeyPool(void);
uint8_t GetHwAddrIint(void);




 /*dever*/
#ifdef  GTLCS207_ER4GS_V1
#define  CH1_OPEN  			      \
do{P12=1;DrvSYS_Delay(80000);P12=0;}while(0) 
#define  CH1_CLOSE 				  \
do{P13=1;DrvSYS_Delay(80000);P13=0;}while(0)
#define  CH2_OPEN  				  \
do{P10=1;DrvSYS_Delay(80000);P10=0;}while(0)
#define  CH2_CLOSE 				  \
do{P11=1;DrvSYS_Delay(80000);P11=0;}while(0)
#define  CH3_OPEN  				  \
do{P01=1;DrvSYS_Delay(80000);P01=0;}while(0)
#define  CH3_CLOSE 				  \
do{P00=1;DrvSYS_Delay(80000);P00=0;}while(0)
#define  CH4_OPEN  				  \
do{P03=1;DrvSYS_Delay(80000);P03=0;}while(0)
#define  CH4_CLOSE 				  \
do{P02=1;DrvSYS_Delay(80000);P02=0;}while(0)
 /*LED indicate*/
#define  CH1_LED  P05
#define  CH2_LED  P04
#define  CH3_LED  P06
#define  CH4_LED  P07
#endif


/* Dever */
#ifdef  GTRMS107_ER4AS_V10
#define  CH1_OPEN  			      \
do{P23=1;}while(0) 
#define  CH1_CLOSE 				  \
do{P23=0;}while(0)
#define  CH2_OPEN  				  \
do{P22=1;}while(0)
#define  CH2_CLOSE 				  \
do{P22=0;}while(0)
#define  CH3_OPEN  				  \
do{P21=1;}while(0)
#define  CH3_CLOSE 				  \
do{P21=0;}while(0)
#define  CH4_OPEN  				  \
do{P20=1;}while(0)
#define  CH4_CLOSE 				  \
do{P20=0;}while(0)

 /*
    LED indicate
 	No need
 */
#define  CH1_LED  		0
#define  CH2_LED  		0
#define  CH3_LED  		0
#define  CH4_LED  		0
#endif







#endif
