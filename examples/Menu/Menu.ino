 
/* 
   Menu.ino example file for yasm library.
   
   The purpose of this arduino sketch is to create a basic menu on 16*2 LCD display
   It uses the Arduino provided LiquidCrystal library to drive the LCD
   It uses 3 buttons (+, -, Enter) to navigate the menu
   
   The circuit:
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
      
    * button + switch between Gnd and digital pin 6
    * button - switch between Gnd and digital pin 7
    * button Enter switch between Gnd and digital pin 8
    
    
   
   
*/



#include <yasm.h>	        //include the yasm library
#include <LiquidCrystal.h>  //include the LCD library

//define the pins we use to connect the LCD and the buttons
#define LCD_RS  12
#define LCD_EN  11
#define LCD_D4  5
#define LCD_D5  4
#define LCD_D6  3
#define LCD_D7  2

#define BTN_PLUS    6
#define BTN_MINUS   7
#define BTN_ENTER   8

// initialize the LCD library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

YASM menu;      //declaration of the "menu" state machine

BTN btnPlus;    //declaration of the 3 buttons
BTN btnMinus;
BTN btnEnter;




void setup()
{
    //set up the pins for buttons input
    //we activate the internal input pullup resistor so we
    //don't need any additional component
    pinMode(PIN_SW,INPUT_PULLUP);
    pinMode(PIN_SW,INPUT_PULLUP);
    pinMode(PIN_SW,INPUT_PULLUP);
    
    
    lcd.begin(16, 2);     //set up the LCD's number of columns and rows
    
	menu.next(menuStart); //set the initial state of the menu state machine
}

void loop()
{
	//update the buttons status
    //we use "!" because btn switch to gnd so it is active LOW, but the library
    //needs an active HIGH input, thus we need to invert the value we just read
    btnPlus.update(!digitalRead(PIN_BTN_PLUS)); 
    btnMinus.update(!digitalRead(PIN_BTN_MINUS));
    btnEnter.update(!digitalRead(PIN_BTN_ENTER));
    
    //then update the state machine    
    menu.run();
}

//////////menu state machine/////////////

void menuStart()
{
 	if(menu.isFirstRun()) {
		lcd.clear();
		lcd.print("Appuyez pour rechercher sonde ");
		lcd.print(numSonde);
		lcd.print("/");
		lcd.print(NBR_SONDE);
	}
	if(btnEnter.state(BTN_CLICK)) {
		menu.next(menu_recherche);
		lcd.clear();
	}	
	if(btn.state(BTN_LONGCLICK)) {
		menu.next(menu_affiche);
		numSonde=1;
		//lcd.clear();
	}
	if(numSonde>NBR_SONDE) menu.next(menu_fin);
}   

BTN_MINUSjyg
