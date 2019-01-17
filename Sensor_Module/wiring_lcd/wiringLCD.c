#include <wiringPi.h>
#include <lcd.h>
#include <stdio.h>

#define LCD_RS 25	// 실제로 GPIO 26
#define LCD_E 24	// 실제로 GPIO 19
#define LCD_D4 23	// 실제로 GPIO 13
#define LCD_D5 22	// 실제로 GPIO 6
#define LCD_D6 21	// 실제로 GPIO 5 
#define LCD_D7 26	// 실제로 GPIO 12

int main(void){

	int lcd;
	wiringPiSetup();

	if(lcd = lcdInit(2,16,4,LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7,0,0,0,0)){
		printf("lcd init failed! \n");
		return -1;
	}

	lcdPosition(lcd,0,0);
	lcdPuts(lcd, "I LOVE YoonSun!!");
	lcdPosition(lcd,8,1);
	lcdPuts(lcd, "D-279");
	getchar();
}
