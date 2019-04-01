#include "address_map_arm.h"
#include <stdio.h>
#include <stdlib.h>

volatile int * Hex_ptr = (int*)HEX3_HEX0_BASE;
volatile int * GPIO = (int*)HPS_GPIO0_BASE;

int createWaterData()
{
	int a;
	time_t t;
	while (1)
	{
		srand((unsigned)time(&t));
		for (int i = 0; i; i++)
		{
			a = rand() % 255;
			return a;
		}
	}
}




void main()
{
	*(GPIO) |= 1UL << 14;



	while (1)
	{
		int val = createWaterData();
		
		if (val <= 50)
		{
			*(Hex_ptr) = 0x383F;
		}
		else
		{
			*(Hex_ptr) = 0x7D3F;
		}

	}

}
