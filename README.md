# yasm
Yet Another State Machine library - a function pointer based state machine library for arduino

A library for creating and managing states machines based on function pointers.

***********  Quick start : ***********************

First you need to create the state machine object with :
YASM MyMachine;

Then create the states you need. Each state must be a separate function of type "void" with no parameter :
void State1()
{
  do_something;  
  if (need_trigger_state_change)  MyMachine.next(State2);
}

Then initialise the machine telling it wich one is the initial state :
void setup() {
  MyMachine.next(Sate1);
}

Then call repeatedly the update function from your main loop :
void loop() {
  MyMachine.run();
}

Most important thing to remind is the state functions should be non-blocking so the whole system remains responsive no matter
how complex the task is. So you may avoid using while or delay() or anything that may keep the processor busy for a long time.
If you need a delay before doing something when entering a state, instead of delay() use the provided timing functions.
For example if you need a 3 seconds delay when you enter State3, use elapsed(delay) function :
void State3()
{
  do_something_imediately;
  if (elapsed(3E3)) do_something_only_after_a_3s_delay;
}


***********  Complete tour : ***********************
The YASM class provide the following control and timing functions and datas :
class YASM{
	public:
		YASM(){pState=YASM::nop;};
		void next(void (*)() );
		boolean run();
		void stop();
		void resume();
		unsigned long timeOnState();
		boolean elapsed(unsigned long);
		boolean periodic(unsigned long);
		boolean isFirstRun;
    
YASM() is class constructor, called when creating you state machine object :
YASM MyMachine;

void next(void (*nextstateptr)() ) is the function to call when requesting a state change or when giving the initial state 
to te machine :
MyMachine.next(StateX);

boolean run() is the update function. You need to constantly call this function to keep the machine running. Each time the 
function is called the current state function is launched. It returns true if the machine is actually running or false if it
is stopped (or not initialized).

void stop() stops the machine. This function can be called at any moment, even from inside the current running state. It
causes the machine to stop so any further call to run() will do nothing. It also records what the current state was so it
can be resumed by :

void resume() resume the machine execcution to the last used state. A stopped machine can also be restarted using next(state)
to restart from another state.

unsigned long timeOnState() returns the time in milliseconds spent in the current state since the last state change.

boolean elapsed(timeout) returns true if the timeout (in ms) is elapsed since last state change. It is very convenient to 
implement  



