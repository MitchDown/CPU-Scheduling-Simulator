#include "Scheduler.h"

//Header file for the "Shortest Remaining Time First" algorithm

class SRTF: public Scheduler
{
	private:
		priority_queue<PCB> priorityReadyQueue;
	public:
		SRTF();
		void CheckForNewProcess();
		void Simulate();
		void ContextSwitch();
};