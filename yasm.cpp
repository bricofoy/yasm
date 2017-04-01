#include "yasm.h"

void YASM::next(void (*pnextstate)())
{
	if (pnextstate == _pState) return; //we do nothing if we stay in the same state

	//we change the state so we set the associated values as needed
	_isFirstRun = true; 
	_lastTime = _enterTime = millis();
	_runCount = 0;
	
	//and enventually change exec pointer to the next state
	_pState = pnextstate; 
}

bool YASM::run()
{
	if(_pState==YASM::nop) return false; //check if the machine is currently stopped
										//and just return false if this is the case
	//now machine is running
	_pLastState=_pState; //store the current state
	_pState(); //run the current state
		
	//if pState is the same now than before running it means we did not got state 
	//change request during _pState() execution so next time we again will run the 
	//same state, so we clear the flag and increment runs counter
	if (_pState==_pLastState) {
		_isFirstRun = false; 
		_runCount++; 
	}
	return true; //and eventually report machine was running this time
}

void YASM::stop()
{
	//Same check done at the end of run() for the case when a 
	//state just run once and calls itself for stop().
	//Without doing so here _isFirstRun and _runCount are not updated prior to 
	//stop the machine, and this leads to wrong values used on resume()
	if (_pState==_pLastState) {
		_isFirstRun = false; 
		_runCount++; 
	}
	//Then stop the machine
	_pState = YASM::nop;
}

bool YASM::elapsed(unsigned long durationms)
{
	if (YASM::timeOnState()>durationms) return true;
	return false;
}

bool YASM::periodic(unsigned long durationms)
{
	unsigned long time = (millis()-_lastTime);
	if( time >= durationms ) 
	{
		_lastTime += time;
		return true;
	}
	return false;
}

		
		
		
