
/* 
 *   Menu.ino example file for yasm library.
 *   
 *   The purpose of this arduino sketch is to create a basic menu on 16*2 LCD display
 *   It uses the Arduino provided LiquidCrystal library to drive the LCD
 *   It uses 3 buttons (+, -, Enter) to navigate the menu
 *   
 *   The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K potentiometer:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 *      
 * button + switch between Gnd and digital pin 6
 * button - switch between Gnd and digital pin 7
 * button Enter switch between Gnd and digital pin 8
 *    
 * led anode on pin 13, 1k resistor between cathode and gnd
 *      (most arduino boards already include this circuit)
 *    
 *   
 *   
 */



#include <yasm.h>			//include the yasm library
#include <btn.h>			//include the  button input yasm add-on

#include <LiquidCrystal.h>	//include the LCD driver library

//define the pins we use to connect the LCD,led and buttons

//pins for LCD
#define LCD_RS	8
#define LCD_EN	9
#define LCD_D4	4
#define LCD_D5	5
#define LCD_D6	6
#define LCD_D7	7

//pin for the led. we use pin 13 because most arduino boards have a builtin led on this one
#define PIN_LED	13 

// initialize the LCD library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

//declaration of the state machines
YASM menu, led;

//declaration of the 3 button input helpers
BTN btnPlus, btnMinus, btnEnter;

//declaratin of some variables we need to control the led
int onTime = 500;
int offTime = 500;
bool isBlinking = true;


#define btnRIGHT  1
#define btnUP     2
#define btnDOWN   3
#define btnLEFT   4
#define btnSELECT 5
#define btnNONE   0

// read the buttons
int readButtons()
{
	int btnInput = analogRead(A0); // read the value from the analog input
	// my buttons when read give these values : 0, 131, 305, 479, 720
	// we add approx 50 to those values and check to see if we are close
	// you may need to adjust the thresholds to what your shield needs
	if (btnInput > 1000) return btnNONE; //we check this 1st for speed reasons since it will be the most likely result
	if (btnInput < 50)   return btnRIGHT;  
	if (btnInput < 280)  return btnUP; 
	if (btnInput < 350)  return btnDOWN; 
	if (btnInput < 530)  return btnLEFT; 
	if (btnInput < 770)  return btnSELECT;  
	
	return btnNONE;  // when all others fail, return this...
}


void setup()
{
	/*//set up the pins for buttons input
	//we activate the internal input pullup resistor so we
	//don't need any additional component
	pinMode(PIN_BTN_PLUS,INPUT_PULLUP);
	pinMode(PIN_BTN_MINUS,INPUT_PULLUP);
	pinMode(PIN_BTN_ENTER,INPUT_PULLUP);*/
	
	//set up the pin for led output
	pinMode(PIN_LED,OUTPUT);
	
	lcd.begin(16, 2);     //set up the LCD's number of columns and rows
	
	menu.next(menu_start); //set the initial state of the menu state machine
}

void loop()
{
	//read the buttons status
	int _readbtn=readButtons();
	
	//update the buttons helpers
	btnEnter.update(_readbtn==btnSELECT);
	btnPlus.update(_readbtn==btnUP);
	btnMinus.update(_readbtn==btnDOWN);
	
	//update the state machine    
	menu.run();
	led.run();
}

//////////menu state machine/////////////

void menu_start()
{
	if(menu.isFirstRun()) {
		lcd.clear();
		lcd.print(F(" YASM Menu demo"));
		lcd.setCursor(1,2);
		lcd.print(F("press enter"));
	}
	
	if(btnEnter.state(BTN_CLICK)) {
		menu.next(menu_select);
		lcd.clear();
	}
}   

void menu_select()
{
	if(menu.isFirstRun()) {
		lcd.clear();
		lcd.print(F(" Blink "));
	}
	
	if(btnEnter.state(BTN_CLICK)) {
		//menu.next(menu_choose);
		lcd.clear();
	}
	
	if(btnEnter.state(BTN_LONGCLICK)) {
		menu.next(menu_start);
	}	
} 


