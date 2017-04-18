#ifndef BTN_h
#define BTN_h
#include <Arduino.h>
#include <yasm.h>

//button possible states
#define BTN_OFF			0
//#define BTN_ON			1
#define BTN_CLICK		2
#define BTN_LONGCLICK	4
#define BTN_DOUBLECLICK	8

//delays (ms)
#define BTN_D_DEBOUNCE		5
#define BTN_D_LONGCLICK		700
#define BTN_D_DOUBLECLICK	100

class BTN{
	public:
		BTN(){_SM.next(BTN::btn_wait);};
		void update(bool);
		bool state(byte);
	private:
		YASM _SM;
		bool _input;
		byte _state=BTN_OFF;
		static BTN* _this;
		static void btn_wait();
		static void btn_debounce();
		static void btn_check();
		static void btn_checkdouble();
		static void btn_longclick();
		static void btn_doubleclick();
};
#endif