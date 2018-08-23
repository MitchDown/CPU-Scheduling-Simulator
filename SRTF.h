#include "Scheduler.h"

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