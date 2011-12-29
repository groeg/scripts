#include <sysinit.h>

#include "basic/basic.h"

#include "lcd/render.h"
#include "lcd/backlight.h"
#include "lcd/allfonts.h"
#include "basic/simpletime.h"

#define BTN_NONE 0
#define BTN_UP   (1<<0)
#define BTN_DOWN (1<<1)
#define BTN_LEFT (1<<2)
#define BTN_RIGHT (1<<3)
#define BTN_ENTER (1<<4)

// Definitionen der Methoden
// void decBacklight(void);
void getVoltage(void);
void gotoISP(void);
int calculateLoadLevel();
void turnOnLight(void);
void blinken(void);

// drawing lines hLine, vLine
void hLine(int y, int x1, int x2, bool pixel);
void vLine(int x, int y1, int y2, bool pixel);

/**************************************************************************/
static const struct MENU mainmenu = {"Mainmenu", {
 {"Invoke ISP", &gotoISP}, 
 {"Check Voltage", &getVoltage},
 {"TurnOnLight", &turnOnLight},
 {"BlinkenLight", &blinken},
 {NULL, NULL},
}};

int posleds = 0;

void main_start(void) {

  backlightInit();
	// Helligkeit auf n% stellen.
	backlightSetBrightness(50);

    while (1) {
 				backlightSetBrightness(50); 			
				lcdDisplay();
        delayms(10);

        lcdFill(0); // clear display buffer
        DoString(0, 0, "Menue");

        if (getInput() == BTN_ENTER) {
            handleMenu(&mainmenu);
        }
    }
    return;
}

void blinken(void) {
	int i = 1;

	while (getInput() != BTN_ENTER) {
		gpioSetValue(RB_LED0,i%2);
		i++;
		gpioSetValue(RB_LED2,i%2);
		delayms(100);
	}

	gpioSetValue(RB_LED0,0);
	gpioSetValue(RB_LED2,0);
	handleMenu(&mainmenu);

}

void turnOnLight(void) {

	if(posleds != 1) {	
		gpioSetValue(RB_LED1, 1);		
		posleds = 1;
	} else {
		gpioSetValue(RB_LED1, 0);
		posleds = 0;
	}
	
	if (getInput() == BTN_ENTER) {
		handleMenu(&mainmenu);
	}
}

void getVoltage (void) {
	int v, mv;

	do {
		mv = GetVoltage();
		v = mv/1000;
		lcdFill(0);
	
		DoString(0,0, "Battery Status");
		// Draw the frame
		hLine(16, 14, 74, true);
		hLine(51, 14, 74, true);
		vLine(14, 16, 51, true);
		vLine(74, 16, 24, true);
    vLine(74, 43, 51, true);
    hLine(24, 74, 82, true);
    hLine(43, 74, 82, true);
    vLine(82, 24, 43, true);
	
		for (int i=16; i<=calculateLoadLevel(); ++i) {
			if(i%8 != 0) vLine(i, 18, 49, true);
		}
		
		lcdDisplay();
	} while (getInput() != BTN_ENTER);

	handleMenu(&mainmenu);

}

void gotoISP(void) {
	DoString(0,58,"Enter ISP!");
	lcdDisplay();
	EnableWatchdog(5000);
	ReinvokeISP();
}

void hLine(int y, int x1, int x2, bool pixel) {
	for (int i=x1; i<=x2; ++i) {
		lcdSetPixel(i,y,pixel);
	}
}

void vLine(int x, int y1, int y2, bool pixel) {
	for (int i=y1;i<=y2; ++i) {
		lcdSetPixel(x,i,pixel);
	}
}

int calculateLoadLevel() {
  int mw = GetVoltage() - 3550;
  mw = mw >> 6;
  mw = mw * 3;
  return mw + 16;
}
