/* 
				YASM - Yet Another State Machine library

Lightweight library for creating function pointer based state machines

Copyright 2016/2017 bricofoy bricofoy@free.fr


Library provide basic functions for managing state machine execution
and state running timings and counts, and it is intended to be very 
easy to use.

Please see examples and README for documentation.



This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA */

#define YASM_VERSION "1.0.1"

#ifndef YASM_h
#define YASM_h
#include "Arduino.h"
class YASM{
	public:
		YASM(){_pState=YASM::nop;};
		void next(void (*pnextsate)(), bool reset=false);
		bool run();
		void stop();
		void resume(){YASM::_pState=YASM::_pLastState;};
		unsigned long timeOnState(){return (millis()-YASM::_enterTime);};
		bool elapsed(unsigned long durationms);
		bool periodic(unsigned long durationms, bool first=true);
		bool isFirstRun(){return YASM::_isFirstRun;};
		unsigned int runCount(){return YASM::_runCount;};
        	bool isInState(void (*pstate)()){return pstate==YASM::_pState;};
	private:
		void (*_pState)();
		void (*_pLastState)();
		unsigned long _enterTime;	
		unsigned long _lastTime;
		double _runCount;
		static void nop(){};
		bool _isFirstRun;
};
#endif
