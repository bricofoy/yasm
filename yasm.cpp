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

#include "yasm.h"

// YASM::YASM()
// {
//     _stateInfos.isStopped = true;
//     //we set the pointers to something just in case resume() is called before next()
//     _pState=_pLastState=nop;
// }

void YASM::next(void (*pnextstate)(), bool reset/*=false*/)
{
	if ((!reset) && (pnextstate == _pState)) return; //we do nothing if we stay in the same state

	//we change the state so we set the associated flag as needed
	_stateInfos.needReset = true; 
	
	//and enventually change exec pointer to the next state
	_pState = pnextstate; 
}

bool YASM::run()
{
	if(_stateInfos.isStopped) return false; //check if the machine is currently stopped
										//and just return false if this is the case

    //now machine is running
	
	//if state change flag is true, we are in the first pass in the current state (either 
	//it is a real state change or a restart of the previous state), so we set the
	//associated values as needed
	if(_stateInfos.needReset) {
        _stateInfos.needReset=false;
        _stateInfos.isFirstRun=true;
        _lastTime = _enterTime = millis();
        _runCount = 0;
    }

    //and run the machine
	_pLastState=_pState; //store the current state
	_pState(); //run the current state
		
	//if pState is the same now than before running it means we did not got state 
	//change request during _pState() execution so next time we again will run the 
	//same state, so we clear the first run flag and increment runs counter.
    //if stop flag is set, this means running state called itself stop() so
    //we also need to clear the flag and increment runs counter to get things right
    //in case resume() is called.
    if (_pState==_pLastState || _stateInfos.isStopped) {
		_stateInfos.isFirstRun = false; 
		_runCount++; 
	}
	return true; //and eventually report machine was running this time
}

bool YASM::elapsed(unsigned long durationms)
{
	if (YASM::timeOnState()>durationms) return true;
	return false;
}

bool YASM::periodic(unsigned long durationms, bool first/*=true*/)
{
	unsigned long time = (millis()-_lastTime);
	if( time >= durationms ) {
		_lastTime += time;
		return true;
	}
	if(first) return _stateInfos.isFirstRun;
	return false;
}

		
		
		
