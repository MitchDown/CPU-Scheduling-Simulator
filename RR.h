#include "Scheduler.h"

//Header file for the "Round Robin" algorithm

class RR: public Scheduler
{
	private:
		int timeQuantum;
		int currentQuantum;
	public:
		RR(int quantum);
		void Simulate();
};