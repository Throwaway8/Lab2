#include <time.h>

volatile int *buttons = (int*)KEY_BASE;
volatile int *timer_ptr = (int *)HPS_TIMER0_BASE;
int running = 0;
volatile int DELAY_LENGTH = 700000;
volatile unsigned char * Hex_ptr = (unsigned char*)HEX3_HEX0_BASE;
volatile unsigned char * Hex_ptr2 = (unsigned char*)HEX3_HEX0_BASE + 1;
volatile unsigned char * Hex_ptr3 = (unsigned char*)HEX3_HEX0_BASE + 2;
volatile unsigned int * Hex_ptr4 = (unsigned int*)HEX5_HEX4_BASE;
volatile unsigned char* led = (unsigned int*)LED_BASE;

#define GPIOA ((GPIO_TypeDef *) 0x48000000))
#define GPIOB ((GPIO_TypeDef *) 0x48000400))
#define RCC ((RCC_TypeDef *) 0x40021000))
#define RCC_AHB1ENR_GPIOAEN (0x00000002))
#define RCC_AHB1ENR_GPIOBEN (0x00000002))

void GPIO_Clock_Enable()
{
	RCC->AHB1ENR_GPIOAEN |= RCC_AHB1ENR_GPIOAEN; 
	RCC->AHB2ENR_GPIOBEN |= RCC_AHB1ENR_GPIOBEN;
}

void GPIO_Init()
{
	// set GPIO A and B as digital input
	GPIOA->MODER &= ~(3UL << 4);
	GPIOB->MODER &= ~(3UL << 4);

	// open drain set
	GPIOA->OTYPER &= ~(1 << 2);
	GPIOB->OTYPER &= ~(1 << 2);

	//set data speed
	GPIOA->OSPEEDR &= ~(3UL << 4);
	GPIOB->OSPEEDR &= ~(3UL << 4);

	// set pins as no pull up or pull down
	GPIOA->PUPDR &= ~(3UL << 4);
	GPIOB->PUPDR &= ~(3UL << 4);

}


void config_HPS_timer()
{
	// register and load value
	*(timer_ptr + 2) &= 0x000;
	int counter = 0b1000000;
	*(timer_ptr) = counter;
	*(timer_ptr + 2) = 0b011;
}

int RandSensor() {
	// create random values within sensor data range to sim 
	time_t t;
	srand((unsigned)time(&t));

	return rand() % 255;

}

void ReadTemp() {

	// read sim sensor and display value
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
	int i = 0;
	int RH = RandSensor();

	int dig0 = RH % 10;
	int dig1 = (RH / 10) % 10;
	int dig2 = (RH / 100) % 10;

	*(Hex_ptr) = lookUpTable[dig0];
	*(Hex_ptr + 1) = lookUpTable[dig1];
	*(Hex_ptr + 2) = lookUpTable[dig2];
}


void LEDhumid()
{
	// read sim data and display level of humidity on LEDs
	int RH = RandSensor();
	if (RH < 10) {
		*led = 0x00;
	}
	else if (RH >= 10 && RH < 19) {
		*led = 0x01;
	}
	else if (RH >= 19 && RH < 39) {
		*led = 0x03;
	}
	else if (RH >= 39 && RH < 59) {
		*led = 0x07;
	}
	else if (RH >= 59 && RH < 79) {
		*led = 0x0F;
	}
	else if (RH >= 79 && RH < 99) {
		*led = 0x1F;
	}
	else if (RH >= 99 && RH < 119) {
		*led = 0x3F;
	}
	else if (RH >= 119 && RH < 139) {
		*led = 0x7F;
	}
	else if (RH >= 139 && RH < 159) {
		*led = 0xFF;
	}
	else if (RH >= 159) {
		*led = 0x1FF;
	}
}

void readWater()
{
	// read sim data and display message on HEX 
	int val = RandSensor();
	if (val <= 10)
	{
		*(Hex_ptr4) = 0x383F;
	}
	else
	{
		*(Hex_ptr4) = 0x7D3F;
	}
}


int main(void) {

	GPIO_Clock_Enable();
	GPIO_Init();

	int count = 0;
	
	*(timer_ptr + 2) = 0b000;
	*(timer_ptr + 2) = 0b011;

	while (1)
	{

		if (*buttons == 0b0001) { running = 1; } 
		while (running)
		{
			config_HPS_timer(); // read data on intervals using hps interrupt
			while (*(timer_ptr) == 0)
			{
				if ((*(timer_ptr) &= 0b1) == 1) {
					count++;
					if (count == 500) {

						count = 0;
					}
				}
			}
			readWater();
			ReadTemp();
			LEDhumid();
		}
	}
}
