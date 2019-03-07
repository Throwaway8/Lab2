#include "address_map_arm.h"

volatile int * load_ptr = (int*)HPS_TIMER0_BASE;
volatile int * currVal_ptr = (int*)HPS_TIMER0_BASE + 1;
volatile int * ctrl_ptr = (int*)HPS_TIMER0_BASE + 2;
volatile int * endInterrupt_ptr = (int*)HPS_TIMER0_BASE + 3;
volatile int * interrupt_ptr = (int*)HPS_TIMER0_BASE + 4;
volatile int * hex_ptr = (int*)HEX3_HEX0_BASE;
volatile int * hex_ptr2 = (int*)HEX5_HEX4_BASE;
volatile int * Key_ptr = (int*)KEY_BASE;

void start()
{
	int count = 0;
	int count2 = 0;
	int count3 = 0;
	int count4 = 0;
	int count5 = 0;
	int count6 = 0;
	int lookUpTable[10];
	lookUpTable[0] = 0x3F;
	lookUpTable[1] = 0x6;
	lookUpTable[2] = 0x5B;
	lookUpTable[3] = 0x4F;
	lookUpTable[4] = 0x66;
	lookUpTable[5] = 0x6D;
	lookUpTable[6] = 0x7D;
	lookUpTable[7] = 0x7;
	lookUpTable[8] = 0x7F;
	lookUpTable[9] = 0x6F;
	*(hex_ptr) = 0x3F;
	*(hex_ptr + 1) = 0x3F;
	*(hex_ptr + 2) = 0x3F;
	*(hex_ptr + 3) = 0x3F;
	*(hex_ptr2) = 0x3F;
	*(hex_ptr2 + 1) = 0x3F;
	while (*(Key_ptr) == 0)
	{
		*(ctrl_ptr) &= 0x000;
		*(load_ptr) |= 0xF4240;
		*(ctrl_ptr) |= 0b011;
		
		*(hex_ptr) = *lookUpTable + 1;
		*(hex_ptr+1) = *lookUpTable + 1;
		*(hex_ptr + 2) = *lookUpTable + 1;
		*(hex_ptr+3) = *lookUpTable + 1;
		*(hex_ptr2) = *lookUpTable;
		*(hex_ptr2+1) = *lookUpTable + 1;
		
		
		
		if ((*(interrupt_ptr) &= 0b1) == 1)
		{
			
			count++;
			if (count == 10)
			{
				
				count = 0;
				count2++;
				if (count2 == 10)
				{
			
					count2 = 0;
					count3++;
					if (count3 == 10)
					{
						
						count3 = 0;
						count4++;
						if (count4 == 10)
						{
							
							count4 = 0;
							count5++;
							if (count5 == 10)
							{
								
								count5 = 0;
								count6++;
								if (count6 == 10)
								{
									count6 = 0;
								}
							}
						}
					}
				}
			}
		}
	}
}

void reset()
{
	int lookUpTable[10];
	lookUpTable[0] = 0x3F;
	lookUpTable[1] = 0x6;
	lookUpTable[2] = 0x5B;
	lookUpTable[3] = 0x4F;
	lookUpTable[4] = 0x66;
	lookUpTable[5] = 0x6D;
	lookUpTable[6] = 0x7D;
	lookUpTable[7] = 0x7;
	lookUpTable[8] = 0x7F;
	lookUpTable[9] = 0x6F;
	*(hex_ptr) = 0x3F;
	*(hex_ptr + 1) = 0x3F;
	*(hex_ptr + 2) = 0x3F;
	*(hex_ptr + 3) = 0x3F;
	*(hex_ptr2) = 0x3F;
	*(hex_ptr2 + 1) = 0x3F;
}

void stop()
{
	*(ctrl_ptr) &= 0x0;
}


int main(void) {


	while (1)
	{
		if ((*(Key_ptr) &= 1) == 1) 
		{
			start();
			*(Key_ptr) &= 0x0;
		}
		else if ((*(Key_ptr) &= 2) == 1)
		{
			stop();
			*(Key_ptr) &= 0x0;
		}
		else if ((*(Key_ptr) &= 4) == 1)
		{
			reset();
			*(Key_ptr) &= 0x0;
		}
		else
		{
			
		}
	}
}
