#include "address_map_arm.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

volatile int *buttons = (int*)KEY_BASE;
volatile int *timer_ptr = (int *)HPS_TIMER0_BASE;
int ms1, ms2, s1, s2, m1, m2 = 0;
int running = 0;
volatile int DELAY_LENGTH = 700000;
volatile int * Hex_ptr = (int*)HEX3_HEX0_BASE;
volatile int * Hex_ptr2 = (int*)HEX5_HEX4_BASE ;
volatile int* led = (int*)LED_BASE;

void config_HPS_timer()
{
	*(timer_ptr + 2) &= 0x000; 
	int counter = 0b1000000; 
	*(timer_ptr) = counter; 
	*(timer_ptr + 2) = 0b011;
}

int RandSensor(){
		
		time_t t;
		srand((unsigned)time(&t));
		
		return rand() % 255;
	
}

void ReadHumidity(){
	
	int RH = RandSensor();
	
			
		if(RH < 60){
			*(Hex_ptr2) = 0x383F;
		}
		else{
			*(Hex_ptr2) = 0x7D3F;
		}
            
		
	}

void LEDtemp()
{
	int RH = RandSensor();
			if(RH < 10){
			*led = 0x00;
		}
		else if(RH >= 10 && RH < 19){
			*led = 0x01;
		}
		else if(RH >= 19 && RH < 39){
			*led = 0x03;
		}
		else if(RH >= 39 && RH < 59){
			*led = 0x07;
		}
		else if(RH >= 59 && RH < 79){
			*led = 0x0F;
		}
		else if(RH >= 79 && RH < 99){
			*led = 0x1F;
		}
		else if(RH >= 99 && RH < 119){
			*led = 0x3F;
		}
		else if(RH >= 119 && RH < 139){
			*led = 0x7F;
		}
		else if(RH >= 139 && RH < 159){
			*led = 0xFF;
		}
		else if(RH >= 159){
			*led = 0x1FF;
		}
}	
	
void readWater()
{
	int val = RandSensor();
	if (val <= 10)
		{
			*(Hex_ptr) = 0x383F;
		}
		else
		{
			*(Hex_ptr) = 0x7D3F;
		}
	
}


int main(void){
int count = 0;
int delay_count;
*(timer_ptr + 2) = 0b000;
//int runTime = 1000000;
*(timer_ptr + 2) = 0b011;
	while (1)
	{
		
		if (*buttons == 0b0001){running = 1;}
		while (running)
		{
			config_HPS_timer();
			while(*(timer_ptr) == 0)
			{
				if((*(timer_ptr) &= 0b1) == 1){
					count++;
					if(count == 100){

						count = 0;
					}
				}
			}
			readWater();
			ReadHumidity();
			LEDtemp();
		}			
	}
}

