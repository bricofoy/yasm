#include "btn.h"
//static(global) pointer on BTN object, updated by the update() method wich is not 
//static to the current used BTN object when calling it. 
//So through it static member functions can still acces non-static variables 
//corresponding to the right BTN object if more than one are in use.
static BTN* BTN::_this;

/////////////acces methods//////////////////////

void BTN::update(bool input)
{
	_input=input;
	_this=this;
	_SM.run();
}

bool BTN::state(byte state)
{
	if(state==_state)
	{
		_state=BTN_OFF;
		return true;
	}
	return false;
}

byte BTN::state()
{
	byte ret=_state;
	_state=BTN_OFF;
	return ret;
}

/////////////button state machine///////////////

void BTN::btn_wait()
{
	if(BTN::_this->_SM.elapsed(50)) if(BTN::_this->_input) BTN::_this->_SM.next(BTN::btn_debounce);
}

void BTN::btn_debounce()
{
	if(!BTN::_this->_input) BTN::_this->_SM.next(BTN::btn_wait);
	if(BTN::_this->_SM.elapsed(BTN_D_DEBOUNCE)) BTN::_this->_SM.next(BTN::btn_check);
}

void BTN::btn_check()
{
	if(BTN::_this->_SM.elapsed(BTN_D_LONGCLICK)) { 
		BTN::_this->_SM.next(BTN::btn_longclick); 
		BTN::_this->_state = BTN_LONGCLICK;
		return;
	}
	if(!BTN::_this->_input) {
		BTN::_this->_SM.next(BTN::btn_checkdouble);
	}
}

void BTN::btn_checkdouble()
{
	if(BTN::_this->_SM.elapsed(BTN_D_DOUBLECLICK)) { 
		BTN::_this->_SM.next(BTN::btn_wait); 
		BTN::_this->_state = BTN_CLICK;
		return;
	}
	if(BTN::_this->_input) {
		BTN::_this->_SM.next(BTN::btn_doubleclick);
		BTN::_this->_state = BTN_DOUBLECLICK;
	}
}

void BTN::btn_doubleclick()
{
	if(!BTN::_this->_input) BTN::_this->_SM.next(BTN::btn_wait);
}

void BTN::btn_longclick()
{
	if(!BTN::_this->_input) BTN::_this->_SM.next(BTN::btn_wait);
}