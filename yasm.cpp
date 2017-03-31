#include "yasm.h"

void YASM::next(void (*pnextstate)())
{
	if (pnextstate == pState) return; //we do nothing if we stay in the same state

	//we change the state so we set the associated values as needed
	isFirstRun = true; 
	lastTime = enterTime = millis();
	runCount = 0;
	
	//and enventually change exec pointer to the next state
	pState = pnextstate; 
}

boolean YASM::run()
{
	if(pState==YASM::nop) return false; //check if the machine is currently stopped
										//and just return false if this is the case
	//now machine is running
	pLastState=pState; //store the current state
	pState(); //run the current state
		
	//if pState is the same now than before running it means we did not got state 
	//change request during pState() execution so next time we again will run the 
	//same state, so we clear the flag and increment runs counter
	if (pState==pLastState) {
		isFirstRun = false; 
		runCount++; 
	}
	return true; //and eventually report machine was running this time
}

void YASM::stop()
{
	//Same check done at the end of run() for the case when a 
	//state just run once and calls itself for stop().
	//Without doing so here isFirstRun and runCount are not updated prior to 
	//stop the machine, and this leads to wrong values used on resume()
	if (pState==pLastState) {
		isFirstRun = false; 
		runCount++; 
	}
	//Then stop the machine
	pState = YASM::nop;
}

void YASM::resume()
{
	pState = pLastState;
}

unsigned long YASM::timeOnState()
{
	return (millis() - enterTime);
}

boolean YASM::elapsed(unsigned long durationms)
{
	if (YASM::timeOnState()>durationms) return true;
	return false;
}

boolean YASM::periodic(unsigned long durationms)
{
	unsigned long time = (millis()-lastTime);
	if( time >= durationms ) 
	{
		lastTime += time;
		return true;
	}
	return false;
}

		
		
		
