#include "address_map_arm.h"
#include <stdio.h>
#include <stdlib.h>

volatile int * Hex_ptr = (int*)HEX3_HEX0_BASE;


void createWaterData()
{
	char waterData[255];
	for (int i = 0; i <= 255; i++)
	{
		waterData[i] = i;
	}
}




void main()
{

}